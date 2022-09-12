#include <iostream>

#include "base/Logging.h"
#include "net/UsageEnvironment.h"
#include "base/ThreadPool.h"
#include "net/EventScheduler.h"
#include "net/Event.h"
#include "net/RtspServer.h"
#include "net/MediaSession.h"
#include "net/InetAddress.h"
#include "net/H264FileMediaSource.h"
#include "net/H264RtpSink.h"
#include "net/AACFileMediaSource.h"
#include "net/AACRtpSink.h"

int main(int argc, char* argv[])
{
    if(argc !=  3)
    {
        std::cout<<"Usage: "<<argv[0]<<" <h264 file> <aac file>"<<std::endl;
        return -1;
    }

    
    Logger::setLogLevel(Logger::LogInfo);

    EventScheduler* scheduler = EventScheduler::createNew(EventScheduler::POLLER_SELECT);
    ThreadPool* threadPool = ThreadPool::createNew(1);
    UsageEnvironment* env = UsageEnvironment::createNew(scheduler, threadPool);

    Ipv4Address ipAddr("0.0.0.0", 8554);
    RtspServer* server = RtspServer::createNew(env, ipAddr);
    MediaSession* session = MediaSession::createNew("live");


    MediaSource* videoSource = H264FileMediaSource::createNew(env, argv[1]);
    RtpSink* videoRtpSink = H264RtpSink::createNew(env, videoSource);

    //测试不同的mediasession
    /* MediaSession* Accsession = MediaSession::createNew("zjj");
    MediaSource* accSource =  AACFileMeidaSource::createNew(env, argv[2]);
    RtpSink* audioRtpSink = AACRtpSink::createNew(env, accSource);
 */
    

    MediaSource* audioSource = AACFileMeidaSource::createNew(env, argv[2]);
    RtpSink* audioRtpSink = AACRtpSink::createNew(env, audioSource);

    session->addRtpSink(MediaSession::TrackId0, videoRtpSink);
    session->addRtpSink(MediaSession::TrackId1, audioRtpSink);
    
    //session->startMulticast(); //多播
    
    server->addMediaSession(session);
    server->start();

    std::cout<<"Play the media using the URL \""<<server->getUrl(session)<<"\""<<std::endl;
    //std::cout<<"Play the media using the URL \""<<server->getUrl(Accsession)<<"\""<<std::endl;
    env->scheduler()->loop();

    return 0;
}