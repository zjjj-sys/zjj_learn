#ifndef __DEBUG_H__
#define __DEBUG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */



#define DEBUG_DEVICE_SERIAL_COM (1 << 1)
#define DEBUG_DEVICE_NETWORK    (1 << 2)
#define DEBUG_DEVICE_STORAGE 	(1 << 3)



typedef struct{
	uint8_t debugSwitch;
	uint8_t xsiot_rt_debug : 1;
	uint8_t codec_rt_debug : 1;
	uint8_t mc_rt_debug : 1;
	uint8_t miscdev_rt_debug : 1;
	uint8_t alarmadapter_rt_debug : 1;
	uint8_t rtspserver_rt_debug : 1;
	uint8_t storage_rt_debug : 1;
	uint8_t nvt_rt_debug : 1;
	uint8_t gui_rt_debug : 1;
	uint8_t upgrade_rt_debug : 1;
	uint8_t fh_body_detect_rt_debug : 1;
	uint8_t sdk_json_debug : 1;
	uint8_t ai_media_info_rt_debug : 1;
	uint8_t ai_detect_debug : 1;
	uint8_t img_mirror : 1;
	uint8_t img_flip : 1;
}DEBUG_CONTEXT;



void AH_COMM_DebugInit(void);
int  AH_COMM_DebugPrint(int debugLevel,const char * process,const char * file,const char * func,int line,const char * format,...);
void AH_COMM_DebugDeinit(void);


extern DEBUG_CONTEXT * g_pDebugCtx;




#define IS_FH_BODY_DETECT_RT_DEBUG_ENABLE (g_pDebugCtx && g_pDebugCtx->fh_body_detect_rt_debug)
#define IS_FH_NVT_RT_DEBUG_ENABLE (g_pDebugCtx && g_pDebugCtx->nvt_rt_debug)
#define IS_STORAGE_RT_DEBUG_ENABLE (g_pDebugCtx && g_pDebugCtx->storage_rt_debug)






#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */







#endif //__DEBUG_H__


