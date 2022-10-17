#include "Curlt.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <exception> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CURL_COMMAND "curl -k --insecure --connect-timeout 10 -m 15 "
#define CURL_HEAD_CONTENT "-H \"Content-Type: application/json\" "
#define CURL_HEAD_KEY "-H \"dcqc-third-app-key: F32749C735274B388D51FDC6D134895D\" "
#define CURL_HEAD_CHANLE "-H \"dcqc-channel-type: 99\" "
#define CURL_HEAD_ID "-H \"dcqc-request-id: "
#define CURL_HEAD_PARAM "-H"
#define CURL_T "\" "
#define CURL_P "\""
#define CURL_POST "-X POST --data @/tmp/param.json "


extern bool g_bYKMAdapterStop;
extern CYKMsgHandler * g_pYKMsgHandler;

CURLT::CURLT():mode(GET),decode_sm4(new sm4())
{
    //curl_global_init(CURL_GLOBAL_ALL);
    Lasttime = std::chrono::high_resolution_clock::now();
    url = YKM_URL;
    decode_sm4->setKey(YKM_KEY);
    decode_sm4->setType();
    expiresIn = 0;
}

CURLT::~CURLT()
{
    delete decode_sm4;
    decode_sm4 = NULL;
}

int CURLT::URIselect(int mode, std::string &param, std::string msg="")
{
    int ret = 0;
    switch (mode)
    {
    case Access_token:
        param += "v1/ykm/third-api/access-token?";
        param += msg;
        break;
    case Verify_code:
        param += "v1/ykm/third-api/verify-code";
        break;
    default:
        std::cout << "The correct opting was not selected" << std::endl;
        ret = -1;
        break;
    }
    return ret;
}

std::string CURLT::Post_verify(const std::string &code)
{
    int nRet = 0;
    std::string handdle;
    std::string msg;
    std::string post_url(url);
    mode = POST;

    nRet = URIselect(mode, post_url);
    if (nRet != 0)
    {
        std::cout << " POST failed" << std::endl;
    }
    Json::Value item;
    item["code"] = code.c_str();
    item["accessToken"] = asToken;
    msg = item.toStyledString();

    handdle = POST_COMMAND(post_url,msg);
    if(handdle.empty())
    {
        DEBUG_WARN("get post_content is empty:\n");
        return "";
    }
    handdle = recv_handle_verify(handdle);

    return handdle;
}

bool CURLT::Get_token()
{
    int nRet = 0;
    std::string msg;
    std::string get_url(url);
    std::string get_content;
    mode = GET;
    bool flag;

    msg = APPSECRET;
    msg += GRANTTYPE;
    nRet = URIselect(mode, get_url, msg);
    DEBUG_INFO("get_url :%s\n",get_url.c_str());
    if (nRet != 0)
    {
        std::cout << " GET param failed" << std::endl;
    }
    get_content = GET_COMMAND(get_url);
    if(get_content.empty())
    {
        DEBUG_WARN("get_content is empty:\n");
        return false;
    }
    DEBUG_INFO("get_content:%s\n",get_content.c_str());
    flag = recv_handle_token(get_content);
    if(flag==false){
        DEBUG_INFO("GET asToken failed:\n");
    }
    return flag;
}

bool CURLT::recv_handle_token(std::string &content)
{

    Json::Value value;
    std::string tsexpiresIn;
    JSONCPP_STRING errs;
    Json::CharReaderBuilder readerBuilder;

    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());

    bool res = jsonReader->parse(content.c_str(), content.c_str()+content.length(), &value, &errs);

    if (!res || !errs.empty()) {
        DEBUG_WARN("parseJson err:%d \n" , errs );
        return false;
    }

    asToken = value["data"]["accessToken"].asString();
    if(asToken.empty())
    {
        DEBUG_WARN("Get asToken information is empty\n");
        return false;
    }
    tsexpiresIn = value["data"]["expiresIn"].asString();
    DEBUG_INFO("asToken:%s\n", asToken.c_str());
    DEBUG_INFO("tsexpiresIn:%s\n", tsexpiresIn.c_str());
    expiresIn = atoi(tsexpiresIn.c_str());
    
    return true;
}



std::string CURLT::recv_handle_verify(std::string &content)
{
    std::string verify_data;
    std::string userName;
    std::string certNo;
    std::string phone;
    std::string errhandle;

    Json::Value value;
    Json::Value root;
    Json::Value data;
    int code_type = 0;

    Json::StreamWriterBuilder writerBuilder;
    std::ostringstream os;

    JSONCPP_STRING errs;
    Json::CharReaderBuilder readerBuilder;

    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());

    bool res = jsonReader->parse(content.c_str(), content.c_str()+content.length(), &value, &errs);

    if (!res || !errs.empty()) {
        DEBUG_WARN("parseJson err:%d \n" , errs );
        return "";
    }
    try{

        code_type = value["code"].isNull();
        if(code_type==1)
        {
            DEBUG_WARN("code non-existent:");
            return "";
        }
        root["code"] = value["code"].asInt();
        if(10005==value["code"].asInt() || 10010 == value["code"].asInt())
        {
            
            DEBUG_WARN("asToken invalid:10005 or 10010\n");
            std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
            jsonWriter->write(root, &os);
            errhandle = os.str();
            return errhandle;
        }
        userName = value["data"]["userName"].asString();
        certNo = value["data"]["certNo"].asString();
        phone = value["data"]["phone"].asString();

        data["certType"] = value["data"]["certType"].asString();
        data["healthStatus"] = value["data"]["healthStatus"].asInt();
        int mode = value["data"]["healthStatus"].asInt();

        switch(mode)
        {
            case 1:
                asenStatus = enum_rna_status_green;
                break;
            case 2:
                asenStatus = enum_rna_status_yellow;
                break;
            case 3:
                asenStatus = enum_rna_status_red;
                break;
            case 99:
                asenStatus = enum_rna_status_unknow;
                break;
            default:
                asenStatus = enum_rna_status_unknow;
                break;
        }

        data["vaccinationStatus"] = value["data"]["vaccinationStatus"].asInt();
        data["vaccinationPlusStatus"] = value["data"]["vaccinationPlusStatus"].asInt();
        data["lastRNATime"] = value["data"]["lastRNATime"].asString();
        rna_hour = 0;
        data["lastRNAResult"] = value["data"]["lastRNAResult"].asInt();
        data["travelStatus"] = value["data"]["travelStatus"].asInt();
    
        root["msg"] = value["msg"].asString();
    }
    catch (std::exception& e)
    {
        DEBUG_ERROR("recv jsonstring exception %s:\n",e.what());
        return "";
    }

        
    decode_verify(userName, certNo , phone);
    
    data["userName"] = userName;
    data["certNo"] = certNo;
    data["phone"] = phone;

    root["data"] = data;

    std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &os);
    verify_data = os.str();
    DEBUG_INFO("recv verify_data :\n");
    return verify_data;
}


std::string CURLT::srand_str()
{
    char upper[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[27]="abcdefghijklmnopqrstuvwxyz";
    char number[11]="0123456789";
    char m[64] = {0}, s[10] = {0};
    srand(time(0));
    char x='0';
    int type;
    for (int i = 0; i < 32; i++)
    {
        
        type = rand() % 3;
        if (type == 0) //判断随机类型生成大小写或者字母
        {
            x = upper[rand() % 26];
        }
        else if (type == 1)
        {
            x = lower[rand() % 26];
        }
        else if (type == 2)
        {
            x = number[rand() % 10];
        }
        sprintf(s, "%c", x);
        strcat(m, s);
    }
    std::string str(m);
    return str;
}


void CURLT::decode_verify(std::string &userName , std::string &certNo , std::string &phone)
{
    
    char p[200]={0};
    Base64decode(p,userName.c_str());
    userName.clear();
    userName.assign(p);
    userName= decode_sm4->decrypt(userName);
    memset(p,0,sizeof(p));

    Base64decode(p,certNo.c_str());
    certNo.clear();
    certNo.assign(p);
    certNo =decode_sm4->decrypt(certNo);
    memset(p,0,sizeof(p));
    
    Base64decode(p,phone.c_str());
    phone.clear();
    phone.assign(p);
    phone =decode_sm4->decrypt(phone);
    memset(p,0,sizeof(p));

    DEBUG_INFO("userName:%s\n", userName.c_str());
    DEBUG_INFO("certNo:%s\n", certNo.c_str());
    DEBUG_INFO("phone:%s\n", phone.c_str());
    
}


void CURLT::Get_handle()
{
    bool flag;
    flag = Get_token();
    if(flag)
    {
        DEBUG_INFO("asexpiresIn:%d\n",expiresIn);
        Lasttime  = std::chrono::high_resolution_clock::now();
    }
    while(flag == false)
    {
        flag = Get_token();
        if(flag==true)
        {
            Lasttime  = std::chrono::high_resolution_clock::now();
        }else{
            DEBUG_WARN("Get asToken information is empty\n");
            usleep(300*1000);
        }
    }
}

void CURLT::run()
{
    std::string result;
    std::string qrstringcode;
    std::string errhandle;
    u_int8_t flag;
    RNA_INFO Rna_info;
    Json::Value value;
    JSONCPP_STRING errs;
    Json::CharReaderBuilder readerBuilder;

    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
    Get_handle();
    while(!g_bYKMAdapterStop)
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>( current_time - Lasttime);

        DEBUG_INFO("asexpiresIn:%d\n",expiresIn);
        DEBUG_INFO("asToken:%s\n", asToken.c_str());
        DEBUG_INFO("time_span:%lf\n",time_span.count());

        if(time_span.count() >= (expiresIn+3) ){
            Get_handle();
        }
        flag = pop_qrstring(qrstringcode);
        if(flag){
            result=Post_verify(qrstringcode);
            if(result.empty())
            {
                DEBUG_WARN("POST qrcode information is empty\n");
                usleep(300*1000);
                continue;
            }
            bool res = jsonReader->parse(result.c_str(), result.c_str()+result.length(), &value, &errs);
            if (!res || !errs.empty()) {
                DEBUG_ERROR("parseJson err. \n");
            }
            int type = value["code"].asInt();
            if(type == 10005 || type == 10010)
            {
                DEBUG_WARN("asToken Invalid need retrieve token:\n");
                Get_handle();
                continue;
            }
            DEBUG_INFO("result:%s\n",result.c_str());
            g_pYKMsgHandler->broadcastYKMParseResult(result);
            DEBUG_INFO("send result success:\n");
            Rna_info.enStatus = asenStatus;
            Rna_info.hour = rna_hour;
            g_pYKMsgHandler->playVoicePromptForRNAResult(Rna_info);
        }
        else{
            usleep(300*1000);
            continue;
        }
    }

}

bool CURLT::push_qrstring(std::string qrcodestring)
{
    std::lock_guard<std::mutex> lck(m_qrmutex);
    if(qrcodestring.empty()||m_qrstringlist.size()>=5)
    {
        return false;
    }
    m_qrstringlist.push_back(qrcodestring);
    return true;
}

bool CURLT::pop_qrstring(std::string &qrstring)
{
    std::lock_guard<std::mutex> lck(m_qrmutex);
    if(m_qrstringlist.empty())
    {
        return false;
    }
    qrstring = m_qrstringlist.front();
    DEBUG_INFO("qrstring :%s\n",qrstring.c_str());
    m_qrstringlist.pop_front();

    return true;
}


std::string CURLT::execute_command(std::string &command_str)
{
    std::string recv_content;
    size_t retbyte;
    FILE *fp;
    char buffer[1024] = {0};
    fp = popen(command_str.c_str(), "r");
    if(fp == NULL)
    {
        DEBUG_WARN("Call curl_command failed:\n");
        pclose(fp);
        return "";
    }
    retbyte =fread(buffer, 1, sizeof(buffer), fp);
    if(retbyte<=0)
    {
        DEBUG_WARN("read file failed:\n");
        pclose(fp);
        return "";
    }
    recv_content.assign(buffer,sizeof(buffer));
    pclose(fp);
    DEBUG_INFO("recv_content: %s\n",recv_content.c_str());
    return recv_content;
}

std::string CURLT::GET_COMMAND(std::string get_url)
{
    std::string cmd_msg;
    std::string get_content;
    std::string dcqc_id;

    dcqc_id += CURL_HEAD_ID;
    dcqc_id += srand_str();
    dcqc_id += CURL_T;
    cmd_msg += CURL_COMMAND;
    cmd_msg += CURL_HEAD_KEY;
    cmd_msg += CURL_HEAD_CONTENT;
    cmd_msg += CURL_HEAD_CHANLE;
    cmd_msg += dcqc_id;
    cmd_msg += CURL_P;
    cmd_msg+=get_url;
    cmd_msg += CURL_P;
    DEBUG_INFO("msg_cmd: %s\n",cmd_msg.c_str());

    get_content = execute_command(cmd_msg);
    return get_content;
}



std::string CURLT::POST_COMMAND(std::string post_url ,std::string &post_body)
{

    int fd;
    int ret = 0;
    std::string post_content;
    std::string cmd_msg;
    std::string dcqc_id;

    dcqc_id += CURL_HEAD_ID;
    dcqc_id += srand_str();
    dcqc_id += CURL_T;
    cmd_msg += CURL_COMMAND;
    cmd_msg += CURL_HEAD_KEY;
    cmd_msg += CURL_HEAD_CONTENT;
    cmd_msg += CURL_HEAD_CHANLE;
    cmd_msg += dcqc_id;
    cmd_msg +=CURL_POST;
    fd = open("/tmp/param.json",O_RDWR|O_CREAT|O_TRUNC,0664);
    if(fd < 0)
    {
        DEBUG_ERROR("open param.json failed\n");
        close(fd);
    }
    ret = write(fd,post_body.c_str(),post_body.size());
    if(ret <=0 )
    {
        DEBUG_WARN("write data param.json failed :");
    }
    close(fd);
    cmd_msg += CURL_P;
    cmd_msg+= post_url;
    cmd_msg += CURL_P;

    DEBUG_INFO("msg_cmd: %s\n",cmd_msg.c_str());

    post_content = execute_command(cmd_msg);
    
    return post_content;
}
