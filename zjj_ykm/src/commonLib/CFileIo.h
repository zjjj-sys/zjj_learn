#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include "common.h"

#if defined(HI3516CV500) || defined(SV823)
#include <memory>
#include <tuple>
#endif

namespace FileIO{
	int save(const char *,void * pData,uint32_t nDataSize);
	int load(const char *,void * pBuf,uint32_t nBufSize);
#if defined(HI3516CV500) || defined(SV823)
	std::tuple<bool,std::shared_ptr<uint8_t>,uint32_t>  load(const char *);
	bool load(const char *,std::shared_ptr<uint8_t> &,uint32_t &);
#endif
};












#endif //__FILE_IO_H__


