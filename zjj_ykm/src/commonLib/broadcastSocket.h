#ifndef __BROADCAST_SOCKET_H__
#define __BROADCAST_SOCKET_H__


typedef struct{
	uint32_t 	ip;
	uint16_t 	port;
	uint8_t 	mac[6];
	uint32_t 	cmd;
	uint32_t 	data_size;
	uint8_t 	data[0];
}__attribute__((packed))BROADCAST_MSG_st;


enum{
	ENUM_BROADCAST_MSG_DEVICE_DISCOVERY_CMD 	= 0x10000,

};

enum{
	ENUM_UNICAST_MSG_DEVICE_DISCOVERY_RESP_CMD = 0x2000,
	ENUM_UNICAST_MSG_DEVICE_WILL_UPGRADE,
	ENUM_BROADCAST_MSG_IP_CONFLICT,
};


typedef struct{
	uint32_t model;
	char     devName[64];//osd name.
	char	 sn[64];
	char 	 iot[16]; //tutk,txiot
	uint16_t mediaPort;//
	uint8_t  appVer1;
	uint8_t  appVer2;
	uint8_t  appVer3;
	uint8_t  appVer4;
	uint8_t  sysVer1;
	uint8_t  sysVer2;
	uint8_t  sysVer3;
	uint8_t  sysVer4;

}__attribute__((packed))DEVICE_DISCOVERY_MSG;




class CBroadcastSocket
{
public:
	CBroadcastSocket(uint16_t port);
	virtual ~CBroadcastSocket();
	int broadcastMsg(uint8_t * msg,uint32_t msgSize,uint16_t dstBroadcastPort);
	int unicastMsg(uint8_t * msg,uint32_t msgSize,uint32_t dstIp,uint16_t dstBroadcastPort);
	virtual int doRecvBroadcastMsg(uint8_t * msg,uint32_t msgSize,uint32_t Ip,uint16_t port);
	bool getIpMac(uint32_t & ip,uint8_t * mac,uint32_t macSize);
private:
	bool startRecvBroadcastMsgThread();
	bool stopRecvBroadcastMsgThread();
	int createBroadcastSocket();
	bool closeBroadcastSocket();

public:
	static void * RecvBroadcastMsgFunc(void * args);
	bool doRecvBroadcastMsgFunc();
protected:
	bool	m_bStopRecvBroadcastMsg;
	pthread_t m_nRecvBroadcastMsgThreadId;
	pthread_mutex_t m_stSendLock;
	int m_nSocket;
	uint8_t m_arryRecvBuf[1472];
	uint16_t m_nBindPort;

};






























#endif //__BROADCAST_SOCKET_H__

