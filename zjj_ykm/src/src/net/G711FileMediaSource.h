#ifndef _G711FILE_MEDIA_SOURCE_H_
#define _G711FILE_MEDIA_SOURCE_H_
#include <string>

#include "UsageEnvironment.h"
#include "MediaSource.h"
#include "ThreadPool.h"
#include "CShmBuf.h"

class G711FileMediaSource : public MediaSource
{
public:
    static G711FileMediaSource* createNew(UsageEnvironment* env, CShmBuf* VideoConsume);
    
    G711FileMediaSource(UsageEnvironment* env, CShmBuf* VideoConsume);
    ~G711FileMediaSource();

protected:
    virtual void readFrame();

private:
    //int getFrameFromH265File(int fd, uint8_t* frame, int size);

private:
    CShmBuf* mConsume;
    FRAME* tagframe;
    int mFd;
};

#endif //_H265FILE_MEDIA_SOURCE_H_