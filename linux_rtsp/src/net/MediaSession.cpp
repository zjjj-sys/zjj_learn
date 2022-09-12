#include <stdio.h>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <assert.h>

#include "net/MediaSession.h"
#include "net/SocketsOps.h"
#include "base/Logging.h"
 
#include <iostream>

MediaSession *MediaSession::createNew(std::string sessionName)
{
    return new MediaSession(sessionName);
    
}

MediaSession::MediaSession(const std::string &sessionName) : mSessionName(sessionName)
{
    mTracks[0].mTrackId = TrackId0;
    mTracks[1].mTrackId = TrackId1;
    mTracks[0].mIsAlive = false;
    mTracks[1].mIsAlive = false;
}

MediaSession::~MediaSession()
{
}

//处理rtsp协议的 视频sdp
std::string MediaSession::generateSDPDescription()
{
    if (!mSdp.empty())
        return mSdp;

    std::string ip = sockets::getLocalIp();
    char buf[2048] = {0};

    snprintf(buf, sizeof(buf),
             "v=0\r\n"
             "o=- 9%ld 1 IN IP4 %s\r\n"
             "t=0 0\r\n"
             "a=control:*\r\n"
             "a=type:broadcast\r\n",
             (long)time(NULL), ip.c_str());

    for (int i = 0; i < MEDIA_MAX_TRACK_NUM; ++i)
    {
        uint16_t port = 0;

        if (mTracks[i].mIsAlive != true)
            continue;

        snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf),
                 "%s\r\n", mTracks[i].mRtpSink->getMediaDescription(port).c_str());

        snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf),
                 "c=IN IP4 0.0.0.0\r\n");

        snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf),
                 "%s\r\n", mTracks[i].mRtpSink->getAttribute().c_str());

        snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf),
                 "a=control:track%d\r\n", mTracks[i].mTrackId);
    }

    mSdp = buf;
    return mSdp;
}
//根据track_id 获取对应的 tarck 实例
MediaSession::Track *MediaSession::getTrack(MediaSession::TrackId trackId)
{
    for (int i = 0; i < MEDIA_MAX_TRACK_NUM; ++i)
    {
        if (mTracks[i].mTrackId == trackId)
            return &mTracks[i];
    }

    return NULL;
}
//设置client连接 和rtp——id号 根据 ID号确定将要进行的rtp分包处理
bool MediaSession::addRtpSink(MediaSession::TrackId trackId, RtpSink *rtpSink)
{
    Track *track;

    track = getTrack(trackId);
    if (!track)
        return false;

    track->mRtpSink = rtpSink;
    track->mIsAlive = true;
    rtpSink->setSendFrameCallback(sendPacketCallback, this, track);

    return true;
}
// 把对应的track_id 加入对应的 tarck实例中
bool MediaSession::addRtpInstance(MediaSession::TrackId trackId, RtpInstance *rtpInstance)
{
    
    Track *track = getTrack(trackId);
    if (!track || track->mIsAlive != true)
        return false;

    track->mRtpInstances.push_back(rtpInstance);

    return true;
}

//从track实例中移除RTP实例
bool MediaSession::removeRtpInstance(RtpInstance *rtpInstance)
{
    for (int i = 0; i < MEDIA_MAX_TRACK_NUM; ++i)
    {
        if (mTracks[i].mIsAlive == false)
            continue;

        std::list<RtpInstance *>::iterator it = std::find(mTracks[i].mRtpInstances.begin(),
                                                          mTracks[i].mRtpInstances.end(),
                                                          rtpInstance);
        if (it == mTracks[i].mRtpInstances.end())
            continue;

        mTracks[i].mRtpInstances.erase(it);
        return true;
    }

    return false;
}
//注册发送 RTPpacket的回调函数和参数
void MediaSession::sendPacketCallback(void *arg1, void *arg2, RtpPacket *rtpPacket)
{
    MediaSession *mediaSession = (MediaSession *)arg1;
    MediaSession::Track *track = (MediaSession::Track *)arg2;
    mediaSession->sendPacket(track, rtpPacket);
}

//RTP Packet的回调函数
void MediaSession::sendPacket(MediaSession::Track *track, RtpPacket *rtpPacket)
{
    std::list<RtpInstance *>::iterator it;

    int ret ;
    for (it = track->mRtpInstances.begin(); it != track->mRtpInstances.end(); ++it)
    {
        if ((*it)->alive() == true)
        {
            
            ret = (*it)->send(rtpPacket);
            if(ret == 0)
            {
                track->mRtpInstances.erase(it);
                delete *it;
            }
        }
    }
}
