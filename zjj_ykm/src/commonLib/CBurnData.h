#ifndef __BURN_DATA_H__
#define __BURN_DATA_H__





#include <fstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


#include "MiscDataType.h"

#include <iostream>

using std::string;



typedef struct{
	string Did;
	string ApiLic;
	string InitStringDName;
	string InitStringIp;
}P2P_INFO;


typedef struct{
	string ip;
	int16_t port;
}ALARM_SERVER;



typedef struct{
	string ip;
	int16_t port;
}REGISTER_SERVER;



typedef struct{
	string domain;
	string ip;
	int16_t port;
}AUTH_SERVER_INFO;

#define MAX_AUTH_SERVER_COUNT 4

typedef struct{
	AUTH_SERVER_INFO server[MAX_AUTH_SERVER_COUNT];
}AUTH_SERVER;






typedef struct{
	string DevId;//platform login id
	int32_t CustomId;
	P2P_INFO p2p;
	ALARM_SERVER alarm;
	REGISTER_SERVER platform;
	AUTH_SERVER auth;
}MEIAN_BURN_DATA;





///////////////////////////////////////////////////////////////////////////////////
// p2p config...
///////////////////////////////////////////////////////////////////////////////////
struct P2P_CONFIG
{
public:
	string Did;
	string ApiLic;
	string InitStringDName;
	string InitStringIp;
	
	int flag1;				// reserved flag1
	int flag2;				// reserved flag2
	int flag3;				// reserved flag3
	int flag4;				// reserved flag4

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( Did );
        ar &BOOST_SERIALIZATION_NVP ( ApiLic );
        ar &BOOST_SERIALIZATION_NVP ( InitStringDName );
        ar &BOOST_SERIALIZATION_NVP ( InitStringIp );
	    ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );

	}
};

///////////////////////////////////////////////////////////////////////////////////
// alarm config...
///////////////////////////////////////////////////////////////////////////////////
struct ALARM_CONFIG
{
public:
	string ip;
	int16_t port;
	
	int flag1;				// reserved flag1
	int flag2;				// reserved flag2
	int flag3;				// reserved flag3
	int flag4;				// reserved flag4

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( ip );
        ar &BOOST_SERIALIZATION_NVP ( port );
	    ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );

	}
};


///////////////////////////////////////////////////////////////////////////////////
// platform register server config...
///////////////////////////////////////////////////////////////////////////////////

struct PLATFORM_REGISTER_SVR_CONFIG
{
public:
	string ip;
	int16_t port;
	
	int flag1;				// reserved flag1
	int flag2;				// reserved flag2
	int flag3;				// reserved flag3
	int flag4;				// reserved flag4

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( ip );
        ar &BOOST_SERIALIZATION_NVP ( port );
	    ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );

	}
};

///////////////////////////////////////////////////////////////////////////////////
// auth server config...
///////////////////////////////////////////////////////////////////////////////////

struct AUTH_SERVER_CONFIG
{
public:
	string domain;
	string ip;
	int16_t port;
	
	int flag1;				// reserved flag1
	int flag2;				// reserved flag2
	int flag3;				// reserved flag3
	int flag4;				// reserved flag4

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( domain );
	    ar &BOOST_SERIALIZATION_NVP ( ip );
        ar &BOOST_SERIALIZATION_NVP ( port );
        ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );		
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );

	}
};



struct AUTH_CONFIG
{
public:
	AUTH_SERVER_CONFIG server[MAX_AUTH_SERVER_COUNT];

	
	int flag1;				// reserved flag1
	int flag2;				// reserved flag2
	int flag3;				// reserved flag3
	int flag4;				// reserved flag4

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( server );
	    ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );

	}
};






struct BurnRomData
{
public:
	string mac;				
	string DevId;	
	int CustomId;
	struct P2P_CONFIG p2p;
	struct ALARM_CONFIG alarm;
	struct PLATFORM_REGISTER_SVR_CONFIG platform;
	struct AUTH_CONFIG auth;
	
	int flag1;				// reserved flag1
	int flag2;				// reserved flag2
	int flag3;				// reserved flag3
	int flag4;				// reserved flag4

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( mac );
        ar &BOOST_SERIALIZATION_NVP ( DevId );
        ar &BOOST_SERIALIZATION_NVP ( CustomId );
        ar &BOOST_SERIALIZATION_NVP ( p2p );
        ar &BOOST_SERIALIZATION_NVP ( alarm );
        ar &BOOST_SERIALIZATION_NVP ( platform );
        ar &BOOST_SERIALIZATION_NVP ( auth );		
	    ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );

	}
};






class CBurnRomData{
public:
	CBurnRomData();
	virtual ~CBurnRomData();
    void loadConfig();
    void saveConfig();
    void genDefConfig();
public:
	void MacString(string & mac);
	void setMac(string & mac);
	void saveBurnData(MEIAN_BURN_DATA & stBurnData);
	void loadBurnData(MEIAN_BURN_DATA & stBurnData);
	bool compareBurnData(MEIAN_BURN_DATA & stBurnData1,MEIAN_BURN_DATA & stBurnData2,bool & isIdentical); // return isIdentical

public:
	struct BurnRomData  m_stConfig;
	static pthread_mutex_t m_lock;
};







































#endif //__BURN_DATA_H__

