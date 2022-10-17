#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "H264FileMediaSource.h"
#include "Logging.h"
 

static inline int startCode3(uint8_t* buf);
static inline int startCode4(uint8_t* buf);

H264FileMediaSource *H264FileMediaSource::createNew(UsageEnvironment *env, CShmBuf *VideoConsume)
{
    return new H264FileMediaSource(env, VideoConsume);
}

H264FileMediaSource::H264FileMediaSource(UsageEnvironment *env, CShmBuf *VideoConsume) : MediaSource(env),mConsume(VideoConsume)
{

    setFps(25); //设置视频帧数 来算时间戳
    tagframe = (FRAME *)malloc(sizeof(FRAME) + FRAME_MAX_SIZE);
    memset(tagframe, 0, sizeof(FRAME) + FRAME_MAX_SIZE);
    for (int i = 0; i < DEFAULT_FRAME_NUM; ++i)
    {
        mEnv->threadPool()->addTask(mTask);
    }
}

H264FileMediaSource::~H264FileMediaSource()
{
    free(tagframe);
    tagframe = NULL;
}

//读取数据并把数据加入输出的视频帧队列
void H264FileMediaSource::readFrame()
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
        frame->m_ftimestamp = tagframe->timestamp;
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

static inline int startCode3(uint8_t* buf)
{
    if(buf[0] == 0 && buf[1] == 0 && buf[2] == 1)
        return 1;
    else
        return 0;
}

static inline int startCode4(uint8_t* buf)
{
    if(buf[0] == 0 && buf[1] == 0 && buf[2] == 0 && buf[3] == 1)
        return 1;
    else
        return 0;
}

static uint8_t* findNextStartCode(uint8_t* buf, int len)
{
    int i;

    if(len < 3)
        return NULL;

    for(i = 0; i < len-3; ++i)
    {
        if(startCode3(buf) || startCode4(buf))
            return buf;
        
        ++buf;
    }

    if(startCode3(buf))
        return buf;

    return NULL;
}

int H264FileMediaSource::getFrameFromH264File(int fd, uint8_t* frame, int size)
{
    int rSize, frameSize;
    uint8_t* nextStartCode;

    if(fd < 0)
        return fd;

    rSize = read(fd, frame, size);
    if(!startCode3(frame) && !startCode4(frame))
        return -1;
    
    nextStartCode = findNextStartCode(frame+3, rSize-3);
    if(!nextStartCode)
    {
        lseek(fd, 0, SEEK_SET);
        frameSize = rSize;
    }
    else
    {
        frameSize = (nextStartCode-frame);
        lseek(fd, frameSize-rSize, SEEK_CUR);
    }

    return frameSize;
}
