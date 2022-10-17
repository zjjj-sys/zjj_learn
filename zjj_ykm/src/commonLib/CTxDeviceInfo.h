#ifndef __CTX_DEVICE_INFO_H__
#define __CTX_DEVICE_INFO_H__

#include <fstream>
#include <iostream>
#include <string>
#include <stdint.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>



struct TxXferConfig
{
public:
	std::string 	downloadPath;

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( downloadPath );
    }
};


struct TxOTAConfig
{
public:
	std::string 	fwPath;
	int 			TimeoutSec;

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( fwPath );
        ar &BOOST_SERIALIZATION_NVP ( TimeoutSec );
    }
};



struct TxDebugConfig
{
public:
	int isWriteLogFile;
	int isOpenCbPrint;

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( isWriteLogFile );
        ar &BOOST_SERIALIZATION_NVP ( isOpenCbPrint );
    }
};



struct TxDevConfig
{
public:
    std::string 		platform;
    std::string			devName;
	std::string 		sn;
	std::string 		licensePath;
	std::string 		privateKeyPath;
	std::string 		serverPubKeyPath;
	int	   				networkType;
	uint32_t 			productId;	
	uint32_t 			productVersion;

	std::string 		systemPath;
	uint32_t			systemPathCap;
	std::string 		appPath;
	uint32_t			appPathCap;
	std::string 		tmpPath;
	uint32_t			tmpPahtCap;
	TxDebugConfig		debugConfig;
	TxOTAConfig			otaConfig;
	TxXferConfig		xferConfig;
public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( platform );
        ar &BOOST_SERIALIZATION_NVP ( devName );
        ar &BOOST_SERIALIZATION_NVP ( sn );
        ar &BOOST_SERIALIZATION_NVP ( licensePath );
        ar &BOOST_SERIALIZATION_NVP ( privateKeyPath );		
        ar &BOOST_SERIALIZATION_NVP ( serverPubKeyPath );
        ar &BOOST_SERIALIZATION_NVP ( networkType );
        ar &BOOST_SERIALIZATION_NVP ( productId );
        ar &BOOST_SERIALIZATION_NVP ( productVersion );
        ar &BOOST_SERIALIZATION_NVP ( systemPath );
        ar &BOOST_SERIALIZATION_NVP ( systemPathCap );
        ar &BOOST_SERIALIZATION_NVP ( appPath );
        ar &BOOST_SERIALIZATION_NVP ( appPathCap );
        ar &BOOST_SERIALIZATION_NVP ( tmpPath );
        ar &BOOST_SERIALIZATION_NVP ( tmpPahtCap );
        ar &BOOST_SERIALIZATION_NVP ( debugConfig );
        ar &BOOST_SERIALIZATION_NVP ( otaConfig );
        ar &BOOST_SERIALIZATION_NVP ( xferConfig );

    }
};


class CTxDevConfig{
public:
	CTxDevConfig();
	~CTxDevConfig();
    void loadConfig();
    void saveConfig();
    void genDefConfig();

public:
	TxDevConfig m_stConfig;
	static pthread_mutex_t m_lock;
};










#endif //__CTX_DEVICE_INFO_H__


