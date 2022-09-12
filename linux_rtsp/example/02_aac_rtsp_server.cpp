#include <iostream>

#include "base/Logging.h"
#include "net/UsageEnvironment.h"
#include "base/ThreadPool.h"
#include "net/EventScheduler.h"
#include "net/Event.h"
#include "net/RtspServer.h"
#include "net/MediaSession.h"
#include "net/InetAddress.h"
#include "net/AACFileMediaSource.h"
#include "net/AACRtpSink.h"

int main(int argc, char* argv[])
{
    if(argc !=  2)
    {
        std::cout<<"Usage: "<<argv[0]<<" <aac file>"<<std::endl;
        return -1;
    }

   
    Logger::setLogLevel(Logger::LogWarning);

    EventScheduler* scheduler = EventScheduler::createNew(EventScheduler::POLLER_SELECT);
    ThreadPool* threadPool = ThreadPool::createNew(2);
    UsageEnvironment* env = UsageEnvironment::createNew(scheduler, threadPool);

    Ipv4Address ipAddr("0.0.0.0", 8554);
    RtspServer* server = RtspServer::createNew(env, ipAddr);
    MediaSession* session = MediaSession::createNew("live");
    MediaSource* mediaSource = AACFileMeidaSource::createNew(env, argv[1]);
    RtpSink* rtpSink = AACRtpSink::createNew(env, mediaSource);

    session->addRtpSink(MediaSession::TrackId0, rtpSink);
    

    std::cout<<"Play the media using the URL \""<<server->getUrl(session)<<"\""<<std::endl;

    server->addMediaSession(session);
    server->start();

    env->scheduler()->loop();
    LOG_ERROR("not correct quit :\n");
    return 0;
}