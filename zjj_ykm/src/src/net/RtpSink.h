#ifndef _MEDIA_SINK_H_
#define _MEDIA_SINK_H_
#include <string>
#include <stdint.h>

#include "MediaSource.h"
#include "Event.h"
#include "UsageEnvironment.h"
#include "Rtp.h"


class RtpSink
{
public:
    typedef void (*SendPacketCallback)(void* arg1, void* arg2, RtpPacket* mediaPacket);

    RtpSink(UsageEnvironment* env, MediaSource* mediaSource, int payloadType);
    virtual ~RtpSink();

    virtual std::string getMediaDescription(uint16_t port) = 0;
    virtual std::string getAttribute() = 0;

    void setSendFrameCallback(SendPacketCallback cb, void* arg1, void* arg2);

protected:
    //virtual void handleFrame(AVFrame* frame) = 0;
    virtual int handleFrame(AVFrame*  frame) = 0;
    void sendRtpPacket(RtpPacket* packet);
    void start(int ms);
    void stop();

public:
    static void timeoutCallback(void*);
    static int SendFramedCallback(void*);

protected:
    UsageEnvironment* mEnv;
    MediaSource* mMediaSource;
    uint8_t mPayloadType;
    SendPacketCallback mSendPacketCallback;
    void* mArg1;
    void* mArg2;

    uint8_t mCsrcLen;
    uint8_t mExtension;
    uint8_t mPadding;
    uint8_t mVersion;
    uint8_t mMarker;
    uint16_t mSeq;
    uint32_t mTimestamp;
    uint32_t mSSRC;

private:
    TimerEvent* mTimerEvent;
    Timer::TimerId mTimerId;
};

#endif //_MEDIA_SINK_H_