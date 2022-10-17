#ifdef CONFIG_SUPPORT_MTD_DEVICE_OPERATION
#ifndef __CMTD_DATA_OBJ_H__
#define __CMTD_DATA_OBJ_H__

#include "CMtdDevice.h"



#define CONFIG_QRCODE_DB_DATA_HDR_MAGIC "QrCodeDataBase@"
#define CONFIG_ACCLOG_DB_DATA_HDR_MAGIC "AccLogDataBase@"
typedef struct{
	char magic[16];
	uint32_t data_size;
	uint32_t crc_val;
	uint8_t data[0];
}MTD_DATA_OBJ_HDR;


typedef struct{
	uint32_t offset;
	uint32_t size;
}MTD_DATA_OBJ_PART_INFO;


class CMtdDataObj{
public:
	CMtdDataObj();
	virtual ~CMtdDataObj();
	uint32_t maxQrCodeDBSize();
	bool saveQrCodeDB(std::shared_ptr<uint8_t> & ptrData,
		uint32_t nDataSize);
	bool loadQrCodeDB(std::shared_ptr<uint8_t> & ptrData,
		uint32_t & nDataSize);
	
	uint32_t maxAccessLogDBSize();
	bool saveAccessLogDB(std::shared_ptr<uint8_t> & ptrData,
		uint32_t nDataSize);
	bool loadAccessLogDB(std::shared_ptr<uint8_t> & ptrData,
		uint32_t & nDataSize);

private:
	bool WriteDataObjToMTD(const char * pObjMagic, 
		std::shared_ptr<uint8_t> & ptrData,
		uint32_t nDataSize,const size_t nMaxDataObjPartSize,uint32_t offset);
	bool ReadDataObjFromMTD(const char * pObjMagic,
		std::shared_ptr<uint8_t> & ptrData,
		uint32_t & nDataSize,const size_t nMaxDataObjPartSize,uint32_t offset);
	
private:
	int m_nMtdDevIndex ;
	std::shared_ptr<CMtdDevice> m_ptrMtdDev;
	MTD_DATA_OBJ_PART_INFO m_stQrCodeDB;
	MTD_DATA_OBJ_PART_INFO m_stAccLogDB;

	std::mutex m_MtdObjMutex;
};

























#endif //__CMTD_DATA_OBJ_H__
#endif //#ifdef CONFIG_SUPPORT_MTD_DEVICE_OPERATION


