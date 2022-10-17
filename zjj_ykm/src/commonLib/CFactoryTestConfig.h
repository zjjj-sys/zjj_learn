#ifdef CONFIG_SUPPORT_JSONCPP_SERIALIZE

#ifndef __FACTORY_TEST_CONFIG__HH__
#define __FACTORY_TEST_CONFIG__HH__



#include "common.h"
#include "commFunc.h"
class CFactoryTestConfig{
public:
	CFactoryTestConfig(const char * pCfgFile = TMP_DIR_FACTORY_TEST_FILE);
	virtual ~CFactoryTestConfig();
	bool getFactoryWifiParam(std::string & strEssid,std::string & strPassword);
private:
	void loadConfig();
	
private:
	std::string m_strCfgFile;
	Json::Value m_objRoot;
};




































#endif //__FACTORY_TEST_CONFIG__HH__
#endif //#ifdef CONFIG_SUPPORT_JSONCPP_SERIALIZE

