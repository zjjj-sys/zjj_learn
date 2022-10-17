#ifdef CONFIG_SUPPORT_OPENSSL_CPP_WRAPPER
#ifndef __EVP_DIGEST_HH__
#define __EVP_DIGEST_HH__






#include "OpenSslDataDefine.h"
#include "OpenSslNamespace.h"

#include <memory>
#include <string>



namespace OpenSsl{

class CEvpDigest{
public:
	CEvpDigest(const char * digestName,ENGINE *impl = NULL);
	virtual ~CEvpDigest();
	bool update(const uint8_t * data,const uint32_t size);
	// binary digest
	std::string final();
	// text digest
	std::string finalText(bool bLowCase = true);

	// binary digest
	static std::string digest(const char * digestName,ENGINE *impl,
		const uint8_t * data,const uint32_t size);
	// text digest
	static std::string digestText(const char * digestName,ENGINE *impl,
		const uint8_t * data,const uint32_t size,bool bLowCase = true);
private:
	EVP_MD_CTX * m_pstEvpMdCtx;

};







/*
<    test[                test.cpp]   803>[INFO]Digest MD4 size 16
<    test[                test.cpp]   803>[INFO]Digest MD5 size 16
<    test[                test.cpp]   803>[INFO]Digest MD5-SHA1 size 36
<    test[                test.cpp]   803>[INFO]Digest BLAKE2b512 size 64
<    test[                test.cpp]   803>[INFO]Digest BLAKE2s256 size 32
<    test[                test.cpp]   803>[INFO]Digest SHA1 size 20
<    test[                test.cpp]   803>[INFO]Digest SHA224 size 28
<    test[                test.cpp]   803>[INFO]Digest SHA256 size 32
<    test[                test.cpp]   803>[INFO]Digest SHA384 size 48
<    test[                test.cpp]   803>[INFO]Digest SHA512 size 64
<    test[                test.cpp]   803>[INFO]Digest SHA512-224 size 28
<    test[                test.cpp]   803>[INFO]Digest SHA512-256 size 32
<    test[                test.cpp]   803>[INFO]Digest SHA3-224 size 28
<    test[                test.cpp]   803>[INFO]Digest SHA3-256 size 32
<    test[                test.cpp]   803>[INFO]Digest SHA3-384 size 48
<    test[                test.cpp]   803>[INFO]Digest SHA3-512 size 64
<    test[                test.cpp]   803>[INFO]Digest SHAKE128 size 16
<    test[                test.cpp]   803>[INFO]Digest SHAKE256 size 32
<    test[                test.cpp]   803>[INFO]Digest MDC2 size 16
<    test[                test.cpp]   803>[INFO]Digest RIPEMD160 size 20
<    test[                test.cpp]   803>[INFO]Digest whirlpool size 64
<    test[                test.cpp]   803>[INFO]Digest SM3 size 32

*/




















};












#endif // __EVP_DIGEST_HH__


#endif //#ifdef CONFIG_SUPPORT_OPENSSL_CPP_WRAPPER


