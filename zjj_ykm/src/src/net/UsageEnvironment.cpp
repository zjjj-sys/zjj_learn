#include <stdio.h>

#include "UsageEnvironment.h"
#include "Logging.h"

UsageEnvironment* UsageEnvironment::createNew(EventScheduler* scheduler, ThreadPool* threadPool)
{
    if(!scheduler)
        return NULL;
    
    return new UsageEnvironment(scheduler, threadPool);
    
}

UsageEnvironment::UsageEnvironment(EventScheduler* scheduler, ThreadPool* threadPool) :
    mScheduler(scheduler),
    mThreadPool(threadPool)
{

}

UsageEnvironment::~UsageEnvironment()
{

    LOG_ERROR("not correct quit:\n");
    delete mScheduler;
    mScheduler = NULL;
    delete mThreadPool;
    mThreadPool = NULL;
}

EventScheduler* UsageEnvironment::scheduler()
{
    return mScheduler;
}

ThreadPool* UsageEnvironment::threadPool()
{
    return mThreadPool;
}