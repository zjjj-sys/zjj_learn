#ifndef _MEDIA_SOURCE_H_
#define _MEDIA_SOURCE_H_
#include <queue>
#include <stdint.h>
#include <mutex>
#include <condition_variable>
#include "UsageEnvironment.h"
#include "Mutex.h"

#define FRAME_MAX_SIZE (512*1024) //512k
#define DEFAULT_FRAME_NUM 3

class AVFrame
{
public:
    AVFrame() :mBuffer(new uint8_t[FRAME_MAX_SIZE]),mFrameSize(0),key_frame(0),m_ftimestamp(0)
    { }

    ~AVFrame()
    { delete mBuffer; }

    uint8_t* mBuffer;
    uint8_t* mFrame;
    int mFrameSize;
    int key_frame;
    unsigned int m_ftimestamp;
    
};

class MediaSource
{
public:
    virtual ~MediaSource();
    //std::mutex M_mutex;
    AVFrame* getFrame();
    void putFrame(AVFrame* frame);
    int getFps() const { return mFps; }

protected:
    MediaSource(UsageEnvironment* env);
    virtual void readFrame() = 0;
    void setFps(int fps) { mFps = fps; }

private:
    static void taskCallback(void*);

protected:
    UsageEnvironment* mEnv;
    AVFrame mAVFrames[DEFAULT_FRAME_NUM];
    std::queue<AVFrame*> mAVFrameInputQueue;
    std::queue<AVFrame*> mAVFrameOutputQueue;
    Mutex* mMutex;
    
    ThreadPool::Task mTask;
    int mFps;
};

#endif //_MEDIA_SOURCE_H_