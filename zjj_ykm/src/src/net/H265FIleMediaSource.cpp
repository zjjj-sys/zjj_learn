#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>
#include <iostream>
#include "H265FIleMediaSource.h"
#include "Logging.h"



H265FileMediaSource *H265FileMediaSource::createNew(UsageEnvironment *env, CShmBuf *VideoConsume)
{
    return new H265FileMediaSource(env, VideoConsume);
}

H265FileMediaSource::H265FileMediaSource(UsageEnvironment *env, CShmBuf *VideoConsume) : MediaSource(env),mConsume(VideoConsume)
{

    //setFps(25); //设置视频帧数 来算时间戳
    tagframe = (FRAME *)malloc(sizeof(FRAME) + FRAME_MAX_SIZE);
    memset(tagframe, 0, sizeof(FRAME) + FRAME_MAX_SIZE);
    for (int i = 0; i < DEFAULT_FRAME_NUM; ++i)
    {
        mEnv->threadPool()->addTask(mTask);
    }
}

H265FileMediaSource::~H265FileMediaSource()
{
    free(tagframe);
    tagframe = NULL;
}

#if 0
//读取文件数据并把数据加入输出的视频帧队列
void H265FileMediaSource::readFrame()
{
    MutexLockGuard mutexLockGuard(mMutex);
    uint32_t retsize = 0;
    uint32_t payload_len = 0;
    if (mAVFrameInputQueue.empty())
    {
        return;
    }

    AVFrame *frame = mAVFrameInputQueue.front(); //默认是缓存4个视频帧 发送完一帧后才会从输出队列把AVFrame实例重新加入输入队列
    retsize = mConsume->getFrame(tagframe, FRAME_MAX_SIZE);
    if (retsize < 0)
    {
        return;
    }
    else if (retsize == 0)
    {
        //usleep(5*1000);
        frame->mFrameSize = 0;
        mAVFrameInputQueue.pop();
        mAVFrameOutputQueue.push(frame);
    }
    else
    {
        payload_len = tagframe->data_size;
        frame->mFrameSize = payload_len - 4;
        frame->m_ftimestamp = tagframe->timestamp;
        frame->key_frame = tagframe->key_frame;
        if(tagframe->key_frame == 1)
        {
            std::stringstream ss;
            for(int i=0;i<100;i++)
            {
                ss << std::setw(2)<<std::hex <<(unsigned int)(unsigned char)tagframe->data[i];
            }
            std::cout <<"key_frame data "<<ss.str()<<std::endl;
            LOG_INFO("where is keyframe : %d success\n",tagframe->key_frame);
        }
        
        memcpy(frame->mBuffer, tagframe->data, payload_len);
        memset(tagframe, 0, sizeof(FRAME) + FRAME_MAX_SIZE);
        frame->mFrame = frame->mBuffer + 4;
        mAVFrameInputQueue.pop();
        mAVFrameOutputQueue.push(frame);
    }
}
#endif

//#if 0
//读取文件数据并把数据加入输出的视频帧队列
void H265FileMediaSource::readFrame()
{
    MutexLockGuard mutexLockGuard(mMutex);
    uint32_t retsize = 0;
    uint32_t payload_len = 0;
    if (mAVFrameInputQueue.empty())
    {
        return;
    }

    AVFrame *frame = mAVFrameInputQueue.front(); //默认是缓存4个视频帧 发送完一帧后才会从输出队列把AVFrame实例重新加入输入队列
    retsize = mConsume->getFrame(tagframe, FRAME_MAX_SIZE);
    if (retsize < 0)
    {
        return;
    }
    else if (retsize == 0)
    {
        
        frame->mFrameSize = 0;
        mAVFrameInputQueue.pop();
        mAVFrameOutputQueue.push(frame);
        usleep(10*1000);
    }
    else
    {
        payload_len = tagframe->data_size;
        frame->m_ftimestamp = (u_int32_t)tagframe->timestamp;
        frame->key_frame = tagframe->key_frame;
        memcpy(frame->mBuffer, tagframe->data, payload_len);
        if(tagframe->key_frame == 1)
        {
        
            frame->mFrameSize = payload_len;
            frame->mFrame = frame->mBuffer ;
        }
        else
        {
            frame->mFrameSize = payload_len - 4;
            frame->mFrame = frame->mBuffer + 4;
        }
        memset(tagframe, 0, sizeof(FRAME) + FRAME_MAX_SIZE);
        mAVFrameInputQueue.pop();
        mAVFrameOutputQueue.push(frame);
    }
}
//#endif
