#ifndef __UPGRADE_BIN_H__
#define __UPGRADE_BIN_H__


#include <iostream>
#include <string>

#include <stdio.h>
#include <stdint.h>


using std::string;

#define MAX_MTD_COUNT 8



typedef struct{
	uint32_t enable;
	uint32_t crc;
	uint32_t offset;
	uint32_t size;
	char mtd[64]; // eg. /dev/mtd0	
	char name[64]; // eg.uboot,kernel,rootfs,app.....
}UPGRADE_PART_INFO;

typedef struct{
	UPGRADE_PART_INFO part[MAX_MTD_COUNT]; // app partition first...
}UPGRADE_BIN_INFO;


#define APP_PART_NAME "App"
#define UPGRADE_NAME  "Upgrade"
#define UPGRADE_INFO_NAME "UpgradeInfo"
#define KERNEL_NAME "Kernel"
#define PRODUCT_XML "ProductConfig.xml"
#define ALARM_HOST_NAME "AlarmHost"




class CUpgradeBinGen
{
public:
	explicit CUpgradeBinGen(const char * bin);
	virtual ~CUpgradeBinGen();
	// app
	bool gen(const char * pAppSqfsFile,const char * pUpgradeExeFile,const char * pUpgradeInfoXmlFile);
	// app + kernel
	bool gen(const char * pAppSqfsFile,const char * pKernelFile,const char * pUpgradeExeFile,const char * pUpgradeInfoXmlFile);
	// app + kernel + ProductConfig.xml
	bool gen(const char * pAppSqfsFile,const char * pKernelFile,const char * pProductConfigXmlFile,const char * pUpgradeExeFile,const char * pUpgradeInfoXmlFile);
	// app + alarmHost
	bool genAppWithUpgrade(const char * pAppSqfsFile,const char * AlarmHostUpgradeFile,const char * pUpgradeExeFile,const char * pUpgradeInfoXmlFile);

	// app + rootfs
//	bool gen(const char * pAppSqfsFile,const char * pRootfsSqfsFile,const char * pUpgradeExeFile,const char * pUpgradeInfoXmlFile);
	// app + rootfs + kernel
//	bool gen(const char * pAppSqfsFile,const char * pKernelFile,const char * pRootfsSqfsFile,const char * pUpgradeExeFile,const char * pUpgradeInfoXmlFile);


private:


private:
	string m_strBin;
	FILE * m_pFile;

};




















#endif  //__UPGRADE_BIN_H__


