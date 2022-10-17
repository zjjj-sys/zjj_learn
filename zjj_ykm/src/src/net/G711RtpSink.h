#ifndef _G711_RTP_SINK_H_
#define _G711_RTP_SINK_H_

#include "UsageEnvironment.h"
#include "RtpSink.h"
#include "MediaSource.h"

class G711RtpSink : public RtpSink
{
public:
    static G711RtpSink* createNew(UsageEnvironment* env, MediaSource* mediaSource);
    
    G711RtpSink(UsageEnvironment* env, MediaSource* mediaSource, int payloadType);
    virtual ~G711RtpSink();

    virtual std::string getMediaDescription(uint16_t port);
    virtual std::string getAttribute();

protected:
    virtual void handleFrame(AVFrame* frame);

private:
    RtpPacket mRtpPacket;
    uint32_t mSampleRate;   // 采样频率
    uint32_t mChannels;         // 通道数
    int mFps;
};

#endif //_AAC_RTP_SINK_H_