#ifndef __BYTE_BUFFER_H__
#define __BYTE_BUFFER_H__

#include "common.h"
#include "commFunc.h"

class CByteBuffer{
public:
	explicit CByteBuffer(uint32_t size);
	virtual ~CByteBuffer();
	uint32_t dataSize();
	uint32_t freeSize();
	bool empty();
	bool full();
	void reset();
	uint32_t append(void * pData,uint32_t nDataSize);
	uint32_t ate(uint32_t size);
	uint8_t * data();

private:
	uint8_t * m_pBuffer;
	uint32_t  m_nBufferSize;
	uint32_t  m_nBufferDataSize;


AVOID_CLASS_COPY_ASSIGNMENT(CByteBuffer)
};



















#endif //__BYTE_BUFFER_H__

