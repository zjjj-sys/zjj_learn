#include "commFunc.h"
#include "CProduct.h"
#include "CYKMsgHandler.h"
#include "array_size.h"
#include "Curlt.h"
extern CURLT* g_YKMcurlt;
extern bool g_bYKMAdapterStop;
extern CProduct * g_pProduct;

static int do_recv_will_reboot_msg(void * data,uint32_t dataSize,void * private_data)
{
	CYKMsgHandler * pThis = (CYKMsgHandler *)private_data;
	return pThis->doWillReboot(data ,dataSize);
}

static int do_recv_upgrade_msg(void * data,uint32_t dataSize,void * private_data)
{
	CYKMsgHandler * pThis = (CYKMsgHandler *)private_data;
	return pThis->doUpgrade(data ,dataSize);
}

static int do_recv_upgrade_before_download_msg(void * data,uint32_t dataSize,void * private_data)
{
	CYKMsgHandler * pThis = (CYKMsgHandler *)private_data;
	return pThis->doRecvUpgradeBeforeDownloadMsg(data ,dataSize);
}

static int do_recv_upgrade_before_write_flash_msg(void * data,uint32_t dataSize,void * private_data)
{
	CYKMsgHandler * pThis = (CYKMsgHandler *)private_data;
	return pThis->doRecvUpgradeBeforeWriteFlashMsg(data ,dataSize);
}

static int do_recv_read_qr_code_or_rf_id_msg(void * data,uint32_t dataSize,void * private_data)
{
	CYKMsgHandler * pThis = (CYKMsgHandler *)private_data;
	return pThis->doReadQrCodeOrRfIdMsg(data ,dataSize);
}

static MSG_HANDLE YKMAdapterMsgHdl[] = {
	{MSG_ID_BROADCAST_REBOOT			,	do_recv_will_reboot_msg},
	{MSG_ID_BROADCAST_UPGRADE,				do_recv_upgrade_msg},
	{MSG_ID_BROADCAST_UPGRADE_BEFORE_DOWNLOAD,				do_recv_upgrade_before_download_msg},
	{MSG_ID_BROADCAST_UPGRAGE_BEFORE_WRITE_FLASH,			do_recv_upgrade_before_write_flash_msg},
	{MSG_ID_BROADCAST_READ_QR_CODE_OR_RF_ID_INFO,			do_recv_read_qr_code_or_rf_id_msg},
};








CYKMsgHandler::CYKMsgHandler()
{
	DEBUG_INFO("[%s]\n",__FUNCTION__);
	int fd = CLocalMsgEngine::connectLocalMsgSvr();
	if(fd < 0){
		DEBUG_ERROR("Connect msg svr error,exit...\n");
		DEBUG_ERROR("Connect msg svr error,exit...\n");
		DEBUG_ERROR("Connect msg svr error,exit...\n");
		sleep(5);
		exit(-1);
	}


	m_nTimeout = 5000;


	string name = "YKM";
	m_pMsgEngine	= (CMessageEngine *)new CLocalMsgEngine(fd,this);
	m_pMsgEngine->regMsg(YKMAdapterMsgHdl,ARRAY_SIZE(YKMAdapterMsgHdl),name);

}
CYKMsgHandler:: ~CYKMsgHandler()
{
	DEBUG_INFO("[%s]\n",__FUNCTION__);
	if(m_pMsgEngine){
		delete m_pMsgEngine;
		m_pMsgEngine = NULL;
	}

}

int CYKMsgHandler::postMsg(uint32_t cmd,void * sendData,uint32_t sendDataSize)
{

	if(NULL == m_pMsgEngine){
		DEBUG_ERROR("m_pMsgEngine is null\n");
		return MSG_ERROR(MSG_ERROR_CONNECT_NOT_EXIST);
	}
	int ret = m_pMsgEngine->sendMsg(cmd,sendData,sendDataSize);
	if(-1 == ret){
		DEBUG_ERROR("Send msg error\n");
		return MSG_ERROR(MSG_ERROR_SEND_MSG_ERROR);
	}
	return 0;
}

int CYKMsgHandler::sendMsg(uint32_t cmd,void * sendData,uint32_t sendDataSize,
	void * recvBuf,uint32_t recvBufSize,
	uint32_t & resultSize,uint32_t timeout)
{
	uint64_t start = COMM_FUNC::getStartTimeMs();

	if(NULL == m_pMsgEngine){
		DEBUG_ERROR("m_pMsgEngine is null\n");
		return MSG_ERROR(MSG_ERROR_CONNECT_NOT_EXIST);
	}
	int ret = m_pMsgEngine->sendMsg(cmd,sendData,sendDataSize);
	if(-1 == ret){
		DEBUG_ERROR("Send msg error\n");
		return MSG_ERROR(MSG_ERROR_SEND_MSG_ERROR);
	}
	int token = ret;
	ret = m_pMsgEngine->recvMsg(token,recvBuf,recvBufSize,timeout);
	if(ret > 0){
		DEBUG_INFO("Msg:%08x cost %lldms...\n",cmd,COMM_FUNC::getStartTimeMs() - start);
		resultSize = ret;
		return MSG_ERROR(MSG_ERROR_NONE);
	}else{
		DEBUG_INFO("Recv timeout...\n");
		return MSG_ERROR(MSG_ERROR_TIMEOUT);
	}

}



int CYKMsgHandler::doUpgrade(void * data,uint32_t dataSize)
{
	DEBUG_INFO("[%s]\n",__FUNCTION__);

	g_bYKMAdapterStop = true;

	return 0;
}


int CYKMsgHandler::doWillReboot(void * data,uint32_t dataSize)
{
	DEBUG_INFO("[%s]\n",__FUNCTION__);

	g_bYKMAdapterStop = true;
	
	return 0;
}

int CYKMsgHandler::broadcastYKMParseResult(const std::string & result)
{
	if(result.empty()){
		DEBUG_WARN("YKM Parse result json string is empty!\n");
		return -1;
	}
	return postMsg(MSG_ID_BROADCAST_YKM_PARSE_RESULT_MSG, 
		(void *)(result.data()),result.size() + 1 /*Contain char '\0' */);
}






int CYKMsgHandler::doRecvUpgradeBeforeDownloadMsg(void * data,uint32_t dataSize)
{
	DEBUG_INFO("%s\n",__FUNCTION__);

	LOCAL_MSG_t * pMsg = (LOCAL_MSG_t *)data; 
	MSG_BROADCAST_UPGRADE_BEFORE_DOWNLOAD * pMsgParam = (MSG_BROADCAST_UPGRADE_BEFORE_DOWNLOAD *)(pMsg->Body);
	(void)pMsgParam;
	if(sizeof(MSG_BROADCAST_UPGRADE_BEFORE_DOWNLOAD) != pMsg->bodySize){
		DEBUG_ERROR("upgrade before download broadcast msg size invalid:%d != %d\n",
			pMsg->bodySize,sizeof(MSG_BROADCAST_UPGRADE_BEFORE_DOWNLOAD));
		return 0;
	}
	DEBUG_INFO("[UPGRADE before DOWNLOAD]:MqttAdapter exit\n");
	
	g_bYKMAdapterStop = true;

	return 0;
}


int CYKMsgHandler::doRecvUpgradeBeforeWriteFlashMsg(void * data,uint32_t dataSize)
{
	DEBUG_INFO("%s\n",__FUNCTION__);

	LOCAL_MSG_t * pMsg = (LOCAL_MSG_t *)data; 
	MSG_BROADCAST_UPGRADE_BEFORE_WRITE_FLASH * pMsgParam = (MSG_BROADCAST_UPGRADE_BEFORE_WRITE_FLASH *)(pMsg->Body);
	(void)pMsgParam;
	if(sizeof(MSG_BROADCAST_UPGRADE_BEFORE_WRITE_FLASH) != pMsg->bodySize){
		DEBUG_ERROR("upgrade before write flash broadcast msg size invalid:%d != %d\n",
			pMsg->bodySize,sizeof(MSG_BROADCAST_UPGRADE_BEFORE_WRITE_FLASH));
		return 0;
	}
	g_bYKMAdapterStop = true;

	return 0;
}



int CYKMsgHandler::doReadQrCodeOrRfIdMsg(void * data,uint32_t dataSize)
{
	DEBUG_INFO("%s\n",__FUNCTION__);

	LOCAL_MSG_t * pMsg = (LOCAL_MSG_t *)data; 
	MSG_BROADCAST_READ_QRCODE_OR_RFID_DATA * pstReq = (MSG_BROADCAST_READ_QRCODE_OR_RFID_DATA  *)pMsg->Body;
	if(sizeof(MSG_BROADCAST_READ_QRCODE_OR_RFID_DATA ) != pMsg->bodySize){
		DEBUG_WARN("doReadQrCodeOrRfIdMsg msg size invalid:%d != %d\n",
			pMsg->bodySize,sizeof(MSG_BROADCAST_READ_QRCODE_OR_RFID_DATA ));
		return -1;
	}
	if((enum_access_mode_qr_code == pstReq->enAccessMode) && STRING_ARRAY_CHECK(pstReq->qrCode)){
		DEBUG_INFO("Qr Code:%s\n",pstReq->qrCode);
		if(enum_qr_code_type_ykm != COMM_FUNC::qrCodeType(g_pProduct, pstReq->qrCode)){
			DEBUG_INFO("qr code {%s} is not YKM!\n",pstReq->qrCode);
			return 0;
		}
		doReadQrCodeString(pstReq->qrCode);
		return 0;
	}else if((enum_access_mode_rf_id == pstReq->enAccessMode) && STRING_ARRAY_CHECK(pstReq->rfId)){
		//DEBUG_INFO("Rf ID  :%s\n",pstReq->rfId);
		return 0;
	}else{
		DEBUG_ERROR("Invalid access mode : %d\n",pstReq->enAccessMode);
		return -1;
	}
}







void CYKMsgHandler::doReadQrCodeString(const std::string & qrCodeString)
{
	if(!qrCodeString.empty()){
		if(g_YKMcurlt){
			g_YKMcurlt->push_qrstring(qrCodeString);
		}
	}
}




void CYKMsgHandler::playVoicePrompt(uint32_t type)
{
	DEBUG_INFO("Send voice prompt req:%d\n",type);


	MSG_VOICE_PROMPT_PARAM msg;
	msg.voice_prompt_type = type;
	postMsg(MSG_ID_POST_VOICE_PORMPT_CMD,&msg,sizeof(msg));
}



void CYKMsgHandler::playVoicePromptForRNAResult(const RNA_INFO & stRNAStatus)
{
	switch(stRNAStatus.enStatus){
	case enum_rna_status_green:
		doPlayVoicePromptForRNAGreenResult(stRNAStatus);
		break;
	case enum_rna_status_yellow:
		playVoicePrompt(MEIAN_VOICE_PROMPT_RNA_YELLOW_CODE);
		break;
	case enum_rna_status_red:
		playVoicePrompt(MEIAN_VOICE_PROMPT_RNA_RED_CODE);
		break;
	case enum_rna_status_unknow:
		playVoicePrompt(MEIAN_VOICE_PROMPT_RNA_UNKONW);
		break;	
	default:
		DEBUG_ERROR("BUG IN HERE!!! Invalid RNA Status : %d\n",(int)stRNAStatus.enStatus);
		break;
	}


}

void CYKMsgHandler::doPlayVoicePromptForRNAGreenResult(const RNA_INFO & stRNAStatus)
{
	switch(stRNAStatus.hour){
	case 24:
		playVoicePrompt(MEIAN_VOICE_PROMPT_24H);
		break;
	case 48:
		playVoicePrompt(MEIAN_VOICE_PROMPT_48H);
		break;
	case 72:
		playVoicePrompt(MEIAN_VOICE_PROMPT_72H);
		break;
	default:
		break;
	}

	playVoicePrompt(MEIAN_VOICE_PROMPT_RNA_GREEN_CODE);
}



















