/**
 * @file     fh_objdetect_vbcli.h
 * @brief    object detect gvbus client
 * @version  V0.4.5
 * @date     12-Dec-2018
 * @author   Software Team
 *
 * @note
 * Copyright (C) 2018 Shanghai Fullhan Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * @par
 * Fullhan is supplying this software which provides customers with programming
 * information regarding the products. Fullhan has no responsibility or
 * liability for the use of the software. Fullhan not guarantee the correctness
 * of this software. Fullhan reserves the right to make changes in the software
 * without notification.
 *
 */

#ifndef FH_OBJECT_VBCLI_H_
#define FH_OBJECT_VBCLI_H_

#include "types/type_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*ERROR CODE*/
#define FH_ODET_ERR_BASE (-400)

#define FH_ODET_SUCCESS (0)
#define FH_ODET_FAILED (FH_ODET_ERR_BASE - 1)
#define FH_ODET_NULL_PTR (FH_ODET_ERR_BASE - 2)                   /*空指针错误*/
#define FH_ODET_INV_PARAM (FH_ODET_ERR_BASE - 3)                  /*输入参数错误*/
#define FH_ODET_FOPEN_FAIL (FH_ODET_ERR_BASE - 4)                 /*文件打开失败*/
#define FH_ODET_FORMAT_ERR (FH_ODET_ERR_BASE - 5)                 /*分析器参数文件格式错误*/

#define FH_OBJDET_ERR_BASE (-100)

#define FH_OBJDET_FAILED (FH_OBJDET_ERR_BASE - 1)
#define FH_OBJDET_DETECTOR_INVAILD (FH_OBJDET_ERR_BASE - 2)       /*人形检测句柄无效*/
#define FH_OBJDET_DETECTOR_NOT_READY (FH_OBJDET_ERR_BASE - 3)     /*人形检测句柄没有准备好*/
#define FH_OBJDET_DETECTOR_MODE_ERROR (FH_FH_OBJDET_ERR_BASE - 4) /*人形检测模式配置错误*/
#define FH_OBJDET_DUPLICATE_MODEL_CONFIG (FH_OBJDET_ERR_BASE - 5) /*重复模型配置*/
#define FH_OBJDET_MODEL_CONFIG_IS_FULL (FH_OBJDET_ERR_BASE - 6)   /*装载模型大于4个*/
#define FH_OBJDET_MODEL_NOT_INSTALL (FH_OBJDET_ERR_BASE - 7)      /*人形检测模型未安装*/
#define FH_OBJDET_ROTATEANGLE_INVAILD (FH_OBJDET_ERR_BASE - 8)    /*旋转角度为无效角度*/
#define FH_OBJDET_MALLOC_FAILED (FH_OBJDET_ERR_BASE - 9)
#define FH_OBJDET_INPUTPIC_TOOSMALL (FH_OBJDET_ERR_BASE - 10)
#define FH_OBJDET_MODEL_TYPE_NOT_SUPPORT (FH_OBJDET_ERR_BASE - 11)

#define FH_OBJDET_TRACKER_FAILED  (FH_OBJDET_ERR_BASE -21)
#define FH_OBJDET_TRACKER_DET_MODELNO_ERROR  (FH_OBJDET_ERR_BASE -22)
#define FH_OBJDET_TRACKER_ROI_TOOSMALL  (FH_OBJDET_ERR_BASE -23)
#define FH_OBJDET_TRACKER_ROI_OUTFRAME  (FH_OBJDET_ERR_BASE -24)
#define FH_OBJDET_TRACKER_FRAMESIZE_ERROR  (FH_OBJDET_ERR_BASE -25)
#define FH_OBJDET_TRACKER_MALLOC_FAILED  (FH_OBJDET_ERR_BASE -26)
#define FH_OBJDET_TRACKER_MODELNO_OVERFLOW (FH_OBJDET_ERR_BASE -27)

#define MAX_MODEL_NUM 5

enum FH_ODET_modelId
{
    FH_ODET_BODY_MODEL        = 73733930,   /* 推荐阈值: 20 */
    FH_ODET_BODY_2_MODEL      = 86185770,   /* 推荐阈值: 30 */
    FH_ODET_HEAD_MODEL        = 73733582,   /* 推荐阈值: 5 */
    FH_ODET_HEAD_2_MODEL      = 86185422,   /* 推荐阈值: 5 */
    FH_ODET_HEADUP_MODEL      = 72946060,   /* 0.7.8 and versions after not support */
    FH_ODET_MIDDLEBODY_MODEL  = 86185450,   /* 0.7.8 and versions after not support */
    FH_ODET_FACE_MODEL        = 77403532,   /* 推荐阈值: 10 */
    FH_ODET_FRONTFACE_MODEL   = 79074700,   /* 0.7.8 and versions after not support */
    FH_ODET_FRONTFACE_2_MODEL = 81677840   /* 推荐阈值: 10 */
};/*检测模型枚举*/

typedef enum FH_DET_MODE {
    FH_OBJDET_FULL_FRAME,       /*全幅面模式，返回物体个数以及坐标*/
    FH_OBJDET_ROI_ONLY          /*ROI模式，返回是否包含被测物体*/
}FH_DET_MODE_t;/*检测模式枚举*/

typedef enum FH_MODEL_SUPPORTED_MODE {
    FH_MODE_TIME_SAVING,             /* FH0.5 mode with least time cost */
    FH_MODE_PERFORMACE_INHANCE,      /* FH0.6 mode with 5% more cost than V05, but better detect performance*/
    FH_MODE_YS_MODELS,               /* FH0.7 mode for YS models*/
    FH_MODE_SIMPLE_YS_MODELS         /* FH0.7 simple mode for YS models*/
}FH_MODEL_SUPPORTED_MODE_t;

typedef struct FH_ODET_objPos {
    FH_SINT16 x;                 /*左上角横坐标*/
    FH_SINT16 y;                 /*左上角纵坐标*/
    FH_SINT16 w;                 /*物体水平宽度*/
    FH_SINT16 h;                 /*物体垂直高度*/
} FH_ODET_objPos_t;

typedef struct FH_ODET_Obj {
    FH_ODET_objPos_t pos;       /*物体位置信息*/
    FH_UINT16        confidence;        /*置信度 0~100 100 表示 100% 确认目标为被检物体*/
} FH_ODET_Obj_t;

typedef struct FH_ODET_objGroup {
    FH_ODET_Obj_t  objlist[8];  /*目标列表*/
    FH_SINT32      num;           /*目标数量*/
    FH_UINT32     modelId;      /*模板编号*/
} FH_ODET_objGroup_t;

typedef struct FH_ODET_cfg {
    FH_SINT32                 maxImageWidth;     /*输入画面最大宽度*/
    FH_SINT32                 maxImageHeight;    /*输入画面最大高度*/

    FH_SINT32                 modelCnt;         /*预装模型个数*/
    FH_UINT8                  *modelFile[MAX_MODEL_NUM];     /*检测模型文件数据*/
    FH_UINT32                 modelFileLen[MAX_MODEL_NUM];  /*检测模型文件数据长度*/
    FH_SINT32                 modelThres[MAX_MODEL_NUM];    /*检测模型阈值, 范围：0-100*/
    FH_SINT32                 rotateAngle;      /*旋转角度 1:90度 2:180度 3:270度*/
    FH_UINT8                  perScaleRate;     /*图像缩放比率，范围：128-236，数值越大漏检越少，检测时间越长*/
    FH_UINT8                  maxScaleNum;      /*最大图像缩放层数，范围0 - 40*/
    FH_UINT8                  slideStep;        /*滑窗步长，范围：1-5，数值越大，精度越低，检测时间越少*/
    FH_DET_MODE_t             detectMode;  /*检测模式: 0:全幅面  1:roi*/
    FH_MODEL_SUPPORTED_MODE_t model_mode;  /* 模型支持模式 */
} FH_ODET_cfg_t;

typedef struct FH_ODET_trackerCfg {
    FH_ODET_objPos_t       trackRoi; /* 初始化跟踪位置 */
    FH_SINT32              modelId;  /* 跟踪模型ID */
    FH_SINT32              detectEn; /* 跟踪检测使能 */
} FH_ODET_trackerCfg_t;        /* 跟踪器初始化参数 */

typedef struct FH_ODET_trackerOut{
    FH_ODET_objPos_t trackRoi; /* 跟踪目标位置 */
    FH_SINT32        trackerResponse;       /* 跟踪结果置信度 范围(跟踪检测使能：0 - 100 跟踪检测不使能：0 - 99) */
} FH_ODET_trackerOut_t;        /* 跟踪结果输出 */


struct FH_ODET_Handle;
struct FH_ODET_Tracker;
typedef struct FH_ODET_Tracker* FH_ODET_Tracker_t;

struct FH_subImgY8;
struct FH_imgY8;
/**
 * 创建一个detector
 * input:   *cfg        detector相关配置
 * return:  detHandle   detector句柄
            NULL        创建detector失败
 */
struct FH_ODET_Handle *VB_ODET_create(FH_ODET_cfg_t *cfg);

/**
 * 销毁一个detector
 * input:   *det        detector句柄
 * return:  ERRNO       FH_ODET_SUCCESS
 *                      其他：错误码
 */
FH_SINT32 VB_ODET_destroy(struct FH_ODET_Handle *det);

/**
 * 检测目标全幅面模式
 * input:   *det        detector句柄
 *          *img        y8子画面格式输入图像
 * output   *out        输出被检测物体列表
 *          modelNum    detect model number
 * return:  ERRNO       FH_ODET_SUCCESS
 *                      其他：错误码
 *
 */
FH_SINT32 VB_ODET_detectObject(struct FH_ODET_Handle *det, struct FH_subImgY8 *img, FH_ODET_objGroup_t *out, FH_UINT32 modelNum);

/**
 * 在ROI区域中检测目标
 * input:   *det            detector句柄
 *          *roi            y8子画面格式ROI输入图像
 * return:  hasObj/ERRNO    1: 检测到物体
 *                          0: 未检测到物体
 *                          其他：错误码
 */
FH_SINT32 VB_ODET_hasObjectInRoi(struct FH_ODET_Handle *det, struct FH_subImgY8 *roi);

/**
 *旋转检测角度
 * input:   *det            detector句柄
 *          *rotateAngle    旋转角度
 * return:  hasObj/ERRNO    FH_ODET_SUCCESS
 *                          其他：错误码
 */
FH_SINT32 VB_ODET_ModelRotate(struct FH_ODET_Handle *det, FH_SINT32 rotateAngle);

/**
 * 动态设置单个模型阈值
 *
 * input:   *handle         detector句柄
 *          modelId         检测模型ID
 *          thresh          检测模型阈值设置值
 * return:  ERRNO           FH_ODET_SUCCESS
 *                          其他：错误码
 */
FH_SINT32 VB_ODET_MODEL_setThresh(struct FH_ODET_Handle *handle, FH_UINT32 modelId, FH_SINT32 thresh);

/**
 * 动态设置scale系数、最大scale层数和滑动步长
 *
 * input:   *handle         detector句柄
 *          perscaleRate    scale系数
 *          maxScaleNum     最大scale层数
 *          slideStep       滑动步长
 * return:  ERRNO           FH_ODET_SUCCESS
 *                          其他：错误码
 */
FH_SINT32 VB_ODET_setSampleWinPara(struct FH_ODET_Handle *handle, FH_UINT8 perScaleRate, FH_UINT8 maxScaleNum, FH_UINT8 slideStep);
/**
 * 创建、初始化跟踪器
 *
 * input:   *img            图像输入
 *          handle          检测句柄
 *          tracker_cfg     跟踪参数
 * return:  跟踪器指针
 *          空指针
 */
FH_SINT32 VB_ODET_Create_Tracker(struct FH_imgY8 *imgY8, struct FH_ODET_Handle *handle,
                                             FH_ODET_trackerCfg_t tracker_cfg, FH_ODET_Tracker_t *tracker);

/**
 * 更新跟踪目标框
 *
 * input:   *img            图像输入
 *          handle          检测句柄
 *          tracker         跟踪器
 *          trackOut        跟踪更新输出
 * return:  FH_ODET_SUCCESS
 *          其他：错误码
 */
FH_SINT32 VB_ODET_Update_Tracker(struct FH_imgY8 *imgY8, struct FH_ODET_Handle *handle, struct FH_ODET_Tracker *tracker,
                            FH_ODET_trackerOut_t *trackOut);

/**
 * 销毁跟踪器
 *
 * input:   tracker         跟踪器
 * return:  FH_ODET_SUCCESS
 *          其他：错误码
 */
FH_SINT32 VB_ODET_Destroy_Tracker(FH_ODET_Tracker_t *tracker);

/**
 * 更新跟踪目标框
 *
 * input:   *objList        目标列表
 *          objNum          目标数量
 * output:  *out            融合后的目标列表
 * return:  FH_ODET_SUCCESS
 *          其他：错误码
 */
FH_SINT32 VB_ODET_objNms(FH_ODET_Obj_t *objList, FH_SINT32 objNum, FH_ODET_objGroup_t *out);

/**
 * 获取人形相关库信息
 *
 * input:   print_enable         是否打印信息
 * return:  FH_VOID
 */
FH_VOID VB_ODET_Version(FH_SINT32 print_enable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* !FH_OBJDETECT_H_*/

