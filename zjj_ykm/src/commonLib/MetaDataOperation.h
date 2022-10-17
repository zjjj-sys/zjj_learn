#ifndef __META_DATA_OPERATION_H__
#define __META_DATA_OPERATION_H__

#if defined (HI3516CV500)|| defined(FH8852V201)  || defined(HI3516DV300) || defined(FH8852V200) || defined(FH8852) || defined(SV823)

#include <stdio.h>
#include <stdint.h>

#include <iostream>
#include <string>
#include <error.h>
#include <errno.h>

#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/vfs.h>

#include <list>
#include <memory>



#include "debug.h"
#include "MiscDataType.h"
#include "CMetaData.h"

using std::string;
using std::list;

// face body...
#define CONFIG_SENSETIME_DATA_MAGIC 0xfAcEb0d1



typedef struct{
	uint32_t left;
	uint32_t top;
	uint32_t right;
	uint32_t bottom;
	double   score;  // [0.0 , 1.0];
}RFCN_RESULT;

typedef struct{
	uint32_t left;
	uint32_t top;
	uint32_t right;
	uint32_t bottom;
}FACE_BODY_RECT;

typedef struct{
	uint32_t id;
	float score;
	uint32_t label;
	uint16_t imgWidth;
	uint16_t imgHeight;
	FACE_BODY_RECT position;
}FACE_BODY_DETECT_RESULT;

typedef struct{
	uint32_t magic;
	uint32_t id;
	uint32_t size;
	uint8_t * jpeg;
}FACE_BODY_SNAPSHOT_PIC;



typedef struct{
	uint32_t magic;
	uint32_t id;
	uint32_t size;	// feature size ,not feature count... release it use delete [] (uint8_t *)feature;
	float * feature;
}FACE_FEATURE;

typedef struct{
	uint32_t magic;
	uint32_t id ;
	float    score;
	uint32_t name_size;
	char *	name;
	uint32_t addr_size;
	char * addr;
	uint32_t age;
	uint32_t sex;
	uint32_t faceid;  // unique id...
	uint32_t reserved;
	char * 	 userid;
	uint32_t userid_size;
	uint8_t * reg_pic;
	uint32_t reg_pic_size;
}FACE_COMPARE_RESULT;





typedef struct {
        char label[128]; 
        float feature; 
} FACE_ATTRIBUTE_LABEL;


typedef struct{
	uint32_t magic;
    char category[32]; ///
    int result_idx; ///
    int label_size; //
    FACE_ATTRIBUTE_LABEL *label; //// label size ,not label count... release it use delete [] (uint8_t *)label;
}FACE_ATTRIBUTE;


typedef struct{
	int32_t id;
	uint32_t isLiveness;
}FACE_LIVENESS_DETECT_RESULT;


namespace MetaData{
	CMetaData * RFCNResult2MetaData(std::list<RFCN_RESULT> & lRfcnResultList);
	bool MetaData2RFCNResult(CMetaData * pMetaData,std::list<RFCN_RESULT> & lRfcnResultList);

	CMetaData * FaceLivenessDetectResult2MetaData(std::list<FACE_LIVENESS_DETECT_RESULT> & lLivenessScoreList);
	bool MetaData2FaceLivenessDetectResult(CMetaData * pMetaData,std::list<FACE_LIVENESS_DETECT_RESULT> & lLivenessScoreList);

	// face body detect result...
	CMetaData * FaceBodyDetectResult2MetaData(std::list<FACE_BODY_DETECT_RESULT> & lFaceBodyDetectResultList);
	bool MetaData2FaceBodyDetectResult(CMetaData * pMetaData,std::list<FACE_BODY_DETECT_RESULT> & lFaceBodyDetectResultList);

	CMetaData * AuxFaceBodyDetectResult2MetaData(std::list<FACE_BODY_DETECT_RESULT> & lFaceBodyDetectResultList);
	bool MetaData2AuxFaceBodyDetectResult(CMetaData * pMetaData,std::list<FACE_BODY_DETECT_RESULT> & lFaceBodyDetectResultList);

	// face body snapshot pic result...
	CMetaData * FaceBodySnapshotPic2MetaData(std::list<FACE_BODY_SNAPSHOT_PIC> & lFaceBodySnapshotPicList);
	bool MetaData2FaceBodySnapshotPic(CMetaData * pMetaData,std::list<FACE_BODY_SNAPSHOT_PIC> & lFaceBodySnapshotPicList);
	bool MetaData2FaceBodySnapshotPic(CMetaData * pMetaData,std::list<std::shared_ptr<FACE_BODY_SNAPSHOT_PIC> > & lptrFaceBodySnapshotPicList);


	// face verify feature result...
	
	CMetaData * FaceFeatureResult2MetaData(std::list<FACE_FEATURE> & lFaceFeatureList);
	bool MetaData2FaceFeatureResult(CMetaData * pMetaData,std::list<FACE_FEATURE> & lFaceFeatureList);
	bool MetaData2FaceFeatureResult(CMetaData * pMetaData,std::list<std::shared_ptr<FACE_FEATURE> > & lFaceFeatureList);


	// face compare result...
	CMetaData * FaceCompareResult2MetaData(std::list<FACE_COMPARE_RESULT> & lFaceCompareResultList,META_DATA_TYPE enType);
	bool MetaData2FaceCompareResult(CMetaData * pMetaData,std::list<FACE_COMPARE_RESULT> & lFaceCompareResultList,META_DATA_TYPE enType);
	bool MetaData2FaceCompareResult(CMetaData * pMetaData,std::list<std::shared_ptr<FACE_COMPARE_RESULT> >& lptrFaceCompareResultList,META_DATA_TYPE enType);

	// WL : White list face compare...
	CMetaData * WLFaceCompareResult2MetaData(std::list<FACE_COMPARE_RESULT> & lFaceCompareResultList);
	bool MetaData2WLFaceCompareResult(CMetaData * pMetaData,std::list<FACE_COMPARE_RESULT> & lFaceCompareResultList);
	bool MetaData2WLFaceCompareResult(CMetaData * pMetaData,std::list<std::shared_ptr<FACE_COMPARE_RESULT> >& lptrFaceCompareResultList);
	// BL : Black list face compare...
	CMetaData * BLFaceCompareResult2MetaData(std::list<FACE_COMPARE_RESULT> & lFaceCompareResultList);
	bool MetaData2BLFaceCompareResult(CMetaData * pMetaData,std::list<FACE_COMPARE_RESULT> & lFaceCompareResultList);
	bool MetaData2BLFaceCompareResult(CMetaData * pMetaData,std::list<std::shared_ptr<FACE_COMPARE_RESULT> >& lptrFaceCompareResultList);


	// face attribute;
	CMetaData * FaceAttributeResult2MetaData(std::list<FACE_ATTRIBUTE> & lFaceAttributeList);
	bool MetaData2FaceAttributeResult(CMetaData * pMetaData,std::list<FACE_ATTRIBUTE> & lFaceAttributeList);

};




















#endif //HI3516CV500




#endif //__META_DATA_OPERATION_H__

