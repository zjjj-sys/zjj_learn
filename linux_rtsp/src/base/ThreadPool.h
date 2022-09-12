#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "base/Thread.h"


class ThreadPool
{
public:
    class Task
    {
    public:
        
        typedef void (*TaskCallback)(void*);
        Task() { };
        
        void setTaskCallback(TaskCallback cb, void* arg) {
            mTaskCallback = cb; mArg = arg;
        }

        void handle() { 
            if(mTaskCallback) 
                mTaskCallback(mArg); 
        }
        void operator=(const Task& task){
            this->mTaskCallback = task.mTaskCallback;
            this->mArg = task.mArg;
        }
    private:
        void (*mTaskCallback)(void*);
        void* mArg;
    };

    static ThreadPool* createNew(int num);
    
    ThreadPool(int num);
    ~ThreadPool();

    void addTask(Task& task);

    std::mutex& get_mutex()
    {
        return m_mutex;
    }

private:
    class MThread : public Thread
    {
    protected:
        virtual void run(void *arg);
    };

    void createThreads();
    void cancelThreads();
    void handleTask();

private:
    std::queue<Task> mTaskQueue;
    
    std::mutex m_mutex;
    std::condition_variable m_condition;
   
    std::vector<MThread> mThreads;
    bool mQuit;
};

#endif //_THREADPOOL_H_