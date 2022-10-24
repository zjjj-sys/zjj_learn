#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "G711FileMediaSource.h"
#include "Logging.h"
#include "audio_g711.h"
/* static inline int startCode3(uint8_t *buf);
static inline int startCode4(uint8_t *buf); */

G711FileMediaSource *G711FileMediaSource::createNew(UsageEnvironment *env, CShmBuf *VideoConsume)
{
    return new G711FileMediaSource(env, VideoConsume);
}

G711FileMediaSource::G711FileMediaSource(UsageEnvironment *env, CShmBuf *VideoConsume) : MediaSource(env),mConsume(VideoConsume)
{
    
    tagframe = (FRAME *)malloc(sizeof(FRAME) + FRAME_MAX_SIZE);
    //setFps(17);
    memset(tagframe, 0, sizeof(FRAME) + FRAME_MAX_SIZE);
    for (int i = 0; i < DEFAULT_FRAME_NUM; ++i)
    {
        mEnv->threadPool()->addTask(mTask);
    }
}

G711FileMediaSource::~G711FileMediaSource()
{
    free(tagframe);
    tagframe = NULL;
}


//读取文件数据并把数据加入输出的视频帧队列
void G711FileMediaSource::readFrame()
{
    MutexLockGuard mutexLockGuard(mMutex);
    uint32_t retsize = 0;
    uint32_t payload_len = 0;
    uint32_t ret_len = 0;
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
        usleep(20*1000);
    }
    else
    {
        payload_len = tagframe->data_size;
        frame->m_ftimestamp = (u_int32_t)tagframe->timestamp;

        frame->key_frame = tagframe->key_frame;
        //LOG_INFO("m_frame_time : %u\n",frame->m_ftimestamp);
        ret_len = ALawEncode(frame->mBuffer, (int16_t*)tagframe->data ,payload_len ); //音频G711A编码
        
        frame->mFrameSize = ret_len;
        frame->mFrame = frame->mBuffer ;

        memset(tagframe, 0, sizeof(FRAME) + FRAME_MAX_SIZE);
        mAVFrameInputQueue.pop();
        mAVFrameOutputQueue.push(frame);
    }
}
//#endif

