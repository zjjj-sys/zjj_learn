#include <arpa/inet.h>

#include "RtpSink.h"
#include "Logging.h"
#include <unistd.h>
#include <iostream>
RtpSink::RtpSink(UsageEnvironment* env, MediaSource* mediaSource, int payloadType) :
    mEnv(env),
    mMediaSource(mediaSource),
    mPayloadType(payloadType),
    mSendPacketCallback(NULL),
    mCsrcLen(0),
    mExtension(0),
    mPadding(0),
    mVersion(RTP_VESION),
    
    mMarker(0),
    mSeq(0),
    mTimestamp(0),
    mTimerId(0)
    
{
    mTimerEvent = TimerEvent::createNew(this);
    mTimerEvent->setTimeoutCallback(timeoutCallback);
    mSeq = rand();
    mSSRC = rand();
}

RtpSink::~RtpSink()
{
    mEnv->scheduler()->removeTimedEvent(mTimerId);
    delete mTimerEvent;
    delete mMediaSource;
   
}

//注册发送数据的回调函数
void RtpSink::setSendFrameCallback(SendPacketCallback cb, void* arg1, void* arg2)
{
    mSendPacketCallback = cb;
    mArg1 = arg1;
    mArg2 = arg2;
}

void RtpSink::sendRtpPacket(RtpPacket* packet)
{
    RtpHeader* rtpHead = packet->mRtpHeadr;
    rtpHead->csrcLen = mCsrcLen;
    rtpHead->extension = mExtension;
    rtpHead->padding = mPadding;
    rtpHead->version = mVersion;
    rtpHead->payloadType = mPayloadType;
    rtpHead->marker = mMarker;
    rtpHead->seq = htons(mSeq);
    rtpHead->timestamp = htonl(mTimestamp);
    
    rtpHead->ssrc = htonl(mSSRC);
    
    packet->mSize += RTP_HEADER_SIZE;
    
    if(mSendPacketCallback)
    {
        mSendPacketCallback(mArg1, mArg2, packet);
    }
}
//定时器时间到达后的触发事件函数
void RtpSink::timeoutCallback(void* arg)
{
    RtpSink* rtpSink = (RtpSink*)arg;
    AVFrame* frame = rtpSink->mMediaSource->getFrame();
    if(!frame)
    {
        return;
    }

    rtpSink->handleFrame(frame);   
    rtpSink->mMediaSource->putFrame(frame);
    
}
//test sendframe
int RtpSink::SendFramedCallback(void* arg)
{
    int Ret = 0 ;
    RtpSink* rtpsink = (RtpSink*)arg;
    AVFrame* frame = rtpsink->mMediaSource->getFrame();
    if(!frame)
    {
        return 0;
    }
    Ret = rtpsink->handleFrame(frame);
    rtpsink->mMediaSource->putFrame(frame);
    return Ret;
}

void RtpSink::start(int ms)
{
    mTimerId = mEnv->scheduler()->addTimedEventRunEvery(mTimerEvent, ms);
}

void RtpSink::stop()
{
    mEnv->scheduler()->removeTimedEvent(mTimerId);
}