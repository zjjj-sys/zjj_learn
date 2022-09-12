#ifndef _EVENT_SCHEDULER_H_
#define _EVENT_SCHEDULER_H_
#include <vector>
#include <queue>
#include <mutex>
#include "net/poller/Poller.h"
#include "net/Timer.h"

class EventScheduler
{
public:
    typedef void (*Callback)(void*);

    enum PollerType
    {
        POLLER_SELECT,
        POLLER_POLL,
        POLLER_EPOLL
    };

    static EventScheduler* createNew(PollerType type);

    EventScheduler(PollerType type);
    virtual ~EventScheduler();

    bool addTriggerEvent(TriggerEvent* event);
    Timer::TimerId addTimedEventRunEvery(TimerEvent* event, Timer::TimeInterval interval);
    bool removeTimedEvent(Timer::TimerId timerId);
    bool addIOEvent(IOEvent* event);
    bool updateIOEvent(IOEvent* event);
    bool removeIOEvent(IOEvent* event);

    void loop();


private:
    void handleTriggerEvents();
    static void handleReadCallback(void*);
    void handleRead();

private:
    bool mQuit;
    Poller* mPoller;
    TimerManager* mTimerManager;
    std::vector<TriggerEvent*> mTriggerEvents;
   
    
    std::mutex m_mutex;
};

#endif //_EVENT_SCHEDULER_H_