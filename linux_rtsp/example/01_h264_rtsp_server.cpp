#include <iostream>
#include <signal.h>
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
#include "net/H265FIleMediaSource.h"
#include "net/H265RtpSink.h"

void sigterm(int dummy)
{
	LOG_INFO("caught SIGTERM:  shutting down\n");
    exit(0);
	
}

void sigint(int dummy)
{
	LOG_INFO("caught SIGINT:  shutting down\n");
	exit(0);
}


void init_signals(void)
{
	struct sigaction sa;

	sa.sa_flags = 0;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGTERM);
	sigaddset(&sa.sa_mask, SIGINT);

	sa.sa_handler = sigterm;
	sigaction(SIGTERM, &sa, NULL);

	sa.sa_handler = sigint;
	sigaction(SIGINT, &sa, NULL);
	
	signal(SIGPIPE, SIG_IGN);
}


int main(int argc, char* argv[])
{
    init_signals();
    if(argc !=  2)
    {
        std::cout<<"Usage: "<<argv[0]<<" <h264 file>"<<std::endl;
        return -1;
    }
    std::cout << "Main Inside Thread :: Thread ID : " << pthread_self() << "\n";
    //Logger::setLogFile("xxx.log");
    Logger::setLogLevel(Logger::LogInfo);

    EventScheduler* scheduler = EventScheduler::createNew(EventScheduler::POLLER_SELECT);
    ThreadPool* threadPool = ThreadPool::createNew(1);
    UsageEnvironment* env = UsageEnvironment::createNew(scheduler, threadPool); 

    Ipv4Address ipAddr("0.0.0.0", 8554);
    RtspServer* server = RtspServer::createNew(env, ipAddr);
    MediaSession* session = MediaSession::createNew("live");
    //MediaSource* mediaSource = H264FileMediaSource::createNew(env, argv[1]);
    //RtpSink* rtpSink = H264RtpSink::createNew(env, mediaSource);
    MediaSource* mediaSource = H265FileMediaSource::createNew(env, argv[1]);
    RtpSink* rtpSink = H265RtpSink::createNew(env, mediaSource);
    session->addRtpSink(MediaSession::TrackId0, rtpSink);
  
    server->addMediaSession(session);
    server->start();

    std::cout<<"Play the media using the URL \""<<server->getUrl(session)<<"\""<<std::endl;

    env->scheduler()->loop();

    return 0;
}