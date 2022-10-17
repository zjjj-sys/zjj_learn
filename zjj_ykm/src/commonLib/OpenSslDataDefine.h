#ifndef __OPENSSL_DATA_DEFINE_H__
#define __OPENSSL_DATA_DEFINE_H__

#if defined(x86) || defined(x64)

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <pthread.h>
#include <unistd.h>

#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"




#define IPC_DEBUG_DECLARE(process_name) \
        char * gProcessName = (char *)process_name;

extern char * gProcessName;


#define DEBUG_INFO(s,...)  {printf(NONE"<%8s[%24s]%6u>[INFO]",gProcessName,__FILE__,__LINE__);printf(s,##__VA_ARGS__);printf(NONE);}
#define DEBUG_WARN(s,...)  {printf(YELLOW"<%8s[%24s]%6u>[WARN]",gProcessName,__FILE__,__LINE__);printf(s,##__VA_ARGS__);printf(NONE);}
#define DEBUG_ERROR(s,...) {printf(LIGHT_RED"<%8s[%24s]%6u>[ERR ]",gProcessName,__FILE__,__LINE__);printf(s,##__VA_ARGS__);printf(NONE);} 









#else
#include "common.h"

#endif





//////////////////////////////////////////////////////////////////
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>



#define RSA_KEY_TYPE_PUBLIC (1 << 0)
#define RSA_KEY_TYPE_PRIVATE (1 << 1)


typedef enum{
	enum_load_rsa_key_from_mem = 0,
	enum_load_rsa_key_from_file= 1,	
}ENUM_LOAD_RSA_KEY_TYPE;


typedef enum{
	enum_evp_cipher_type_encrypt = 0,
	enum_evp_cipher_type_decrypt = 1,
}ENUM_EVP_CIPHER_TYPE;




#endif //__OPENSSL_DATA_DEFINE_H__

