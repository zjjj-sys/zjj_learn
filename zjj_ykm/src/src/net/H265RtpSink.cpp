#include <stdio.h>
#include <string.h>

#include "H265RtpSink.h"
#include "Logging.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <iomanip>
static inline int startCode3(uint8_t *buf);
static inline int startCode4(uint8_t *buf);

static u_int32_t Pretimestamp = 0;

static inline int startCode3(uint8_t *buf)
{
    if (buf[0] == 0 && buf[1] == 0 && buf[2] == 1)
        return 1;
    else
        return 0;
}

static inline int startCode4(uint8_t *buf)
{
    if (buf[0] == 0 && buf[1] == 0 && buf[2] == 0 && buf[3] == 1)
        return 1;
    else
        return 0;
}

static uint8_t *findNextStartCode(uint8_t *buf, int len)
{
    int i;

    if (len < 3)
        return NULL;

    for (i = 0; i < len - 3; ++i)
    {
        if (startCode3(buf) || startCode4(buf))
        {
            return buf;
        }
            

        ++buf;
    }

    if (startCode3(buf))
    {
        return buf;
    }
        

    return NULL;
}

H265RtpSink *H265RtpSink::createNew(UsageEnvironment *env, MediaSource *mediaSource)
{
    if (!mediaSource)
        return NULL;

    return new H265RtpSink(env, mediaSource);
}

H265RtpSink::H265RtpSink(UsageEnvironment *env, MediaSource *mediaSource) : RtpSink(env, mediaSource, RTP_PAYLOAD_TYPE_H264),
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
    //sprintf(buf+strlen(buf), "a=framerate:%d", mFps);

    return std::string(buf);
}

#if 0
//对frame 进行 rtp分包并发送
void H265RtpSink::handleFrame(AVFrame* frame)
{
    if(frame->mFrameSize == 0)
    {
        usleep(5*1000);
        return ;
    }
    RtpHeader* rtpHeader = mRtpPacket.mRtpHeadr;
    uint8_t naluType = frame->mFrame[0];
    uint8_t type = (naluType & 0x7E)>>1 ;
    if(frame->mFrameSize <= RTP_MAX_PKT_SIZE)    //单一封包模式
    {
        memcpy(rtpHeader->payload, frame->mFrame, frame->mFrameSize);
        mRtpPacket.mSize = frame->mFrameSize;
        sendRtpPacket(&mRtpPacket);
        mSeq++;

        /* if (((naluType & 0x7E)>>1)== 32 || ((naluType & 0x7E)>>1 )== 33 || ((naluType & 0X7E)>>1)== 34 || ((naluType & 0X7E)>>1)== 39) // 如果是VPS SPS、PPS就不需要加时间戳
            return; */
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
    //mTimestamp = frame->m_ftimestamp;
    mTimestamp += mClockRate/mFps;
    
}
#endif

void H265RtpSink::sendhandleFrame(AVFrame *frame)
{

    RtpHeader *rtpHeader = mRtpPacket.mRtpHeadr;
    uint8_t naluType = frame->mFrame[0];
    uint8_t type = (naluType & 0x7E) >> 1;

    uint32_t interval_time = 0;
    
    if(Pretimestamp !=0 )
    {
        interval_time = (frame->m_ftimestamp - Pretimestamp)*90;
    }
    else
    {
        interval_time = 0 ;
    }
    
    Pretimestamp = frame->m_ftimestamp;
    //LOG_INFO("mTimestamp : %u\n",mTimestamp);
    //rtpHeader->timestamp = htonl(frame->m_ftimestamp);
    
    if (frame->mFrameSize <= RTP_MAX_PKT_SIZE) //单一封包模式
    {
        memcpy(rtpHeader->payload, frame->mFrame, frame->mFrameSize);
        mRtpPacket.mSize = frame->mFrameSize;
        sendRtpPacket(&mRtpPacket);
        mSeq++;

        /* if (((naluType & 0x7E)>>1)== 32 || ((naluType & 0x7E)>>1 )== 33 || ((naluType & 0X7E)>>1)== 34 || ((naluType & 0X7E)>>1)== 39) // 如果是VPS SPS、PPS就不需要加时间戳
            return;  */
    }
    else
    {
        int pktNum = frame->mFrameSize / RTP_MAX_PKT_SIZE;        // 有几个完整的包
        int remainPktSize = frame->mFrameSize % RTP_MAX_PKT_SIZE; // 剩余不完整包的大小
        int pos = 2;

        rtpHeader->payload[0] = (naluType & 0x81) | (49 << 1);
        rtpHeader->payload[1] = frame->mFrame[1];
        rtpHeader->payload[2] = (type | 0x80);

        /* 发送完整的包 */
        for (int i = 0; i < pktNum; i++)
        {

            if (remainPktSize == 0 && i == pktNum - 1) //最后一包数据
                rtpHeader->payload[2] |= 0x40;         // end

            memcpy(rtpHeader->payload + 3, frame->mFrame + pos, RTP_MAX_PKT_SIZE);
            mRtpPacket.mSize = RTP_MAX_PKT_SIZE + 3;

            sendRtpPacket(&mRtpPacket);

            mSeq++;
            pos += RTP_MAX_PKT_SIZE;
            rtpHeader->payload[2] &= ~0x80;
        }

        /* 发送剩余的数据 */
        if (remainPktSize > 0)
        {
            rtpHeader->payload[2] |= 0x40; //end

            memcpy(rtpHeader->payload + 3, frame->mFrame + pos, remainPktSize);
            mRtpPacket.mSize = remainPktSize + 2;
            sendRtpPacket(&mRtpPacket);
            mSeq++;
        }
    }
    
    mTimestamp += interval_time;
    //mTimestamp +=3600;
}

//对frame 进行 rtp分包并发送
void H265RtpSink::handleFrame(AVFrame *frame)
{
    int rSize, frameSize;
    int pos = 0;
    uint8_t *nextStartCode;
    AVFrame temp_frame;
    
    if (frame->mFrameSize == 0)
    {
        usleep(5 * 1000);
        return;
    }
    rSize = frame->mFrameSize;

    temp_frame.m_ftimestamp = frame->m_ftimestamp;
    //LOG_INFO("temp_frame: %u\n",temp_frame.m_ftimestamp);
    if (frame->key_frame == 1)
    {
        if (!startCode3(frame->mFrame) && !startCode4(frame->mFrame))
        {
            LOG_INFO("no start code\n");
            return;
        }
        for (int j = 0; j < 4; j++)
        {
            nextStartCode = findNextStartCode(frame->mBuffer + 3 + pos, rSize - 3 - pos);
            if (nextStartCode == NULL)
            {
                frameSize = rSize-pos-4;
                temp_frame.mFrameSize = frameSize;
                memcpy(temp_frame.mBuffer, frame->mBuffer + pos + 4, frameSize);
                temp_frame.mFrame = temp_frame.mBuffer;
                
                sendhandleFrame(&temp_frame);    
                
                break;
            }
            else
            {
                frameSize = (nextStartCode - frame->mBuffer); //计算出两个起始码之间的数据量
                frameSize -=pos;
                
                memcpy(temp_frame.mBuffer, frame->mBuffer + pos + 4, frameSize - 4);
                temp_frame.mFrameSize = frameSize - 4;
                temp_frame.mFrame = temp_frame.mBuffer;
                
                sendhandleFrame(&temp_frame);

                pos += frameSize;
                nextStartCode = NULL;
                
            }
        }
    }
    else
    {
        sendhandleFrame(frame);
    }
}