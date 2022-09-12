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
    
    if(argc !=  2)
    {
        std::cout<<"Usage: "<<argv[0]<<" <h264 file>"<<std::endl;
        return -1;
    }
    init_signals();
    
    Logger::setLogLevel(Logger::LogInfo);

    EventScheduler* scheduler = EventScheduler::createNew(EventScheduler::POLLER_SELECT);  //选择IO复用的框架
    ThreadPool* threadPool = ThreadPool::createNew(1);    //创建一个线程不断的获取视频帧数据
    UsageEnvironment* env = UsageEnvironment::createNew(scheduler, threadPool);  //创建事件轮询分发器

    Ipv4Address ipAddr("0.0.0.0", 8554);
    RtspServer* server = RtspServer::createNew(env, ipAddr);
    MediaSession* session = MediaSession::createNew("live");   //设置RTSP的URL
    MediaSource* mediaSource = H264FileMediaSource::createNew(env, argv[1]);  //选择需要传输的文件
    RtpSink* rtpSink = H264RtpSink::createNew(env, mediaSource);

    session->addRtpSink(MediaSession::TrackId0, rtpSink);  //选择需要的RTPSINK 
  

    server->addMediaSession(session);
    server->start();   //把mediasession加入事件轮询 进行监听

    std::cout<<"Play the media using the URL \""<<server->getUrl(session)<<"\""<<std::endl;

    env->scheduler()->loop();    //事件轮询

    return 0;
}