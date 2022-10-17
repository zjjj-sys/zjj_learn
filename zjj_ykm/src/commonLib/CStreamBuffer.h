#ifndef __CSTREAM_BUFFER_H__
#define __CSTREAM_BUFFER_H__
	
#include "mm.h"	
	

	
class CStreamBuffer
{
public:
	CStreamBuffer(const char * name,unsigned int flag,	unsigned int mem_block_size,unsigned int mem_block_num,
		unsigned int frame_header_num);
	~CStreamBuffer();
	/*
	int getFrame(unsigned int * key_frame,unsigned int * ts,	unsigned char * buf_data,unsigned int buf_size);
	int putFrame(unsigned int key_frame,unsigned char * frame_data,	unsigned int frame_size);
	int putFrame2(unsigned int key_frame,unsigned int ts,unsigned char * frame_data, unsigned int frame_size);
	*/
	int getFrameExt(unsigned int * key_frame,unsigned int * ts,	unsigned char * buf_data,
		unsigned int buf_size,unsigned int * frame_type);
	int putFrameExt(unsigned int key_frame,unsigned int ts,unsigned char * frame_data, 
		unsigned int frame_size,unsigned int frame_type);

private:
	mem_block_user* m_pMemBlockUser;
};
	
	
	
	
	
	
#endif // __CSTREAM_BUFFER_H__
	
	





























