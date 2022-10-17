#ifndef __COMMON_H__
#define __COMMON_H__



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/prctl.h>
#include <sys/un.h>  
#include <pthread.h>
#include <unistd.h>
#ifndef x86
#define CONFIG_USE_DEBUG_SUBSYSTEM 1
#endif
#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"



extern char * gProcessName;
#define IPC_DEBUG_DECLARE(process_name) \
	char * gProcessName = (char *)process_name;\
	DEBUG_CONTEXT * g_pDebugCtx = NULL;



//#define IPC_DEBUG(s,...) {printf("<%8s[%24s]%6u>\t",gProcessName,__FILE__,__LINE__);printf(s,##__VA_ARGS__);}


#ifdef CONFIG_USE_DEBUG_SUBSYSTEM

#include "debug.h"

#define DEBUG_LOG_LEVEL_ERROR 0
#define DEBUG_LOG_LEVEL_WARN  1
#define DEBUG_LOG_LEVEL_INFO  2






#define DEBUG_INFO(s,...)  AH_COMM_DebugPrint(DEBUG_LOG_LEVEL_INFO,gProcessName,__FILE__,__FUNCTION__,__LINE__,s,##__VA_ARGS__)
#define DEBUG_WARN(s,...)  AH_COMM_DebugPrint(DEBUG_LOG_LEVEL_WARN,gProcessName,__FILE__,__FUNCTION__,__LINE__,s,##__VA_ARGS__)
#define DEBUG_ERROR(s,...) AH_COMM_DebugPrint(DEBUG_LOG_LEVEL_ERROR,gProcessName,__FILE__,__FUNCTION__,__LINE__,s,##__VA_ARGS__) 

#define LOGI(s,...)  AH_COMM_DebugPrint(DEBUG_LOG_LEVEL_INFO,gProcessName,__FILE__,__FUNCTION__,__LINE__,s,##__VA_ARGS__)
#define LOGW(s,...)  AH_COMM_DebugPrint(DEBUG_LOG_LEVEL_WARN,gProcessName,__FILE__,__FUNCTION__,__LINE__,s,##__VA_ARGS__)
#define LOGE(s,...) AH_COMM_DebugPrint(DEBUG_LOG_LEVEL_ERROR,gProcessName,__FILE__,__FUNCTION__,__LINE__,s,##__VA_ARGS__) 

#else

#define DEBUG_INFO(s,...)  {printf(NONE"<%8s[%24s]%6u>[INFO]",gProcessName,__FILE__,__LINE__);printf(s,##__VA_ARGS__);printf(NONE);}
#define DEBUG_WARN(s,...)  {printf(YELLOW"<%8s[%24s]%6u>[WARN]",gProcessName,__FILE__,__LINE__);printf(s,##__VA_ARGS__);printf(NONE);}
#define DEBUG_ERROR(s,...) {printf(LIGHT_RED"<%8s[%24s]%6u>[ERR ]",gProcessName,__FILE__,__LINE__);printf(s,##__VA_ARGS__);printf(NONE);} 

#endif

#define IPC_DEBUG DEBUG_INFO 


//generic message define...
typedef struct{
	uint32_t magic;
	uint32_t size;
	uint8_t  data[0];
}__attribute__((packed))GMSG_t;


#define MSG_SERVER_ADDR "/tmp/.msgServer"

#define CONFIG_MSG_TIMEOUT_S 5000



#define WEBSOCKET_LISTEN_PORT 8008
#define TCP_LISTEN_PORT 8000

#define UNIX_LISTEN_ADDR "/tmp/.unixSocket"
#if 0
#define DEVICE_DISCOVER_LISTEN_PORT 65532
#define DEVICE_DISCOVER_RESP_PORT 65533
#else
#define DEVICE_DISCOVER_LISTEN_PORT 8080
#define DEVICE_DISCOVER_RESP_PORT 8080

#endif
#ifdef x86
#define CONFIG_FILE_DIR "/tmp/param/"
#define CONFIG_ROM_DIR "/tmp/param/"

#else
#define CONFIG_FILE_DIR "/mnt/param/config/"
#define CONFIG_ROM_DIR "/mnt/param/ROM/"
#endif 

#define DEBUG_FILE_FLAG "/mnt/param/config/debug"
#define CONFIG_ISP_CALIBRATION_FLAG "/mnt/param/config/debugIsp"
#define CONFIG_MAX_MSG_FRAME_SIZE (16*1024)


#define DOG_FLAG_RESET 		"/tmp/dog.reset"
#define DOG_FLAG_UPGRADE 	"/tmp/dog.upgrade"
#define DOG_FLAG_REBOOT		"/tmp/dog.reboot"
#define DOG_FLAG_JUST_FEED  "/tmp/dog.feed"


#define SDCARD_MOUNT_DIR "/mnt/sd/"
#define SDCARD_FORMAT_FLAG_NAME "format.dont.remove.this.file"
#define SDCARD_FORMAT_FLAG_FILE "/mnt/sd/format.dont.remove.this.file"
#define SDCARD_FACTORY_TEST_FILE SDCARD_MOUNT_DIR"/factory/factory.json"
#define TMP_DIR_FACTORY_TEST_FILE "/tmp/.factory.json"

#if defined(MSC313E) || defined(MSC316DM)
#define SD_CARD_DEV_PATH "/dev/block/mmcblk0"
#define SD_CARD_DEV_NAME "/dev/block/mmcblk0p1"
#else
#define SD_CARD_DEV_PATH "/dev/mmcblk0"
#define SD_CARD_DEV_NAME "/dev/mmcblk0p1"
#endif 	

#define DISK_RECORD_PARTITION "/dev/sda"
#define DISK_RECORD_PARTITION_1 "/dev/sda1"

// /dev/mmcblk0p1 , mmc card
// /dev/mmcblk1p1 , sd card
#define MMC_RECORD_PARTITION "/dev/mmcblk1p1"

#define STORAGE_WROK_DIR "/mnt/sd/record"
#define STORAGE_MOUNT_DIR "/mnt/sd/"

#define RECV_FIRMWARE_FILE "/tmp/firmware.mc"			// ipcam upgrade firmware name
#define RECV_FIRMWARE_FILE_MOUNT_POINT "/mnt/reserved/"
#define RECV_FIRMWARE_FILE_IN_FLASH RECV_FIRMWARE_FILE_MOUNT_POINT"firmware.mc"			// ipcam upgrade (save in flash)firmware name
#define RECV_JPEG_FILE_IN_FLASH RECV_FIRMWARE_FILE_MOUNT_POINT"SaveJpeg"
#define RECV_MCU_FIRMWARE_FILE "/tmp/firmware.alarm"	// mcu upgrade firmware name


#define DEV_LICENSE_BIN_PATH CONFIG_ROM_DIR"uIPCam.lic"


#define SDCARD_LOG_DIR SDCARD_MOUNT_DIR".log/"
#define SDCARD_LOG_FILE_MAX_TOTAL_SIZE (32*1024*1024)
#define SDCARD_LOG_FILE_MAX_SIZE (1024 * 1024)



#define MT7601_WIFI_INTF_NAME "ra0"
#define RTL8188X_WIFI_INTF_NAME "wlan0"
#define S9083H_WIFI_INTF_NAME   "wlan0"
#define BROADCOM_WIFI_INTF_NAME   "wlan0"



#define RTSP_MAIN_STREAM_NAME "MainStream"
#define RTSP_SUB_STREAM_NAME "SubStream"

#define RTSP_AUX_MAIN_STREAM_NAME "AuxMainStream"
#define RTSP_AUX_SUB_STREAM_NAME "AuxSubStream"


#define CONFIG_OTA_UPGRADE_XML_FILE "/tmp/OTAUpgradeInfo.xml"


#define CONFIG_NVR_SUIT_FLAG (CONFIG_FILE_DIR"NVRSuit.flag")


#define CONFIG_FACE_DB_DIR "/mnt/data/face-db"
#define CONFIG_FACE_DB_PATH CONFIG_FACE_DB_DIR"/face.db"
#define CONFIG_FACE_DB_SINGLE_FACE_TMP_SAVE_PATH CONFIG_FACE_DB_DIR"/tmp/"
#define CONFIG_FACE_DB_MAX_SIZE (10*1024*1024)
#define CONFIG_FACE_DB_IMPORT_PATH CONFIG_FACE_DB_DIR"/face.db.import"

#define CONFIG_RFID_DB_DIR "/mnt/data/rfid-db"
#define CONFIG_RFID_DB_PATH CONFIG_RFID_DB_DIR"/rfid.db"
#define CONFIG_QRCODE_DB_DIR "/mnt/data/qrCode-db"
#define CONFIG_QRCODE_DB_PATH CONFIG_QRCODE_DB_DIR"/qrCode.db"

#define CONFIG_DEVICE_QRCODE_PIC_PATH "/tmp/DevQrCode.png"
#define CONFIG_UDISK_MOUNT_POINT "/mnt/udisk/"

#define CONFIG_MMC_TMP_DIR "/mnt/reserved/tmp"
#define CONFIG_MMC_TMP_FW_PATH CONFIG_MMC_TMP_DIR"/fw.bin"

#define CONFIG_DEV_IP_VOICE_PROMPTE_PLAYED_FLAG "/tmp/.dev.ip.voice.played"

/*
 * lifan @2020.07.02
 * Check C style string array valid.
 * eg.
 *     char str[2000];
 *     if str valid
 *			STRING_ARRAY_CHECK(str) return true value
 *     else
 *          STRING_ARRAY_CHECK(str) return true value
 *  WARNING:
 *		CHECK STRING MUST BE ARRAY TYPE!!!
 *		CHECK STRING MUST BE ARRAY TYPE!!!
 *		CHECK STRING MUST BE ARRAY TYPE!!!
 *		CHECK STRING MUST BE ARRAY TYPE!!!
 *
*/
#define STRING_ARRAY_CHECK(s) (strnlen(s,sizeof(s)) < sizeof(s))

/*
 * lifan @2020.07.02
 * Check C style string pointer valid.
 * eg.
 *     char str[2000];
 *	   char * pstr = str;
 *     if pstr valid
 *			STRING_POINTER_CHECK(pstr,2000) return true value
 *     else
 *          STRING_POINTER_CHECK(pstr,2000) return true value
 *
*/
#define STRING_POINTER_CHECK(s,maxSize) (strnlen(s,(maxSize)) < (maxSize))


#define CONFIG_MAX_FACE_ADD_QUEUE_SIZE 10000
#define CONFIG_INVALID_FLOOR (-10000)
#define CONFIG_LOCAL_GUI_SESSION_ID 0xffffffff


#define CONFIG_NVT_CHANGE_NETWORK_PARAM_FLAG "/tmp/.nvt.changed.net.flag"

#if defined(SV823)
#define CONFIG_TZ_ENV_FILE "/mnt/param/config/TZ"
#else
#define CONFIG_TZ_ENV_FILE "/tmp/TZ"
#endif

#define CONFIG_4G_MOD_NEED_RESET_FLAG "/tmp/.4gModNeedReset"
// xsiot . lifan @2022.01.14
#define CONFIG_XSIOT_UPLOAD_RESULT_JSON_FILE_PATH "/tmp/.xsiot_upload_result/"
#define CONFIG_XSIOT_UPLOAD_EVENT_FILE_PATH "/tmp/.xsiot_upload_event/"


#define STORAGE_RT_DEBUG_INFO(s,...) if(g_pDebugCtx && g_pDebugCtx->storage_rt_debug){DEBUG_INFO(s,##__VA_ARGS__);}
#define STORAGE_RT_DEBUG_WARN(s,...) if(g_pDebugCtx && g_pDebugCtx->storage_rt_debug){DEBUG_WARN(s,##__VA_ARGS__);}
#define STORAGE_RT_DEBUG_ERROR(s,...) if(g_pDebugCtx && g_pDebugCtx->storage_rt_debug){DEBUG_ERROR(s,##__VA_ARGS__);}

#define SDK_JSON_DEBUG_INFO(s,...) if(g_pDebugCtx && g_pDebugCtx->sdk_json_debug){DEBUG_INFO(s,##__VA_ARGS__);}
#define SDK_JSON_DEBUG_WARN(s,...) if(g_pDebugCtx && g_pDebugCtx->sdk_json_debug){DEBUG_WARN(s,##__VA_ARGS__);}
#define SDK_JSON_DEBUG_ERROR(s,...) if(g_pDebugCtx && g_pDebugCtx->sdk_json_debug){DEBUG_ERROR(s,##__VA_ARGS__);}

#define AI_DETECT_DEBUG_INFO(s,...) if(g_pDebugCtx && g_pDebugCtx->ai_detect_debug){DEBUG_INFO(s,##__VA_ARGS__);}
#define AI_DETECT_DEBUG_WARN(s,...) if(g_pDebugCtx && g_pDebugCtx->ai_detect_debug){DEBUG_WARN(s,##__VA_ARGS__);}
#define AI_DETECT_DEBUG_ERROR(s,...) if(g_pDebugCtx && g_pDebugCtx->ai_detect_debug){DEBUG_ERROR(s,##__VA_ARGS__);}








#define CONFIG_DATE_TIME_FMT "%04u/%02u/%02u %02u:%02u:%02u"

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __COMMON_H__ */









