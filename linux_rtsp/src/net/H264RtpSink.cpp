#include <stdio.h>
#include <string.h>

#include "net/H264RtpSink.h"
#include "base/Logging.h"
 
#include <iostream>
H264RtpSink* H264RtpSink::createNew(UsageEnvironment* env, MediaSource* mediaSource)
{
    if(!mediaSource)
        return NULL;

    return new H264RtpSink(env, mediaSource);
    
}

H264RtpSink::H264RtpSink(UsageEnvironment* env, MediaSource* mediaSource) :
    RtpSink(env, mediaSource, RTP_PAYLOAD_TYPE_H264),
    mClockRate(90000),
    mFps(mediaSource->getFps())
{
    start(1000/mFps);
}

H264RtpSink::~H264RtpSink()
{

}
//获取视频信息
std::string H264RtpSink::getMediaDescription(uint16_t port)
{
    char buf[100] = {0};
    sprintf(buf, "m=video %hu RTP/AVP %d", port, mPayloadType);

    return std::string(buf);
}
//获取视频属性
std::string H264RtpSink::getAttribute()
{
    char buf[100];
    sprintf(buf, "a=rtpmap:%d H264/%d\r\n", mPayloadType, mClockRate);
    sprintf(buf+strlen(buf), "a=framerate:%d", mFps);

    return std::string(buf);
}

//对frame 进行 rtp分包并发送
void H264RtpSink::handleFrame(AVFrame* frame)
{
    RtpHeader* rtpHeader = mRtpPacket.mRtpHeadr;
    uint8_t naluType = frame->mFrame[0];
    
    if(frame->mFrameSize <= RTP_MAX_PKT_SIZE)    //单一封包模式
    {
        memcpy(rtpHeader->payload, frame->mFrame, frame->mFrameSize);
        mRtpPacket.mSize = frame->mFrameSize;
        sendRtpPacket(&mRtpPacket);
        mSeq++;

        if ((naluType & 0x1F) == 7 || (naluType & 0x1F) == 8) // 如果是SPS、PPS就不需要加时间戳
            return;
    }
    else
    {
        int pktNum = frame->mFrameSize / RTP_MAX_PKT_SIZE;       // 有几个完整的包
        int remainPktSize = frame->mFrameSize % RTP_MAX_PKT_SIZE; // 剩余不完整包的大小
        int i, pos = 1;    //pos=1 是过滤掉264的第一个自己 nalu_type

        /* 发送完整的包 */
        for (i = 0; i < pktNum; i++)
        {
            /*
            *     FU Indicator
            *    0 1 2 3 4 5 6 7
            *   +-+-+-+-+-+-+-+-+
            *   |F|NRI|  Type   |
            *   +---------------+
            * */
            rtpHeader->payload[0] = (naluType & 0x60) | 28; //(naluType & 0x60)表示nalu的重要性，28表示为分片
            
            /*
            *      FU Header
            *    0 1 2 3 4 5 6 7
            *   +-+-+-+-+-+-+-+-+
            *   |S|E|R|  Type   |
            *   +---------------+
            * */
            rtpHeader->payload[1] = naluType & 0x1F;
            
            if (i == 0) //第一包数据
                rtpHeader->payload[1] |= 0x80; // start
            else if (remainPktSize == 0 && i == pktNum - 1) //最后一包数据
                rtpHeader->payload[1] |= 0x40; // end

            memcpy(rtpHeader->payload+2, frame->mFrame+pos, RTP_MAX_PKT_SIZE);
            mRtpPacket.mSize = RTP_MAX_PKT_SIZE+2;
            sendRtpPacket(&mRtpPacket);

            mSeq++;
            pos += RTP_MAX_PKT_SIZE;
        }

        /* 发送剩余的数据 */
        if (remainPktSize > 0)
        {
            rtpHeader->payload[0] = (naluType & 0x60) | 28;
            rtpHeader->payload[1] = naluType & 0x1F;
            rtpHeader->payload[1] |= 0x40; //end

            memcpy(rtpHeader->payload+2, frame->mFrame+pos, remainPktSize);
            mRtpPacket.mSize = remainPktSize+2;
            sendRtpPacket(&mRtpPacket);

            mSeq++;
        }
    }
    mTimestamp += mClockRate/mFps;
    
}
