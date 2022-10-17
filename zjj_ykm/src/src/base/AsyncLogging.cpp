#include <stdio.h>
#include <assert.h>
#include <chrono>
#include "AsyncLogging.h"
#include "Logging.h"
 

AsyncLogging* AsyncLogging::mAsyncLogging = NULL;

AsyncLogging::AsyncLogging(std::string file) :
    mFile(file),
    mRun(true)
{
    

    mFp = fopen(mFile.c_str(), "w");
    assert(mFp >= 0);

    for(int i = 0; i < BUFFER_NUM; ++i)
        mFreeBuffer.push(&mBuffer[i]);

    mCurBuffer = mFreeBuffer.front();

    start(NULL);
}

AsyncLogging::~AsyncLogging()
{
    for(int i = 0; i < (int)mFlushBuffer.size(); ++i)
    {
        LogBuffer* buffer = mFlushBuffer.front();
        fwrite(buffer->data(), 1, buffer->length(), mFp);
        mFlushBuffer.pop();
    }

    fwrite(mCurBuffer->data(), 1, mCurBuffer->length(), mFp);

    fflush(mFp);
    fclose(mFp);

    mRun = false;
    m_condition.notify_all();
   
}

AsyncLogging* AsyncLogging::instance()
{
    if(!mAsyncLogging)
    {
        mAsyncLogging = new AsyncLogging(Logger::getLogFile());
    }

    return mAsyncLogging;
}

void AsyncLogging::append(const char* logline, int len)
{
    std::unique_lock<std::mutex> lck(m_mutex);
    
    if(mCurBuffer->avail() > len)
    {
        mCurBuffer->append(logline, len);
    }
    else
    {
        mFreeBuffer.pop();
        mFlushBuffer.push(mCurBuffer);

        /* 如果缓存区已经用完，那么就睡眠等待 */
        while(mFreeBuffer.empty())
        {
            m_condition.notify_one();
            m_condition.wait(lck);
            
        }
        
        mCurBuffer = mFreeBuffer.front();
        mCurBuffer->append(logline, len);
        m_condition.notify_one();
        //mCond->signal();
    }
}

void AsyncLogging::run(void *arg)
{
    while(mRun)
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        std::cv_status ret = m_condition.wait_for(lck,std::chrono::seconds(3));
        
        if(mRun == false)
            break;

        if(ret == std::cv_status::timeout) //signal
        {
            bool empty = mFreeBuffer.empty();
            int bufferSize = mFlushBuffer.size();
            for(int i = 0; i < bufferSize; ++i)
            {
                LogBuffer* buffer = mFlushBuffer.front();
                fwrite(buffer->data(), 1, buffer->length(), mFp);
                mFlushBuffer.pop();
                buffer->reset();
                mFreeBuffer.push(buffer);
                fflush(mFp);
            }

            if(empty)
                m_condition.notify_one();
            
        }
        else //timeout
        {
            if(mCurBuffer->length() == 0)
                continue;
            fwrite(mCurBuffer->data(), 1, mCurBuffer->length(), mFp);
            mCurBuffer->reset();
            fflush(mFp);
        }
    }
}