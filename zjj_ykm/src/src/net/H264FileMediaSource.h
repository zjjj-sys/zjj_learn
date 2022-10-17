#ifndef _H264FILE_MEDIA_SOURCE_H_
#define _H264FILE_MEDIA_SOURCE_H_
#include <string>

#include "UsageEnvironment.h"
#include "MediaSource.h"
#include "ThreadPool.h"
#include "CShmBuf.h"

class H264FileMediaSource : public MediaSource
{
public:
    static H264FileMediaSource* createNew(UsageEnvironment* env, CShmBuf* VideoConsume);
    
    H264FileMediaSource(UsageEnvironment* env, CShmBuf* VideoConsume);
    ~H264FileMediaSource();

protected:
    virtual void readFrame();

private:
    int getFrameFromH264File(int fd, uint8_t* frame, int size);

private:
    CShmBuf* mConsume;
    FRAME* tagframe;
    int mFd;
};

#endif //_H264FILE_MEDIA_SOURCE_H_