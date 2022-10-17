#ifndef __C_TUYA_BURN_ROM_DATA_H__
#define __C_TUYA_BURN_ROM_DATA_H__

#include <fstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

using std::string;

typedef struct {
	bool   Enable;
	string ProductKey;
	string UUID;
	string AuthKey;	
}TUYA_BURN_DATA;


struct TuyaBurnRomData
{
public:
	bool   Enable;
	string ProductKey;
	string UUID;
	string AuthKey;

	int flag1;	// reserved flag1
	int flag2;	// reserved flag2
	int flag3;	// reserved flag3
	int flag4;	// reserved flag4

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( Enable );
        ar &BOOST_SERIALIZATION_NVP ( ProductKey );
        ar &BOOST_SERIALIZATION_NVP ( UUID );
        ar &BOOST_SERIALIZATION_NVP ( AuthKey );
	
	    ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );
	}
};

class CTuyaBurnRomData{
public:
	CTuyaBurnRomData();
	virtual ~CTuyaBurnRomData();
    void loadConfig();
    void saveConfig();
    void genDefConfig();

public:
	bool isTuyaServiceEnable();
	int  getTuyaBurnData(TUYA_BURN_DATA & stBurnData);
	int  setTuyaBurnData(TUYA_BURN_DATA & stBurnData);

public:
	struct TuyaBurnRomData  m_stConfig;
	static pthread_mutex_t  m_lock;
};

#endif //__C_TUYA_BURN_ROM_DATA_H__

