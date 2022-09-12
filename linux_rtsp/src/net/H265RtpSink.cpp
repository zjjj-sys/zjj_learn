#include <stdio.h>
#include <string.h>

#include "net/H265RtpSink.h"
#include "base/Logging.h"
 
#include <iostream>
H265RtpSink* H265RtpSink::createNew(UsageEnvironment* env, MediaSource* mediaSource)
{
    if(!mediaSource)
        return NULL;

    return new H265RtpSink(env, mediaSource);
    
}

H265RtpSink::H265RtpSink(UsageEnvironment* env, MediaSource* mediaSource) :
    RtpSink(env, mediaSource, RTP_PAYLOAD_TYPE_H264),
    mClockRate(90000),
    mFps(mediaSource->getFps())
{
    //start(1000/mFps);
}

H265RtpSink::~H265RtpSink()
{

}
//获取视频信息
std::string H265RtpSink::getMediaDescription(uint16_t port)
{
    char buf[100] = {0};
    sprintf(buf, "m=video %hu RTP/AVP %d", port, mPayloadType);

    return std::string(buf);
}
//获取视频属性
std::string H265RtpSink::getAttribute()
{
    char buf[100];
    sprintf(buf, "a=rtpmap:%d H265/%d\r\n", mPayloadType, mClockRate);
    sprintf(buf+strlen(buf), "a=framerate:%d", mFps);

    return std::string(buf);
}

//对frame 进行 rtp分包并发送
void H265RtpSink::handleFrame(AVFrame* frame)
{
    RtpHeader* rtpHeader = mRtpPacket.mRtpHeadr;
    uint8_t naluType = frame->mFrame[0];
    uint8_t type = (naluType & 0x7E)>>1 ;
    if(frame->mFrameSize <= RTP_MAX_PKT_SIZE)    //单一封包模式
    {
        memcpy(rtpHeader->payload, frame->mFrame, frame->mFrameSize);
        mRtpPacket.mSize = frame->mFrameSize;
        sendRtpPacket(&mRtpPacket);
        mSeq++;

        if (((naluType & 0x7E)>>1)== 32 || ((naluType & 0x7E)>>1 )== 33 || ((naluType & 0X7E)>>1)== 34 || ((naluType & 0X7E)>>1)== 39) // 如果是VPS SPS、PPS就不需要加时间戳
            return;
    }
    else
    {
        int pktNum = frame->mFrameSize / RTP_MAX_PKT_SIZE;       // 有几个完整的包
        int remainPktSize = frame->mFrameSize % RTP_MAX_PKT_SIZE; // 剩余不完整包的大小
        int pos = 2;
        
        rtpHeader->payload[0] = (naluType & 0x81) | (49<<1); 
        rtpHeader->payload[1] = frame->mFrame[1];
        rtpHeader->payload[2] = (type | 0x80);
        
        /* 发送完整的包 */
        for (int i = 0; i < pktNum; i++)
        {
            
            if (remainPktSize == 0 && i == pktNum - 1) //最后一包数据
                rtpHeader->payload[2] |= 0x40; // end

            memcpy(rtpHeader->payload+3, frame->mFrame+pos, RTP_MAX_PKT_SIZE);
            mRtpPacket.mSize = RTP_MAX_PKT_SIZE+3;
            
            sendRtpPacket(&mRtpPacket);

            mSeq++;
            pos += RTP_MAX_PKT_SIZE;
            rtpHeader->payload[2] &= ~0x80;
        }

        /* 发送剩余的数据 */
        if (remainPktSize > 0)
        {
            rtpHeader->payload[2] |= 0x40; //end
            
            memcpy(rtpHeader->payload+3, frame->mFrame+pos, remainPktSize);
            mRtpPacket.mSize = remainPktSize+2;
            sendRtpPacket(&mRtpPacket);
            mSeq++;
        }
    }
    mTimestamp += mClockRate/mFps;
    
}
