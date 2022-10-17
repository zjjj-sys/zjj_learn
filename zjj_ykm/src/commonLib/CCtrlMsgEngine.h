#ifndef __CCTRL_MSG_ENGINE_H__
#define __CCTRL_MSG_ENGINE_H__

#include "MessageEngine.h"
#include "MiscDataType.h"
//#include "uIPCamAuthMoudle.h"



enum {
	CMD_ID_SEND_CMD_BASE		= 0x100000,		//send CMD
	CMD_ID_SEND_LOGIN,
	CMD_ID_SEND_LOGOUT,
	CMD_ID_SEND_HEART_BEAT,
	CMD_ID_SEND_GET_DEVICE_INFO,
	CMD_ID_SEND_GET_DEVICE_STATUS,
	CMD_ID_SEND_GET_DEVICE_CAPACITY,
	CMD_ID_SEND_GET_USER_LIST,
	CMD_ID_SEND_GET_ONLINE_USER_LIST,
	CMD_ID_SEND_ADD_USER,
	CMD_ID_SEND_DEL_USER,
	CMD_ID_SEND_MODIFY_PASSWORD,
	CMD_ID_SEND_GET_DEVICE_TIME,
	CMD_ID_SEND_SET_DEVICE_TIME,
	CMD_ID_SEND_REBOOT,
	CMD_ID_SEND_EXPORT_CONFIG,
	CMD_ID_SEND_IMPORT_CONFIG,
	CMD_ID_SEND_UPGRADE_BEFORE_DOWNLOAD,		// we will download firmware,pls release mem
	CMD_ID_SEND_OPEN_VIDEO,
	CMD_ID_SEND_CLOSE_VIDEO,
	CMD_ID_SEND_OPEN_AUDIO,
	CMD_ID_SEND_CLOSE_AUDIO,
	CMD_ID_SEND_OPEN_SPEAKER,
	CMD_ID_SEND_CLOSE_SPEAKER,
	CMD_ID_SEND_GET_VIDEO_ENC_PARAM,
	CMD_ID_SEND_SET_VIDEO_ENC_PARAM,
	CMD_ID_SEND_GET_VIDEO_INPUT_PARAM,
	CMD_ID_SEND_SET_VIDEO_INPUT_PARAM,
	CMD_ID_SEND_GET_AUDIO_ENC_PARAM,
	CMD_ID_SEND_SET_AUDIO_ENC_PARAM,
	CMD_ID_SEND_GET_AUDIO_INPUT_PARAM,
	CMD_ID_SEND_SET_AUDIO_INPUT_PARAM,
	CMD_ID_SEND_GET_AUDIO_DEC_PARAM,
	CMD_ID_SEND_SET_AUDIO_DEC_PARAM,
	CMD_ID_SEND_GET_AUDIO_OUTPUT_PARAM,
	CMD_ID_SEND_SET_AUDIO_OUTPUT_PARAM,
	CMD_ID_SEND_GET_MOTION_ALARM_PARAM,
	CMD_ID_SEND_SET_MOTION_ALARM_PARAM,
	CMD_ID_SEND_GET_SOUND_ALARM_PARAM,
	CMD_ID_SEND_SET_SOUND_ALARM_PARAM,
	CMD_ID_SEND_SNAPSHOT,
	CMD_ID_SEND_GET_IRCUT_PARAM,
	CMD_ID_SEND_SET_IRCUT_PARAM,
	CMD_ID_SEND_GET_REC_PARAM,
	CMD_ID_SEND_SET_REC_PARAM,
	CMD_ID_SEND_PLAYBACK_QUERY,
	CMD_ID_SEND_PLAYBACK_START,
	CMD_ID_SEND_PLAYBACK_STOP,
	CMD_ID_SEND_PLAYBACK_SEEK,
	CMD_ID_SEND_GET_WIFI_PARAM,
	CMD_ID_SEND_SET_WIFI_PARAM,
	CMD_ID_SEND_GET_WIFI_LIST,
	CMD_ID_SEND_UPDATE_WIFI_LIST,
	CMD_ID_SEND_GET_NETWORK_PARAM,
	CMD_ID_SEND_SET_NETWORK_PARAM,
	CMD_ID_SEND_GET_FTP_PARAM,
	CMD_ID_SEND_SET_FTP_PARAM,
	CMD_ID_SEND_FORCE_KEY_FRAME_CMD,
	CMD_ID_SEND_GET_SNAPSHOT_QUALITY_CMD,
	CMD_ID_SEND_SET_SNAPSHOT_QUALITY_CMD,
	CMD_ID_SEND_GET_OSD_PARAM_CMD,
	CMD_ID_SEND_SET_OSD_PARAM_CMD,
	CMD_ID_SEND_UPGRADE_BEFORE_WRITE_FLASH,
	CMD_ID_SEND_GET_VERSION_CMD,
	CMD_ID_SEND_BURN_DEV_LIC_REQ_CMD,
	CMD_ID_SEND_GET_DEVICE_LICENSE_INFO_CMD,
	CMD_ID_SEND_TEST_IRCUT_OPEN,
	CMD_ID_SEND_TEST_IRCUT_CLOSE,
	CMD_ID_SEND_DEBUG_OPEN_TELNET_CMD,
	CMD_ID_SEND_DEBUG_CLOSE_TELNET_CMD,
	CMD_ID_SEND_START_AI_AO_LOOP_CMD,
	CMD_ID_SEND_STOP_AI_AO_LOOP_CMD,
	CMD_ID_SEND_START_SDCARD_TEST_CMD,
	CMD_ID_SEND_STOP_SDCARD_TEST_CMD,
	CMD_ID_SEND_GET_AUTO_MAINTENANCE_ATTR_CMD,
	CMD_ID_SEND_SET_AUTO_MAINTENANCE_ATTR_CMD,
	CMD_ID_SEND_SET_AUDIO_ATTR_CMD,
	CMD_ID_SEND_GET_AUDIO_ATTR_CMD,
	CMD_ID_SEND_GET_DEBUG_LOG_STATUS_CMD,
	CMD_ID_SEND_SET_DEBUG_LOG_STATUS_CMD,




	CMD_ID_RESP_CMD_BASE		= 0x200000,		//response CMD for send CMD
	CMD_ID_RESP_LOGIN,
	CMD_ID_RESP_LOGOUT,
	CMD_ID_RESP_HEART_BEAT,
	CMD_ID_RESP_GET_DEVICE_INFO,
	CMD_ID_RESP_GET_DEVICE_STATUS,
	CMD_ID_RESP_GET_DEVICE_CAPACITY,
	CMD_ID_RESP_GET_USER_LIST,
	CMD_ID_RESP_GET_ONLINE_USER_LIST,
	CMD_ID_RESP_ADD_USER,
	CMD_ID_RESP_DEL_USER,
	CMD_ID_RESP_MODIFY_PASSWORD,
	CMD_ID_RESP_GET_DEVICE_TIME,
	CMD_ID_RESP_SET_DEVICE_TIME,
	CMD_ID_RESP_REBOOT,
	CMD_ID_RESP_EXPORT_CONFIG,
	CMD_ID_RESP_IMPORT_CONFIG,
	CMD_ID_RESP_UPGRADE_BEFORE_DOWNLOAD,
	CMD_ID_RESP_OPEN_VIDEO,
	CMD_ID_RESP_CLOSE_VIDEO,
	CMD_ID_RESP_OPEN_AUDIO,
	CMD_ID_RESP_CLOSE_AUDIO,
	CMD_ID_RESP_OPEN_SPEAKER,
	CMD_ID_RESP_CLOSE_SPEAKER,
	CMD_ID_RESP_GET_VIDEO_ENC_PARAM,
	CMD_ID_RESP_SET_VIDEO_ENC_PARAM,
	CMD_ID_RESP_GET_VIDEO_INPUT_PARAM,
	CMD_ID_RESP_SET_VIDEO_INPUT_PARAM,
	CMD_ID_RESP_GET_AUDIO_ENC_PARAM,
	CMD_ID_RESP_SET_AUDIO_ENC_PARAM,
	CMD_ID_RESP_GET_AUDIO_INPUT_PARAM,
	CMD_ID_RESP_SET_AUDIO_INPUT_PARAM,
	CMD_ID_RESP_GET_AUDIO_DEC_PARAM,
	CMD_ID_RESP_SET_AUDIO_DEC_PARAM,
	CMD_ID_RESP_GET_AUDIO_OUTPUT_PARAM,
	CMD_ID_RESP_SET_AUDIO_OUTPUT_PARAM,
	CMD_ID_RESP_GET_MOTION_ALARM_PARAM,
	CMD_ID_RESP_SET_MOTION_ALARM_PARAM,
	CMD_ID_RESP_GET_SOUND_ALARM_PARAM,
	CMD_ID_RESP_SET_SOUND_ALARM_PARAM,
	CMD_ID_RESP_SNAPSHOT,
	CMD_ID_RESP_GET_IRCUT_PARAM,
	CMD_ID_RESP_SET_IRCUT_PARAM,
	CMD_ID_RESP_GET_REC_PARAM,
	CMD_ID_RESP_SET_REC_PARAM,
	CMD_ID_RESP_PLAYBACK_QUERY,
	CMD_ID_RESP_PLAYBACK_START,
	CMD_ID_RESP_PLAYBACK_STOP,
	CMD_ID_RESP_PLAYBACK_SEEK,
	CMD_ID_RESP_GET_WIFI_PARAM,
	CMD_ID_RESP_SET_WIFI_PARAM,
	CMD_ID_RESP_GET_WIFI_LIST,
	CMD_ID_RESP_UPDATE_WIFI_LIST,
	CMD_ID_RESP_GET_NETWORK_PARAM,
	CMD_ID_RESP_SET_NETWORK_PARAM,
	CMD_ID_RESP_GET_FTP_PARAM,
	CMD_ID_RESP_SET_FTP_PARAM,
	CMD_ID_RESP_FORCE_KEY_FRAME_CMD,
	CMD_ID_RESP_GET_SNAPSHOT_QUALITY_CMD,
	CMD_ID_RESP_SET_SNAPSHOT_QUALITY_CMD,
	CMD_ID_RESP_GET_OSD_PARAM_CMD,
	CMD_ID_RESP_SET_OSD_PARAM_CMD,
	CMD_ID_RESP_UPGRADE_BEFORE_WRITE_FLASH,
	CMD_ID_RESP_GET_VERSION_CMD,
	CMD_ID_RESP_BURN_DEV_LIC_REQ_CMD,
	CMD_ID_RESP_GET_DEVICE_LICENSE_INFO_CMD,
	CMD_ID_RESP_TEST_IRCUT_OPEN,
	CMD_ID_RESP_TEST_IRCUT_CLOSE,
	CMD_ID_RESP_DEBUG_OPEN_TELNET_CMD,
	CMD_ID_RESP_DEBUG_CLOSE_TELNET_CMD,
	CMD_ID_RESP_START_AI_AO_LOOP_CMD,
	CMD_ID_RESP_STOP_AI_AO_LOOP_CMD,
	CMD_ID_RESP_START_SDCARD_TEST_CMD,
	CMD_ID_RESP_STOP_SDCARD_TEST_CMD,
	CMD_ID_RESP_GET_AUTO_MAINTENANCE_ATTR_CMD,
	CMD_ID_RESP_SET_AUTO_MAINTENANCE_ATTR_CMD,
	CMD_ID_RESP_SET_AUDIO_ATTR_CMD,
	CMD_ID_RESP_GET_AUDIO_ATTR_CMD,
	CMD_ID_RESP_GET_DEBUG_LOG_STATUS_CMD,
	CMD_ID_RESP_SET_DEBUG_LOG_STATUS_CMD,



	CMD_ID_POST_BASE			= 0x300000,		// post CMD ,need not response
	CMD_ID_POST_RESET_CMD,
	CMD_ID_POST_RESET_CODEC_CMD,
	CMD_ID_POST_SDCARD_TEST_RESULT,
	

	CMD_ID_BROADCAST_BASE		= 0x400000,		// broadcast CMD
	CMD_ID_BROADCAST_MOTION_DETECTED,
	CMD_ID_BROADCAST_MOTION_STOPED,
	CMD_ID_BROADCAST_WIFI_CONNECTED,
	CMD_ID_BROADCAST_WIFI_DISCONNECTED,
	CMD_ID_BROADCAST_RESET,
	CMD_ID_BROADCAST_UPGRADE,
	CMD_ID_BROADCAST_EXPORT,
	CMD_ID_BROADCAST_IMPORT,
	CMD_ID_BROADCAST_DEV_LICENSE_BURNED,


	CMD_ID_BULK_SEND_VIDEO_DATA		= 0x500000,
	CMD_ID_BULK_SEND_AUDIO_DATA,
	CMD_ID_BULK_RECV_AUDIO_DATA,
	CMD_ID_BULK_RECV_FIRMWARE,
	CMD_ID_BULK_RECV_IMPORT_CONFIG_FILE,
	CMD_ID_BULK_SEND_EXPORT_CONFIG_FILE,
	CMD_ID_BULK_SEND_PLAYBACK_VIDEO_DATA,
	CMD_ID_BULK_SEND_PLAYBACK_AUDIO_DATA,
	
};
/*
	upgrade.
	1.notify other process release memory,we will download firmware.
		a.msg server/main controller/dog/misc dev will exist
		b.network hold 
		c.download process exist.eg tx_device_svr
		d.codec and rtsp server exit,and codec ko rmmod...
		e.clear /tmp dir 
	2.check  memory size,free memory size must be large than firmware size.
	3.if memory ok,download firmware
	4.download firmware ok.
	5.send msg to main controller,preper to write flash
	6.main controller uncompress firmware.and get upgrade process.
	7.upgrade do last work.


*/


enum {
	ERROR_NONE 				= 0,
	ERROR_CONNECT_NOT_EXIST,
	ERROR_SEND_MSG_ERROR,
	ERROR_RECV_MSG_ERROR,
	ERROR_TIMEOUT,
	ERROR_MSG_SIZE_INVALID,
	ERROR_CMD_LOGIN_FAILED,
	ERROR_CMD_LOGOUT_FAILED,
	ERROR_CMD_HEART_FAILED,
	ERROR_CMD_GET_DEVICE_INFO_FAILED,
	ERROR_CMD_GET_DEVICE_STATUS_FAILED,
	ERROR_CMD_GET_DEVICE_CAPACITY_FAILED,
	ERROR_CMD_GET_USER_LIST_FAILED,
	ERROR_CMD_ADD_USER_FAILED,
	ERROR_CMD_DEL_USER_FAILED,
	ERROR_CMD_MODIFY_USER_PASSWORD_FAILED,
	ERROR_CMD_GET_DEVICE_TIME_FAILED,
	ERROR_CMD_SET_DEVICE_TIME_FAILED,
	ERROR_CMD_REBOOT_FAILED,
	ERROR_CMD_INVALID_USER_NAME,
	ERROR_CMD_INVALID_PASSWORD,
	ERROR_CMD_INVALID_PRIVILEGE,
	ERROR_CMD_GET_VENC_FAILED,
	ERROR_CMD_SET_VENC_FAILED,

	ERROR_CMD_GET_VI_FAILED,
	ERROR_CMD_SET_VI_FAILED,
	ERROR_CMD_SESSION_NOT_LOGIN,
	ERROR_CMD_FORCE_KEY_FAILED,
	ERROR_CMD_SNAPSHOT_FAILED,
	ERROR_CMD_GET_SNAPSHOT_QUALITY_FAILED,
	ERROR_CMD_SET_SNAPSHOT_QUALITY_FAILED,
	ERROR_CMD_GET_MOTION_DETECT_PARAM_FAILED,
	ERROR_CMD_SET_MOTION_DETECT_PARAM_FAILED,
	ERROR_CMD_GET_OSD_PARAM_FAILED,
	ERROR_CMD_SET_OSD_PARAM_FAILED,
	ERROR_CMD_GET_WIFI_PARAM_FAILED,
	ERROR_CMD_SET_WIFI_PARAM_FAILED,
	ERROR_CMD_PARAM_IS_NULL,
	ERROR_CMD_PARAM_INVALID,
	ERROR_CMD_GET_NETWORK_STATUS_FAILED,
	ERROR_CMD_SET_NETWORK_ATTR_FAILED,
	ERROR_CMD_UPGRADE_BEFORE_DOWNLOAD,
	ERROR_CMD_UPGRADE_BEFORE_WRITE_FLASH,
	ERROR_CMD_GET_VERSION_FAILED,
	ERROR_CMD_OPEN_VIDEO_STREAM_TYPE_NOT_SUPPORT,
	ERROR_CMD_OPEN_VIDEO_STREAM_HAD_OPENED,
	ERROR_CMD_CLOSE_VIDEO_NOT_STREAM_OPENED,
	ERROR_CMD_CLOSE_VIDEO_STREAM_NOT_OPENED,
	ERROR_CMD_OPEN_AUDIO_STREAM_HAD_OPENED,
	ERROR_CMD_CLOSE_AUDIO_STREAM_HAD_STOPED,
	ERROR_CMD_INVALID_STREAM_TYPE,
	ERROR_CMD_OPEN_VIDEO_FAILED,
	ERROR_CMD_OPEN_AUDIO_FAILED,
	ERROR_CMD_OPEN_SPEAKER_FAILED,
	ERROR_CMD_CLOSE_VIDEO_FAILED,
	ERROR_CMD_CLOSE_AUDIO_FAILED,
	ERROR_CMD_CLOSE_SPEAKER_FAILED,
	ERROR_CMD_PLAYBACK_QUERY_FAILED,
	ERROR_CMD_PLAYBACK_START_FAILED,
	ERROR_CMD_PLAYBACK_STOP_FAILED,
	ERROR_CMD_GET_STORAGE_CONFIG_FAILED,
	ERROR_CMD_SET_STORAGE_CONFIG_FAILED,
	ERROR_CMD_POST_MSG_FAILED,
	ERROR_CMD_LOCAL_UNIX_SOCKET_NOT_SUPPORT,
	ERROR_CMD_AV_CALLBACK_FUNC_NULL,
	ERROR_CMD_AV_CALLBACK_ARGS_NULL,
	ERROR_CMD_AV_CALLBACK_ARGS_INVALID,
	ERROR_CMD_AV_CALLBACK_HANDLER_NOT_SET,
	ERROR_CMD_FW_FILE_NOT_EXIST,
	ERROR_CMD_FW_READ_ERROR,
	ERROR_CMD_FW_SEND_ERROR,
	ERROR_CMD_GET_STORAGE_STATUS_ERR,
	ERROR_CMD_BURN_DEV_LIC_FAILED,
	ERROR_CMD_BURN_DEV_LIC_FILE_SIZE_INVALID,
	ERROR_CMD_BURN_WRITE_TMP_DEV_LIC_FAILED,
	ERROR_CMD_DEV_LIC_FILE_INVALID,
	ERROR_CMD_GET_DEV_LICENSE_INFO_FAILED,
	ERROR_CMD_GET_IRCUT_MODE_FAILED,
	ERROR_CMD_SET_IRCUT_MODE_FAILED,
	ERROR_CMD_TEST_IRCUT_OPEN_FAILED,
	ERROR_CMD_TEST_IRCUT_CLOSE_FAILED,
	ERROR_CMD_DEBUG_OPEN_TELNET_FAILED,
	ERROR_CMD_DEBUG_CLOSE_TELNET_FAILED,
	ERROR_CMD_OPEN_AI_AO_LOOP_FAILED,
	ERROR_CMD_CLOSE_AI_AO_LOOP_FAILED,
	ERROR_CMD_START_SDCARD_TEST_FAILED,
	ERROR_CMD_STOP_SDCARD_TEST_FAILED,
	ERROR_CMD_GET_AUTO_MAINTENANCE_ATTR_FAILED,
	ERROR_CMD_SET_AUTO_MAINTENANCE_ATTR_FAILED,
	ERROR_CMD_SET_AUDIO_ATTR_FAILED,
	ERROR_CMD_GET_AUDIO_ATTR_FAILED,
	ERROR_CMD_GET_DEBUG_STATUS_FAILED,
	ERROR_CMD_SET_DEBUG_STATUS_FAILED,
	ERROR_CMD_DEBUG_SERVICE_NOT_RUNNING,
	ERROR_CMD_TALK_ON_HAD_OPENED,
	ERROR_CMD_CLEAR_FACE_DB_MC_FAILED,
	ERROR_CMD_CLEAR_FACE_DB_MC_NULL,
	ERROR_CMD_MC_IS_NULL,
	ERROR_CMD_GET_SOUND_PLAY_PARAM_FAILED,
	ERROR_CMD_SET_SOUND_PLAY_PARAM_FAILED,
	ERROR_CMD_SET_SOUND_PLAY_PARAM_INVALID,
	
};




#define SESSION_ERR(e) (-e) 





#define MAX_NAME_LEN 32
#define MAX_PASSWORD_LEN 32


#if 0
typedef struct {
	char user[MAX_NAME_LEN + 1];
	char password[MAX_PASSWORD_LEN + 1];
	uint16_t encrypt;
}__attribute__((packed))LOGIN_INFO;


typedef struct{
	int32_t result;
	uint32_t id;
}__attribute__((packed))LOGIN_RESULT;

typedef struct {
	uint32_t id;
	uint32_t reserved;
}__attribute__((packed))LOGOUT_INFO;

typedef struct{
	int32_t result;
	uint32_t id;
}__attribute__((packed))LOGOUT_RESULT;




typedef struct{
	uint32_t index;
	uint32_t reserved;
}__attribute__((packed))HEARTBEAT_INFO;


typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))HEARTBEAT_RESULT;


#if 0
typedef struct{
	uint32_t reserved;
}__attribute__((packed))GET_DEVICEINFO_CMD;



typedef struct{
	int32_t result;
	PRODUCT_INFO productInfo;
}__attribute__((packed))GET_DEVICEINFO_CMD_RESULT;


typedef struct{
	uint32_t reserved;
}__attribute__((packed))GET_DEVICE_STATUS_CMD;



typedef struct{
	int32_t result;
	DEVICE_STATUS devStatus;
}__attribute__((packed))GET_DEVICE_STATUS_CMD_RESULT;





typedef struct{
	uint32_t reserved;
}__attribute__((packed))GET_DEVICE_CAP_CMD;



typedef struct{
	int32_t result;
	DEVICE_CAPACITY devCap;
}__attribute__((packed))GET_DEVICE_CAP_CMD_RESULT;

#endif

#define MAX_ACCOUT_COUNT 16



typedef struct{
	char user[MAX_NAME_LEN + 1];
	char password[MAX_PASSWORD_LEN + 1];
	uint16_t privilege;
}__attribute__((packed))ACCOUT;


typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_USER_LIST_CMD;

typedef struct{
	uint32_t count;
	ACCOUT accout[MAX_ACCOUT_COUNT];
}__attribute__((packed))USER_LIST;



typedef struct{
	int32_t result;
	uint32_t count;
	ACCOUT accout[MAX_ACCOUT_COUNT];
}__attribute__((packed))GET_USER_LIST_CMD_RESULT;

typedef struct{
	ACCOUT account;
}__attribute__((packed))ADD_USER_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))ADD_USER_CMD_RESULT;


typedef struct{
	char user[MAX_NAME_LEN + 1];
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t reserved3;	
}__attribute__((packed))DEL_USER_CMD;


typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))DEL_USER_CMD_RESULT;


typedef struct{
	char user[MAX_NAME_LEN + 1];
	char password[MAX_PASSWORD_LEN + 1];
	uint16_t reserved;
}__attribute__((packed))MODIFY_USER_PASSWORD_CMD;


typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))MODIFY_USER_PASSWORD_CMD_RESULT;


typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_DEVICE_INFO_CMD;


typedef struct{
	int32_t result;
	uint32_t reserved;
	DEVICE_INFO device_info;
}__attribute__((packed))GET_DEVICE_INFO_CMD_RESULT;



typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_DEVICE_STATUS_CMD;


typedef struct{
	int32_t result;
	DEVICE_STATUS device_stat;
}__attribute__((packed))GET_DEVICE_STATUS_CMD_RESULT;



typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_DEVICE_CAP_CMD;


typedef struct{
	int32_t result;
	DEVICE_CAPACITY device_cap;
}__attribute__((packed))GET_DEVICE_CAP_CMD_RESULT;





typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_DEVICE_TIME_CMD;



typedef struct{
	uint32_t result;
	uint32_t reserved;
	DEVICE_TIME devTime;
}__attribute__((packed))GET_DEVICE_TIME_CMD_RESULT;


typedef struct{
	DEVICE_TIME devTime;
}__attribute__((packed))SET_DEVICE_TIME_CMD;



typedef struct{
	uint32_t result;
	uint32_t reserved;
}__attribute__((packed))SET_DEVICE_TIME_CMD_RESULT;


typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))REBOOT_CMD;

typedef struct{
	uint32_t result;
	uint32_t reserved;
}__attribute__((packed))REBOOT_CMD_RESULT;


typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_VIDEO_ENC_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
	VIDEO_ENC_ATTR VencParam;
}__attribute__((packed))GET_VIDEO_ENC_PARAM_CMD_RESULT;



typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))FORCE_KEY_FRAME_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))FORCE_KEY_FRAME_CMD_RESULT;





typedef struct{
	VIDEO_ENC_ATTR VencParam;
}__attribute__((packed))SET_VIDEO_ENC_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))SET_VIDEO_ENC_PARAM_CMD_RESULT;




typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_VIDEO_INPUT_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
	VIDEO_INPUT_ATTR ViParam;
}__attribute__((packed))GET_VIDEO_INPUT_PARAM_CMD_RESULT;


typedef struct{
	VIDEO_INPUT_ATTR ViParam;
}__attribute__((packed))SET_VIDEO_INPUT_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))SET_VIDEO_INPUT_PARAM_CMD_RESULT;

typedef struct{
	char  jpegFileName[256];
}__attribute__((packed))SNAPSHOT_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))SNAPSHOT_PARAM_CMD_RESULT;

typedef struct{
	int32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_SNAPSHOT_PARAM_CMD;

typedef struct{
	int32_t result;
	int32_t level;
}__attribute__((packed))GET_SNAPSHOT_PARAM_CMD_RESULT;

typedef struct{
	int32_t level;
	uint32_t reserved;
}__attribute__((packed))SET_SNAPSHOT_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))SET_SNAPSHOT_PARAM_CMD_RESULT;

typedef struct{
	int32_t enable;
	int32_t sensitivity;
}__attribute__((packed))SET_MOTION_DETECT_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))SET_MOTION_DETECT_PARAM_CMD_RESULT;


typedef struct{
	int32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_MOTION_DETECT_PARAM_CMD;

typedef struct{
	int32_t result;
	int32_t enable;
	int32_t sensitivity;
	uint32_t reserved;
}__attribute__((packed))GET_MOTION_DETECT_PARAM_CMD_RESULT;





typedef struct{
	OSD_PARAM osd;
}__attribute__((packed))SET_OSD_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))SET_OSD_PARAM_CMD_RESULT;


typedef struct{
	int32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_OSD_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
	OSD_PARAM osd;
}__attribute__((packed))GET_OSD_PARAM_CMD_RESULT;



typedef struct{
	WIFI_BASIC_ATTR attr;
}__attribute__((packed))SET_WIFI_PARAM_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))SET_WIFI_PARAM_CMD_RESULT;



typedef struct{
	int32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_WIFI_PARAM_CMD;



typedef struct{
	int32_t result;
	uint32_t reserved;
	WIFI_INFO info;
}__attribute__((packed))GET_WIFI_PARAM_CMD_RESULT;



typedef struct{
	int32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))GET_NETWORK_STATUS_CMD;

typedef struct{
	int32_t result;
	uint32_t reserved;
	NETWORK_STATUS status;
}__attribute__((packed))GET_NETWORK_STATUS_CMD_RESULT;


typedef struct{
	NETWORK_ATTR attr;
}__attribute__((packed))SET_NETWORK_ATTR_CMD;

typedef struct{
	int32_t result;
}__attribute__((packed))SET_NETWORK_ATTR_CMD_RESULT;


typedef struct{
	uint32_t reserved;
}__attribute__((packed))POST_RESET_CMD;

typedef struct{
	uint32_t reserved;
}__attribute__((packed))POST_RESET_CODEC_CMD;



typedef struct{
	char requester[64];  // upgrade requester
}__attribute__((packed))UPGRADE_CMD;

typedef struct{
	int32_t result;			// 0:just imply recv upgrade,we will upgrade ;  < 0 :error
	int32_t freeMemSize;	// free memory size ,must be large than firmware size...
}__attribute__((packed))UPGRADE_CMD_RESULT;


typedef struct{
	char requester[64];  // upgrade requester
	char firmware[256];	 // firmware path;
}__attribute__((packed))UPGRADE_CMD_BEFORE_WRITE_FLASH;

typedef struct{
	int32_t result;			// 0:just imply recv upgrade,we will upgrade ;  < 0 :error
						// recv resp msg,you need exit to release memory...
}__attribute__((packed))UPGRADE_CMD_BEFORE_WRITE_FLASH_RESULT;



typedef struct{
	int32_t reserved;
}__attribute__((packed))GET_VERSION_CMD;

typedef struct{
	int32_t result;
	uint8_t sysVer1;
	uint8_t sysVer2;
	uint8_t sysVer3;
	uint8_t sysVer4;
	uint8_t appVer1;
	uint8_t appVer2;
	uint8_t appVer3;
	uint8_t appVer4;

}__attribute__((packed))GET_VERSION_CMD_RESULT;


#define MAX_DEV_LIC_SIZE (24 * 1024)
typedef struct{
	uint32_t size;
	uint8_t data[MAX_DEV_LIC_SIZE];
}__attribute__((packed))BURN_DEV_LIC_REQ;

typedef struct{
	int32_t result;
	int32_t reserved;
}BURN_DEV_LIC_RESP;


typedef struct{
	int32_t reserved;
	int32_t reserved2;
}GET_DEV_LICENSE_INFO_REQ;

typedef struct{
	int32_t result;
	int32_t reserved;
	DEV_LICENSE_INFO info;
}GET_DEV_LICENSE_INFO_RESP;


/*
enum{
	ENUM_STREAM_TYPE_MAIN	= 0,
	ENUM_STREAM_TYPE_SUB,
	ENUM_STREAM_TYPE_JPEG,
	ENUM_STREAM_TYPE_MJPEG,
	ENUM_STREAM_TYPE_COUNT,
};


*/
typedef struct{
	int32_t streamType; // ENUM_STREAM_TYPE_XXX
}__attribute__((packed))OPEN_VIDEO_CMD;

typedef struct{
	int32_t result;
}__attribute__((packed))OPEN_VIDEO_CMD_RESULT;


typedef struct{
	int32_t streamType; // ENUM_STREAM_TYPE_XXX
}__attribute__((packed))OPEN_AUDIO_CMD;

typedef struct{
	int32_t result;
}__attribute__((packed))OPEN_AUDIO_CMD_RESULT;


typedef struct{
	int32_t streamType; // ENUM_STREAM_TYPE_XXX
}__attribute__((packed))OPEN_SPEAKER_CMD;

typedef struct{
	int32_t result;
}__attribute__((packed))OPEN_SPEAKER_CMD_RESULT;









typedef struct{
	int32_t streamType; // ENUM_STREAM_TYPE_XXX
}__attribute__((packed))CLOSE_VIDEO_CMD;

typedef struct{
	int32_t result;
}__attribute__((packed))CLOSE_VIDEO_CMD_RESULT;


typedef struct{
	int32_t streamType; // ENUM_STREAM_TYPE_XXX
}__attribute__((packed))CLOSE_AUDIO_CMD;

typedef struct{
	int32_t result;
}__attribute__((packed))CLOSE_AUDIO_CMD_RESULT;


typedef struct{
	int32_t streamType; // ENUM_STREAM_TYPE_XXX
}__attribute__((packed))CLOSE_SPEAKER_CMD;

typedef struct{
	int32_t result;
}__attribute__((packed))CLOSE_SPEAKER_CMD_RESULT;


#endif

/////////////////////////////////////////////////////////////
//
//				PUSH MSG STRUCT
//
/////////////////////////////////////////////////////////////



typedef struct{
	uint64_t timestamp;	// system start time;
	time_t t;			// system time;
	uint32_t reserved;
}__attribute__((packed))__attribute__((packed))PUSH_MSG_MOTION_DETECTED;
typedef struct{
	uint64_t timestamp;	// system start time;
	time_t t;			// system time;
	uint32_t reserved;
}__attribute__((packed))PUSH_MSG_MOTION_STOPED;

typedef struct{
	int32_t reserved;
	int32_t reserved2;
}__attribute__((packed))PUSH_MSG_WIFI_CONNECTED;

typedef struct{
	int32_t reserved;
	int32_t reserved2;
}__attribute__((packed))PUSH_MSG_WIFI_DISCONNECT;

typedef struct{
	int32_t reserved;
	int32_t reserved2;
}__attribute__((packed))PUSH_MSG_RESET;


typedef struct{
	int32_t reserved;
	int32_t reserved2;
}__attribute__((packed))PUSH_DEV_LIC_BURNED_MSG;


typedef struct{
	uint32_t 	index;
	uint32_t 	totalSlice;
	uint32_t	totalSize;
	uint32_t  	endFlag;
	uint32_t  	playloadSize;
	uint8_t   	playload[0];
}__attribute__((packed))BULK_SLICE_MSG;







class CCtrlMsgEngine : public CMessageEngine
{
public:
	CCtrlMsgEngine(int sock,void * private_data);
//	CCtrlMsgEngine(int sock,void * private_data,void * pKey);
//	CCtrlMsgEngine(int sock,void * private_data,void * pKey,uint32_t nSendQueueSize,uint32_t nRecvBufSize,uint32_t nSendBufSize);
	virtual ~CCtrlMsgEngine();
	virtual void regMsg(MSG_HANDLE * msgHdl,uint32_t msgHdlSize,std::string & name);
	void init();
protected:
	virtual int doRecvData(void * data,uint32_t nSize);
	virtual bool isRespMsg(uint32_t respMsgId);
	
private:
	void * m_pPriData;
};





















#endif //__CCTRL_MSG_ENGINE_H__

