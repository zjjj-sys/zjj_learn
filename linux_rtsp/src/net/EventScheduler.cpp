#include <sys/eventfd.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>

#include "net/EventScheduler.h"
#include "net/poller/SelectPoller.h"
#include "net/poller/PollPoller.h"
#include "net/poller/EPollPoller.h"
#include "base/Logging.h"
 

EventScheduler* EventScheduler::createNew(PollerType type)
{
    if(type != POLLER_SELECT && type != POLLER_POLL && type != POLLER_EPOLL)
        return NULL;

    return new EventScheduler(type);
   
}

EventScheduler::EventScheduler(PollerType type) :mQuit(false)//s,mWakeupFd(fd)
{
    switch (type)
    {
    case POLLER_SELECT:
        mPoller = SelectPoller::createNew();
        break;

    case POLLER_POLL:
        mPoller = PollPoller::createNew();
        break;
    
    case POLLER_EPOLL:
        mPoller = EPollPoller::createNew();
        break;

    default:
        _exit(-1);
        break;
    }

    mTimerManager = TimerManager::createNew(mPoller);


}

EventScheduler::~EventScheduler()
{
    
    delete mTimerManager;
    delete mPoller;
   
}

bool EventScheduler::addTriggerEvent(TriggerEvent* event)
{
    mTriggerEvents.push_back(event);
    
    return true;
}

//设置定时器事件的触发间隔
Timer::TimerId EventScheduler::addTimedEventRunEvery(TimerEvent* event, Timer::TimeInterval interval)
{
    Timer::Timestamp when = Timer::getCurTime();
    when += interval;
    
    return mTimerManager->addTimer(event, when, interval);
}

bool EventScheduler::removeTimedEvent(Timer::TimerId timerId)
{
    return mTimerManager->removeTimer(timerId);
}

bool EventScheduler::addIOEvent(IOEvent* event)
{
    return mPoller->addIOEvent(event);
}

bool EventScheduler::updateIOEvent(IOEvent* event)
{
    return mPoller->updateIOEvent(event);
}

bool EventScheduler::removeIOEvent(IOEvent* event)
{
    return mPoller->removeIOEvent(event);
}
//主线程一直循环
void EventScheduler::loop()
{
    while(mQuit != true)
    {
        this->handleTriggerEvents(); //优先处理触发的关闭事件
        mPoller->handleEvent();
    }
}
//处理触发事件的事件
void EventScheduler::handleTriggerEvents()
{
    if(!mTriggerEvents.empty())
    {
        for(std::vector<TriggerEvent*>::iterator it = mTriggerEvents.begin();
            it != mTriggerEvents.end(); ++it)
        {
            (*it)->handleEvent();
        }

        mTriggerEvents.clear();
    }
}

