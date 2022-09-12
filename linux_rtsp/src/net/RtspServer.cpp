#include <algorithm>
#include <assert.h>
#include <stdio.h>

#include "net/RtspServer.h"
 

RtspServer* RtspServer::createNew(UsageEnvironment* env, Ipv4Address& addr)
{
    return new RtspServer(env, addr);
    
}

RtspServer::RtspServer(UsageEnvironment* env, const Ipv4Address& addr) :
    TcpServer(env, addr)
{
    mTriggerEvent = TriggerEvent::createNew(this);
    mTriggerEvent->setTriggerCallback(triggerCallback);
}

RtspServer::~RtspServer()
{
    delete mTriggerEvent;
   
}
//给每一个连接创建一个connection 实例 注册好对应的销毁函数
void RtspServer::handleNewConnection(int connfd)
{
    RtspConnection* conn = RtspConnection::createNew(this, connfd);
    conn->setDisconnectionCallback(disconnectionCallback, this);    //设置每一个Connection 实例的关闭fd函数
    mConnections.insert(std::make_pair(connfd, conn));
}
//收到关闭命令触发相应回调
void RtspServer::disconnectionCallback(void* arg, int sockfd)
{
    RtspServer* rtspServer = (RtspServer*)arg;
    rtspServer->handleDisconnection(sockfd);
}

//将要处理的socket_fd放入队列，其实每次就一个实例，把要关闭的FD 加入到事件轮询中
void RtspServer::handleDisconnection(int sockfd)
{
    //std::lock_guard<std::mutex> lck(m_mutex);
    mDisconnectionlist.push_back(sockfd);
   
    mEnv->scheduler()->addTriggerEvent(mTriggerEvent);
}
//把媒体会话加入队列
bool RtspServer::addMediaSession(MediaSession* mediaSession)
{
    if(mMediaSessions.find(mediaSession->name()) != mMediaSessions.end())
        return false;

    mMediaSessions.insert(std::make_pair(mediaSession->name(), mediaSession));

    return true;
}
//获取对应的会话
MediaSession* RtspServer::loopupMediaSession(std::string name)
{
    std::map<std::string, MediaSession*>::iterator it = mMediaSessions.find(name);
    if(it == mMediaSessions.end())
        return NULL;
    
    return it->second;
}
//获取URL
std::string RtspServer::getUrl(MediaSession* session)
{
    char url[200];

    snprintf(url, sizeof(url), "rtsp://%s:%d/%s", sockets::getLocalIp().c_str(),
                mAddr.getPort(), session->name().c_str());

    return std::string(url);
}
//触发回调函数
void RtspServer::triggerCallback(void* arg)
{
    RtspServer* rtspServer = (RtspServer*)arg;
    rtspServer->handleDisconnectionList();
}
//将fd对应的rtspconnection连接给关闭，触发事件真正调用的函数
void RtspServer::handleDisconnectionList()
{   
    //std::lock_guard<std::mutex> lck(m_mutex);
    for(std::vector<int>::iterator it = mDisconnectionlist.begin(); it != mDisconnectionlist.end(); ++it)
    {
        int sockfd = *it;
        std::map<int, RtspConnection*>::iterator cit = mConnections.find(sockfd);
        if(cit != mConnections.end())
        {
            delete cit->second;
            mConnections.erase(sockfd);
            LOG_INFO("disconnect client fd : %d\n",sockfd);
        }else{
            continue;
        }
        
    }

    mDisconnectionlist.clear();
}