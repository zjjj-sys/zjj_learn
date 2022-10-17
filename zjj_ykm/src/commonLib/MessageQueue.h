#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__


#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <pthread.h>



#define GENERIC_MESSAGE_MAGIC (('M' << 24) | ('S' << 16) | ('G' << 8) | 'Q')





class CMessageQueue{
public:
	CMessageQueue(uint32_t size);
	virtual ~CMessageQueue();
	uint32_t push(void * data,uint32_t size);
	uint32_t pop(void * buf,uint32_t bufSize);
	bool	empty();
private:
	uint32_t dataSize();
	uint32_t availSize();
	uint8_t * currPtr();
	void lock();
	void unlock();
	
private:
	uint32_t 	m_nBufSize;
	uint8_t *	m_pBuf;
	uint32_t	m_nWriteOffset;
	pthread_mutex_t m_lock;
};




#endif //__MESSAGE_QUEUE_H__

