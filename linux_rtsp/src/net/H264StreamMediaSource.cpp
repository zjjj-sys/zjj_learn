#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "net/H264StreamMediaSource.h"
#include "base/Logging.h"
 

H264StreamMediaSource* H264StreamMediaSource::createNew(UsageEnvironment* env)
{
    return new H264StreamMediaSource(env);
   
}

H264StreamMediaSource::H264StreamMediaSource(UsageEnvironment* env) :MediaSource(env)
{
   
    setFps(30); //设置视频帧数 来算时间戳

    for(int i = 0; i < DEFAULT_FRAME_NUM; ++i)
        mEnv->threadPool()->addTask(mTask);
}

H264StreamMediaSource::~H264StreamMediaSource()
{
}

//读取文件数据并把数据加入输出的视频帧队列
void H264StreamMediaSource::readFrame()
{
    MutexLockGuard mutexLockGuard(mMutex);
    //std::lock_guard<std::mutex> lck(M_mutex);
    if(mAVFrameInputQueue.empty())
        return;

    AVFrame* frame = mAVFrameInputQueue.front();  //默认是缓存4个视频帧 发送完一帧后才会从输出队列把AVFrame实例重新加入输入队列
    // insert stream



    //将获取的frame加入到输出队列
    mAVFrameInputQueue.pop();
    mAVFrameOutputQueue.push(frame);
    
}


