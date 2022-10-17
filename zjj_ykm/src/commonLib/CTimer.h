#ifndef _CTIMER_H__
#define _CTIMER_H__



#include <iostream>
#include <list>


#include <stdint.h>
#include <mutex>
#include <atomic>

using std::list;


#define MAX_SCHEDULE_PER_DAY 48

enum {
	ENUM_TIMER_EVENT_TYPE_ONESHOT 	= 0,
	ENUM_TIMER_EVENT_TYPE_PERIOD,
	ENUM_TIMER_EVENT_TYPE_SCHEDULE,
	ENUM_TIMER_EVENT_TYPE_BUTT,
};


typedef int (*CALLBACK_TIMER_EVENT_ENTER)(void * args);
typedef int (*CALLBACK_TIMER_EVENT_EXIT)(void * args);



typedef struct{
	uint64_t expire_ms ; //ms
}__attribute__((packed))TIMER_ONESHOT_EVENT;

typedef struct{
	uint64_t period_ms; // ms
	uint64_t base_ms; // just init it 0,don't modify it in run time...
}__attribute__((packed))TIMER_PERIOD_EVENT;



enum {
	Sun	= 0,
	Mon,
	Tue,
	Wed,
	Thu,
	Fri,
	Sat,
};


typedef struct{
	uint8_t wday;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
}__attribute__((packed))DAILY_SCHEDULE_TIME;

typedef struct{
	struct{
		uint32_t start;		//second of day
		uint32_t end;		//second of day
		int hasStart;
		int hasExit;
	}item[MAX_SCHEDULE_PER_DAY];
}DAILY_SCHEDULE; // daily schedule

typedef struct{
	DAILY_SCHEDULE day[7];//SUN MON THU、WED、THU、FRI、SAT
}__attribute__((packed))TIMER_SCHEDULE_EVENT;



typedef struct{
	int type;
	int timerId;
	CALLBACK_TIMER_EVENT_ENTER enter;
	CALLBACK_TIMER_EVENT_EXIT exit;
	uint8_t * private_data;        // private data
	void * args;
}__attribute__((packed))TIMER_EVENT;



class CTimer{
public:
	CTimer();
	virtual ~CTimer();

	void run(bool & bStop);

	// BUG in here,Do not invoke unregXXX in callback function @lifan
	// maybe broken list strcut...
	uint32_t regDelayEvent(uint64_t delayMs,CALLBACK_TIMER_EVENT_ENTER callbackFunc,void *args);
	bool 	unregDelayEvent(uint32_t timeId);


	uint32_t regPeroidEvent(uint64_t periodMs,CALLBACK_TIMER_EVENT_ENTER callbackFunc,void *args);
	bool	unregPeroidEvent(uint32_t timeId);

	uint32_t regScheduleEvent(TIMER_SCHEDULE_EVENT & schedule,
		CALLBACK_TIMER_EVENT_ENTER callbackFuncEnter,
		CALLBACK_TIMER_EVENT_EXIT  callbackFuncExit,
		void *args);
	bool	unregScheduleEvent(uint32_t timeId);

	static bool addDailySchedule(TIMER_SCHEDULE_EVENT & schedule,DAILY_SCHEDULE_TIME & start,
		DAILY_SCHEDULE_TIME & end);

	static bool DailyTimeToWeekSec(DAILY_SCHEDULE_TIME & time,uint32_t & weekSec);
	static bool WeekSecToDailyTime(uint32_t & weekSec,DAILY_SCHEDULE_TIME & time);
private:

	int add(TIMER_EVENT * event); // return timer_id
	bool remove(int timerId);


	
	int genTimerId();
	void lock();
	bool tryLock();
	void unlock();

private:	
	pthread_mutex_t m_lock;
	list<TIMER_EVENT * > m_lTimerEventList;
	std::atomic<uint32_t> m_nTimerId;

	list<TIMER_EVENT * > m_lTmpAddTimerEventList;
	list<uint32_t> m_lTmpDelTimerEventIdList;
};




















#endif //_CTIMER_H__

