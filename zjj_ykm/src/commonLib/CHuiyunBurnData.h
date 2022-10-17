#ifndef __C_HUIYUN_BURN_ROM_DATA_H__
#define __C_HUIYUN_BURN_ROM_DATA_H__

#include <fstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

using std::string;

typedef struct {
	bool   Enable;
	string CompanyID;
	string ProductID;
	string DeviceID;	
}HUIYUN_BURN_DATA;


struct HuiyunBurnRomData
{
public:
	bool   Enable;
	string CompanyID;
	string ProductID;
	string DeviceID;

	string flag1;	// reserved flag1
	string flag2;	// reserved flag2
	string flag3;	// reserved flag3
	string flag4;	// reserved flag4

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( Enable );
        ar &BOOST_SERIALIZATION_NVP ( CompanyID );
        ar &BOOST_SERIALIZATION_NVP ( ProductID );
        ar &BOOST_SERIALIZATION_NVP ( DeviceID );
	
	    ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );
	}
};

class CHuiyunBurnRomData{
public:
	CHuiyunBurnRomData();
	virtual ~CHuiyunBurnRomData();
    void loadConfig();
    void saveConfig();
    void genDefConfig();

public:
	bool isHuiyunServiceEnable();
	int  getHuiyunBurnData(HUIYUN_BURN_DATA & stBurnData);
	int  setHuiyunBurnData(HUIYUN_BURN_DATA & stBurnData);

public:
	struct HuiyunBurnRomData  m_stConfig;
	static pthread_mutex_t  m_lock;
};

#endif //__C_HUIYUN_BURN_ROM_DATA_H__

