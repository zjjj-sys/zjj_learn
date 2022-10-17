#ifndef __MSG_OBJECT_QUEUE_H__
#define __MSG_OBJECT_QUEUE_H__




#include <string>
#include <iostream>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <list>
#include <map>
#include <tuple>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <stdint.h>



template <typename T>
class CMsgObjectQueue
{
public:
	CMsgObjectQueue(uint32_t nMaxCount)
	{
		m_nMaxCount = nMaxCount;
		m_pCond		= new std::condition_variable();
	}
	virtual ~CMsgObjectQueue()
	{
		m_lQueueList.clear();
		if(m_pCond){
			delete m_pCond;
			m_pCond = NULL;
		}
		
	}
	bool push(std::shared_ptr<T> & ptr){
		{
		std::unique_lock<std::mutex>  locker(m_stMutex);
		if(m_lQueueList.size() >= m_nMaxCount){
			return false;
		}

		m_lQueueList.push_back(ptr);
		}

		m_pCond->notify_all();
	
		return true;
	}
	bool pop(std::shared_ptr<T> & ptr){
		std::unique_lock<std::mutex>  locker(m_stMutex);
		if(m_lQueueList.empty()){
			// wait_for : 1.release lock
			//            2.wait notify signal until timeout...
			//            3.get signal or timeout,exit with get lock..
			m_pCond->wait_for(locker,std::chrono::seconds(1));
			if(m_lQueueList.empty()){
			return false;
		}
		}

		ptr = m_lQueueList.front();
		m_lQueueList.pop_front();
		return true;
	}

	bool testAndPop(std::shared_ptr<T> & ptr){
		std::unique_lock<std::mutex>  locker(m_stMutex);
		if(m_lQueueList.empty()){
			return false;
		}

		ptr = m_lQueueList.front();
		m_lQueueList.pop_front();
		return true;
	}
	bool isEmpty(){
		std::unique_lock<std::mutex>  locker(m_stMutex);
		return m_lQueueList.empty();
	}
	bool isFull(){
		std::unique_lock<std::mutex>  locker(m_stMutex);
		return m_lQueueList.size() == m_nMaxCount;
	}
	bool clear(){
		std::unique_lock<std::mutex>  locker(m_stMutex);
		m_lQueueList.clear();
		return true;
	}

private:
	uint32_t m_nMaxCount;
	std::mutex m_stMutex;
	std::list<std::shared_ptr<T> > m_lQueueList;
	std::condition_variable * m_pCond;

};



#endif //__MSG_OBJECT_QUEUE_H__


