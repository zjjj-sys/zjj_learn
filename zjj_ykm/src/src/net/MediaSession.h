#ifndef _MEDIASESSION_H_
#define _MEDIASESSION_H_
#include <string>
#include <list>

#include "RtpInstance.h"
#include "RtpSink.h"

#define MEDIA_MAX_TRACK_NUM 2

class MediaSession
{
public:
    enum TrackId
    {
        TrackIdNone = -1,
        TrackId0    = 0,
        TrackId1    = 1,
        TrackId2    = 2,
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


class TestMediaSession
{
public:
    enum TrackID
    {
        track1 = 0,
        track2 = 1,
        track3 = 2,
    };

    static TestMediaSession* createNew(std::string session_name);
    ~TestMediaSession();

    std::string name() const { return mSessionName; }
    std::string generateSDPDescription();
    bool addRtpSink(MediaSession::TrackId trackId, RtpSink* rtpSink);
    bool addRtpInstance(MediaSession::TrackId trackId, RtpInstance* rtpInstance);
    bool removeRtpInstance(RtpInstance* rtpInstance);


private:
    TestMediaSession(std::string sessionname);
    class TestSubMediaSession
    {
    public:
        friend class TestMediaSession;
        
    private:
        RtpSink* mRtpSink;
        int mtrackId;
        bool mIsAlive;
        std::list<RtpInstance*> mRtpInstances;
    };
    
    TestSubMediaSession* getTrack(MediaSession::TrackId trackId);
    static void sendPacketCallback(void* arg1, void* arg2, RtpPacket* rtpPacket);
    void sendPacket(TestMediaSession::TestSubMediaSession* tarck, RtpPacket* rtpPacket);


private:

    std::string mSessionName;
    std::string mSdp;
    std::map<TestSubMediaSession* , int> mTracks;
    int mtrack_conut;

};



#endif //_MEDIASESSION_H_