#ifndef __ABSTRACT_SOCKET_H__
#define __ABSTRACT_SOCKET_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>


//#include <openssl/aes.h>



#include "MessageQueue.h"
//#include "auth.h"
//#include "openssl_aes.h"


#define SOCKET_MESSAGE_MAGIC (('S' << 24) | ('O' << 16) | ('C' << 8) | 'K')






class CAbstractSocket{
public:
	CAbstractSocket(int skfd,uint32_t nSendQueueSize,uint32_t nRecvBufSize,uint32_t nSendBufSize);
//	CAbstractSocket(int skfd,uint32_t nSendQueueSize,uint32_t nRecvBufSize,uint32_t nSendBufSize,void * pKey);

	virtual ~CAbstractSocket();
	int sendData(void * data,uint32_t nSize);
	int sendPkt(GMSG_t * pkt);
	int doWorkThreadRoutine();
	bool status();
	bool start();
	bool stop();	
	int skfd();
protected:
	virtual int doRecvData(void * data,uint32_t nSize);

	static void * WorkThreadFunc(void * args);
private:

	int  setBlockFd(int fd);
	int  setNoblockFd(int fd);
	int  sendPktData(GMSG_t * msg,int &resendCount);
	int  recvDataHandle();
private:
	CMessageQueue * m_pSendQueue;
	int 			m_nSocket;
	pthread_t 		m_nWorkThreadId;
	bool			m_bStatus;
	uint8_t *		m_pRecvBuf;
	uint32_t		m_nRecvBufSize;
	uint32_t		m_nRecvBufDataSize;
	uint8_t	*		m_pSendBuf;
	uint32_t		m_nSendBufSize;

	pthread_mutex_t	m_stSendLock;


//	void 	* 		m_pKey;
//	AES_CTX 		m_stEncryptAES;
//	AES_CTX 		m_stDecryptAES;
	
};





























#endif //__ABSTRACT_SOCKET_H__

