#ifndef _MEDIA_SOURCE_H_
#define _MEDIA_SOURCE_H_
#include <queue>
#include <stdint.h>
#include <mutex>
#include <condition_variable>
#include "net/UsageEnvironment.h"
#include "base/Mutex.h"

#define FRAME_MAX_SIZE (1024*1024)
#define DEFAULT_FRAME_NUM 4

class AVFrame
{
public:
    AVFrame() :
        mBuffer(new uint8_t[FRAME_MAX_SIZE]),
        mFrameSize(0)
    { }

    ~AVFrame()
    { delete mBuffer; }

    uint8_t* mBuffer;
    uint8_t* mFrame;
    int mFrameSize;
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