#ifdef CONFIG_SUPPORT_MTD_DEVICE_OPERATION

#ifndef __CMTD_DEVICE_HH__
#define __CMTD_DEVICE_HH__

#include "common.h"
#include "mtd-abi.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <sys/ioctl.h>


#include <mutex>


class CMtdDevice{
public:
	explicit CMtdDevice(int index);
	virtual ~CMtdDevice();
	std::string device();
	bool isReady();
	int blockSize();
	int totalSize();
	int writeBlock(const uint8_t * pData,const uint32_t nDataSize,uint32_t offset = 0);
	int readBlock(uint8_t * pData, uint32_t  nDataSize,uint32_t offset = 0);
	bool readAll(std::shared_ptr<uint8_t> & ptrData,uint32_t & nDataSize);
private:
	int __readBlock(uint8_t * pData, uint32_t  nDataSize,uint32_t offset = 0);
private:
	bool __initialize();
	bool __deinit();
	
private:
	bool m_bIsReady;
	int m_nMtdDeviceIndex;
	int m_nMtdFd;
	int m_nTotalSize;
	int m_nBlockSize;

//	static std::mutex m_staticMtdMutex;
};






















#endif //__CMTD_DEVICE_HH__
#endif //CONFIG_SUPPORT_MTD_DEVICE_OPERATION
