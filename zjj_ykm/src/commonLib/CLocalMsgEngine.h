#ifndef __CCODEC_MSG_ENGINE_H__
#define __CCODEC_MSG_ENGINE_H__



#include "MessageEngine.h"
#include "MiscDataType.h"



class CLocalMsgEngine : public CMessageEngine
{
public:
	CLocalMsgEngine(int sock,void * private_data);
	virtual ~CLocalMsgEngine();

	static int connectLocalMsgSvr();
	
protected:
	virtual int doRecvData(void * data,uint32_t nSize);


	
private:
	void * m_pPriData;
};




























#endif //__CCODEC_MSG_ENGINE_H__



