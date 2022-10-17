#if !defined(__INCLUDED_TYPE_DEFINE____H)
#define __INCLUDED_TYPE_DEFINE____H

#if defined WIN32DLL || defined LINUX
typedef int INT32;
typedef unsigned int UINT32;
#endif

#if defined(WIN32)
	typedef unsigned __int64   UINT64;
#elif defined(LINUX)
	typedef unsigned long long int UINT64;
#else
	typedef unsigned long long UINT64;
#endif

typedef short INT16;
typedef unsigned short UINT16;

typedef char CHAR;
typedef signed char	 SCHAR;
typedef unsigned char UCHAR;

typedef long LONG;
typedef unsigned long ULONG;
#if 0
#ifndef bool
#define bool	CHAR
#endif
#endif //
#ifndef _ARC_COMPILER
#ifndef true
#define true	1
#endif

#ifndef false
#define false	0
#endif
#endif ////#ifndef _ARC_COMPILER
#endif  //__INCLUDED_TYPE_DEFINE_H

