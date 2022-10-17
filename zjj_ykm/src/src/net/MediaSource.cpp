#include "MediaSource.h"
#include "Logging.h"

#include <iostream>
MediaSource::MediaSource(UsageEnvironment *env) : mEnv(env)
{
    mMutex = Mutex::createNew();

    for (int i = 0; i < DEFAULT_FRAME_NUM; ++i)
    {
        mAVFrameInputQueue.push(&mAVFrames[i]);
        mTask.setTaskCallback(taskCallback, this);
    }
}

MediaSource::~MediaSource()
{
    delete mMutex;
}

//获取发送队列的视频帧数据
AVFrame *MediaSource::getFrame()
{
    MutexLockGuard mutexLockGuard(mMutex);
    //std::lock_guard<std::mutex> lck(M_mutex);
    
    if (mAVFrameOutputQueue.empty())
    {
        return NULL;
    }

    AVFrame *frame = mAVFrameOutputQueue.front();
    mAVFrameOutputQueue.pop();

    return frame;
}

//把已经发送过的AVFrame实例重新加入缓存队列
void MediaSource::putFrame(AVFrame *frame)
{
    MutexLockGuard mutexLockGuard(mMutex);
    //std::lock_guard<std::mutex> lck(M_mutex);
    mAVFrameInputQueue.push(frame);
    mEnv->threadPool()->addTask(mTask);
}

void MediaSource::taskCallback(void *arg)
{
    MediaSource *source = (MediaSource *)arg;
    source->readFrame();
}
