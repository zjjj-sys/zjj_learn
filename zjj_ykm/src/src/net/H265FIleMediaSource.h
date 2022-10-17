#ifndef _H265FILE_MEDIA_SOURCE_H_
#define _H265FILE_MEDIA_SOURCE_H_
#include <string>

#include "UsageEnvironment.h"
#include "MediaSource.h"
#include "ThreadPool.h"
#include "CShmBuf.h"

class H265FileMediaSource : public MediaSource
{
public:
    static H265FileMediaSource* createNew(UsageEnvironment* env, CShmBuf* VideoConsume);
    
    H265FileMediaSource(UsageEnvironment* env, CShmBuf* VideoConsume);
    ~H265FileMediaSource();

protected:
    virtual void readFrame();

private:
    int getFrameFromH265File(int fd, uint8_t* frame, int size);

private:
    CShmBuf* mConsume;
    FRAME* tagframe;
    int mFd;
};

#endif //_H265FILE_MEDIA_SOURCE_H_