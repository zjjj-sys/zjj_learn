#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "common.h"
#include "commFunc.h"
#include "CProduct.h"
#include "CYKMsgHandler.h"
#include "CShmBuf.h"
#include "MiscDataType.h"
#include "Curlt.h"

#include "Logging.h"
#include "UsageEnvironment.h"
#include "ThreadPool.h"
#include "EventScheduler.h"
#include "Event.h"
#include "RtspServer.h"
#include "MediaSession.h"
#include "InetAddress.h"
#include "H264FileMediaSource.h"
#include "H264RtpSink.h"
#include "H265FIleMediaSource.h"
#include "H265RtpSink.h"
#include "G711FileMediaSource.h"
#include "G711RtpSink.h"

#define BUF_SIZE 1024*1024
#define HI3516DV300 1

IPC_DEBUG_DECLARE("YKM");



CURLT* g_YKMcurlt  = NULL;
CProduct * 		g_pProduct			= NULL;
CYKMsgHandler * g_pYKMsgHandler 	= NULL;
bool g_bYKMAdapterStop = false;

void sigterm(int dummy)
{
	DEBUG_INFO("caught SIGTERM: YKMAdapter: shutting down\n");
	g_bYKMAdapterStop = true;
}

void sigint(int dummy)
{
	DEBUG_INFO("caught SIGINT: YKMAdapter: shutting down\n");
	g_bYKMAdapterStop = true;
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
	
	COMM_FUNC::DebugInit();

	g_pProduct		= new CProduct();


	g_pYKMsgHandler	= new CYKMsgHandler();
#if 0	
	g_pMqttAdapter				= new CMqttAdapter();

	g_pMqttAdapter->run(g_bMqttAdapterStop);

	if(g_pMqttAdapter){
		delete g_pMqttAdapter;
		g_pMqttAdapter = NULL;
	}
#else
	
	
	CShmBuf* StreamAudioConsumer = new CShmBuf("RTSP_Main_",AI_SHM_NAME,AI_SHM_SIZE,MEDIA_MEM_CONSUMER);
	CShmBuf* StreamVideoConsumer = new CShmBuf("RTSP_MAIN",VENC_MAIN_MM_NAME,MAIN_STREAM_SHM_SIZE,MEDIA_MEM_CONSUMER);
	
    Logger::setLogLevel(Logger::LogInfo);
    EventScheduler* scheduler = EventScheduler::createNew(EventScheduler::POLLER_SELECT);
    ThreadPool* threadPool = ThreadPool::createNew(1);
    UsageEnvironment* env = UsageEnvironment::createNew(scheduler, threadPool);

    Ipv4Address ipAddr("0.0.0.0", 8554);
    RtspServer* server = RtspServer::createNew(env, ipAddr);
    MediaSession* session = MediaSession::createNew("live");

    MediaSource* mediaSource = H265FileMediaSource::createNew(env, StreamVideoConsumer);
    RtpSink* rtpSink = H265RtpSink::createNew(env, mediaSource);

	MediaSource* AudioSource = G711FileMediaSource::createNew(env,StreamAudioConsumer);
	RtpSink* AudiortpSink = G711RtpSink::createNew(env,AudioSource);
	
	session->addRtpSink(MediaSession::TrackId0,AudiortpSink);
    session->addRtpSink(MediaSession::TrackId1, rtpSink);
	

    server->addMediaSession(session);
    server->start();

    std::cout<<"Play the media using the URL \""<<server->getUrl(session)<<"\""<<std::endl;

    env->scheduler()->loop();

	
	
#endif

	/* if(env)
	{
		delete env;
		env = NULL;
	}
	 */
	DEBUG_INFO("=============\n");
	if(StreamVideoConsumer){
		delete StreamVideoConsumer;
		StreamVideoConsumer = NULL;
	}

	if(StreamAudioConsumer){
		delete StreamAudioConsumer;
		StreamAudioConsumer = NULL;
	}

	
	if(g_pYKMsgHandler){
		delete g_pYKMsgHandler;
		g_pYKMsgHandler = NULL;
	}



	if(g_pProduct){
		delete g_pProduct;
		g_pProduct = NULL;
	}

	COMM_FUNC::DebugDeinit();
	

	return 0;
}

























