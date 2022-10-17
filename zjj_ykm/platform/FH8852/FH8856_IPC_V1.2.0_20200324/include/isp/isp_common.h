#ifndef _ISP_COMMON_H_
#define _ISP_COMMON_H_

#include "types/type_def.h"
#ifdef OS_RTT
#define fh_printf    rt_kprintf
#ifndef fh_memcpy
#define fh_memcpy    rt_memcpy
#endif
#else //OS_LINXU
#define fh_printf    printf
#ifndef fh_memcpy
#define fh_memcpy    memcpy
#endif
#endif //OS_RTT

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define REG_ISP_NXT_PTR0				 (0xEA000050)
#define REG_ISP_DC1_DEBUG3     	 (0xEA0005d4)
#define IPF_PKG_START_REG	REG_ISP_NXT_PTR0
#define IPF_PKG_END_REG		REG_ISP_DC1_DEBUG3

#define REG_ISP_NXT_PTR1 			(0xEA000720)
#define REG_ISP_DC2_DEBUG3 	(0xEA000AAC)

#define IPB_PKG_START_REG	REG_ISP_NXT_PTR1
#define IPB_PKG_END_REG		REG_ISP_DC2_DEBUG3

#define ISPP_PKG_START_REG REG_ISPP_NXT_PTR0
#define ISPP_PKG_END_REG	REG_ISPP_STAT_MD_FLAG11

#define ISPF_PKG_START_REG REG_ISPF_NXT_PTR1
#define ISPF_PKG_END_REG REG_ISPF_RGBX_CCM_IR1

#define MALLOCED_MEM_BASE_ISP			(0)

#define MALLOCED_MEM_ISPPPKG			(0)
#define MALLOCED_MEM_ISPFPKG			(1)

#define MALLOCED_MEM_DRV			(3)

#define GAIN_NODES		12
#define LINEAR_INTERPOLATION(gain0,gain1,y0,y1,gainx)  (((gainx)-(gain0))*(y1)+((gain1)-(gainx))*(y0))/((gain1)-(gain0))

typedef int (*AeOpStatusCallback)(int,int);//参数1 opstatus：1ae op 2 ae stop  参数2 lumadiff

typedef int (*ispInitCfgCallback)(void);
typedef int (*ispIntCallback)(void);

enum  TAB_COLOR_CODE{
	CC_R = 0,
	CC_GR = 1,
	CC_B = 2,
	CC_GB = 3,
};

typedef enum _ISP_BAYER_TYPE_S_ {
	BAYER_RGGB	= 0x0,
	BAYER_GRBG	= 0x1,
	BAYER_BGGR	= 0x2,
	BAYER_GBRG	= 0x3, //
	BAYER_GBGR_AGAG_GRGB_AGAG = 4 + 0x0,
	BAYER_GRGB_AGAG_GBGR_AGAG = 4 + 0x1,
	BAYER_AGAG_GBGR_AGAG_GRGB = 4 + 0x2,
	BAYER_AGAG_GRGB_AGAG_GBGR = 4 + 0x3,
	BAYER_BGRG_GAGA_RGBG_GAGA = 4 + 0x4,
	BAYER_RGBG_GAGA_BGRG_GAGA = 4 + 0x5,
	BAYER_GAGA_BGRG_GAGA_RGBG = 4 + 0x6,
	BAYER_GAGA_RGBG_GAGA_BGRG = 4 + 0x7,
} ISP_BAYER_TYPE;

typedef enum _CURVE_TYPE_ {
	CURVE_BUILTIN = 0x1,
	CURVE_USER_DEFINE = 0x2
} CURVE_TYPE;

typedef enum _SNS_CLK_S_ {
	SNS_CLK_24_POINT_0	= 0x1,
	SNS_CLK_27_POINT_0	= 0x2,
	SNS_CLK_37_POINT_125	= 0x3,
} SNS_CLK;

typedef enum _SNS_DATA_BIT_S_ {
	LINER_DATA_8_BITS = 0x1,
	LINER_DATA_12_BITS = 0x2,
	LINER_DATA_14_BITS = 0x3,
	WDR_DATA_16_BITS = 0x4,
} SNS_DATA_BITS;

typedef enum _SIGNAL_POLARITY_S_ {
	ACTIVE_HIGH	= 0x0,
	ACTIVE_LOW	= 0x1
} SIGNAL_POLARITY;

typedef enum _AE_CMD_KEY_S_ {
	SET_AE_DEFAULT = 0x0,
	SET_ASC_EN = 0x1,
	SET_AGC_EN= 0x2,
	SET_APERTURE_EN = 0x3,
	SET_LUMA_REF = 0x4,
	SET_STAB_ZONE = 0x5,
	SET_STAB_CNT = 0x6,
	SET_DGAIN_MAX = 0x7,
	SET_SENSOR_GAIN_MAX = 0x8,
	SET_INTT_MAX = 0x9,
	SET_INTT_FINE_TIMING = 0xa,
	SET_GAIN_PREC = 0xb,
	SET_INTT_MIN = 0xc,
	SET_AE_SPPED = 0xd,
	SET_METERING_MODE = 0xe,
	SET_METERING_PARAM = 0xf,
	SET_METERING_WEIGHT = 0x10,
	SET_SENSOR_UP_MAX = 0x11,
	SET_SENSOR_UPEN_GAIN = 0x12,
	SET_SENSOR_UPDIS_GAIN = 0x13,
	SET_ADAPTIVE_EN = 0x14,
	SET_LUMA_REF_LOW = 0x15,
	SET_LUMA_REF_HIGH = 0x16,
	UPDATE_TAR_LUMA_STATUS = 0x17,
	GET_ENV_LUMA = 0x18,
	SET_METERING_WEIGHT_EX = 0x19,
	SET_HIGHLIGHT_SUPPRESSION = 0x1a,
} AE_CMD_KEY;


typedef enum _AWB_CMD_KEY_S_ {
	SET_AWB_DEFAULT = 0x0,
	CTRL_AWB_ENABLE = 0x1,
	SET_AWB_SPEED = 0x2,
	SET_AWB_SPEED_BYPASS = 0x3,
	SET_AWB_WHITEPOINT = 0x4,
	SET_STAT_CTRL = 0x5,
	SET_CCM_ARRAY = 0x6,
	SET_AWB_GAIN = 0x7,
	GET_AWB_GAIN = 0x8,
	SET_AWB_SENSOR_GAIN_ENABLE = 0x9,
} AWB_CMD_KEY;

typedef enum IPB_GAMMA_MODE_S_{
	GAMMA_OFF = 0,
	GAMMA_MODE_YC = 1,
	GAMMA_MODE_RGB = 2,
	GAMMA_MODE_RGBY = 3,
} IPB_GAMMA_MODE;

typedef struct _ISP_VERSION_S_ {
	FH_UINT32 u32SdkVer;
	FH_UINT32 FH_UINT32ChipVer;
	FH_UINT8 u08SdkSubVer;
	FH_UINT8 u08BuildTime[21];
} ISP_VERSION;

typedef struct _ISP_VI_HW_ATTR_S_ {
	SNS_CLK eSnsClock;
	SNS_DATA_BITS eSnsDataBits;
	SIGNAL_POLARITY eHorizontalSignal;
	SIGNAL_POLARITY eVerticalSignal;
	FH_BOOL u08Mode16;
	FH_UINT32 u32DataMaskHigh;
	FH_UINT32 u32DataMaskLow;
} ISP_VI_HW_ATTR;

typedef struct _ISP_VI_ATTR_ {
	FH_UINT16 u16WndHeight;///<sensor幅面高度
	FH_UINT16 u16WndWidth;/// <sensor幅面宽度
	FH_UINT16 u16InputHeight; ///<sensor输入图像高度
	FH_UINT16 u16InputWidth;///<sensor输入图像宽度
	FH_UINT16 u16OffsetX;///<裁剪水平偏移
	FH_UINT16 u16OffsetY;///<裁剪垂直偏移
	FH_UINT16 u16PicHeight;///<处理的图像高度
	FH_UINT16 u16PicWidth;///<处理的图像宽度
	FH_UINT16 u16FrameRate;///<帧率
	ISP_BAYER_TYPE  enBayerType;///<bayer数据格式
	ISP_BAYER_TYPE	enRgbaBayerType;///<rgba bayer数据格式

} ISP_VI_ATTR_S;

typedef struct _ISP_BLC_ATTR_S_ {
	FH_BOOL bGainmappingEn;
	FH_UINT16 u16Blclv;
	FH_UINT16 u16ChannelMode;
	FH_UINT16 u16BlcChannel0;
	FH_UINT16 u16BlcChannel1;
	FH_UINT16 u16BlcChannel2;
	FH_UINT16 u16BlcChannel3;
	FH_UINT16 u16Blc[GAIN_NODES];
} ISP_BLC_ATTR;

typedef struct _ISP_FFPN_CFG_S_ {
	FH_BOOL bFfpnEn;///<是否进入FPN统计。
	FH_UINT16 u16FpnStatGain;///<FPN统计时的sensor gain。
	FH_UINT16 u16Numexp;///<2^(num_exp+1)==列统计点数
	FH_UINT16	u16Thl;///<饱和度像素阈值
	FH_UINT16 u16Thh;///<饱和度像素阈值
} ISP_FFPN_CFG;

typedef struct _ISP_FFPN_INFO_S_ {
	FH_UINT32 u16StatFfpn[1280];
	FH_UINT16 u16FpnData[1280];
} ISP_FFPN_INFO;

typedef struct _ISP_PFPN_CFG_S_ {
	FH_BOOL bPfpnEn;
	FH_UINT8	u08PfpnMode;
	FH_UINT8	u08DpEn;
	FH_UINT16 u16PfpnGain;
} ISP_PFPN_CFG;

typedef struct _ISP_GB_CFG_S_ {
	FH_BOOL bGBEn;
	FH_UINT16 u16Th;
	FH_UINT16 u16Tl;
} ISP_GB_CFG;

typedef struct _DYNAMIC_DPC_CFG_S_ {
	FH_BOOL  bDpcEn;
	FH_BOOL  bGainMappingEn;
	FH_UINT8 ctrl_mode;
	FH_UINT8 u08Str;
	FH_UINT8 u08DpcMode;// 0:all close;1:white pixel correct open;2.black pixel correct open;3.all open.
	FH_UINT8 u08Strenght[GAIN_NODES];// 包括:mode,w_s,b_s
	FH_UINT8 u08WhiteThr[GAIN_NODES];//白点门限DC值
	FH_UINT8 u08BlackThr[GAIN_NODES];//黑点门限值
	FH_UINT8 u08wdc;
	FH_UINT8 u08bdc;
} DYNAMIC_DPC_CFG;

typedef struct _STATIC_DPC_CFG_S_ {
	FH_BOOL bStaticDccEn;
	FH_BOOL bStaticDpcEn;
	FH_UINT32 u32DpcTable[1024];
	FH_UINT16 u16DpcCol[32];
} STATIC_DPC_CFG;

typedef struct _ISP_LSC_CFG_S_ {
	FH_BOOL bLscEn;
	FH_UINT32 u32Coff[299];
} ISP_LSC_CFG;

typedef struct _ISP_NR3D_CFG_S_ {
	FH_BOOL bNR3DEn;
	FH_BOOL bGainMappingEn;
	FH_UINT8 u08PresetMap;
	FH_UINT8 u08CoeffMapIdx;
	FH_UINT8 u08Str;
	FH_UINT16 u16K1;
	FH_UINT16 u16K2;
	FH_UINT16 u16O1;
	FH_UINT16 u16O2;
	FH_UINT8 u08CoeffOffset;
	FH_UINT8 u8Nr3dSft;
	FH_UINT16  u16Dc;
	FH_UINT16  u8MtStr;
	FH_UINT8 u08StrMap[GAIN_NODES];
	FH_UINT8 u08CoeffOffsetMap[GAIN_NODES];
	FH_UINT8 u08MtStrMap[GAIN_NODES];
	FH_UINT8 u08RefCoeffRatio;
	FH_UINT8 u08CurCoeffRatio;
} ISP_NR3D_CFG;

typedef struct _ISP_LTM_CFG_S_ {
	FH_BOOL bLtmEn;
	CURVE_TYPE eCurveType;
	FH_UINT32 u32TonemapCurve[128];
	FH_UINT32 u32LtmIdx;
	FH_BOOL bRefresh;
	FH_BOOL bMode;
	FH_BOOL bLtmHwEn;
	FH_UINT8 u08HlYScaler;
	FH_UINT8 u08NlYScaler;
	FH_UINT8 u08YMaxRatio;
	FH_UINT8 u08YMeanRatio;
	FH_UINT8 u08YMinRatio;
	FH_UINT8 u08NlCtr;
	FH_UINT8 u08Weight1;
	FH_UINT8 u08Weight3;
	FH_UINT8 u08Weight0;
	FH_UINT8 u08Weight2;
	FH_UINT8 u08NlYScalerMap[GAIN_NODES];
	FH_UINT8 u08HlYScalerMap[GAIN_NODES];
	FH_UINT8 u08NlCtrMap[GAIN_NODES];
	FH_UINT8 u08EpsWdr;
	FH_UINT8 u08EpsLinear;
} ISP_LTM_CFG;

typedef struct _ISP_NR2D_CFG_S_ {
	FH_BOOL bNR2DEn;
	FH_BOOL bGainMappingEn;
	FH_UINT8 u8BlendingVal;
	FH_UINT8 u8Nr2dSft;
	FH_UINT8 u8CoeffOffset;
	FH_UINT8 u08Str;
	FH_UINT16 u16K1;
	FH_UINT16 u16K2;
	FH_UINT16 u16O1;
	FH_UINT16 u16O2;
	FH_UINT8 u08StrMap[GAIN_NODES];
} ISP_NR2D_CFG;

typedef struct _ISP_HLR_CFG_S_ {
	FH_BOOL bHlrEn;
	FH_SINT8 s08Level;
} ISP_HLR_CFG;

typedef struct _ISP_CONTRAST_CFG_S_ {
	FH_BOOL bYcEn;
	FH_BOOL bGainMappingEn;
	FH_UINT8 u08Crt;
	FH_UINT8 u08Mid;
	FH_UINT8 u08CrtMap[GAIN_NODES];//
} ISP_CONTRAST_CFG;

typedef struct _ISP_BRIGHTNESS_CFG_S_ {
	FH_BOOL bYcEn;
	FH_BOOL bGainMappingEn;
	FH_UINT8 u08Brt;
	FH_UINT8 u08BrtMap[GAIN_NODES];
} ISP_BRIGHTNESS_CFG;

typedef struct _ISP_SAT_CFG_S_ {
	FH_BOOL bGainMappingEn;
	FH_SINT8 s08RollAngle; //色度旋转因子 | [-64,63]
	FH_UINT8 u08Sat;
	FH_UINT8 u08BlueSurp;
	FH_UINT8 u08RedSurp;
	FH_UINT8 u08SatMap[GAIN_NODES];
} ISP_SAT_CFG;

typedef struct _ISP_APC_CFG_S_ {
	FH_BOOL bApcEn;
	FH_BOOL bMergesel;
	FH_BOOL bLutMode;
	FH_BOOL bLutMappingEn;
	FH_UINT8 u08DetailLutNum;
	FH_UINT8 u08EdgeLutNum;
	FH_BOOL bFilterMode;
	FH_BOOL bFilterMappingEn;
	FH_UINT8 u08DetailFNum;
	FH_UINT8 u08EdgeFNum;
	FH_BOOL bGainMappingEn;
	FH_UINT8 u08Pgain;
	FH_UINT8 u08EdgeLv;
	FH_UINT8 u08Ngain;
	FH_UINT8 u08DetailLv;
	FH_UINT16 u16DetailThl;
	FH_UINT16 u16DetailThh;
	FH_UINT16 u16EdgeThh;
	FH_UINT16 u16EdgeThl;
	FH_UINT8 u08EdgeMap[GAIN_NODES];
	FH_UINT8 u08DetailMap[GAIN_NODES];
	FH_UINT8 u08PgainMap[GAIN_NODES];
	FH_UINT8 u08NgainMap[GAIN_NODES];
	FH_UINT8 u08DetailLutMap[GAIN_NODES];
	FH_UINT8 u08EdgeLutMap[GAIN_NODES];
	FH_UINT8 u08DetailFilterMap[GAIN_NODES];
	FH_UINT8 u08EdgeFilterMap[GAIN_NODES];
} ISP_APC_CFG;

typedef enum  _GAMMA_BUILTIN_IDX_ {
	GAMMA_CURVE_10 = 0,
	GAMMA_CURVE_12 = 1,
	GAMMA_CURVE_14 = 2,
	GAMMA_CURVE_16 = 3,
	GAMMA_CURVE_18 = 4,
	GAMMA_CURVE_20 = 5,
	GAMMA_CURVE_22 = 6,
	GAMMA_CURVE_24 = 7,
	GAMMA_CURVE_26 = 8,
	GAMMA_CURVE_28 = 9,
} GAMMA_BUILTIN_IDX;

typedef struct _ISP_GAMMA_CFG_S_ {
	FH_BOOL bGammaEn;
	IPB_GAMMA_MODE u8GammaMode;
	CURVE_TYPE eCCurveType;
	GAMMA_BUILTIN_IDX eCGammaBuiltInIdx;
	FH_UINT16 u16CGamma[160];
	CURVE_TYPE eYCurveType;
	GAMMA_BUILTIN_IDX eYGammaBuiltInIdx;
	FH_UINT16 u16YGamma[160];
} ISP_GAMMA_CFG;

typedef struct _ISP_HIST_STAT_S_ {
	FH_UINT32 u32histBin[33][2];
} ISP_HIST_STAT;

typedef struct _ISP_YNR_CFG_S_ {
	FH_BOOL bYnrEn;
	FH_BOOL bGainMappingEn;
	FH_BOOL bCtrlMode;
	FH_BOOL bCoeffEn;
	FH_SINT8 s08YnrThSlopeM0;
	FH_SINT8 s08YnrThSlopeM1;
	FH_SINT8 s08YnrThSlopeM2;
	FH_UINT8 u08YnrThOffsetM0;
	FH_UINT8 u08YnrThOffsetM1;
	FH_UINT8 u08YnrThOffsetM2;
	FH_UINT8 u08MtCoeff0;
	FH_UINT8 u08MtCoeff1;
	FH_UINT8 u08YnrMtStrM0;
	FH_UINT8 u08YnrMtStrM1;
	FH_SINT8 s08YnrThSlope0[GAIN_NODES];
	FH_SINT8 s08YnrThSlope1[GAIN_NODES];
	FH_SINT8 s08YnrThSlope2[GAIN_NODES];
	FH_UINT8 u08YnrThOffset0[GAIN_NODES];
	FH_UINT8 u08YnrThOffset1[GAIN_NODES];
	FH_UINT8 u08YnrThOffset2[GAIN_NODES];
	FH_UINT8 u08YnrMtStr0[GAIN_NODES];
	FH_UINT8 u08YnrMtStr1[GAIN_NODES];
} ISP_YNR_CFG;

typedef struct _ISP_CNR_CFG_S_ {
	FH_BOOL bCnrEn;
	FH_BOOL bCnrCtrlMode;
	FH_UINT8 u08CnrStr;
	FH_BOOL bGainMappingEn;
	FH_UINT8 u08CnrStrMap[GAIN_NODES];
} ISP_CNR_CFG;

typedef struct _ISP_PURPLEFRI_CFG_S_ {
	FH_BOOL bPurpleEn;
	FH_UINT8 u08Shiftbits;
	FH_BOOL bSatcorrenable;
	FH_UINT16 u16Rollangle;
	FH_UINT16 u16Adjangle;
	FH_UINT16 u16Ygapth;
	FH_UINT16 u16Yth;
	FH_UINT16 u16Expoth;
	FH_UINT16 u16Ulth;
	FH_UINT16 u16Uhth;
	FH_UINT16 u16Satthh;
	FH_UINT16 u16Satthl;
} ISP_PURPLEFRI_CFG;

typedef struct _ISP_LC_CFG_S_ {
	FH_BOOL bLc0En;
	FH_UINT8 u08Gain0;
	FH_UINT8 u08Alpha0;
	FH_UINT16 u16Theta0;
	FH_BOOL bLc1En;
	FH_UINT8 u08Gain1;
	FH_UINT8 u08Alpha1;
	FH_UINT16 u16Theta1;
	FH_BOOL bLc2En;
	FH_UINT8 u08Gain2;
	FH_UINT8 u08Alpha2;
	FH_UINT16 u16Theta2;
} ISP_LC_CFG;

typedef struct _ISP_AE_PARAM_S_ {
	FH_UINT32 u32Dev;
} ISP_AE_PARAM;

typedef struct _ISP_AE_STAT1_S_ {
	FH_UINT32 u32SumLuma[9];
	FH_UINT32 u32Cnt[9];
} ISP_AE_STAT1;

typedef struct _ISP_AE_STAT2_S_ {
	FH_UINT64 u64SumLuma[33];
	FH_UINT32 u32Cnt[33];
} ISP_AE_STAT2;

typedef struct _ISP_AE_STAT3_S_ {
	FH_UINT16 u32GlobalAvgLuma[1024];
} ISP_AE_STAT3;

typedef struct _ISP_AE_STAT_S_ {
	ISP_AE_STAT1 stAeStat1;
	ISP_AE_STAT2 stAeStat2;
} ISP_AE_STAT;

typedef struct _AE_STAT_CFG_S_ {
	FH_BOOL bChange;
	FH_UINT16 FH_UINT16HistStatThr[32];
} AE_STAT_CFG;

typedef struct _ISP_AE_INFO_S_ {
	FH_UINT32 u32Intt;
	FH_UINT32 u32IspGain;
	FH_UINT32 u32IspGainShift;
	FH_UINT32 u32SensorGain;
	FH_UINT32 u32TotalGain;
	AE_STAT_CFG stAeStatCfg;
} ISP_AE_INFO;

typedef struct _ISP_AE_STAT_WIN_S_ {
	FH_UINT16 winHOffset;
	FH_UINT16 winVOffset;
	FH_UINT16 winHSize;
	FH_UINT16 winVSize;
} ISP_AE_STAT_WIN;

typedef struct _AE_WEIGHT_CFG_S_ {
	FH_UINT8 u08Weight[9];
} AE_WEIGHT_CFG;

typedef struct _AE_WEIGHT_EX_CFG_S_ {
	FH_UINT8 u08Weight[256];
} AE_WEIGHT_EX_CFG;

typedef struct _AE_HIGHLIGHT_SUPPRESSION_CFG_S {
	FH_UINT8 u08LumaBoundary;
	FH_UINT8 u08RoiWeight;
	FH_UINT8 u08SensQuality;
} AE_HIGHLIGHT_SUPPRESSION_CFG;

typedef struct _AE_DEFAULT_CFG_S_ {
	FH_BOOL bAscEn;
	FH_BOOL bAgcEn;
	FH_BOOL bApertureEn;
	FH_UINT8 u08LumaRef;
	FH_UINT8 u08StabZone0;
	FH_UINT8 u08StabZone1;
	FH_UINT8 u08StabCnt;
	FH_UINT16 u16DgainMax;
	FH_UINT16 u16SensorGainMax;
	FH_UINT16 u16InttMax;
	FH_UINT8 u08InttFineTiming;
	FH_UINT8 u08InttMin;
	FH_UINT8 u08AeSpeed;
	FH_UINT8 u08MeteringMode;
	FH_UINT8 u08MeteringParam;
	AE_WEIGHT_CFG weightParam;
	FH_UINT8 u08UpMax;
	FH_UINT16 u16UpEnGain;
	FH_UINT16 u16UpDisGAIN;
	FH_BOOL bAdaptiveEn;
	FH_UINT8 u08LumaRefLow;
	FH_UINT8 u08LumaRefHigh;
	FH_UINT8 u08GainPrec;
	AE_WEIGHT_EX_CFG weightExParam;
	AE_HIGHLIGHT_SUPPRESSION_CFG highlightParam;
} AE_DEFAULT_CFG;

typedef struct _ISP_AWB_PARAM_S_ {
	FH_UINT32 u32Dev;
} ISP_AWB_PARAM;

typedef struct _ISP_AWB_STAT1_S_ {
	FH_UINT32 u32AwbBlockCnt[9];
	FH_UINT32 u32AwbBlockB[9];
	FH_UINT32 u32AwbBlockG[9];
	FH_UINT32 u32AwbBlockR[9];
} ISP_AWB_STAT1;

typedef struct _ISP_AWB_STAT2_S_ {
	FH_UINT16 u32AwbBlockCnt[1024];
	FH_UINT16 u32AwbBlockB[1024];
	FH_UINT16 u32AwbBlockG[1024];
	FH_UINT16 u32AwbBlockR[1024];
} ISP_AWB_STAT2;

typedef struct _ISP_AWB_FRONT_STAT_S_{
	FH_UINT32 u32AwbBlockCnt[64];
	FH_UINT32 u32AwbBlockB[64];
	FH_UINT32 u32AwbBlockG[64];
	FH_UINT32 u32AwbBlockR[64];
} ISP_AWB_FRONT_STAT;

typedef struct _ISP_AWB_INFO_S_ {
	ISP_AWB_STAT1 stAwbStat1;
} ISP_AWB_INFO;

typedef struct _ISP_AWB_STAT_WIN_S_ {
	FH_UINT16 winHOffset;
	FH_UINT16 winVOffset;
	/*FH8856's WinHsize and winVsize need to be 16 pixels alignment in wdr mode*/
	FH_UINT16 winHSize;
	FH_UINT16 winVSize;
} ISP_AWB_STAT_WIN;

typedef struct _STAT_WHITE_POINT_S_ {
	FH_UINT16 u16Coordinate_w;
	FH_UINT16 u16Coordinate_h;
} STAT_WHITE_POINT;

typedef struct _AWB_STAT_CFG_S_ {
	FH_BOOL bChange;
	FH_UINT16 u16YHighThreshold;
	FH_UINT16 u16YLowThreshold;
	STAT_WHITE_POINT stPoint[7];
} AWB_STAT_CFG;

typedef struct _ISP_AWB_CFG_S_ {
	FH_UINT32 u32AwbGain[3];	//rgain,ggain,bgain
	FH_UINT16 u16CcmCfg[12];
	AWB_STAT_CFG stAwbStatCtrl;
	AWB_STAT_CFG stAwbLongStatCtrl;
	AWB_STAT_CFG stAwbShortStatCtrl;
} ISP_AWB_CFG;

typedef struct _AWB_WHITE_POINT_S_ {
	FH_UINT16 u16BOverG[4];
	FH_UINT16 u16ROverG[4];
} AWB_WHITE_POINT;

typedef struct _AWB_WHITE_EREA_S_ {
	FH_UINT32 u32Area_P[5];
} AWB_WHITE_EREA;

typedef struct _CCM_TABLE_S_ {
	FH_UINT16 u16CcmTable[4][12];
} CCM_TABLE;

typedef struct _STAT_CTRL_S_ {
	FH_UINT16 u16AwbThresholdL;
	FH_UINT16 u16AwbThresholdH;
} STAT_CTRL;

typedef struct _AWB_DEFAULT_CFG_S_ {
	FH_BOOL bAwbEn;
	FH_BOOL bCcmEn;
	FH_UINT8 awbMode;
	FH_UINT16 u16AwbSpeed;
	AWB_WHITE_POINT stWhitePoint;
	AWB_WHITE_EREA  stWhiteArea;
	STAT_CTRL stStatCtrl;
	CCM_TABLE stCcmTable;
} AWB_DEFAULT_CFG;

typedef struct _AWB_SENSOR_REG_S_ {
	FH_SINT32(*pfAwbGetDefaultParam)(AWB_DEFAULT_CFG *pstIspAwbCfg);
} AWB_SENSOR_REG;

typedef struct _ISP_ALGORITHM_S_ {
	FH_UINT8	u08Name[16];
	FH_UINT8 u08AlgorithmId;
	FH_VOID(*run)(FH_VOID);
} ISP_ALGORITHM;

typedef struct _ISP_DEFAULT_PARAM_ {
	ISP_BLC_ATTR stBlcCfg;
	ISP_LTM_CFG stLtmCfg;
	ISP_GAMMA_CFG stGamma;
	ISP_SAT_CFG stSaturation;
	ISP_APC_CFG stApc;
	ISP_CONTRAST_CFG stContrast;
	ISP_BRIGHTNESS_CFG stBrt;
	ISP_NR3D_CFG stNr3d;
	ISP_NR2D_CFG stNr2d;
	ISP_YNR_CFG stYnr;
	ISP_CNR_CFG stCnr;
	DYNAMIC_DPC_CFG  stDpc;
	ISP_LSC_CFG stLscCfg;
} ISP_DEFAULT_PARAM;

typedef struct _ISP_VI_STAT_S {
	FH_UINT32 u32IPBIntCnt;                /* The video frame back interrupt count */
	FH_UINT32 u32IPFIntCnt;                /* The video frame front interrupt count */
	FH_UINT32 u32FrmRate;                  /* current frame rate */
	FH_UINT32 u32PicWidth;                 /* curren pic width */
	FH_UINT32 u32PicHeight;                /* current pic height */
	FH_UINT32 u32IpfOverFlow;
	FH_UINT32 u32IspErrorSt;
} ISP_VI_STAT_S;

typedef struct _GLOBE_STAT_S {
	struct _Block_gstat {
		FH_UINT32 sum;
		FH_UINT32 cnt;
		FH_UINT32 max;
		FH_UINT32 min;
	} r, gr, gb, b;
} GLOBE_STAT;

typedef struct _GLOBE_STAT_CFG_S {
	FH_UINT8 width;
	FH_UINT8 height;
	FH_UINT8 cnt_x;
	FH_UINT8 cnt_y;
} GLOBE_STAT_CFG;

//----------------AF-------------------
typedef struct _ISP_AF_FILTER_S {
	FH_SINT8  afPreFilterCoe[7];
	FH_UINT16 afPreFilterMul;
	FH_UINT16 afPreFilterShift;
	FH_SINT8  afVfilter0[25];
	FH_UINT16 afVFilter0Shift;
	FH_UINT16 afVFilter0T;
//*no use below (FH8856)*//
	FH_SINT8  afVfilter1[25];
	FH_UINT16 afVFilter1Shift;
	FH_UINT16 afVFilter1T;
	FH_BOOL   afHfilter0En[3];
	FH_UINT8  afHfilter0Gain;
	FH_UINT16 afHFilter0T;
	FH_SINT16 afHFilter0Offset;
	FH_UINT8  afHFilter0Shift[7];
	FH_UINT16 afHFilter0C[6];
	FH_UINT16 afHFilter0D[6];
	FH_BOOL   afHfilter1En[3];
	FH_UINT8  afHfilter1Gain;
	FH_UINT16 afHFilter1T;
	FH_SINT16 afHFilter1Offset;
	FH_UINT8  afHFilter1Shift[7];
	FH_UINT16 afHFilter1C[6];
	FH_UINT16 afHFilter1D[6];

} ISP_AF_FILTER;

typedef struct _ISP_AF_WIN_INFO_S {
	FH_UINT16 winHStart0;		/*the start pixel in horizontal direction, more than 2*/
	FH_UINT16 winVStart0;		/*the start pixel in vertical direction, more than 2*/

	FH_UINT8 winWidth0;			/*window width*/
	FH_UINT8 winHeight0;			/*window height*/
	FH_UINT16 winHStart1;		/*the start pixel in horizontal direction, more than 2*/
	FH_UINT16 winVStart1;		/*the start pixel in vertical direction, more than 2*/
	FH_UINT8 winHCnt1;			/*the number of window in horizontal direction*/
	FH_UINT8 winVCnt1;			/*the number of window in vertical direction*/
	FH_UINT8 winWidth1;			/*window width*/
	FH_UINT8 winHeight1;			/*window height*/
} ISP_AF_WIN_INFO;

typedef struct _ISP_AF_STAT_ADDR_S {
	FH_UINT32 startAddr;
} ISP_AF_STAT_ADDR;

typedef struct _ISP_AF_STAT_PIXEL_S {
	FH_UINT32 line_e;
	FH_UINT32 line_o;
	FH_UINT32 column_e;
	FH_UINT32 column_o;
} ISP_AF_STAT_DATA;

typedef struct _ISP_AF_STAT_S {
	ISP_AF_STAT_DATA stat_win1[16];
	ISP_AF_STAT_DATA stat_win0;
} ISP_AF_STAT;

typedef struct _ISP_GME_PARAM_S_ {
	FH_SINT32 s32x; //x vector
	FH_SINT32 s32y; //y vector
} ISP_GME_PARAM;

typedef struct _ISP_STATUS_S_ {
	FH_UINT32 u32day;
} ISP_STATUS;


typedef struct _ISP_DEBUG_INFO_S_ {
	FH_UINT32 envLuma;
	FH_UINT32 sqrtenvLuma;
	FH_UINT32 sensor_gain;
	FH_UINT32 isp_gain;
} ISP_DEBUG_INFO;

typedef struct _ISP_WDR_MERGE_CFG_ {
    FH_UINT16 u16MergeX0;  // Merge曲线的第一个折点横坐标。
    FH_UINT16 u16MergeX1;  // Merge曲线的第二个折点横坐标。
    FH_UINT16 u16MergeX2;  // Merge曲线的第三个折点横坐标。
    FH_UINT16 u16MergeX3;  // Merge曲线的第四个折点横坐标。
    FH_UINT16 u16MergeY0;  // Merge曲线的第一个折点纵坐标。
    FH_UINT16 u16MergeY1;  // Merge曲线的第二个折点纵坐标。
    FH_UINT16 u16MergeY2;  // Merge曲线的第三个折点纵坐标。
    FH_UINT16 u16MergeY3;  // Merge曲线的第四个折点纵坐标。
}ISP_WDR_MERGE_CFG;

typedef struct _ISP_WDR_CFG_S_ {
	FH_BOOL bWdrEn;
	FH_BOOL bShowHist;
	FH_BOOL bMode;
	FH_BOOL bAutoAdjustEn;
	FH_UINT8 u08SframeCorrMode;
	FH_UINT16 u16SensorOutputMax;
	FH_UINT16 u16SframeCorrTiming;
	FH_UINT8 u08ExposureRatio;
	FH_UINT8 u08ExposureRatioMin;
	FH_UINT8 u08ExposureRatioMax;
	FH_UINT16 u16WdrDc;
	FH_UINT8 u08WdrMergeCfg;
	FH_UINT8 u08PreCurveIdx;
	FH_UINT16 u16LfOverexpRatioThh;
	FH_UINT16 u16LfOverexpRatioThl;
	FH_UINT16 u16SfOverexpRatioTh;
	FH_UINT16 u16GainTh;
} ISP_WDR_CFG;

typedef struct _ISP_POST_GAIN_CFG_S {
	FH_UINT16 rGain;
	FH_UINT16 gGain;
	FH_UINT16 bGain;
	FH_UINT16 rOffset;
	FH_UINT16 gOffset;
	FH_UINT16 bOffset;
} ISP_POST_GAIN_CFG;

typedef struct _RGBA_ABAL_CFG_S_
{
    FH_UINT8 abalSpeed;
    FH_UINT8 abalThl;
    FH_UINT8 abalThh;
    FH_UINT8 abalStabTime;
    FH_UINT8 abalStep;
    FH_UINT8 abalTargetStabTime;
    FH_UINT8 abalTargetThr;
} RGBA_ABAL_CFG;

typedef struct _RGBA_WEIGHT_CFG_S_
{
    FH_UINT8  W2Speed;
    FH_UINT8  W2Thl;
    FH_UINT8  W2Thh;
    FH_UINT8  W2StabTime;
    FH_UINT8  W2Step;
    FH_UINT8  W2AThl;
    FH_UINT8  W2AThh;
    FH_UINT16 W2GThl;
    FH_UINT16 W2GThh;
} RGBA_WEIGHT_CFG;

typedef struct _RGBA_CCM_TABLE_S_
{
    FH_UINT16 RgbaCcmTable[2][16];
} RGBA_CCM_TABLE;

typedef struct _RGBA_CONVERT_TH_S_
{
    FH_UINT16 convThl;
    FH_UINT16 convThh;
} RGBA_CONVERT_TH;

typedef struct _RGBA_ENHANCE_TH_S_
{
    FH_UINT16 enhThl;
    FH_UINT16 enhThh;
} RGBA_ENHANCE_TH;

typedef struct _RGBA_ETH_S_
{
    FH_UINT16 eThl;
    FH_UINT16 eThh;
} RGBA_ETH;

typedef struct _RGBA_EGAIN_CFG_S_
{
    FH_UINT8 egainR;
    FH_UINT8 egainG;
    FH_UINT8 egainB;
} RGBA_EGAIN_CFG;

typedef struct _RGBA_DEFAULT_CFG_S_
{
    FH_BOOL         bRgbaEn;
    FH_BOOL         bIrmode;
    FH_BOOL         bFirFrm;
    RGBA_ABAL_CFG   abalParam;
    RGBA_WEIGHT_CFG weightParam;
    RGBA_CCM_TABLE  ccmTab;
    RGBA_CONVERT_TH convTh;
    RGBA_ENHANCE_TH enhTh;
    RGBA_ETH        eTh;
    RGBA_EGAIN_CFG  egain;
} RGBA_DEFAULT_CFG;

typedef struct _RGBA_CURR_INFO_S_
{
    FH_UINT16 u08RBalGainPre;
    FH_UINT8  u08RBalCnt;
    FH_UINT8  u08RBalTargetCnt;
    FH_UINT16 u16W2Pre;
    FH_UINT16 u16W2Cnt;
} RGBA_CURR_INFO;

typedef enum _RGBA_CMD_KEY_S_ {
    SET_RGBA_DEFAULT = 0x0,
    SET_RGBA_EN = 0x1,
    SET_RGBA_FIRFRM = 0x2,
    SET_RGBA_IRMODE = 0x3,
    SET_ABAL_PARA = 0x4,
    SET_WEIGHT_PARA = 0x5,
    SET_RGBA_CCM_TABLE = 0x6,
    SET_CONVERT_TH = 0x7,
    SET_ENHANCE_TH = 0x8,
    SET_ETH = 0x9,
    SET_EGAIN = 0xa,
} RGBA_CMD_KEY;


typedef struct _RGBA_LUT_S_
{
    FH_UINT32 lut[6];
} RGBA_LUT;

typedef struct _RGBA_STAT_INFO_S_
{
    struct rgba_blk_info
    {
        FH_UINT32 R_sum;
        FH_UINT32 G_sum;
        FH_UINT32 B_sum;
        FH_UINT32 A_sum;
        FH_UINT32 IR_sum;
        FH_UINT32 cnt;
    } blk_rgba[32];
} RGBA_STAT_INFO;

typedef struct _RGBA_DPC_CFG_S
{
    FH_BOOL   bRGBADpcEn;
    FH_BOOL   bGainMappingEn;
    FH_UINT8  u08DpcMode;  // 0:all close;1:white pixel correct open;2.black pixel correct open;3.all open.
    FH_UINT8  u08ModeIdx;
    FH_UINT8  u08Str;
    FH_UINT8  u08wdc;
    FH_UINT8  u08bdc;
    FH_UINT8  u08ThhIR;
    FH_UINT8  u08ThlIR;
    FH_UINT8  u08ThhG;
    FH_UINT8  u08ThlG;
    FH_UINT16 u16DiffMin;
    FH_UINT8  u08DiffShift;
    FH_UINT8  u08Strenght[GAIN_NODES];  // 包括:mode,w_s,b_s
    FH_UINT8  u08WhiteThr[GAIN_NODES];  //白点门限DC值
    FH_UINT8  u08BlackThr[GAIN_NODES];  //黑点门限值
} RGBA_DPC_CFG;

typedef struct _SMART_IR_CFG_S {
	FH_UINT16 u16gainDay2Night;    //for bayer sensor
	FH_UINT16 u16gainNight2Day;    //for bayer sensor
	FH_UINT16 u16lumaDay2Night;    //for rgbir sensor
	FH_UINT16 u16lumaNight2Day;    //for rgbir sensor
} SMART_IR_CFG;

/******************************************************************/
/******************isp init cfg structure**************************/
/******************************************************************/
/******************************************************************/
typedef struct _BLC_INIT_CFG_S {
	FH_UINT16 blc_level;
} BLC_INIT_CFG;

typedef struct _WB_INIT_CFG_S {
	FH_UINT16 wbGain[3]; //rgain, ggain, bgain;
} WB_INIT_CFG;

typedef struct _CCM_INIT_CFG_S {
	FH_UINT16 ccmCfg[9]; //rr, gr, br, rg, gg, bg, rb, gb, bb
} CCM_INIT_CFG;

typedef struct _DPC_INIT_CFG_S {
	FH_UINT8 ctrlMode;
	FH_UINT8 str;
} DPC_INIT_CFG;

typedef struct _APC_INIT_CFG_S {
	FH_UINT8 edgeStr; //
	FH_UINT8 detailStr; //
	FH_UINT8 positiveStr; //
	FH_UINT8 negativeStr; //
} APC_INIT_CFG;

typedef struct _YNR_INIT_CFG_S {
	FH_UINT8 th_slope[3]; //
	FH_UINT8 th_offset[3]; //
} YNR_INIT_CFG;

typedef struct _CTR_INIT_CFG_S {
	FH_UINT16 ctr;
} CTR_INIT_CFG;

typedef struct _SAT_INIT_CFG_S {
	FH_UINT16 sat;
	FH_UINT16 blue_surp;
	FH_UINT16 red_surp;
} SAT_INIT_CFG;

typedef struct _GAMMA_MODE_INIT_CFG_S {
	FH_UINT16 gamma_mode;
} GAMMA_MODE_INIT_CFG;

typedef struct _GAMMA_INIT_CFG_S {
	FH_UINT32 gamma[80];
} GAMMA_INIT_CFG;

typedef struct _LTM_INIT_CFG_S {
	FH_UINT32 ltm[128];
} LTM_INIT_CFG;
/******************************************************************/
/******************end of isp init cfg structure*******************/
/******************************************************************/
/******************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*_ISP_COMMON_H_*/
