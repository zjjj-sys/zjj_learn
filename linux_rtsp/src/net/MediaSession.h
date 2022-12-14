#ifndef _MEDIASESSION_H_
#define _MEDIASESSION_H_
#include <string>
#include <list>

#include "net/RtpInstance.h"
#include "net/RtpSink.h"

#define MEDIA_MAX_TRACK_NUM 2

class MediaSession
{
public:
    enum TrackId
    {
        TrackIdNone = -1,
        TrackId0    = 0,
        TrackId1    = 1,
    };

    static MediaSession* createNew(std::string sessionName);

    MediaSession(const std::string& sessionName);
    ~MediaSession();

    std::string name() const { return mSessionName; }
    std::string generateSDPDescription();
    bool addRtpSink(MediaSession::TrackId trackId, RtpSink* rtpSink);
    bool addRtpInstance(MediaSession::TrackId trackId, RtpInstance* rtpInstance);
    bool removeRtpInstance(RtpInstance* rtpInstance);
    

public:
    class Track
    {
    public:
        RtpSink* mRtpSink;
        int mTrackId;
        bool mIsAlive;
        std::list<RtpInstance*> mRtpInstances;
    };

    Track* getTrack(MediaSession::TrackId trackId);
    static void sendPacketCallback(void* arg1, void* arg2, RtpPacket* rtpPacket);
    void sendPacket(MediaSession::Track* tarck, RtpPacket* rtpPacket);

private:
    std::string mSessionName;
    std::string mSdp;
    Track mTracks[MEDIA_MAX_TRACK_NUM];
   
    
};

#endif //_MEDIASESSION_H_