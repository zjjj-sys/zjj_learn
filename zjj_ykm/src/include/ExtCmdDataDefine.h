#ifndef __EXT_CMD_DATA_DEFINE_H__
#define __EXT_CMD_DATA_DEFINE_H__

#include "IPCMsgDataType.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */





#define CONFIG_MAX_SLICE_FRAME_SIZE (1 << 16)
#define CONFIG_MAX_EXT_MSG_SIZE (1 << 20)

#define CMD_EXTEN_BULK_CMD 0xcc80 





typedef enum{
	// send msg...
	enum_ext_cmd_add_face_to_white_list		= 0xf0000000,
	enum_ext_cmd_add_face_to_black_list,
	enum_ext_cmd_del_face_in_white_list,
	enum_ext_cmd_del_face_in_black_list,
	enum_ext_cmd_edit_face_in_white_list,
	enum_ext_cmd_edit_face_in_black_list,
	enum_ext_cmd_get_white_list,
	enum_ext_cmd_get_black_list,
	enum_ext_cmd_start_export_face_db,
	enum_ext_cmd_stop_export_face_db,
	enum_ext_cmd_start_import_face_db,
	enum_ext_cmd_stop_import_face_db,
	enum_ext_cmd_query_sensetime_sdk_satatus,
	enum_ext_cmd_get_mqtt_adapter_param_req,
	enum_ext_cmd_set_mqtt_adapter_param_req,
	enum_ext_cmd_get_door_electric_relay_param_req,
	enum_ext_cmd_set_door_electric_relay_param_req,	
	enum_ext_cmd_get_access_voice_prompt_param_req,
	enum_ext_cmd_set_access_voice_prompt_param_req,	
	enum_ext_cmd_get_ai_input_image_size_req,
	enum_ext_cmd_get_extract_face_feature_req,
	enum_ext_cmd_get_rfid_reader_mode_req,
	enum_ext_cmd_set_rfid_reader_mode_req,
	enum_ext_cmd_add_rfid_req,
	enum_ext_cmd_del_rfid_req,
	enum_ext_cmd_get_body_detect_alarm_config_req,
	enum_ext_cmd_set_body_detect_alarm_config_req,
	enum_ext_cmd_get_product_model_req,
	enum_ext_cmd_clear_face_db_req,
	enum_ext_cmd_get_black_list_alarm_config_req,
	enum_ext_cmd_set_black_list_alarm_config_req,	
	enum_ext_cmd_get_alarm_sound_play_param_req,
	enum_ext_cmd_set_alarm_sound_play_param_req,
	enum_ext_cmd_get_double_sensor_white_light_ctrl_param_req,
	enum_ext_cmd_set_double_sensor_white_light_ctrl_param_req,
	enum_ext_cmd_get_face_area_ratio_req,
	enum_ext_cmd_set_face_area_ratio_req,
	enum_ext_cmd_get_body_temp_sns_param_req,
	enum_ext_cmd_set_body_temp_sns_param_req,	
	// 2021.04.25
	enum_ext_cmd_get_network_status_req,
    enum_ext_cmd_get_ethernet_param_req,
    enum_ext_cmd_set_ethernet_param_req,
    enum_ext_cmd_get_wifi_essid_password_req,
    enum_ext_cmd_set_wifi_essid_password_req,
    enum_ext_cmd_get_wifi_net_param_req,
    enum_ext_cmd_set_wifi_net_param_req,
    enum_ext_cmd_start_wifi_scan_req,
    enum_ext_cmd_stop_wifi_scan_req,

	// 2021.11.16
	enum_ext_cmd_get_ircut_param_req,
	enum_ext_cmd_set_ircut_param_req,
	enum_ext_cmd_get_image_mirror_flip_param_req,
	enum_ext_cmd_set_image_mirror_flip_param_req,
	enum_ext_cmd_ptz_ctrl_req,
	enum_ext_cmd_get_osd_param_req,
	enum_ext_cmd_set_osd_param_req,
	enum_ext_cmd_get_auto_maintenance_param_req,
	enum_ext_cmd_set_auto_maintenance_param_req,

	// response msg...
	enum_ext_cmd_add_face_to_white_list_result = 0xf0010000,
	enum_ext_cmd_add_face_to_black_list_result,
	enum_ext_cmd_del_face_in_white_list_result,
	enum_ext_cmd_del_face_in_black_list_result,
	enum_ext_cmd_edit_face_in_white_list_result,
	enum_ext_cmd_edit_face_in_black_list_result,
	enum_ext_cmd_get_white_list_result,
	enum_ext_cmd_get_black_list_result,
	enum_ext_cmd_start_export_face_db_result,
	enum_ext_cmd_start_import_face_db_result,
	enum_ext_cmd_add_face_result,
	enum_ext_cmd_query_sensetime_sdk_satatus_result,
	enum_ext_cmd_del_face_result,
	enum_ext_cmd_edit_face_result,
	enum_ext_cmd_get_mqtt_adapter_param_resp,
	enum_ext_cmd_set_mqtt_adapter_param_resp,
	enum_ext_cmd_get_door_electric_relay_param_resp,
	enum_ext_cmd_set_door_electric_relay_param_resp,	
	enum_ext_cmd_get_access_voice_prompt_param_resp,
	enum_ext_cmd_set_access_voice_prompt_param_resp,	
	enum_ext_cmd_get_ai_input_image_size_resp,
	enum_ext_cmd_get_extract_face_feature_resp,
	enum_ext_cmd_get_rfid_reader_mode_resp,
	enum_ext_cmd_set_rfid_reader_mode_resp,
	enum_ext_cmd_add_rfid_resp,
	enum_ext_cmd_del_rfid_resp,
	enum_ext_cmd_get_body_detect_alarm_config_resp,
	enum_ext_cmd_set_body_detect_alarm_config_resp,
	enum_ext_cmd_get_product_model_resp,
	enum_ext_cmd_clear_face_db_resp,
	enum_ext_cmd_get_black_list_alarm_config_resp,
	enum_ext_cmd_set_black_list_alarm_config_resp,
	enum_ext_cmd_get_alarm_sound_play_param_resp,
	enum_ext_cmd_set_alarm_sound_play_param_resp,	
	enum_ext_cmd_get_double_sensor_white_light_ctrl_param_resp,
	enum_ext_cmd_set_double_sensor_white_light_ctrl_param_resp,
	enum_ext_cmd_get_face_area_ratio_resp,
	enum_ext_cmd_set_face_area_ratio_resp,
	enum_ext_cmd_get_body_temp_sns_param_resp,
	enum_ext_cmd_set_body_temp_sns_param_resp,	
	// lifan 2021.04.25
	enum_ext_cmd_get_network_status_resp,
    enum_ext_cmd_get_ethernet_param_resp,
    enum_ext_cmd_set_ethernet_param_resp,
    enum_ext_cmd_get_wifi_essid_password_resp,
    enum_ext_cmd_set_wifi_essid_password_resp,
    enum_ext_cmd_get_wifi_net_param_resp,
    enum_ext_cmd_set_wifi_net_param_resp,
    enum_ext_cmd_start_wifi_scan_resp,
    enum_ext_cmd_stop_wifi_scan_resp,

	// 2021.11.16
	enum_ext_cmd_get_ircut_param_resp,
	enum_ext_cmd_set_ircut_param_resp,
	enum_ext_cmd_get_image_mirror_flip_param_resp,
	enum_ext_cmd_set_image_mirror_flip_param_resp,
	enum_ext_cmd_get_osd_param_resp,
	enum_ext_cmd_set_osd_param_resp,
	enum_ext_cmd_get_auto_maintenance_param_resp,
	enum_ext_cmd_set_auto_maintenance_param_resp,
	
	// post msg...

	enum_ext_cmd_push_export_face_db_result				= 0xf0020000,
	enum_ext_cmd_push_import_face_db_result,
	enum_ext_cmd_push_rfid_push_msg,
	enum_ext_cmd_push_rfid_auto_add_msg,
	enum_ext_cmd_push_wifi_scan_result_msg,
	enum_ext_cmd_push_ai_protobuf_lite_msg,
	// bulk msg...
	enum_ext_cmd_face_db_transfer			= 0xf0030000,



	enum_ext_cmd_stream_operation_base 		= 0xf0040000,
	enum_ext_cmd_stream_open_rt_video		= enum_ext_cmd_stream_operation_base,
	enum_ext_cmd_stream_open_rt_audio,
	enum_ext_cmd_stream_close_rt_video,
	enum_ext_cmd_stream_close_rt_audio,
	enum_ext_cmd_stream_open_rt_talk,
	enum_ext_cmd_stream_close_rt_talk,


	enum_ext_cmd_stream_video_bulk_data		= 0xf0050000,
	enum_ext_cmd_stream_audio_bulk_data,
	enum_ext_cmd_stream_talk_bulk_data,
	enum_ext_cmd_stream_rt_data, 


	enum_ext_cmd_json_msg_to_dev		 	= 0xf0060000,
	enum_ext_cmd_json_msg_to_client,
}ENUM_EXT_CMD;


typedef struct{
	uint32_t cmd;			// ENUM_EXT_CMD
    uint32_t total_size;
    uint32_t slice_size;
    uint32_t frame_index:24;
    uint32_t end_flag:1;
    uint32_t reserved:7;
	uint64_t token;
    uint8_t  data[0];
}__attribute__((packed))EXT_MSG_SLICE_FRAME;




typedef struct{
	int32_t result;  // ENUM_ADD_FACE_RESULT;
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_BODY_ADD_FACE_RESULT;



typedef struct{
	uint32_t faceid;
}__attribute__((packed))EXT_MSG_BODY_DEL_FACE_REQ;


typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_BODY_DEL_FACE_RESULT;

typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_BODY_EDIT_FACE_RESULT;

typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_BODY_START_EXPORT_FACE_DB;
typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_BODY_START_EXPORT_FACE_DB_RESULT;
typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_BODY_STOP_EXPORT_FACE_DB;
typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_BODY_STOP_EXPORT_FACE_DB_RESULT;

typedef struct{
	uint32_t size;
	uint32_t crc_val;
}__attribute__((packed))EXT_MSG_BODY_START_IMPORT_FACE_DB;
typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_BODY_START_IMPORT_FACE_DB_RESULT;
typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_BODY_STOP_IMPORT_FACE_DB;
typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_BODY_STOP_IMPORT_FACE_DB_RESULT;


typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))EXT_MSG_BODY_QUERY_SENSETIME_SDK_STATUS_REQ;


typedef struct{
	uint32_t status;
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_BODY_QUERY_SENSETIME_SDK_STATUS_RESULT;




typedef struct{
	uint32_t total_size;
	uint32_t slice_size;
	uint32_t slice_index;
	uint32_t end_flag:1;
	uint32_t reserved:31;
	uint8_t data[0];
}EXT_MSG_BODY_FACE_DB_SLICE_HEADER;

typedef enum{
	enum_face_db_export_result_ok 			= 0,
	enum_face_db_export_result_db_empty 	= -1,
	enum_face_db_export_result_db_open_err	= -2,
	enum_face_db_export_result_read_io_err	= -3,
	enum_face_db_export_result_send_err		= -4,
}FACE_DB_EXPORT_RESULT;







typedef struct{
	int32_t result ; // FACE_DB_EXPORT_RESULT
}EXT_MSG_BODY_PUSH_EXPORT_FACE_DB_RESULT;


typedef struct{
	int32_t result ; // FACE_DB_IMPORT_RESULT
}EXT_MSG_BODY_PUSH_IMPORT_FACE_DB_RESULT;





typedef struct{
	uint32_t reserved;
}EXT_MSG_GET_MQTT_ADAPTER_PARAM_REQ;
typedef struct{
	int result;
	MQTT_ADAPTER_PARAM param;
}EXT_MSG_GET_MQTT_ADAPTER_PARAM_RESP;
typedef struct{
	MQTT_ADAPTER_PARAM param;
}EXT_MSG_SET_MQTT_ADAPTER_PARAM_REQ;
typedef struct{
	int result;
}EXT_MSG_SET_MQTT_ADAPTER_PARAM_RESP;



typedef struct{
	uint32_t reserved;
}EXT_MSG_GET_DOOR_ELECTRIC_RELAY_PARAM_REQ;
typedef struct{
	int result;
	DOOR_ELECTRIC_RELAY_PARAM param;
}EXT_MSG_GET_DOOR_ELECTRIC_RELAY_PARAM_RESP;
typedef struct{
	DOOR_ELECTRIC_RELAY_PARAM param;
}EXT_MSG_SET_DOOR_ELECTRIC_RELAY_PARAM_REQ;
typedef struct{
	int result;
}EXT_MSG_SET_DOOR_ELECTRIC_RELAY_PARAM_RESP;



typedef struct{
	uint32_t reserved;
}EXT_MSG_GET_ACCESS_VOICE_PROMPT_PARAM_REQ;
typedef struct{
	int result;
	ACCESS_VOICE_PROMPT_PARAM param;
}EXT_MSG_GET_ACCESS_VOICE_PROMPT_PARAM_RESP;
typedef struct{
	ACCESS_VOICE_PROMPT_PARAM param;
}EXT_MSG_SET_ACCESS_VOICE_PROMPT_PARAM_REQ;
typedef struct{
	int result;
}EXT_MSG_SET_ACCESS_VOICE_PROMPT_PARAM_RESP;


typedef struct{
	uint32_t reserved;
}EXT_MSG_GET_AI_INPUT_IMAGE_SIZE_REQ;
typedef struct{
	int result;
	AI_INPUT_IMAGE_SIZE size;
}EXT_MSG_GET_AI_INPUT_IMAGE_SIZE_RESP;


typedef struct{
	int32_t error_code;
	float face_quality;
	uint32_t feature_size;
	uint8_t feature[0];
}__attribute__((packed))FACE_FEATURE_EXTRACT_RESULT;

typedef struct{
	uint32_t jpeg_size;
	uint8_t jpeg[0];
}__attribute__((packed))EXT_MSG_EXTRACT_FACE_FEATURE_REQ;
typedef struct{
	int32_t result;
	FACE_FEATURE_EXTRACT_RESULT face;
}__attribute__((packed))EXT_MSG_EXTRACT_FACE_FEATURE_RESP;


typedef struct{
	char content[128];
}__attribute__((packed))EXT_MSG_REPORT_RFID_REQ;


typedef struct{
	char content[128];
}__attribute__((packed))EXT_MSG_ADD_RFID_REQ;



typedef struct{
	int32_t result;
	EXT_MSG_ADD_RFID_REQ req;
}__attribute__((packed))EXT_MSG_ADD_RFID_RESP,EXT_MSG_PUSH_AUTO_ADD_RFID_MSG;


typedef struct{
	char content[128];
}__attribute__((packed))EXT_MSG_DEL_RFID_REQ;


typedef struct{
	int32_t result;
	EXT_MSG_DEL_RFID_REQ req;
}__attribute__((packed))EXT_MSG_DEL_RFID_RESP;

typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_GET_RFID_READER_MODE_REQ;

typedef struct{
	int32_t result;
	uint32_t mode;
}__attribute__((packed))EXT_MSG_GET_RFID_READER_MODE_RESP;


typedef struct{
	uint32_t mode;
}__attribute__((packed))EXT_MSG_SET_RFID_READER_MODE_REQ;

typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_SET_RFID_READER_MODE_RESP;


typedef struct{
	uint32_t chn;    // default : 0 - ipc(Only one sensor) ,Face device(0 : MainSensor, 1 : AuxSensor), NVR (multichannel....)
	uint32_t stream; // default : 0 - main stream ; 1 - substream 
}__attribute__((packed))EXT_MSG_OPEN_RT_VIDEO_STREAM_REQ;
typedef struct{
	uint32_t chn;    // default : 0 - ipc(Only one sensor) ,Face device(0 : MainSensor, 1 : AuxSensor), NVR (multichannel....)
	uint32_t stream; // default : 0 - main stream ; 1 - substream 
}__attribute__((packed))EXT_MSG_OPEN_RT_AUDIO_STREAM_REQ;
typedef struct{
	uint32_t chn;    // default : 0 - ipc(Only one sensor) ,Face device(0 : MainSensor, 1 : AuxSensor), NVR (multichannel....)
	uint32_t stream; // default : 0 - main stream ; 1 - substream 
}__attribute__((packed))EXT_MSG_CLOSE_RT_VIDEO_STREAM_REQ;
typedef struct{
	uint32_t chn;    // default : 0 - ipc(Only one sensor) ,Face device(0 : MainSensor, 1 : AuxSensor), NVR (multichannel....)
	uint32_t stream; // default : 0 - main stream ; 1 - substream 
}__attribute__((packed))EXT_MSG_CLOSE_RT_AUDIO_STREAM_REQ;
typedef struct{
	uint32_t chn;    // default : 0 - ipc(Only one sensor) ,Face device(0 : MainSensor, 1 : AuxSensor), NVR (multichannel....)
	uint32_t stream; // default : 0 - main stream ; 1 - substream 
}__attribute__((packed))EXT_MSG_OPEN_RT_TALK_REQ;
typedef struct{
	uint32_t chn;    // default : 0 - ipc(Only one sensor) ,Face device(0 : MainSensor, 1 : AuxSensor), NVR (multichannel....)
	uint32_t stream; // default : 0 - main stream ; 1 - substream 
}__attribute__((packed))EXT_MSG_CLOSE_RT_TALK_REQ;


typedef struct {
	int32_t alarm_limit; // < 0 : No limit , 0 : Disable alarm msg upload, > 1 :Max upload alarm msg count...
	int32_t alarm_interval; // <= 0 : No limit > 1 : upload alarm msg interval ,Unit:second...
	uint32_t reserved[14];
}__attribute__((packed))BODY_DETECT_ALARM_CONFIG,FACE_COMPARE_RESULT_ALARM_CONFIG;

typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_GET_BODY_DETECT_ALARM_CONFIG_REQ;
typedef struct{
	int32_t result;
	BODY_DETECT_ALARM_CONFIG body;
}__attribute__((packed))EXT_MSG_GET_BODY_DETECT_ALARM_CONFIG_RESP;
typedef struct{
	BODY_DETECT_ALARM_CONFIG body;
}__attribute__((packed))EXT_MSG_SET_BODY_DETECT_ALARM_CONFIG_REQ;
typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_SET_BODY_DETECT_ALARM_CONFIG_RESP;


typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_GET_PRODUCT_MODEL_REQ;
typedef struct{
	int32_t result;
	uint32_t model;
}__attribute__((packed))EXT_MSG_GET_PRODUCT_MODEL_RESP;


typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_CLEAR_FACE_DB_REQ;
typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_CLEAR_FACE_DB_RESP;





typedef MSG_GET_SOUND_PLAY_PARAM_REQ  EXT_MSG_GET_SOUND_PLAY_PARAM_REQ;
typedef MSG_GET_SOUND_PLAY_PARAM_RESP  EXT_MSG_GET_SOUND_PLAY_PARAM_RESP;
typedef MSG_SET_SOUND_PLAY_PARAM_REQ  EXT_MSG_SET_SOUND_PLAY_PARAM_REQ;
typedef MSG_SET_SOUND_PLAY_PARAM_RESP  EXT_MSG_SET_SOUND_PLAY_PARAM_RESP;


typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))EXT_MSG_GET_DOUBLE_SENSOR_WHITE_LIGHT_CTRL_PARAM_REQ;
typedef struct{
	int32_t result;
	uint32_t reserved;
	DOUBLE_SENSOR_WHITE_LIGHT_CTRL_PARAM param;
}__attribute__((packed))EXT_MSG_GET_DOUBLE_SENSOR_WHITE_LIGHT_CTRL_PARAM_RESP;

typedef struct{
	DOUBLE_SENSOR_WHITE_LIGHT_CTRL_PARAM param;
}__attribute__((packed))EXT_MSG_SET_DOUBLE_SENSOR_WHITE_LIGHT_CTRL_PARAM_REQ;
typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_SET_DOUBLE_SENSOR_WHITE_LIGHT_CTRL_PARAM_RESP;




typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))EXT_MSG_GET_FACE_AREA_RATIO_REQ;
typedef struct{
	int32_t result;
	uint32_t reserved;
	FACE_AREA_RATIO_INFO param;
}__attribute__((packed))EXT_MSG_GET_FACE_AREA_RATIO_RESP;

typedef struct{
	FACE_AREA_RATIO_INFO param;
}__attribute__((packed))EXT_MSG_SET_FACE_AREA_RATIO_REQ;
typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_SET_FACE_AREA_RATIO_RESP;




typedef struct{
	uint32_t reserved;
	uint32_t reserved2;
}__attribute__((packed))EXT_MSG_GET_BODY_TEMPERATURE_SENSOR_REQ;
typedef struct{
	int32_t result;
	uint32_t reserved;
	BODY_TEMPERATURE_SENSOR_PARAM param;
}__attribute__((packed))EXT_MSG_GET_BODY_TEMPERATURE_SENSOR_RESP;

typedef struct{
	BODY_TEMPERATURE_SENSOR_PARAM param;
}__attribute__((packed))EXT_MSG_SET_BODY_TEMPERATURE_SENSOR_REQ;
typedef struct{
	int32_t result;
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_SET_BODY_TEMPERATURE_SENSOR_RESP;



// IRCUT param
typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_GET_IRCUT_PARAM_REQ;

typedef struct{
	int32_t result;
	uint32_t mode; // ENUM_IRCUT_MODE
}__attribute__((packed))EXT_MSG_GET_IRCUT_PARAM_RESP;

typedef struct{
	uint32_t mode; // ENUM_IRCUT_MODE
}__attribute__((packed))EXT_MSG_SET_IRCUT_PARAM_REQ;

typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_SET_IRCUT_PARAM_RESP;






// Image mirror/flip
typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_GET_IMAGE_MIRROR_FLIP_PARAM_REQ;

typedef struct{
	int32_t result;
	uint32_t mode; // ENUM_IMAGE_MIRROR_FLIP_MODE
}__attribute__((packed))EXT_MSG_GET_IMAGE_MIRROR_FLIP_PARAM_RESP;

typedef struct{
	uint32_t mode; // ENUM_IMAGE_MIRROR_FLIP_MODE
}__attribute__((packed))EXT_MSG_SET_IMAGE_MIRROR_FLIP_PARAM_REQ;

typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_SET_IMAGE_MIRROR_FLIP_PARAM_RESP;



// Ptz cmd
typedef struct{
	uint32_t cmd; // ENUM_PTZ_CMD
}__attribute__((packed))EXT_MSG_PTZ_CTRL_CMD_REQ;









// Osd param
typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_GET_OSD_PARAM_REQ;

typedef struct{
	int32_t result;
	OSD_PARAM osd;
}__attribute__((packed))EXT_MSG_GET_OSD_PARAM_RESP;

typedef struct{
	OSD_PARAM osd;
}__attribute__((packed))EXT_MSG_SET_OSD_PARAM_REQ;

typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_SET_OSD_PARAM_RESP;


// auto maintenance
typedef struct{
	uint32_t reserved;
}__attribute__((packed))EXT_MSG_GET_AUTO_MAINTENACE_PARAM_REQ;

typedef struct{
	int32_t result;
	uint32_t enable; 
}__attribute__((packed))EXT_MSG_GET_AUTO_MAINTENACE_PARAM_RESP;

typedef struct{
	uint32_t enable; 
}__attribute__((packed))EXT_MSG_SET_AUTO_MAINTENACE_PARAM_REQ;

typedef struct{
	int32_t result;
}__attribute__((packed))EXT_MSG_SET_AUTO_MAINTENACE_PARAM_RESP;





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */



#endif //__EXT_CMD_DATA_DEFINE_H__

