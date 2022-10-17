#ifndef CURLT_H
#define CURLT_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <mutex>
#include <chrono>
//#include "curl/curl.h"
#include "json/json.h"
#include "sm4.h"
#include "base64.h"
#include "CYKMsgHandler.h"

#define YKM_URL "https://ykm.bigdatacq.com/"
#define YKM_KEY "626541411D8A42AE"
#define CONTENT_TYPE "Content-Type: application/json"
#define APP_KEY    "dcqc-third-app-key: F32749C735274B388D51FDC6D134895D"
#define CHANLE_TYPE "dcqc-channel-type: 99"
#define APPSECRET "appSecret=626541411D8A42AE"
#define GRANTTYPE "&grantType=CLIENT_AUTH"

enum URI{
    Access_token = 0 ,
    Verify_code 
};

enum URL{
    GET = 0,
    POST
};

class CURLT
{

public:
    CURLT();
    ~CURLT();
    bool push_qrstring(std::string qrcodestring);
    bool pop_qrstring(std::string &m_qrstring);
    std::string Post_verify(const std::string &code);
    void Get_handle();
    
    void run();
private:

    
    int URIselect(int mode, std::string &param, std::string msg);
    bool Get_token();

    std::string GET_COMMAND(std::string get_url);
    std::string POST_COMMAND(std::string post_url ,std::string &post_body);

    std::string srand_str();
    std::string execute_command(std::string &command_str);

    void decode_verify(std::string &userName , std::string &certNo , std::string &phone);
    bool recv_handle_token(std::string &content);
    std::string recv_handle_verify(std::string &content);

private:
        std::string asToken;
        int expiresIn;
        u_int32_t mode;
        ENUM_RNA_STATUS asenStatus;
        int rna_hour;

        sm4* decode_sm4 ;
        std::string url;
        std::mutex m_qrmutex;
        std::list <std::string> m_qrstringlist;
        std::chrono::high_resolution_clock::time_point Lasttime;

};


#endif //CURLT_H
