#ifndef __COMM_FUNC_H__
#define __COMM_FUNC_H__

#include <stdio.h>
#include <stdint.h>

#include <iostream>
#include <string>
#include <error.h>
#include <errno.h>

#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <list>


#include <initializer_list>
#include <algorithm>
#include <memory>
#include <vector>

#include "debug.h"
#include "common.h"
#include "MiscDataType.h"
#include "CProduct.h"

#ifdef CONFIG_SUPPORT_JSONCPP_SERIALIZE
#include <json/json.h>
#endif




#define CXX_TRUE ((bool)true)
#define CXX_FALSE ((bool)false)


using std::string;
using std::list;

#define SCSI_DEVICE_MAJOR_NUM 8


typedef struct{
	uint16_t year;
	uint16_t mon;
	uint16_t day;
	uint16_t week_day;  // 0 - 6 , 0:sunday
	uint16_t hour;
	uint16_t min;
	uint16_t sec;
}__attribute__((packed))DAILY_TIME_t;


typedef struct{
	uint32_t 	major;
	uint32_t 	minor;
	uint32_t 	blocks; // 1K	
	char  		name[256];
}__attribute__((packed))PARTITION_INFO;



enum {
	ENUM_74HC595_PIN_WIFI_POWER 			= 0xff00,
	ENUM_74HC595_PIN_SPEAKER_AMPLIFIER ,
	ENUM_74HC595_PIN_LED_SWITCH ,
	ENUM_74HC595_PIN_IRCUT_A ,
	ENUM_74HC595_PIN_IRCUT_B ,
	ENUM_74HC595_PIN_NET_LED ,
	ENUM_74HC595_PIN_SD_EN,


};

#define __MODEL_SET__
#define __MODEL__

enum{
	enum_haiqing_pin_base					= 0x1000,
	enum_haiqing_pin_white_light_switch 	= enum_haiqing_pin_base,
	enum_haiqing_pin_ir_light_switch,
	enum_haiqing_pin_lcd_power_switch,
	enum_haiqing_pin_lcd_backlight_ctrl,
	enum_haiqing_pin_door_ctrl_gpio,
	enum_haiqing_pin_rs485_send_switch_ctrl,
	enum_haiqing_pin_butt,
};



typedef enum{
	enum_fs_type_vfat 	= 0,
	enum_fs_type_ntfs,
	enum_fs_type_unknow ,
}FS_TYPE;





typedef struct{
	std::string devname;
	std::string mountpoint;
	std::string filesystem;
	std::string option;
	int flag1;
	int flag2;
}MOUNT_INFO;

class CProduct;
class CFactoryTestConfig;

typedef struct{
	std::string intf;
	std::string ip;
	std::string broadcast;
	std::string netmask;
	uint8_t mac[6];
}NET_INTERFACE_INFO;


typedef enum{
	enum_qr_code_type_jinmao = 0,
	enum_qr_code_type_ykm    = 1,

	
	enum_qr_code_type_invalid = 100,
}ENUM_QRCODE_TYPE;


namespace COMM_FUNC
{
	//time func
	uint64_t getStartTimeMs();
	uint64_t getStartTimeUs();
	uint64_t getStartTimeS();

	uint64_t getGmtMs();

	string timeToString(time_t t);
	void getLocalTime(DAILY_TIME_t & daily_time);
	void PrintLocalTime();
	//file func
	uint64_t fileSize(const char * file);
	bool isFileExist(const char * file);
	bool isDirExist(const char * file);
	int32_t readFile(const char * file,uint8_t * buf,uint32_t bufSize);
	std::string readFile(const std::string & file);
	std::string readFile(const char * pFile);
	int32_t writeFile(const char * file ,uint8_t * data,uint32_t dataSize);
	bool getSdcardSize(uint64_t * pTotalSize,uint64_t * pFreeSize,uint64_t * pUsedSize); // get storage size;
	//ip addr
	// [No block] operation uint32_t timeoutMs /*NO USE*/,bool bStop /*NO USE*/
	bool waitAssignIpAddress(string intf,string & stringIp,uint32_t timeoutMs /*NO USE*/,bool bStop /*NO USE*/);
	// [Block   ] operation - lifan @2021.09.08
	bool waitAssignIpAddress2(string intf,string & stringIp,uint32_t timeoutMs,bool & bStop);
	std::string getIpAddrString(uint32_t addr);
	uint32_t getIpAddrBin(std::string ipString);
	uint32_t getIpAddrBin(const char * pIpString);


	//get partition information
	bool getPartitionInfo(list<PARTITION_INFO> & partitionList);
	// getSataPartitionInfo
	bool getSataPartitionInfo(list<PARTITION_INFO> & partitionList);
	bool getRemovableDiskPartitionInfo(list<PARTITION_INFO> & partitionList);
	bool isRemovableDisk(const char * pDiskDev,bool & bRemovable);

	bool getMountInfoList(std::list<MOUNT_INFO> & lMountInfoList);

	bool testWritable(const char * pDir);


	
	// first boot
	bool isFirstBoot();
	bool clearFirstBootFlag();
	
	bool isVoiceLinkMode();
	bool clearVoiceLinkMode();


	bool setAutoMaintenanceFlag();
	bool clearAutoMaintenanceFlag();
	bool isBootWithAutoMaintenance();

	bool isIspCalibrationMode();

	bool setNVTChangedNetworkParamFlag();
	bool testAndClearNVTChangedNetworkParamFlag();
	

	bool createFlagFile(const char * file);
	bool removeFlagFile(const char * file);



	bool isDevIpVoicePromptePlayed();
	bool setDevIpVoicePromptePlayedFlag();

	bool writeLastTimeToFlash(time_t t);
	bool readLastTimeFromFlash(time_t & t);


	//time printf
	string SysLocalTime(time_t t,int32_t nGMTDiff);
	string SysLocalTimeExt(time_t t);
	void getBuildTime(struct tm  & stBuildTime);
	string getBuildTimeString();

	void DebugInit();
	void DebugDeinit();

	void SystemReboot();


	bool xmlNodeContentCheck(const char * xml, string nodeStart);

	bool getXmlNodeContent(const char * xml,string & node,string & content);
	bool getXmlNodeContent(const char * xml,string & node1,string & node2,string & content);
	bool getXmlNodeContent(const char * xml,string & node1,string & node2,string & node3,string & content);
	bool getXmlNodeContent(const char * xml,string & node1,string & node2,string & node3,string & node4,string & content);
	bool getXmlNodeContent(const char * xml,string & node1,string & node2,string & node3,string & node4,string & node5,string & content);

	bool getXmlNodeContent(const char * xml,const char * node1,string & content);
	bool getXmlNodeContent(const char * xml,const char * node1,const char *  node2,string & content);
	bool getXmlNodeContent(const char * xml,const char * node1,const char *  node2,const char * node3,string & content);
	bool getXmlNodeContent(const char * xml,const char * node1,const char *  node2,const char * node3,const char * node4,string & content);
	bool getXmlNodeContent(const char * xml,const char * node1,const char *  node2,const char * node3,const char * node4,const char * node5,string & content);

	// MStar Gpio write/read
	bool gpioInit(int nGpio);
	bool gpioDeinit(int nGpio);
	bool gpioSetOutput(int nGpio);
	bool gpioSetInput(int nGpio);
	bool gpioGetValue(int nGpio,bool & isHightLevel);
	bool gpioSetValue(int nGpio,bool  isHightLevel);

	bool isHaiQingPin(int nGpio);
	bool gpioGetValueHaiQing(int nGpio,bool & isHightLevel);
	bool gpioSetValueHaiQing(int nGpio,bool  isHightLevel);


	bool is74Hc595Pin(int nGpio);
	bool gpioGetValue74Hc595(int nGpio,bool & isHightLevel);
	bool gpioSetValue74Hc595(int nGpio,bool  isHightLevel);


	void sleep(uint32_t sec);

	// Process delay exit...
	void delayExit(int sec);
	void delayReboot(int sec);
	// Meian dev type
	uint32_t getMeianDevType(void * product);
	uint32_t getMeianJsonProtocolDevType(void * product);


	bool setSockKeepAlive(int skfd,int idle,int interval,int count);

	void flushMemoryData(void);

	uint64_t diskFreeSize(const char * pMountDir);
	uint64_t diskDataSize(const char * pMountDir);
	uint64_t diskSize(const char * pMountDir);
	bool getDiskSize(const char * pMountDir,uint64_t * pTotalSize,uint64_t * pFreeSize,uint64_t * pUsedSize); // get storage size;

	uint64_t diskFreeSize();
	uint64_t diskDataSize();
	uint64_t diskSize();
	bool getDiskSize(uint64_t * pTotalSize,uint64_t * pFreeSize,uint64_t * pUsedSize); // get storage size;

	bool SdCardRepair(uint32_t product);
	bool SdCardMount(uint32_t product);
	bool SdCardUmount(void);
	bool SdCardFormat(uint32_t product);
	bool SdRemount(uint32_t product);
	bool SdCardExist(uint32_t product);

	// return val,  < 0,param invalid,eg bit > 31,bit[0,31]
	int TestBit(uint32_t val,uint32_t bit);
	int TestAndClearBit(uint32_t & val,uint32_t bit);
	int SetBit(uint32_t & val,uint32_t bit);
	int ClearBit(uint32_t & val,uint32_t bit);


	// tcp connect
	int  setNoblockFd(int fd);
	int createTcpSocket();
	int connect(string & ip,uint16_t port,uint32_t nTimout/*0: block*/,bool & bStoped);


	bool isNVRSuitStatus();
	bool setNVRSuitStatus();
	bool clearNVRSuitStatus();


	bool removeDir(const char * pDir);
	bool clearDir(const char * pDir);
	bool removeFile(const char * pFile);
	// See linux c method <ftw> . 
	// lifan @2021.08.19

	/*
	FTW(3)                                                                               Linux Programmer's Manual                                                                               FTW(3)

	NAME
	       ftw, nftw - file tree walk

	SYNOPSIS
	       #include <ftw.h>

	       int nftw(const char *dirpath,
	               int (*fn) (const char *fpath, const struct stat *sb,
	                          int typeflag, struct FTW *ftwbuf),
	               int nopenfd, int flags);

	       #include <ftw.h>

	       int ftw(const char *dirpath,
	               int (*fn) (const char *fpath, const struct stat *sb,
	                          int typeflag),
	               int nopenfd);

	   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

	       nftw(): _XOPEN_SOURCE >= 500

	DESCRIPTION
	       nftw()  walks  through the directory tree that is located under the directory dirpath, and calls fn() once for each entry in the tree.  By default, directories are handled before the files
	       and subdirectories they contain (preorder traversal).

	       To avoid using up all of the calling process's file descriptors, nopenfd specifies the maximum number of directories that nftw() will hold  open  simultaneously.   When  the  search  depth
	       exceeds this, nftw() will become slower because directories have to be closed and reopened.  nftw() uses at most one file descriptor for each level in the directory tree.

	       For  each  entry found in the tree, nftw() calls fn() with four arguments: fpath, sb, typeflag, and ftwbuf.  fpath is the pathname of the entry, and is expressed either as a pathname rela\u2010
	       tive to the calling process's current working directory at the time of the call to nftw(), if dirpath was expressed as a relative pathname, or as  an  absolute  pathname,  if  dirpath  was
	       expressed as an absolute pathname.  sb is a pointer to the stat structure returned by a call to stat(2) for fpath.  typeflag is an integer that has one of the following values:


	*/
	
	///////////////////////////////////////////////////////////////////////////////////////
	template<class UnaryPredicate>
	bool iterDir(std::string & strWorkDir,UnaryPredicate pred){
		bool bResult = false;
		do{
			DIR * dir = opendir(strWorkDir.c_str());
			if(NULL == dir){
				DEBUG_ERROR("open dir %s failed,err info(%s)\n",strWorkDir.c_str(),strerror(errno));
				break;
			}


			while(1){
				struct dirent * entry =  readdir(dir);
				if(NULL == entry){
					DEBUG_INFO("scan dir %s completed\n",strWorkDir.c_str());
					break;
				}
				if(0 == strcmp(entry->d_name,".")){
					continue;
				}
				if(0 == strcmp(entry->d_name,"..")){
					continue;
				}

				std::string strEntry = entry->d_name;	
				if(pred(strEntry)){
					continue;
				}else{
					DEBUG_WARN("pred[%s] failed!\n",strEntry.c_str());
					break;
				}
			}

			closedir(dir);
			bResult = true;
		}while(0);

		return bResult;
	}
	///////////////////////////////////////////////////////////////////////////////////////

	void syncSystemDateTimeToRTC();
	void syncSystemDateTimeFromRTC();
	bool executeSystemCmd(const char * cmd);
	bool executeSystemCmd(const std::string & cmd);
	void sync();
	bool wiegand26_output(uint32_t model,uint8_t hid,/*LSB of ID Card HID*/uint16_t pid /*ID Card PID*/);
	bool wiegand34_output(uint32_t model,uint16_t hid,/*ID Card HID*/uint16_t pid/*ID Card PID*/);

	bool wiegand26_output_haiqing(uint8_t hid,/*LSB of ID Card HID*/uint16_t pid /*ID Card PID*/);
	bool wiegand34_output_haiqing(uint16_t hid,/*ID Card HID*/uint16_t pid/*ID Card PID*/);

	bool wiegand26_output_ext(uint32_t model,uint8_t hid,/*LSB of ID Card HID*/uint16_t pid /*ID Card PID*/);
	bool wiegand34_output_ext(uint32_t model,uint16_t hid,/*ID Card HID*/uint16_t pid/*ID Card PID*/);


	bool isModelIn(uint32_t model,std::initializer_list<uint32_t> && lModelSet );
	bool isModelIn(CProduct * pProduct,std::initializer_list<uint32_t> && lModelSet );




	uint32_t getFreeMemSize();

	int stringCut(const char * str,const char * delim,std::list<std::string> & lSubStringList);

	ENUM_4G_MODULE_TYPE get4GModuleType(CProduct * product);


	const char * findRecordDevPath();

	bool tzinit2(int nGMTDiff,uint32_t model);
	bool tzinit2(char *strTimeZone, uint32_t nSize);
	bool tz_apply();

	void set_thread_name(const char * pstrThreadName);
	void waitMS(uint32_t mSec,bool * pbExitFlag = NULL);


	bool is4GModeNeedReset();
	void clear4GModeNeedResetFlag();


	std::string getSocketAddrString(const struct sockaddr * sa,int len);
	bool getSocketAddrString(const struct sockaddr * sa,int len,
		std::string & strSocketAddr);
	int getNetInterfaceInfo(std::list<NET_INTERFACE_INFO> & lNetInterfaceInfo);


#ifdef CONFIG_SUPPORT_JSONCPP_SERIALIZE
	std::shared_ptr<std::string> jsonNodeToString(const Json::Value & jsonNode);
	bool jsonNodeToString(const Json::Value & jsonNode,std::string & jsonString);
	std::shared_ptr<Json::Value> jsonStringToNode(const std::string & jsonString);
	bool jsonStringToNode(const std::string & jsonString,Json::Value &jsonNode);

	std::string jsonNodeDump(const Json::Value & jsonNode);
	bool readJsonFile(const std::string & jsonFile,Json::Value &jsonNode);
#endif //#ifdef CONFIG_SUPPORT_JSONCPP_SERIALIZE
	void *	createShmMem(const char * name,uint32_t mem_size);
	void distroyShmMem(void * mem);
	bool isRtDbgEnable();
	bool getEthPhyLinkStatus(const char * intf = "eth0");

	const char * getUpgradeFileSavePath(void * product, bool &bSaveFWInFlash);
	void dumpMemData(const uint8_t * data,const size_t size);
	//////////////////////////////////////////////////////////////
	bool isWirelessNVRSuitIPC(CProduct * product);

	bool dateTimeToString(int year,int mon,int day,int hour,int min,int sec, std::string & dateTimeString);
	bool stringToDateTime(const std::string & dateTimeString,int & year,int & mon,int & day,int & hour,int & min,int & sec);
	bool dateTimeCheck(int year,int mon,int day,int hour,int min,int sec);
	bool isNetworkReady();
	bool testAndCreatFactTestCfgObj(std::shared_ptr<CFactoryTestConfig> & ptrFactTestCfgObj);
	ENUM_QRCODE_TYPE qrCodeType(CProduct * product,const std::string & qrCodeString);
};















#define AVOID_CLASS_COPY_ASSIGNMENT(T) \
	private:\
	T(const T &);\
	T & operator= (const T &);
/*
private:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);

C++11
#define AVOID_CLASS_COPY_ASSIGNMENT(T) \
	T(const T &) = delete;\
	T & operator= (const T &) = delete;
  

*/






typedef std::vector<uint8_t> DATA_BUFFER;


/*
	eg.

		alloc 128KB memory space 
		DATA_BUFFER buf(128)

*/










#endif //__COMM_FUNC_H__

