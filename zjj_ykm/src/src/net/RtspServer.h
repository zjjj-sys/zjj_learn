#ifndef _RTSPSERVER_H_
#define _RTSPSERVER_H_
#include <map>
#include <vector>
#include <string>
#include <mutex>
#include "TcpServer.h"
#include "UsageEnvironment.h"
#include "RtspConnection.h"
#include "MediaSession.h"
#include "Event.h"


class RtspConnection;

class RtspServer : public TcpServer
{
public:
    static RtspServer* createNew(UsageEnvironment* env, Ipv4Address& addr);

    RtspServer(UsageEnvironment* env, const Ipv4Address& addr);
    virtual ~RtspServer();

    UsageEnvironment* envir() const { return mEnv; }

    bool addMediaSession(MediaSession* mediaSession);
    
    MediaSession* loopupMediaSession(std::string name);
    std::string getUrl(MediaSession* session);

protected:
    virtual void handleNewConnection(int connfd);
    static void disconnectionCallback(void* arg, int sockfd);
    void handleDisconnection(int sockfd);
    static void triggerCallback(void*);
    void handleDisconnectionList();

private:
    std::map<std::string, MediaSession*> mMediaSessions;
    std::map<int, RtspConnection*> mConnections;
    std::vector<int> mDisconnectionlist;
    TriggerEvent* mTriggerEvent;
    
    std::mutex m_mutex;
};

#endif //_RTSPSERVER_H_