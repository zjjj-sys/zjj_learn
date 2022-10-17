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

#ifndef _FHADV_OSD_MPI_H_
#define _FHADV_OSD_MPI_H_

#include "FH_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/** @addtogroup Video OSD
 *  @{
 */
#define FH_OSD_LINEONE_NUM 32
#define FH_OSD_LINETWO_NUM 240
#define FH_OSD_TIME_TEXT_NUM 12

typedef enum
{
    FHTEN_OSD_TimeFmt0  = 0,      /* YYYY-MM-DD 00:00:00 */
    FHTEN_OSD_TimeFmt1  = 1,      /* MM-DD-YYYY 00:00:00 */
    FHTEN_OSD_TimeFmt2  = 2,      /* DD-MM-YYYY 00:00:00 */
    FHTEN_OSD_TimeFmt3  = 3,      /* YYYY/MM/DD 00:00:00 */
    FHTEN_OSD_TimeFmt4  = 4,      /* MM/DD/YYYY 00:00:00 */
    FHTEN_OSD_TimeFmt5  = 5,      /* DD/MM/YYYY 00:00:00 */
    FHTEN_OSD_TimeFmt6  = 6,      /* YYYY-MM-DD 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_OSD_TimeFmt7  = 7,      /* MM-DD-YYYY 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_OSD_TimeFmt8  = 8,      /* DD-MM-YYYY 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_OSD_TimeFmt9  = 9,      /* xxxx年xx月xx日 00:00:00 */
    FHTEN_OSD_TimeFmt10 = 10,    /* xx月xx日xxxx年 00:00:00 */
    FHTEN_OSD_TimeFmt11 = 11,    /* xx日xx月xxxx年 00:00:00 */
    FHTEN_OSD_TimeFmt12 = 12,     /* YYYY/MM/DD 00:00:00 显示中文星期 */
    FHTEN_OSD_TimeFmt13 = 13,     /* MM/DD/YYYY 00:00:00 显示中文星期 */
    FHTEN_OSD_TimeFmt14 = 14,     /* DD/MM/YYYY 00:00:00 显示中文星期 */
    FHTEN_OSD_TimeFmt_BUTT,      /* 判断限值 非交互项 上层不必关心 */
} FHT_OSD_TimeFmt_e;

typedef enum
{
    FHTEN_OSD_GB2312  = 0,
    FHTEN_OSD_UNICODE = 1,
    FHTEN_OSD_UTF8    = 2,
}FHT_OSD_EncType_e;

typedef enum
{
    FHTEN_OSD_INVERT  = 0,  /*反色显示*/
    FHTEN_OSD_HALFBKG = 1,     /*背景半透明显示*/
    FHTEN_OSD_EDGE    = 2,        /*描边显示*/
}FHT_OSD_Style_e;/*osd显示风格*/

typedef struct
{
    signed char hour;
    signed char minute;
} FHT_TIMEZONE_OFFSET_t;       /* 时区偏移量 */

typedef struct
{
    FH_UINT32 libSize;    /* 字库大小 */
    FH_UINT8 *pLibData;  /* 字库数据地址 */
} FHT_OSD_FontLib_t;

typedef struct
{
    FH_SINT32 width;    /* 汉字字符宽度像素， 取值范围[16, 32, 48, 64] */
    FH_SINT32 height;   /* 汉字字符宽度像素， 取值范围[16, 32, 48, 64] */
} FHT_OSD_Size_t;

typedef struct
{
    FH_UINT8 high_level;                           /* 大于等于此值，进行反色 */
    FH_UINT8 low_level;                            /* 小于等于此值，恢复正常颜色 */
}FHT_OSD_Invert_Attr_t;

typedef struct
{
    FHT_RgbColor_t norColor;
    FHT_RgbColor_t bkgColor;
}FHT_OSD_hlColor_t;

typedef struct
{
    FHT_RgbColor_t norColor;
    FHT_RgbColor_t edgeColor;
}FHT_OSD_edgeColor_t;

typedef struct
{
    FHT_OSD_Style_e style; /*osd显示风格*/
    union
    {
         FHT_OSD_Invert_Attr_t invertAttr; /*反色显示参数*/
         FHT_OSD_hlColor_t  osdbkgColor; /*高亮显示参数*/
         FHT_OSD_edgeColor_t  osdedgeColor; /*描边显示参数*/
    };
}FHT_OSD_Style_Attr_t;

typedef struct
{
    FH_UINT32 timeOsdEnable;                                /* 时间OSD使能项 */
    FHT_LeftTopNode_t timeOsdPosition;                      /* 时间OSD坐标 */

    FHT_OSD_TimeFmt_e timeOsdFormat;                        /* 时间OSD格式 */
    FH_UINT8 timeOsdNorm;                                   /* 0: 24小时制 1: 12小时制 */
    FH_UINT8 weekFlag;                                      /* 星期显示标志 与中英文自动匹配 */
    FH_UINT8 timeOsdTextEnable;                             /* 时间OSD中自定义文本使能 */
    FH_UINT8 timeOsdText[FH_OSD_TIME_TEXT_NUM + 1];         /* 时间OSD中自定义文本内容，最多12个ASCII字符 */

    FHT_Color_t osdColor;                                   /* OSD颜色 */
    FHT_OSD_Size_t osdSize;                                 /* 控制OSD字符大小 */

    FH_UINT32 text01Enable;                                 /* 自定义文本1使能 */
    FHT_LeftTopNode_t sttext01Position;                     /* 自定义文本1坐标 */
    FH_UINT8  text01Info[FH_OSD_LINEONE_NUM + 1];           /* 自定义文本1内容 */

    FH_UINT32 text02Enable;                                 /* 自定义文本2使能 */
    FHT_LeftTopNode_t sttext02Position;                     /* 自定义文本2坐标 */
    FH_UINT8 text02Info[FH_OSD_LINETWO_NUM + 1];            /* 自定义文本2内容 */

    FH_UINT32 text03Enable;                                 /* 自定义文本3使能，仅支持FH8632 FH8856 FH8852 */
    FHT_LeftTopNode_t sttext03Position;                     /* 自定义文本3坐标，仅支持FH8632 FH8856 FH8852*/
    FH_UINT8  text03Info[FH_OSD_LINETWO_NUM + 1];           /* 自定义文本3内容，仅支持FH8632 FH8856 FH8852 */

    FH_UINT32 text01CharNum;                                /*自定义文本1最大字符数, 仅在第一次设置osd时生效*/
    FH_UINT32 text02CharNum;                                /*自定义文本2最大字符数*,仅在第一次设置osd时生效*/
    FH_UINT32 text03CharNum;                                /*自定义文本3最大字符数, 仅在第一次设置osd时生效, 仅支持FH8632 FH8856 FH8852*/

    FHT_OSD_Style_Attr_t osdStyle;

    FHT_TIMEZONE_OFFSET_t timezoneOffset;
} FHT_OSD_CONFIG_t;

typedef struct
{
    FH_UINT32 enable;
    FH_UINT32 alpha;
    FHT_Rect_t area;
    FH_UINT8 *pData;
} FHT_OSD_Logo_t;

typedef FH_SINT32 (*FHT_OSD_GET_FONT_FUNC_t)(FH_SINT32 code, FH_VOID** buf);

FH_SINT32 FHAdv_Osd_Init(FH_SINT32 width, FH_SINT32 hight);
FH_SINT32 FHAdv_Osd_Uninit(FH_VOID);

FH_SINT32 FHAdv_Osd_LoadFontLib(FHT_OSD_FontType_e type, FHT_OSD_FontLib_t *pFontData);

FH_SINT32 FHAdv_Osd_UnLoadFontLib(FHT_OSD_FontType_e type);

FH_SINT32 FHAdv_Osd_SetText(FHT_OSD_CONFIG_t *pOsdcfg);
FH_SINT32 FHAdv_Osd_Ex_SetText(FH_SINT32 chn, FHT_OSD_CONFIG_t *pOsdcfg);

FH_SINT32 FHAdv_Osd_SetTextRotate(FH_SINT32 enable, FH_SINT32 value);
FH_SINT32 FHAdv_Osd_Ex_SetTextRotate(FH_SINT32 chn, FH_SINT32 enable, FH_SINT32 value);

FH_SINT32 FHAdv_Osd_SetLogo(FHT_OSD_Logo_t *pLogoCfg);
FH_SINT32 FHAdv_Osd_Font_RegisterCallback(FHT_OSD_GET_FONT_FUNC_t func, FHT_OSD_EncType_e enc_type);
/********
 * 获取打印库版本信息
 ********/
FH_CHAR* FH_ADV_OSD_Version(FH_UINT32 print_enable);

/*@} end of group Video_Md */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
