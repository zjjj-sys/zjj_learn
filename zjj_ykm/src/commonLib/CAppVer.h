#ifndef __CAPP_VER_H__
#define __CAPP_VER_H__


#include <fstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>



#include <pthread.h>
#include "common.h"

using std::string;




struct AppVer
{
public:
    int ver1;
    int ver2; 
    int ver3; 
	int ver4;
public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( ver1 );
        ar &BOOST_SERIALIZATION_NVP ( ver2 );
        ar &BOOST_SERIALIZATION_NVP ( ver3 );
        ar &BOOST_SERIALIZATION_NVP ( ver4 );
    }
};


class CAppVer{
public:
	CAppVer();
    void loadConfig();
	void version(int & ver1,int & ver2,int & ver3,int & ver4);
	string version();
public:
	struct AppVer m_stConfig;
	static pthread_mutex_t m_lock;
};


















#endif //__CAPP_VER_H__





