#ifndef _AAC_RTP_SINK_H_
#define _AAC_RTP_SINK_H_

#include "UsageEnvironment.h"
#include "RtpSink.h"
#include "MediaSource.h"

class AACRtpSink : public RtpSink
{
public:
    static AACRtpSink* createNew(UsageEnvironment* env, MediaSource* mediaSource);;
    
    AACRtpSink(UsageEnvironment* env, MediaSource* mediaSource, int payloadType);
    virtual ~AACRtpSink();

    virtual std::string getMediaDescription(uint16_t port);
    virtual std::string getAttribute();

protected:
    //virtual void handleFrame(AVFrame* frame);
    virtual int handleFrame(AVFrame* frame);
private:
    RtpPacket mRtpPacket;
    uint32_t mSampleRate;   // 采样频率
    uint32_t mChannels;         // 通道数
    int mFps;
};

#endif //_AAC_RTP_SINK_H_