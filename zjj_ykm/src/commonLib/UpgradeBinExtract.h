#ifndef __UPGRADE_BIN_EXTRACT_H__
#define __UPGRADE_BIN_EXTRACT_H__

#include <iostream>
#include <string>

#include "UpgradeBin.h"

using std::string;

class CUpgradeBinExtract
{
public:
	CUpgradeBinExtract(const char * pFile);
	virtual ~CUpgradeBinExtract();

	bool init();
	bool deinit();

	
	bool extractAppFile(const char * file);
	bool extractAppFileByTruncate(const char * file);
	bool extractSys(const char * file);

	bool extractUpgradeFile(const char * file);
	bool extractUpgradeInfoFile(const char * file);
	bool extractProductXmlFile(const char * file);
	bool extractAlarmHostUpgradeFile(const char * file);
	const char * AppMtdDev();
	const char * SysMtdDev();


private:
	bool readFirmwareInfo();



private:
	string m_strFirmwareFile;
	FILE * m_pFile;
	UPGRADE_BIN_INFO m_stFirmwareInfo;
	UPGRADE_PART_INFO * m_pUpgradeExeInfo;
	UPGRADE_PART_INFO * m_pUpgradeXmlFileInfo;
	UPGRADE_PART_INFO * m_pAppImageInfo;
	UPGRADE_PART_INFO * m_pSysImageInfo;
	UPGRADE_PART_INFO * m_pProductXmlInfo;
	UPGRADE_PART_INFO * m_pAlarmHostUpgradeInfo;

};
























#endif //__UPGRADE_BIN_EXTRACT_H__

