#ifndef H265_RTPSINK_H_
#define H265_RTPSINK_H_
#include <stdint.h>
#include "RtpSink.h"

class H265RtpSink : public RtpSink
{
public:
    static H265RtpSink* createNew(UsageEnvironment* env, MediaSource* mediaSource);
    
    H265RtpSink(UsageEnvironment* env, MediaSource* mediaSource);
    virtual ~H265RtpSink();

    virtual std::string getMediaDescription(uint16_t port);
    virtual std::string getAttribute();
    //virtual void handleFrame(AVFrame* frame);
    virtual int handleFrame(AVFrame* frame);

    void sendhandleFrame(AVFrame* frame);

    void packframe(RtpPacket* packet);

private:
    RtpPacket mRtpPacket;
    int mClockRate;
    int mFps;
    //int mwriteindex;

};

#endif //H265_RTPSINK_H_