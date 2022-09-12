#ifndef _RTPINSTANNCE_H_
#define _RTPINSTANNCE_H_
#include <string>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include "net/InetAddress.h"
#include "net/SocketsOps.h"
#include "net/Rtp.h"
 

class RtpInstance
{
public:
    enum RtpType
    {
        RTP_OVER_UDP,
        RTP_OVER_TCP
    };

  

    static RtpInstance *createNewOverTcp(int clientSockfd, uint8_t rtpChannel)
    {
        return new RtpInstance(clientSockfd, rtpChannel);
    }

    ~RtpInstance()
    {
        sockets::close(mSockfd);
    }

    int send(RtpPacket *rtpPacket)
    {
        //加上TCP传输的四个字节 
        uint8_t *rtpPktPtr = rtpPacket->_mBuffer;
        rtpPktPtr[0] = '$';
        rtpPktPtr[1] = (uint8_t)mRtpChannel;
        rtpPktPtr[2] = (uint8_t)(((rtpPacket->mSize) & 0xFF00) >> 8);
        rtpPktPtr[3] = (uint8_t)((rtpPacket->mSize) & 0xFF);
        return sendOverTcp(rtpPktPtr, rtpPacket->mSize + 4);
    }

    bool alive() const { return mIsAlive; }
    void setAlive(bool alive) { mIsAlive = alive; }
    void setSessionId(uint16_t sessionId) { mSessionId = sessionId; }
    uint16_t sessionId() const { return mSessionId; }

private:
    //给client发送rtp分包好的数据
    int sendOverTcp(void *buf, int size)
    {
        return sockets::write(mSockfd, buf, size);
    }

public:
   
    RtpInstance(int clientSockfd, uint8_t rtpChannel) : mRtpType(RTP_OVER_TCP), mSockfd(clientSockfd),mIsAlive(false), mSessionId(0), mRtpChannel(rtpChannel)
    {
    }

private:
    RtpType mRtpType;
    int mSockfd;
    bool mIsAlive;
    uint16_t mSessionId;
    uint8_t mRtpChannel; 
};

#endif //_RTPINSTANNCE_H_