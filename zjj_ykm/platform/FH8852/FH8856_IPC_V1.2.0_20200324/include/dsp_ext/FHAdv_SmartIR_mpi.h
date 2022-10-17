#ifndef _FHADV_SMART_IR_H_
#define _FHADV_SMART_IR_H_

#include "FH_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum
{
	FHADV_IR_DAY     = 0,
	FHADV_IR_NIGHT   = 1,
}FHADV_DAYNIGHT_STA;

typedef enum
{
	FHADV_IR_BAYER   = 0,    /* for bayer sensor */
	FHADV_IR_RGBIR   = 1,    /* for rgbir sensor */
}FHADV_SMARTIR_ATTR;

typedef struct
{
    FH_UINT16 gainDay2Night;    /* for bayer sensor */
    FH_UINT16 gainNight2Day;    /* for bayer sensor */
    FH_UINT16 lumaDay2Night;    /* for rgbir sensor */
    FH_UINT16 lumaNight2Day;    /* for rgbir sensor */
}FHADV_SMARTIR_THRESHOLD_t;

/*
*@ init
*@return 0: 成功 -1：失败
*/
FH_SINT32 FHAdv_SmartIR_Init(FH_VOID);

/*
*@ 设置sensor属性
*@param [in] attribute
*@return 0: 成功 非0：失败
*/
FH_SINT32 FHAdv_SmartIR_SetAttr(FHADV_SMARTIR_ATTR attribute);

/*
*@ 设置sensor属性
*@param [in] attribute
*@return 0: 成功 非0：失败
*/
FH_SINT32 FHAdv_SmartIR_GetAttr(FHADV_SMARTIR_ATTR *pattribute);

/*
*@ 设置日夜切换阀值
*@param [in] pstThreshold
*@return 0: 成功 非0：失败
*/

FH_SINT32 FHAdv_SmartIR_Setthreshold(FHADV_SMARTIR_THRESHOLD_t *pstThreshold);

/*
*@ 获取日夜切换增益阀值
*@param [out] pstThreshold
*@return 0: 成功 非0：失败
*/
FH_SINT32 FHAdv_SmartIR_Getthreshold(FHADV_SMARTIR_THRESHOLD_t *pstThreshold);

/*
*@ 设置切换偏移量，offset >= -80
*@param [in] offset 
*@return 0: 成功 非0：失败
*@值越小，晚上越容易切换白天，bayer格式sensor支持，默认0
*/
FH_SINT32 FHAdv_SmartIR_SetCustom_offset(FH_SINT32 offset);

/*
*@ 获取切换偏移量
*@param [out] poffset 
*@return 0: 成功 非0：失败
*/
FH_SINT32 FHAdv_SmartIR_GetCustom_offset(FH_SINT32 *poffset);

/*
*@ 获取当前白天晚上状态
*@param [in] irCurr  当前ir状态，初始必须为白天
*@return 0:白天 1：晚上
*/
FH_UINT8 FHAdv_SmartIR_GetDayNightStatus(FHADV_DAYNIGHT_STA irCurr);

/********
 * 获取打印库版本信息
 ********/
FH_CHAR* FH_ADV_SMARTIR_Version(FH_UINT32 print_enable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _FHADV_SMART_IR_H_ */


