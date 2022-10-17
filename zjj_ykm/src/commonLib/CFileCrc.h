#ifndef __FILE_CRC_H__
#define __FILE_CRC_H__




#include <stdio.h>
#include <stdint.h>






class CFileCrc
{
public:
	static uint32_t Calu(const char * pFile,uint32_t offset,uint32_t size);
	static uint32_t Calu(const char * pFile,uint32_t offset);
	static uint32_t Calu(const char * pFile);
	static uint64_t fileSize(const char * file);

};
























#endif //__FILE_CRC_H__

