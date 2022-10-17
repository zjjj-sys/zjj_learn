#ifndef __CSHM_BUF_H__
#define __CSHM_BUF_H__

#include <stdint.h>
#include <list>
#include "MediaBuffer.h"
#include "CMetaData.h"

class CShmBuf{
public:
	CShmBuf(const char *ShmUserName,const char * ShmBufName,
		uint32_t ShmBufSize,MEDIA_MEM_TYPE type);
	virtual ~CShmBuf();
	int putFrameBlocked(void * buf,unsigned int size);
	int putFrame(void * buf,unsigned int size);
	int getFrame(void * buf,unsigned int size);
	int getFrame2(void * buf,unsigned int size);
	int putFrame(void * buf,unsigned int size,std::list<CMetaData *> & lMetaDataList,uint32_t nMaxBufSize);
	int getFrame(void * buf,unsigned int size,std::list<CMetaData *> & lMetaDataList);
	
	void clear();
	//productor...
	void clearProductorData();
	int putFrameBlocked2(void * buf,unsigned int size);

	// debug

	void PrintConsumerStatus();
	void PrintProductorStatus();
private:
	void * m_pShmCtx;
};


//g_pAudioMainConsumer       = new CShmBuf("RTSP_Main_",AI_SHM_NAME,AI_SHM_SIZE,MEDIA_MEM_CONSUMER);
//g_pMainStreamVideoConsumer = new CShmBuf("RTSP_",VENC_MAIN_MM_NAME,MAIN_STREAM_SHM_SIZE,MEDIA_MEM_CONSUMER);


#endif //__CSHM_BUF_H__


