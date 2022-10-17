#ifndef _PPPP_API___INC_H_
#define _PPPP_API___INC_H_

#ifdef WIN32DLL
#ifdef PPPP_API_EXPORTS
#define PPPP_API_API __declspec(dllexport)
#else
#define PPPP_API_API __declspec(dllimport)
#endif
#endif //// #ifdef WIN32DLL

#ifdef LINUX
#include <netinet/in.h>
#define PPPP_API_API 
#endif //// #ifdef LINUX

#ifdef _ARC_COMPILER
#include "net_api.h"
#define PPPP_API_API 
#endif //// #ifdef _ARC_COMPILER

#include "PPPP_Type.h"
#include "PPPP_Error.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


typedef struct{	
	CHAR bFlagInternet;		// Internet Reachable? 1: YES, 0: NO
	CHAR bFlagHostResolved;	// P2P Server IP resolved? 1: YES, 0: NO
	CHAR bFlagServerHello;	// P2P Server Hello? 1: YES, 0: NO
	CHAR NAT_Type;			// NAT type, 0: Unknow, 1: IP-Restricted Cone type,   2: Port-Restricted Cone type, 3: Symmetric 
	CHAR MyLanIP[16];		// My LAN IP. If (bFlagInternet==0) || (bFlagHostResolved==0) || (bFlagServerHello==0), MyLanIP will be "0.0.0.0"
	CHAR MyWanIP[16];		// My Wan IP. If (bFlagInternet==0) || (bFlagHostResolved==0) || (bFlagServerHello==0), MyWanIP will be "0.0.0.0"
} st_PPPP_NetInfo,st_PPCS_NetInfo;

typedef struct{	
	INT32  Skt;					// Sockfd
	struct sockaddr_in RemoteAddr;	// Remote IP:Port
	struct sockaddr_in MyLocalAddr;	// My Local IP:Port
	struct sockaddr_in MyWanAddr;	// My Wan IP:Port
	UINT32 ConnectTime;				// Connection build in ? Sec Before
	CHAR DID[24];					// Device ID
	CHAR bCorD;						// I am Client or Device, 0: Client, 1: Device
	CHAR bMode;						// Connection Mode: 0: P2P, 1:Relay Mode
	CHAR Reserved[2];				
} st_PPPP_Session,st_PPCS_Session;


PPPP_API_API UINT32 PPCS_GetAPIVersion(void);
PPPP_API_API CHAR* PPCS_GetAPIInformation(void); //// add 3.5.0
PPPP_API_API INT32 PPCS_QueryDID(const CHAR* DeviceName, CHAR* DID, INT32 DIDBufSize);
PPPP_API_API INT32 PPCS_Initialize(CHAR *Parameter);
PPPP_API_API INT32 PPCS_DeInitialize(void);
PPPP_API_API INT32 PPCS_NetworkDetect(st_PPCS_NetInfo *NetInfo, UINT16 UDP_Port);
PPPP_API_API INT32 PPCS_NetworkDetectByServer(st_PPCS_NetInfo *NetInfo, UINT16 UDP_Port, CHAR *ServerString);
PPPP_API_API INT32 PPCS_Share_Bandwidth(CHAR bOnOff);
PPPP_API_API INT32 PPCS_Enable_SmartDevice(CHAR bOnOff); //// add 3.5.0
PPPP_API_API INT32 PPCS_Listen(const CHAR *MyID, const UINT32 TimeOut_Sec, UINT16 UDP_Port, CHAR bEnableInternet, const CHAR* APILicense);
PPPP_API_API INT32 PPCS_Listen_Break(void);
PPPP_API_API INT32 PPCS_LoginStatus_Check(CHAR* bLoginStatus);
PPPP_API_API INT32 PPCS_Connect(const CHAR *TargetID, CHAR bEnableLanSearch, UINT16 UDP_Port);
PPPP_API_API INT32 PPCS_ConnectByServer(const CHAR *TargetID, CHAR bEnableLanSearch, UINT16 UDP_Port, CHAR *ServerString);
PPPP_API_API INT32 PPCS_Connect_Break();
PPPP_API_API INT32 PPCS_Check(INT32 SessionHandle, st_PPCS_Session *SInfo);
PPPP_API_API INT32 PPCS_Close(INT32 SessionHandle);
PPPP_API_API INT32 PPCS_ForceClose(INT32 SessionHandle);
PPPP_API_API INT32 PPCS_Write(INT32 SessionHandle, UCHAR Channel, CHAR *DataBuf, INT32 DataSizeToWrite);
PPPP_API_API INT32 PPCS_Read(INT32 SessionHandle, UCHAR Channel, CHAR *DataBuf, INT32 *DataSize, UINT32 TimeOut_ms);
PPPP_API_API INT32 PPCS_Check_Buffer(INT32 SessionHandle, UCHAR Channel, UINT32 *WriteSize, UINT32 *ReadSize);
//// Ther following functions are available after ver. 2.0.0
PPPP_API_API INT32 PPCS_PktSend(INT32 SessionHandle, UCHAR Channel, CHAR *PktBuf, INT32 PktSize); //// Available after ver. 2.0.0
PPPP_API_API INT32 PPCS_PktRecv(INT32 SessionHandle, UCHAR Channel, CHAR *PktBuf, INT32 *PktSize, UINT32 TimeOut_ms); //// Available after ver. 2.0.0


#define  PPPP_GetAPIVersion PPCS_GetAPIVersion
#define  PPPP_QueryDID PPCS_QueryDID
#define  PPPP_Initialize PPCS_Initialize
#define  PPPP_DeInitialize PPCS_DeInitialize
#define  PPPP_NetworkDetect PPCS_NetworkDetect
#define  PPPP_NetworkDetectByServer PPCS_NetworkDetectByServer
#define  PPPP_Share_Bandwidth PPCS_Share_Bandwidth
#define  PPPP_Listen PPCS_Listen
#define  PPPP_Listen_Break PPCS_Listen_Break
#define  PPPP_LoginStatus_Check PPCS_LoginStatus_Check
#define  PPPP_Connect PPCS_Connect
#define  PPPP_ConnectByServer PPCS_ConnectByServer
#define  PPPP_Connect_Break PPCS_Connect_Break
#define  PPPP_Check PPCS_Check
#define  PPPP_Close PPCS_Close
#define  PPPP_ForceClose PPCS_ForceClose
#define  PPPP_Write PPCS_Write
#define  PPPP_Read PPCS_Read
#define  PPPP_Check_Buffer PPCS_Check_Buffer

#ifdef __cplusplus
}
#endif // __cplusplus
#endif ////#ifndef _PPPP_API___INC_H_

