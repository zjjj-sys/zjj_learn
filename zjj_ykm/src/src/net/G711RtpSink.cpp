#include <string>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "G711RtpSink.h"
#include "Logging.h"
 


G711RtpSink* G711RtpSink::createNew(UsageEnvironment* env, MediaSource* mediaSource)
{
    return new G711RtpSink(env, mediaSource, RTP_PAYLOAD_TYPE_PCMA);
    
}

G711RtpSink::G711RtpSink(UsageEnvironment* env, MediaSource* mediaSource, int payloadType) :
    RtpSink(env, mediaSource, payloadType),
    mSampleRate(8000),
    mChannels(1),
    mFps(mediaSource->getFps())
{
    mMarker = 1;
    //start(1000/mFps);
}

G711RtpSink::~G711RtpSink()
{

}

std::string G711RtpSink::getMediaDescription(uint16_t port)
{
    char buf[100] = { 0 };
    sprintf(buf, "m=audio %hu RTP/AVP %d", port, mPayloadType);

    return std::string(buf);
}



std::string G711RtpSink::getAttribute()
{
    char buf[500] = { 0 };
    sprintf(buf, "a=rtpmap:8 PCMA/%u/%u\r\n", mSampleRate, mChannels);
    return std::string(buf);
}
#if 0
void G711RtpSink::handleFrame(AVFrame* frame)
{
    RtpHeader* rtpHeader = mRtpPacket.mRtpHeadr;
    int frameSize = frame->mFrameSize; 
    
    if(frameSize == 0)
    {
        usleep(5000);
        return ;
    }
    //rtpHeader->timestamp = htonl(frame->m_ftimestamp);
    //mTimestamp = frame->m_ftimestamp;
    //LOG_INFO("G711_Timestamp: %u\n",mTimestamp);
    memcpy(rtpHeader->payload, frame->mFrame, frameSize);
    mRtpPacket.mSize = frameSize ;

    sendRtpPacket(&mRtpPacket);
    
    mSeq++;
    
    mTimestamp += mSampleRate * (1000 / mFps) / 1000;
    
}
#endif

int G711RtpSink::handleFrame(AVFrame* frame)
{
    uint32_t interval = 0;
    RtpHeader* rtpHeader = mRtpPacket.mRtpHeadr;
    int frameSize = frame->mFrameSize; 
    
    if(frameSize == 0)
    {
        return 0;
    }
    interval = 8*(frame->m_ftimestamp - pretimestamp);
    pretimestamp = frame->m_ftimestamp;
    
    memcpy(rtpHeader->payload, frame->mFrame, frameSize);
    mRtpPacket.mSize = frameSize ;

    sendRtpPacket(&mRtpPacket);
    
    mSeq++;

    mTimestamp += interval;
    //mTimestamp += mSampleRate * (1000 / mFps) / 1000;
    
    return frameSize;
    
}

