#ifndef __CYKM_MSG_HANDLER_H__
#define __CYKM_MSG_HANDLER_H__



#include <iostream>
#include <string>
#include <list>
#include <mutex>

#include "IPCMsgDataType.h"
#include "MiscDataType.h"
#include "CLocalMsgEngine.h"
#include "commFunc.h"

using std::string;
using std::list;


typedef enum{
	enum_rna_status_green = 0,
	enum_rna_status_yellow = 1,
	enum_rna_status_red = 2,
	enum_rna_status_unknow = 3,
}ENUM_RNA_STATUS;


typedef struct{
	ENUM_RNA_STATUS enStatus;
	int hour; // just for rna green code...
}RNA_INFO;


class CYKMsgHandler
{
public:
	CYKMsgHandler();
	virtual ~CYKMsgHandler();

	int broadcastYKMParseResult(const std::string & result);
	void doReadQrCodeString(const std::string & qrCodeString);
	void playVoicePromptForRNAResult(const RNA_INFO & stRNAStatus);

public:
	int doUpgrade(void * data,uint32_t dataSize);
	int doWillReboot(void * data,uint32_t dataSize);
	int doRecvUpgradeBeforeDownloadMsg(void * data,uint32_t dataSize);
	int doRecvUpgradeBeforeWriteFlashMsg(void * data,uint32_t dataSize);
	int doReadQrCodeOrRfIdMsg(void * data,uint32_t dataSize);
private:
	int postMsg(uint32_t cmd,void * sendData,uint32_t sendDataSize);	
	int sendMsg(uint32_t cmd,void * sendData,uint32_t sendDataSize,
		void * recvBuf,uint32_t recvBufSize,
		uint32_t & resultSize,uint32_t timeout);
	void playVoicePrompt(uint32_t type);
	void doPlayVoicePromptForRNAGreenResult(const RNA_INFO & stRNAStatus);
	
private:	
	CMessageEngine * 	m_pMsgEngine;
	uint32_t			m_nTimeout;

AVOID_CLASS_COPY_ASSIGNMENT(CYKMsgHandler)
};











































#endif //__CYKM_MSG_HANDLER_H__


