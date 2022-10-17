#ifndef __MESSAGE_ENGINE_H__
#define	__MESSAGE_ENGINE_H__

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include <iostream>
#include <list>
#include <iostream>
#include <string>
#include <vector>



#include "common.h"
#include "IPCMsgDataType.h"
#include "AbstractSocket.h"


class CMessageEngine:public CAbstractSocket
{
public:
	CMessageEngine(int skfd);
	CMessageEngine(int skfd,void * pKey);
	CMessageEngine(int skfd,uint32_t nSendQueueSize,uint32_t nRecvBufSize,uint32_t nSendBufSize,void * pKey);

	virtual ~CMessageEngine();
	virtual void regMsg(MSG_HANDLE * msgHdl,uint32_t msgHdlSize,std::string & name);
	int sendMsg(uint32_t msgId,void * msgBody,uint32_t bodySize);
	int recvMsg(uint32_t token,void * buf,uint32_t bufSize,uint32_t timeout);
	int replyMsg(uint32_t msgId,void * msgBody,	uint32_t bodySize,uint32_t msgToken);
protected:
	virtual int doRecvData(void * data,uint32_t nSize);
	virtual bool isRespMsg(uint32_t respMsgId);
	int  RespMsgListAdd(LOCAL_MSG_t * pMsg);
	uint32_t genToken();
	int checkResp(uint32_t msgToken,void * respBuf,uint32_t respBufSize);

protected:
	pthread_mutex_t				m_stRespMsgListLock;
	std::list<LOCAL_MSG_t *> 	m_stRespMsgList;
	MSG_HANDLE * 				m_stMsgHdl;		//bug in here,msghander must be static
	uint32_t 					m_nMsgHdlSize;
	int 						m_nMsgToken;
};
















#endif //__MESSAGE_ENGINE_H__


