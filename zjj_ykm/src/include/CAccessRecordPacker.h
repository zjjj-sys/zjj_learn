#ifndef __CACCESS_RECORD_PACKER_H__
#define __CACCESS_RECORD_PACKER_H__


#include "common.h"
#include <memory>
#include <string>
#include <tuple>

#define CONFIG_ACCESS_RECORD_MAGIC 0xbadbeaf4


class CAccessRecord{
public:
	CAccessRecord(time_t _t,int _accessMode,std::string & _userId):
		t(_t),accessMode(_accessMode),userId(_userId){
		magic = CONFIG_ACCESS_RECORD_MAGIC;
	}

	uint32_t size(){
		return sizeof(magic) + sizeof(t) + sizeof(accessMode) + userId.size() + 1;
	}	

	int pack(void * pBuf,uint32_t nBufSize){
		if(NULL == pBuf){
			DEBUG_ERROR("pBuf is NULL!\n");
			return -1;
		}


		if(size() > nBufSize){
			DEBUG_ERROR("buf size small %d > %d\n",size() > nBufSize);
			return -1;
		}



		uint8_t * p = (uint8_t *)pBuf;
		memcpy(p,&magic,sizeof(magic));
		p += sizeof(magic);

		memcpy(p,&t,sizeof(t));
		p += sizeof(t);

		memcpy(p,&accessMode,sizeof(accessMode));
		p += sizeof(accessMode);

		memcpy(p,userId.c_str(),userId.size() + 1);
		p += (userId.size() + 1);

		return (int)(p - (uint8_t *)pBuf);
	}







	
public:
	uint32_t magic;
	time_t t;
	int accessMode;
	std::string userId;
};



class CAccessRecordPacker{
public:
	CAccessRecordPacker(){

	}

	CAccessRecordPacker(void * pBuf,uint32_t nBufSize){
		load(pBuf,nBufSize);
	}

	virtual ~CAccessRecordPacker(){

	}

	uint32_t size(){
		std::unique_lock<std::mutex> locker(m_stMutex);
		uint32_t nSize = 0;
		for(auto & e : m_lRecordList){
			nSize += e.size();
		}

		return nSize;
	}

	bool append(CAccessRecord & record){
		std::unique_lock<std::mutex> locker(m_stMutex);
		m_lRecordList.push_back(record);
		return true;
	}

	bool append(time_t _t,int _accessMode,std::string & _userId){
		CAccessRecord  record(_t,_accessMode,_userId);
		return append(record);
	}

	bool append(time_t _t,int _accessMode,std::string && _userId){
		CAccessRecord  record(_t,_accessMode,_userId);
		return append(record);
	}

	bool empty(){
		std::unique_lock<std::mutex> locker(m_stMutex);
		return m_lRecordList.empty();
	}



	int pack(void * pPacketBuf,uint32_t nPacketBufSize){
		if(NULL == pPacketBuf){
			DEBUG_ERROR("pPacketBuf is NULL!\n");
			return -1;
		}


		if(nPacketBufSize < 8){
			DEBUG_ERROR("invalid nPacketBufSize %d\n",nPacketBufSize);
			return -1;
		}

		std::unique_lock<std::mutex> locker(m_stMutex);
		uint8_t * p = (uint8_t *)pPacketBuf;
		uint32_t nFreeSize = nPacketBufSize;
		for(auto & e : m_lRecordList){
			if(e.size() > nFreeSize){
				DEBUG_ERROR("nPacketBufSize small?(%d)\n",nFreeSize);
				return -1;
			}

			int ret = e.pack(p,nFreeSize);
			if(ret <= 0){
				DEBUG_ERROR("BUG IN HERE!!!,CAccessRecord failed!\n");
				return -1;
			}

			if((uint32_t)ret > nFreeSize){
				DEBUG_ERROR("BUG IN HERE!!! invalid pack size  %d > %d\n",
					ret,nFreeSize);
				return -1;
			}
			p += ret;
			nFreeSize -= ret;
		}


		return (nPacketBufSize - nFreeSize);
	}


	std::tuple<std::shared_ptr<uint8_t>,uint32_t> pack(){
		std::shared_ptr<uint8_t> ptr;
		uint32_t nBufSize = size();
		std::tuple<std::shared_ptr<uint8_t>,uint32_t > result = std::make_tuple(ptr,nBufSize);
		if(!nBufSize){
			return result;
		}

		ptr.reset(new uint8_t[nBufSize],[](uint8_t * p){ delete []p;});
		result = std::make_tuple(ptr,nBufSize);
		int ret = pack(ptr.get(),nBufSize);
		if(ret != (int)nBufSize){
			DEBUG_ERROR("BUG IN HERE!!!....\n");
		}
		return result;
	}

	
	bool load(void * pBuf,uint32_t nBufSize){
		if(NULL == pBuf){
			DEBUG_ERROR("pBuf is NULL!\n");
			return false;
		}
		std::unique_lock<std::mutex> locker(m_stMutex);
		m_lRecordList.clear();
		uint8_t * p = (uint8_t *)pBuf;
		if(0 == nBufSize ){
			return true;
		}
		for(p = (uint8_t *)pBuf; p < (uint8_t *)pBuf + nBufSize;){
			uint32_t * magic = (uint32_t *)p;
			if(CONFIG_ACCESS_RECORD_MAGIC != *magic){
				return false;
			}
			p += sizeof(uint32_t);
			if(p >= (uint8_t *)pBuf + nBufSize){
				DEBUG_ERROR("%p >= %p + %x\n",p,pBuf,nBufSize);
				return false;
			}

			
			time_t t = *((time_t *)p);
			p += sizeof(time_t);
			if(p >= (uint8_t *)pBuf + nBufSize){
				DEBUG_ERROR("%p >= %p + %x\n",p,pBuf,nBufSize);
				return false;
			}

			
			int accessMode = *((int *)p);
			p += sizeof(int);
			if(p >= (uint8_t *)pBuf + nBufSize){
				DEBUG_ERROR("%p >= %p + %x\n",p,pBuf,nBufSize);
				return false;
			}
			uint32_t nMaxSize = (uint32_t)((uint8_t *)pBuf + nBufSize - p);
			if(strnlen((char *)p,nMaxSize) >= nMaxSize){
				DEBUG_ERROR("Invalid userId!\n");
				return false;
			}
			std::string userId = (char *)p;
			p += (userId.size() + 1);
			if(p > (uint8_t *)pBuf + nBufSize){
				DEBUG_ERROR("%p >= %p + %x\n",p,pBuf,nBufSize);
				return false;
			}

			m_lRecordList.push_back(CAccessRecord(t,accessMode,userId));
		}

		return true;
	}





	void accessRecords(std::list<CAccessRecord> & lAccessRecords){
		std::unique_lock<std::mutex> locker(m_stMutex);
		lAccessRecords.clear();
		lAccessRecords = m_lRecordList;
	}



	uint32_t recordCount(){
		std::unique_lock<std::mutex> locker(m_stMutex);
		return m_lRecordList.size();
	}
private:
	std::mutex m_stMutex;
	std::list<CAccessRecord>		m_lRecordList;
	
};



























#endif //__CACCESS_RECORD_PACKER_H__

