#ifndef __CPP_PRINT_FORMAT_HH__
#define __CPP_PRINT_FORMAT_HH__


#include "common.h"
#include <string>



namespace prtfmt{

#if defined(__linux__)
#if __linux__
//__SIZEOF_LONG__
#define CONFIG_SUPPORT_COMM_FUNC_HEX_STRING
	template<typename T>
	std::string _hexStr( T * t){
		std::string result;
		/*
		std::string strFmt;
		if(NULL == fmt){
			//strFmt = R"(%#x)";
			strFmt = "%#x";
		}else{
			strFmt = fmt;
		}
		*/
#if (defined(__SIZEOF_LONG__) && (__SIZEOF_LONG__ == 4))
		// 32bit cpu
		char  buf[128];
		switch(sizeof(T)){
		case 1:
			snprintf(buf,sizeof(buf),"%#04x",*((uint8_t *)t));
			break;
		case 2:
			snprintf(buf,sizeof(buf),"%#06x",*((uint16_t *)t));
			break;
		case 4:
			snprintf(buf,sizeof(buf),"%#010x",*((uint32_t *)t));
			break;
		case 8:
			snprintf(buf,sizeof(buf),"%#018llx",*((uint64_t *)t));
			break;
		default:
			DEBUG_ERROR("Invalid size sizeof(T) = %zd\n",sizeof(T));
			snprintf(buf,sizeof(buf),"%#018llx",*((uint64_t *)t));
			break;
		}
		result.assign(buf);
		return result;
#elif (defined(__SIZEOF_LONG__) && (__SIZEOF_LONG__ == 8))
		// 64bit cpu
		char  buf[128];
		switch(sizeof(T)){
		case 1:
			snprintf(buf,sizeof(buf),"%#04x",*((uint8_t *)t));
			break;
		case 2:
			snprintf(buf,sizeof(buf),"%#06x",*((uint16_t *)t));
			break;
		case 4:
			snprintf(buf,sizeof(buf),"%#010x",*((uint32_t *)t));
			break;
		case 8:
			snprintf(buf,sizeof(buf),"%#018lx",*((uint64_t *)t));
			break;
		default:
			DEBUG_ERROR("Invalid size sizeof(T) = %zd\n",sizeof(T));
			snprintf(buf,sizeof(buf),"%#018lx",*((uint64_t *)t));
			break;
		}
		result.assign(buf);
		return result;
#else
#error "Check you execute platform(_hexString)!!!!"
#endif
	}
		
#endif // #if __linux__
#endif // #if defined(__linux__)


#ifndef CONFIG_SUPPORT_COMM_FUNC_HEX_STRING
#error "Check you execute platform(_hexString)!!!!"
#endif


	template<typename T>
	std::string hexStr( T  t){
		T * pt = &t;
		return _hexStr(pt);
	}
};






#define _s(val) (std::to_string(val).c_str())
#define _h(val) (prtfmt::hexStr(val).c_str())















#endif //__CPP_PRINT_FORMAT_HH__
