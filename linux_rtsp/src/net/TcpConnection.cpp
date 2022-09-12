#include "net/TcpConnection.h"
#include "net/SocketsOps.h"
#include "base/Logging.h"
 
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

TcpConnection::TcpConnection(UsageEnvironment* env, int sockfd) :
    mEnv(env),
    mSocket(sockfd),
    mDisconnectionCallback(NULL),
    mArg(NULL)
{
    mTcpConnIOEvent = IOEvent::createNew(sockfd, this);
    mTcpConnIOEvent->setReadCallback(readCallback);
    mTcpConnIOEvent->setWriteCallback(writeCallback);
    mTcpConnIOEvent->setErrorCallback(errorCallback);
    mTcpConnIOEvent->enableReadHandling(); //默认只开启读
    mEnv->scheduler()->addIOEvent(mTcpConnIOEvent);
}

TcpConnection::~TcpConnection()
{
    mEnv->scheduler()->removeIOEvent(mTcpConnIOEvent);
    delete mTcpConnIOEvent;
}

//注册关闭连接的函数
void TcpConnection::setDisconnectionCallback(DisconnectionCallback cb, void* arg)
{
    mDisconnectionCallback = cb;
    mArg = arg;
}

void TcpConnection::enableReadHandling()
{
    if(mTcpConnIOEvent->isReadHandling())
        return;
    
    mTcpConnIOEvent->enableReadHandling();
    mEnv->scheduler()->updateIOEvent(mTcpConnIOEvent);
}

void TcpConnection::enableWriteHandling()
{
    if(mTcpConnIOEvent->isWriteHandling())
        return;
    
    mTcpConnIOEvent->enableWriteHandling();
    mEnv->scheduler()->updateIOEvent(mTcpConnIOEvent);
}

void TcpConnection::enableErrorHandling()
{
    if(mTcpConnIOEvent->isErrorHandling())
        return;

    mTcpConnIOEvent->enableErrorHandling();
    mEnv->scheduler()->updateIOEvent(mTcpConnIOEvent);
}

void TcpConnection::disableReadeHandling()
{
    if(!mTcpConnIOEvent->isReadHandling())
        return;

    mTcpConnIOEvent->disableReadeHandling();
    mEnv->scheduler()->updateIOEvent(mTcpConnIOEvent);
}   

void TcpConnection::disableWriteHandling()
{
    if(!mTcpConnIOEvent->isWriteHandling())
        return;

    mTcpConnIOEvent->disableWriteHandling();
    mEnv->scheduler()->updateIOEvent(mTcpConnIOEvent);
}

void TcpConnection::disableErrorHandling()
{
    if(!mTcpConnIOEvent->isErrorHandling())
        return;

    mTcpConnIOEvent->disableErrorHandling();
    mEnv->scheduler()->updateIOEvent(mTcpConnIOEvent);
}

//处理IO的读事件
void TcpConnection::handleRead()
{
    int ret = mInputBuffer.read(mSocket.fd());
    
    if(ret == 0)
    {
        LOG_INFO("client disconnect\n");
        handleDisconnection();
        return;
    }
    else if(ret < 0) //不管errno是 EAGAIN 还是 EINTR 也都直接关闭连接
    {
        
        LOG_WARNING("read err\n");
        handleDisconnection();
        return;
    }

    /* 先取消读 */
    //this->disableReadeHandling();

    handleReadBytes();
}

//只是用来保证产生基类实例，实际读写出错函数都通过派生类自己处理
void TcpConnection::handleReadBytes()
{
    LOG_INFO("default read handle\n");
    mInputBuffer.retrieveAll();
}

void TcpConnection::handleWrite()
{
    if(mTcpConnIOEvent->isWriteHandling()){
        handleWriteBytes();
    }
    else{
        LOG_INFO("not handlewrite cancel write_event\n");
        disableWriteHandling();
    }
}

//只是用来保证产生基类实例，实际读写出错函数都通过派生类自己处理
void TcpConnection::handleWriteBytes()
{
    LOG_INFO("default write handle\n");
}

void TcpConnection::handleError()
{
    LOG_INFO("default error handle\n");
}

//有先的client连接进来时回调
void TcpConnection::readCallback(void* arg)
{
    
    TcpConnection* tcpConnection = (TcpConnection*)arg;
    tcpConnection->handleRead();
}

void TcpConnection::writeCallback(void* arg)
{
    
    TcpConnection* tcpConnection = (TcpConnection*)arg;
    tcpConnection->handleWrite();
}

void TcpConnection::errorCallback(void* arg)
{
    TcpConnection* tcpConnection = (TcpConnection*)arg;
    tcpConnection->handleError();
}

/* 收到命令出错 或 收到关闭命令时 回调关闭函数
   实际调用的函数RtspServer::handleDisconnection 
   在handleDisconnection中把事件加如轮询中addTriggerEvent()
*/
void TcpConnection::handleDisconnection()
{
    if(mDisconnectionCallback)
        mDisconnectionCallback(mArg, mSocket.fd());
}