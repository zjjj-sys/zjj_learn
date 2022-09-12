#include "base/ThreadPool.h"
#include "base/Logging.h"
#include <unistd.h>
#include <iostream>
ThreadPool* ThreadPool::createNew(int num)
{
    return new ThreadPool(num);
    
}

ThreadPool::ThreadPool(int num) :
    mThreads(num),
    mQuit(false)
{
    
    createThreads();
}

ThreadPool::~ThreadPool()
{
    cancelThreads();
    
   
}

void ThreadPool::addTask(ThreadPool::Task& task)
{
    std::unique_lock<std::mutex> lck(m_mutex);
    
    mTaskQueue.push(task);
    
    m_condition.notify_one();
   
}

void ThreadPool::handleTask()
{
   
    //LOG_INFO("handle TASK:Inside Thread :: Thread_PID %lu Thread_id  : %lu\n",getpid(),pthread_self());
    while(mQuit != true)
    {
        Task task;
        {
            std::unique_lock<std::mutex> lck(m_mutex);
            
            if(mTaskQueue.empty())
                m_condition.wait(lck);
        
            if(mQuit == true)
                break;

            if(mTaskQueue.empty())
                continue;

            task = mTaskQueue.front();

            mTaskQueue.pop();
        }
        task.handle();
    }
}

void ThreadPool::createThreads()
{
    std::lock_guard<std::mutex> lck(m_mutex);

    for(std::vector<MThread>::iterator it = mThreads.begin(); it != mThreads.end(); ++it)
        (*it).start(this);
}

void ThreadPool::cancelThreads()
{
    std::unique_lock<std::mutex> lck(m_mutex);
    
    mQuit = true;
    m_condition.notify_all();
    
    for(std::vector<MThread>::iterator it = mThreads.begin(); it != mThreads.end(); ++it)
        (*it).join();

    mThreads.clear();
}

void ThreadPool::MThread::run(void* arg)
{
    ThreadPool* threadPool = (ThreadPool*)arg;
    threadPool->handleTask();    
}