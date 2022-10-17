#ifndef __ABSTRACT_THREAD_H__
#define __ABSTRACT_THREAD_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>


#include <pthread.h>




using std::string;


class CAbstractThread
{
public:
	CAbstractThread(string name,void * args);
	virtual ~CAbstractThread();
	bool start();
	bool stop();
	bool isStop();
	const std::string & name();
public:
	static void * ThreadWorkFunc(void * args);

	
public:
	virtual bool ThreadWorkRoutine() = 0;
	bool __ThreadWorkRoutine__() ;

private:
	string 		m_strName;
	void * 		m_pArgs;
	bool   		m_bIsStoped;
	pthread_t	m_nWorkThreadId;

};





















#endif //__ABSTRACT_THREAD_H__

