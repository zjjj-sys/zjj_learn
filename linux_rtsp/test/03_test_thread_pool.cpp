#include <unistd.h>

#include "base/ThreadPool.h"
#include "base/Logging.h"

static void threadTask(void*)
{
    LOG_INFO("run...\n");
    sleep(3);
}

int main(int argc, char* argv[])
{
    /* 默认是/dev/stdout */
    //Logger::setLogFile("xxx.log");

    ThreadPool* threadPool = ThreadPool::createNew(4);

    ThreadPool::Task task;
    task.setTaskCallback(threadTask, NULL);

    for(int i = 0; i < 20; ++i)
    {
        threadPool->addTask(task);
    }

    while(1)
    {
        LOG_INFO("main...\n");
        sleep(1);
    }

    return 0;
}