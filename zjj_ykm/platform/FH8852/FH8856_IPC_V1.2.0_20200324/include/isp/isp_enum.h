#ifndef ISP_ENUM_H_
#define ISP_ENUM_H_

#ifdef OS_RTT
#define ISP_WAIT_VD				0
#define ISP_WAIT_FRAME_EDGE		1
#define ISP_PROC_RUN			2
#define ISP_GET_VERSION			3
#define ISP_GET_AE_STAT		    4
#define ISP_GET_AWB_STAT        5
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

enum  IPB_LTM_CURVE_TYPE{
	LTM_CURVE_LINEAR = 0x0,
	LTM_CURVE_60DB = 0x1,
	LTM_CURVE_80DB = 0x2,
	LTM_CURVE_100DB = 0x3,
	LTM_CURVE_120DB = 0x4,
	LTM_CURVE_USER01 = 0x5,
	LTM_CURVE_USER02 = 0x6,
	LTM_CURVE_USER03 = 0x7,
	LTM_MANUAL_CURVE = 0xF,
};

enum  MISC_DATA_COMP{
	MISC_COMP_NONE = 0x0,
	MISC_COMP_LINEAR_12BIT = 0x1,
	MISC_COMP_LINEAR_10BIT = 0x2,
	MISC_COMP_NORMAL = 0x3,
	MISC_COMP_USER = 0x4,
};

/*-------format setting------------*/
/**
 * @brief bit[0]~bit[7]　传入帧率设置([0~199]12.5fps,15fps,20fps,25fps,30fps,40fps,50fps,60fps,120fps,240fps,220fps,110fps,180fps...;[200~255]user defined)
 *        bit[8]~bit[15]　传入幅面设置([0~199]720P,960P,1080P,1600*1200,1536*1536,1536P,400w,500w,800w,270P,540P,2304*1296,192*192,384*384;[200~255]:user defined)
 *        bit[16]~bit[23]　传入sensor属性(目前bit16配０代表非宽动态，１代表宽动态)
 */

enum FORMAT
{
    FORMAT_720P25       = 0x03,
    FORMAT_720P30       = 0x04,
    FORMAT_960P25       = 0x0103,
    FORMAT_960P30       = 0x0104,
    FORMAT_1080P15      = 0x0201,
    FORMAT_1080P20      = 0x0202,
    FORMAT_1080P25      = 0x0203,
    FORMAT_1080P30      = 0x0204,
    FORMAT_1200P30      = 0x0304,
    FORMAT_1536X1536P15 = 0x0401,
    FORMAT_1536X1536P25 = 0x0403,
    FORMAT_1536X1536P30 = 0x0404,
    FORMAT_1536P15      = 0x0501,
    FORMAT_1536P25      = 0x0503,
    FORMAT_1536P30      = 0x0504,
    FORMAT_1536P40      = 0x0505,
    FORMAT_400WP15      = 0x0601,
    FORMAT_400WP20      = 0x0602,
    FORMAT_400WP25      = 0x0603,
    FORMAT_400WP30      = 0x0604,
    FORMAT_500W12P5     = 0x0700,
    FORMAT_500WP15      = 0x0701,
    FORMAT_500WP20      = 0x0702,
    FORMAT_800WP15      = 0x0801,
    FORMAT_270P240      = 0x0909,
    FORMAT_540P120      = 0x0a08,
    FORMAT_540P180      = 0x0a0c,
    FORMAT_2304X1296P25 = 0x0b03,
    FORMAT_192X192P220  = 0x0c0a,
    FORMAT_384X384P110  = 0x0d0b,
    FORMAT_WDR_1080P25  = 0x10203,
    FORMAT_WDR_1080P30  = 0x10204,
    FORMAT_WDR_1536P15  = 0x10501,
    FORMAT_WDR_1536P25  = 0x10503,
    FORMAT_WDR_1536P30  = 0x10504,
    FORMAT_WDR_1536P40  = 0x10505,
    FORMAT_WDR_400WP15  = 0x10601,
    FORMAT_WDR_400WP20  = 0x10602,
    FORMAT_WDR_400WP25  = 0x10603,
    FORMAT_WDR_400WP30  = 0x10604,
    FORMAT_WDR_500W12P5 = 0x10700,
    FORMAT_WDR_500WP15  = 0x10701,
    FORMAT_WDR_500WP20  = 0x10702,
    FORMAT_WDR_800WP15  = 0x10801,
    SENSOR_FORMAT_MAX   = 0xfffff,
};

enum MOD
{
	TWO_BLOCK_MODE = 0,
	DIRECT_MODE = 1,
	LEFT_DIRECT_RIGHT_DRR = 2,
	FOUR_BLOCK_MODE = 4,
};

enum ISPP_MODE
{
	ISPP_CIRCULAR = 0,
	ISPP_NON_CIRCULAR = 1,
};

enum CHIP_TYPE
{
    FHZY  = 0,
    FHZY2 = 1,
};

enum AWB_MODULE_POS
{
	POST_WB = 0,
	FRONT_SHORT_WB = 1,
	FRONT_LONG_WB = 2,
};

enum SNS_IF
{
    DEFAULT_CASE = 0,
};
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* ISP_ENUM_IF_H_ */
