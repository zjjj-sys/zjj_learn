#ifndef H264STREAM_MEDIA_SOURCE_H_
#define H264STREAM_MEDIA_SOURCE_H_
#include <string>

#include "net/UsageEnvironment.h"
#include "net/MediaSource.h"
#include "base/ThreadPool.h"

class H264StreamMediaSource : public MediaSource
{
public:
    static H264StreamMediaSource* createNew(UsageEnvironment* env);
    
    H264StreamMediaSource(UsageEnvironment* env);
    ~H264StreamMediaSource();

protected:
    virtual void readFrame();

};

#endif //H264STREAM_MEDIA_SOURCE_H__