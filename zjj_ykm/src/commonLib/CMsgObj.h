#ifndef __CCOM_MSG_OBJ_H__
#define __CCOM_MSG_OBJ_H__



#include "common.h"
#include "commFunc.h"
#include <iostream>
#include <functional>

typedef std::function<void(void *)> OBJECT_DELETE_FUNC;


class CMsgObj
{
public:
	CMsgObj(uint32_t msgid,void * pMsg,OBJECT_DELETE_FUNC fDeleteFunc,uint32_t nMsgSize = 0);
	virtual ~CMsgObj();
	void * data();
	uint32_t datasize();
	uint32_t msgid();
private:
	void *	m_pMsg;
	uint32_t m_nMsgId;
	OBJECT_DELETE_FUNC 	m_fDeleteFunc;
	uint32_t m_nMsgSize ; // if pMsg is object, m_nMsgSize is 0;otherwise need set m_nMsgSize
};



typedef enum{
	// meian platform 
	enum_msg_obj_msg_id_meian_plat_init  		= 0x1000,
	enum_msg_obj_msg_id_meian_auth_socket_delete,
	enum_msg_obj_msg_id_meian_create_register_socket,
	enum_msg_obj_msg_id_meian_register_socket_delete,
	enum_msg_obj_msg_id_meian_register_socket_reg_ready,
	enum_msg_obj_msg_id_meian_rt_stream_socket_delete,
	enum_msg_obj_msg_id_meian_rt_stream_socket_reg_ready,
	enum_msg_obj_msg_id_meian_pb_stream_socket_delete,
	enum_msg_obj_msg_id_meian_pb_stream_socket_reg_ready,
	enum_msg_obj_msg_id_meian_alarm_msg_push,
	enum_msg_obj_msg_id_meian_match_code_result_push,
	enum_msg_obj_msg_id_meian_switch_status_changed_push,
	enum_msg_obj_msg_id_meian_ipcam_search_result_push,
	enum_msg_obj_msg_id_meian_request_alarm_video,
	enum_msg_obj_msg_id_meian_alarm_video_upload_socket_delete,
	enum_msg_obj_msg_id_meian_gadget_serial_com_report_msg,



	//////////////////////////////////////////////////////////////

	enum_msg_obj_msg_id_xsiot_init  		= 0x2000,
	enum_msg_obj_msg_id_xsiot_socket_delete,

}MSG_OBJ_MSG_ID;



#endif //__CCOM_MSG_OBJ_H__


