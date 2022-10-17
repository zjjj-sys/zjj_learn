#ifndef __SHM_BUF_MEDIA_DATA_H__
#define __SHM_BUF_MEDIA_DATA_H__

#include "common.h"


#define META_DATA_MAGIC (('M') | ('E' << 8 ) | ('T' << 16) | ('A' << 24))



typedef enum{
	enum_meta_data_type_video = 0,	// reserved,video data isn't meta data... lifan @2019.11.18
	enum_meta_data_type_audio = 1,	// reserved,Audio data isn't meta data... lifan @2019.11.18
	enum_meta_data_type_svp_body_detect_info = 2,
	enum_meta_data_type_svp_face_detect_info = 3,
	enum_meta_data_type_svp_face_recogition  = 4,
	enum_meta_data_type_svp_rfcn_result		 = 5,

	/////////////////////////////////////////////////////
	enum_meta_data_type_sensetime_face_body_detect_result	= 100,
	enum_meta_data_type_sensetime_face_body_snapshot_pic,
	enum_meta_data_type_sensetime_face_feature_result ,
	enum_meta_data_type_sensetime_white_list_face_compare_result,
	enum_meta_data_type_sensetime_black_list_face_compare_result,
	enum_meta_data_type_sensetime_face_attrbute,
	enum_meta_data_type_sensetime_aux_face_body_detect_result,
	enum_meta_data_type_sensetime_face_liveness_detect_result,
	enum_meta_data_type_invalid				 = 0xffffffff,
}META_DATA_TYPE;


typedef struct{
	uint32_t type;// META_DATA_TYPE
	uint32_t offset;
	uint32_t size;
}META_DATA_INFO;


typedef struct{
	uint32_t meta_data_count;
	uint32_t magic;
	uint32_t crc_val;
}META_DATA_TAIL;



class CMetaData{
public:
	explicit CMetaData(META_DATA_TYPE enType,void * data,uint32_t size);
	explicit CMetaData(CMetaData & c);
	CMetaData & operator = (CMetaData & c);
	virtual ~CMetaData();
	
	META_DATA_TYPE type();
	void * data();
	uint32_t size();
protected:
	META_DATA_TYPE   m_enType;
	uint8_t *		 m_pMetaDataBody;
	uint32_t		 m_nMetaDataBodySize;
};
































#endif //__SHM_BUF_MEDIA_DATA_H__

