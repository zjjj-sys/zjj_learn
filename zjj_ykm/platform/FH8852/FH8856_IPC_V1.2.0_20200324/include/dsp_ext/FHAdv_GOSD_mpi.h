/**
 * @file     FHAdv_OSD_mpi.h
 * @brief    FHAdv OSD module interface
 * @version  V1.0.0
 * @date     20-July-2016
 * @author   Software Team
 *
 * @note
 * Copyright (C) 2016 Shanghai Fullhan Microelectronics Co., Ltd.
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

#ifndef _FHADV_GOSD_MPI_H_
#define _FHADV_GOSD_MPI_H_

#include "FH_typedef.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define FH_GOSD_TEXT_NUM 256
#define FH_GOSD_TIME_TEXT_NUM 32

typedef enum
{
    FHTEN_GOSD_TimeFmt0 = 0,      /* YYYY-MM-DD 00:00:00 */
    FHTEN_GOSD_TimeFmt1 = 1,      /* MM-DD-YYYY 00:00:00 */
    FHTEN_GOSD_TimeFmt2 = 2,      /* DD-MM-YYYY 00:00:00 */
    FHTEN_GOSD_TimeFmt3 = 3,      /* YYYY/MM/DD 00:00:00 */
    FHTEN_GOSD_TimeFmt4 = 4,      /* MM/DD/YYYY 00:00:00 */
    FHTEN_GOSD_TimeFmt5 = 5,      /* DD/MM/YYYY 00:00:00 */
    FHTEN_GOSD_TimeFmt6 = 6,      /* YYYY-MM-DD 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_GOSD_TimeFmt7 = 7,      /* MM-DD-YYYY 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_GOSD_TimeFmt8 = 8,      /* DD-MM-YYYY 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_GOSD_TimeFmt9 = 9,      /* xxxx年xx月xx日 00:00:00 */
    FHTEN_GOSD_TimeFmt10 = 10,    /* xx月xx日xxxx年 00:00:00 */
    FHTEN_GOSD_TimeFmt11 = 11,    /* xx日xx月xxxx年 00:00:00 */
    FHTEN_OSD_TimeFmt12  = 12,     /* YYYY/MM/DD 00:00:00 显示中文星期 */
    FHTEN_OSD_TimeFmt13  = 13,     /* MM/DD/YYYY 00:00:00 显示中文星期 */
    FHTEN_OSD_TimeFmt14  = 14,     /* DD/MM/YYYY 00:00:00 显示中文星期 */
    FHTEN_GOSD_TimeFmt_BUTT,      /* 判断限值 非交互项 上层不必关心 */
} FHT_GOSD_TimeFmt_e;

typedef struct
{
    FH_UINT32 libSize;    /* 字库大小 */
    FH_UINT8 *pLibData;  /* 字库数据地址 */
} FHT_GOSD_FontLib_t;

typedef struct
{
    FH_UINT32 gosd_w;  /* the width of gosd */
    FH_UINT32 gosd_h;  /* the height of gosd */
} FHT_GOSD_Size_t;

typedef struct
{
    FH_UINT32          timeOsdEnable;              /* 时间GOSD使能项 */
    FHT_LeftTopNode_t  timeOsdPosition;            /* 时间GOSD坐标 */

    FHT_GOSD_TimeFmt_e timeOsdFormat;              /* 时间GOSD格式 */
    FH_UINT32          timeOsdNorm;                /* 0: 24小时制 1: 12小时制 */
    FH_UINT32          weekFlag;                   /* 星期显示标志 */

    FH_UINT32          timeOsdTextEnable;                        /* 时间OSD中自定义文本使能 */
    FH_UINT8           timeOsdText[FH_GOSD_TIME_TEXT_NUM + 1];    /* 时间OSD中自定义文本内容，最多12个ASCII字符 */

    FHT_Color_t        osdColor;                   /* GOSD颜色 */
    FHT_Color_t        edgeColor;                  /* 勾边色  */
    FH_UINT32          edgePixel;                  /* 镶边像素，0：1个像素， 1：两个像素。*/
    FH_UINT32          gosdfsize;                  /* 字符大小 */

    FH_UINT32          text01Enable;                 /* 自定义文本使能 */
    FHT_LeftTopNode_t  sttext01Position;             /* 自定义文本坐标 */
    FH_UINT8           text01Info[FH_GOSD_TEXT_NUM]; /*自定义文本内容*/

    FH_UINT32          text02Enable;                 /* 自定义文本使能 */
    FHT_LeftTopNode_t  sttext02Position;             /* 自定义文本坐标 */
    FH_UINT8           text02Info[FH_GOSD_TEXT_NUM]; /*自定义文本内容*/

    FH_UINT32          text03Enable;                 /* 自定义文本使能 */
    FHT_LeftTopNode_t  sttext03Position;             /* 自定义文本坐标 */
    FH_UINT8           text03Info[FH_GOSD_TEXT_NUM]; /*自定义文本内容*/

    struct {
        FH_UINT8 highLevel;                   /* 大于等于此值，进行反色 */
        FH_UINT8 lowLevel;                    /* 小于等于此值，恢复正常颜色 */
    } invertColorThreshold;                        /* 反色阈值 */
} FHT_GOSD_CONFIG_t;

typedef struct
{
    FHT_LeftTopNode_t gosdstartPosition;  /* 起点坐标 */
    FHT_GOSD_Size_t   sizeofbox;          /* GOSD的宽高 */
    FHT_Color_t       gosdboxColor;       /* GOSD颜色 */
} FHT_GOSD_BASECFG_t;

typedef struct
{
    FH_SINT8          *graph;            /* logo信息 */
    FHT_LeftTopNode_t graphPosition;     /* 起点坐标 */
    FHT_GOSD_Size_t   sizeofgraph;       /* GOSD的宽高 */
} FHT_GOSD_GRAPHCfg_t;


/*********
 * GOSD  init.初始化GOSD
 *********/
FH_SINT32 FHAdv_Gosd_Init(FH_SINT32 width, FH_SINT32 hight);

/*********
 * GOSD  加载GOSD字库
 *********/
FH_SINT32 FHAdv_Gosd_LoadFontLib(FHT_OSD_FontType_e type, FHT_GOSD_FontLib_t *pFontData);

/*********
 * GOSD  加载GOSD字库
 *********/
FH_SINT32 FHAdv_Gosd_UnLoadFontLib(FHT_OSD_FontType_e type);

/*********
 * GOSD 清除GOSD, x、y为清除区域的左上角坐标，width、height为清除区域的宽、高
 *********/
FH_SINT32 FHAdv_Gosd_Clear(FH_SINT32 x, FH_SINT32 y, FH_SINT32 width, FH_SINT32 height);

/*******
 * 设置GOSD字符，参数为GOSD配置结构体指针.
 *********/
FH_SINT32 FHAdv_Gosd_SetText(FHT_GOSD_CONFIG_t *psetgosdt);

/********
 * 设置GOSD旋转，旋转角度，文本配置结构体指针。
 ********/
FH_SINT32 FHAdv_Gosd_SetRotate(FH_SINT32 enable, FH_SINT32 rotate_value);

/********
 * 设置Grahp logo.
 *******/
FH_SINT32 FHAdv_Gosd_SetGraph(FHT_GOSD_GRAPHCfg_t *pGrahpcfg);

/*********
 * 设置马赛克，参数为，BOX配置结构体指针
 ********/
FH_SINT32 FHAdv_Gosd_SetMask(FHT_GOSD_BASECFG_t *pBoxcfg);

/********
 * 设置矩形框，参数为，BOX配置结构体指针
 ********/
FH_SINT32 FHAdv_Gosd_SetGbox(FHT_GOSD_BASECFG_t *pBoxcfg);

/********
 * 获取打印库版本信息
 ********/
FH_CHAR* FH_ADV_GOSD_Version(FH_UINT32 print_enable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
