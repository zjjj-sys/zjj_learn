#ifndef _ISP_API_H_
#define _ISP_API_H_


#include "isp_common.h"
#include "isp_sensor_if.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define lift_shift_bit_num(bit_num)			(1<<bit_num)
// #define DEBUG_API 1

#define CHECK_VALIDATION(x,a,b)	\
do {							\
	int r;						\
	if( (x<a) || (x>b))			\
	{							\
		if (x<a)				\
			r=a;				\
		else					\
			r=b;				\
		fh_printf("[WARNING]parameter out of range @%s %s= %d | range=[%d,%d] | auto clip to %d\n",__func__,#x,x,a,b,r);\
		x=r;					\
	}							\
}while(0)

#if DEBUG_API
#define TRACE_API fh_printf("!!!CALL API :%s\n",__func__)
#else
#define TRACE_API
#endif

#define FUNC_DEP __attribute__((deprecated))

enum ISP_HW_MODULE_LIST
{
	HW_MODUL_WBS 		=	  lift_shift_bit_num(0),
	HW_MODUL_WBL 		=	  lift_shift_bit_num(1),
	HW_MODUL_WDR 		=	  lift_shift_bit_num(2),
	HW_MODUL_HMIRROR 	=	  lift_shift_bit_num(3),
	HW_MODUL_LSC  		=     lift_shift_bit_num(4),
	HW_MODUL_DPC		=     lift_shift_bit_num(5),
	HW_MODUL_NR3D    	=     lift_shift_bit_num(6),
	HW_MODUL_NR2D   	=     lift_shift_bit_num(7),
	HW_MODUL_GB      	=     lift_shift_bit_num(8),
	HW_MODUL_GAIN   	=     lift_shift_bit_num(9),
	HW_MODUL_POST_GAIN 	=     lift_shift_bit_num(10),
	HW_MODUL_LTM     	=     lift_shift_bit_num(11),
	HW_MODUL_APC     	=     lift_shift_bit_num(12),
	HW_MODUL_CGAMMA		=     lift_shift_bit_num(13),
	HW_MODUL_YGAMMA		=     lift_shift_bit_num(14),
	HW_MODUL_FCCFA	    =     lift_shift_bit_num(15),
	HW_MODUL_HLR        =     lift_shift_bit_num(16),
	HW_MODUL_RGBB 		=     lift_shift_bit_num(17),
	HW_MODUL_WB       	=     lift_shift_bit_num(18),
	HW_MODUL_YNR		=     lift_shift_bit_num(19),
	HW_MODUL_CNR		=     lift_shift_bit_num(20),
	HW_MODUL_PURPLE		=     lift_shift_bit_num(21),
	HW_MODUL_CHROMA		=     lift_shift_bit_num(22),
	HW_MODUL_LOCAL_CHROMA=     lift_shift_bit_num(23),
	HW_MODUL_GLOBE_STAT	=     lift_shift_bit_num(24),
	HW_MODUL_STAT_HIST	=     lift_shift_bit_num(25),
};


typedef struct mirror_cfg_s
{
	FH_BOOL				bEN;
	ISP_BAYER_TYPE		normal_bayer;
	ISP_BAYER_TYPE		mirror_bayer;
}MIRROR_CFG_S;

FH_SINT32 FUNC_DEP API_ISP_GetBuffSize(unsigned int width, unsigned int height);
FH_SINT32 API_ISP_MemInit( FH_UINT32 width, FH_UINT32 height );
//int API_ISP_GetMemSize(FH_UINT32 *u32Memsize);
//int API_ISP_MemCfg(FH_UINT32 u32MemAddr,FH_UINT32 u32MemSize);



/**
 * @brief		获取ISP的param参数的地址和大小
 *
 * @param[out]	*u32BinAddr: param的地址
 * @param[out]   *u32BinSize: param的size
 *
 * @return
 *
 */
FH_SINT32 API_ISP_GetBinAddr(FH_UINT32 *u32BinAddr,FH_UINT32 *u32BinSize);

FH_SINT32 FUNC_DEP API_ISP_SetViHwAttr(const ISP_VI_HW_ATTR *pstViHwAttr);

FH_SINT32 API_ISP_SensorInit(FH_VOID);
FH_SINT32 API_ISP_SetSensorFmt(FH_UINT32 format);

FH_SINT32 API_ISP_SensorKick(FH_VOID);
FH_SINT32 API_ISP_SetSensorIntt(FH_UINT32 intt);
FH_SINT32 API_ISP_SetSensorGain(FH_UINT32 gain);

FH_SINT32 API_ISP_SetSensorReg(FH_UINT16 addr,FH_UINT16 data);
FH_SINT32 API_ISP_GetSensorReg(FH_UINT16 addr, FH_UINT16 *data);
FH_SINT32 API_ISP_SetCisClk(FH_UINT32 cisClk);
FH_SINT32 API_ISP_CisClkEn(FH_BOOL bEn);
FH_SINT32 API_ISP_SetViAttr(const ISP_VI_ATTR_S *pstViAttr);
FH_SINT32 API_ISP_GetViAttr(ISP_VI_ATTR_S *pstViAttr);
FH_SINT32 API_ISP_GetIspMode(FH_UINT32 *mode);
FH_SINT32 API_ISP_Init(FH_VOID);
FH_SINT32 API_ISP_SetIspParam(ISP_DEFAULT_PARAM *pstDefaultParam);
FH_SINT32 API_ISP_LoadIspParam(char *isp_param_buff);
FH_SINT32 API_ISP_EnableCircularErrStopFlow(FH_VOID);
FH_SINT32 API_ISP_DisableCircularErrStopFlow(FH_VOID);
FH_SINT32 API_ISP_CLEAN_CIRCLUAR_BUFF(FH_VOID);
FH_SINT32 API_ISP_Pause(FH_VOID);
FH_SINT32 API_ISP_SoftReset(FH_VOID);
FH_SINT32 FUNC_DEP API_ISP_KickStart(FH_VOID);
FH_SINT32 API_ISP_Resume(FH_VOID);
FH_SINT32 API_ISP_DetectPicSize(FH_VOID);
/*
 * @brief	ISP策略处理函数
 *
 * @return 	0, 处理正常
 * 			-1，图像丢失
 * 			1， 图像恢复
 */
FH_SINT32 API_ISP_Run(FH_VOID);
FH_SINT32 API_ISP_AE_AWB_Run(FH_VOID);
FH_SINT32 API_ISP_Exit(FH_VOID);
FH_SINT32 API_ISP_SensorRegCb(FH_UINT32 u32SensorId, struct isp_sensor_if* pstSensorFunc);
FH_SINT32 API_ISP_SensorUnRegCb(FH_UINT32 u32SensorId);

FH_SINT32 API_ISP_Set_HWmodule_cfg(FH_UINT32 u32modulecfg);
FH_SINT32 API_ISP_Get_HWmodule_cfg(FH_UINT32 *u32modulecfg);
FH_SINT32 API_ISP_GetAlgCtrl(FH_UINT32 *u32AlgCtrl);
FH_SINT32 API_ISP_SetAlgCtrl(FH_UINT32 u32AlgCtrl);

FH_SINT32 FUNC_DEP API_ISP_WaitVD(FH_VOID);
FH_SINT32 FUNC_DEP API_ISP_GetVersion(ISP_VERSION *pstIspVersion);
FH_SINT32 FUNC_DEP API_ISP_SetIspReg(FH_UINT32 u32RegAddr,FH_UINT32 u32RegData);
FH_SINT32 FUNC_DEP API_ISP_GetIspReg(FH_UINT32 u32RegAddr,FH_UINT32 *u32RegData);
FH_SINT32 API_ISP_GetRaw(FH_BOOL strategy_en, FH_VOID* pRawBuff, FH_UINT32 u32Size, FH_UINT32 u32FrameCnt);
FH_SINT32 API_ISP_CheckStatReady(FH_BOOL *isReady);
/**  AE */
FH_SINT32 API_ISP_AEAlgEn(FH_BOOL bEn);
FH_SINT32 API_ISP_AESendCmd(FH_UINT32 u32Cmd,FH_VOID *param);
FH_SINT32 API_ISP_SetAeStatWin(ISP_AE_STAT_WIN *pstAeStatWin);
FH_SINT32 API_ISP_GetAeStatWin(ISP_AE_STAT_WIN *pstAeStatWin);
FH_SINT32 API_ISP_GetAeStat(ISP_AE_STAT * pstAeStat);
FH_SINT32 API_ISP_SetAeInfo(const ISP_AE_INFO *pstAeInfo);
FH_SINT32 API_ISP_GetAeInfo(ISP_AE_INFO *pstAeInfo);
FH_SINT32 API_ISP_GetAeCfg(AE_DEFAULT_CFG *pstAeDefaultCfg);
FH_SINT32 API_ISP_RegisterAeOpStatusCallback(AeOpStatusCallback cb);
/**  AWB */
FH_SINT32 API_ISP_SetAwbStatWin(ISP_AWB_STAT_WIN *pstAwbStatWin);
FH_SINT32 API_ISP_GetAwbStatWin(ISP_AWB_STAT_WIN *pstAwbStatWin);
FH_SINT32 API_ISP_GetAwbStat(const ISP_AWB_INFO * pstAwbInfo);
FH_SINT32 API_ISP_GetAwb1Stat(const ISP_AWB_INFO * pstAwbInfo);
FH_SINT32 API_ISP_GetLongAwbStat(const ISP_AWB_FRONT_STAT * pstAwbFrontStat);
FH_SINT32 API_ISP_GetShortAwbStat(const ISP_AWB_FRONT_STAT * pstAwbFrontStat);
FH_SINT32 API_ISP_SetAwbCfg(ISP_AWB_CFG *pstAwbCfg);
FH_SINT32 API_ISP_AWBAlgEn(FH_BOOL bEn);
FH_SINT32 API_ISP_AWBSendCmd(FH_UINT32 u32Cmd,FH_VOID *param);
FH_SINT32 API_ISP_GetAwbCfg(AWB_DEFAULT_CFG *pstAwbDefaultCfg);
/** GLOBESTATE **/
FH_SINT32 API_ISP_GetGlobeStat(GLOBE_STAT *pstGlobeStat);
FH_SINT32 API_ISP_SetGlobeStat(GLOBE_STAT_CFG *pstGlobeStat);
/**  AF*/
FH_SINT32 FUNC_DEP API_ISP_AFlibRegCb(FH_VOID);
FH_SINT32 FUNC_DEP API_ISP_AFlibUnRegCb(FH_VOID);
FH_SINT32 API_ISP_AFAlgEn(FH_BOOL bEn);
FH_SINT32 API_ISP_AFSendCmd(FH_UINT32 u32Dev,FH_UINT32 u32Cmd,FH_VOID *param);
FH_SINT32 API_ISP_SetAFFilter(const ISP_AF_FILTER *pstAfFilter);
FH_SINT32 API_ISP_GetAFFilter(ISP_AF_FILTER *pstAfFilter);
FH_SINT32 API_ISP_SetAFWinInfo(const ISP_AF_WIN_INFO *pstAfWinInfo);
FH_SINT32 API_ISP_GetAFStat(ISP_AF_STAT *pstAfStat);
FH_SINT32 FUNC_DEP API_ISP_SetAFStatAddr(const ISP_AF_STAT_ADDR *pstAfStatAddr);
FH_SINT32 FUNC_DEP API_ISP_GetAFStatAddr(ISP_AF_STAT_ADDR *pstAfStatAddr);
/**LTM*/
FH_SINT32 API_ISP_SetLtmCfg(ISP_LTM_CFG *pstLtmCfg);
FH_SINT32 API_ISP_GetLtmCfg(ISP_LTM_CFG *pstLtmCfg);
/**  BLC function  */
FH_SINT32 API_ISP_SetBlcAttr(ISP_BLC_ATTR * pstBlcAttr);
FH_SINT32 API_ISP_GetBlcAttr(ISP_BLC_ATTR * pstBlcAttr);

/** GB*/
FH_SINT32 API_ISP_SetGbCfg(ISP_GB_CFG *pstGbCfg);
FH_SINT32 API_ISP_GetGbCfg(ISP_GB_CFG *pstGbCfg);
/** DPC*/
FH_SINT32 FUNC_DEP API_ISP_SetStaticDpc(STATIC_DPC_CFG *pstStaticDpc);
FH_SINT32 FUNC_DEP API_ISP_GetStaticDpc(STATIC_DPC_CFG *pstStaticDpc);
FH_SINT32 API_ISP_SetDynamicDpc(DYNAMIC_DPC_CFG *pstDynamicDpc);
FH_SINT32 API_ISP_GetDynamicDpc(DYNAMIC_DPC_CFG *pstDynamicDpc);
/** LSC*/
FH_SINT32 API_ISP_SetLscCfg(ISP_LSC_CFG *pstLscCfg);
FH_SINT32 API_ISP_GetLscCfg(ISP_LSC_CFG *pstLscCfg);
/** NR3D*/
FH_SINT32 API_ISP_SetNR3D(ISP_NR3D_CFG *pstNr3dCfg);
FH_SINT32 API_ISP_GetNR3D(ISP_NR3D_CFG *pstNr3dCfg);
/** NR2D*/
FH_SINT32 API_ISP_SetNR2DCfg(ISP_NR2D_CFG *pstNr2dCfg);
FH_SINT32 API_ISP_GetNR2DCfg(ISP_NR2D_CFG *pstNr2dCfg);

/**HLR*/
FH_SINT32 API_ISP_SetHlrCfg(ISP_HLR_CFG *pstHlrCfg);
FH_SINT32 API_ISP_GetHlrCfg(ISP_HLR_CFG *pstHlrCfg);
/**Contrast*/
FH_SINT32 API_ISP_SetContrastCfg(ISP_CONTRAST_CFG *pstContrastCfg);
FH_SINT32 API_ISP_GetContrastCfg(ISP_CONTRAST_CFG *pstContrastCfg);
FH_SINT32 API_ISP_SetBrightnessCfg(ISP_BRIGHTNESS_CFG *pstBrightnessCfg);
FH_SINT32 API_ISP_GetBrightnessCfg(ISP_BRIGHTNESS_CFG *pstBrightnessCfg);
/**CE*/
FH_SINT32 API_ISP_SetSaturation(ISP_SAT_CFG *pstCeCfg);
FH_SINT32 API_ISP_GetSaturation(ISP_SAT_CFG *pstCeCfg);
/**APC*/
FH_SINT32 API_ISP_SetApcCfg(ISP_APC_CFG *pstApcCfg);
FH_SINT32 API_ISP_GetApcCfg(ISP_APC_CFG *pstApcCfg);
/**GAMMA*/
FH_SINT32 API_ISP_SetGammaCfg(ISP_GAMMA_CFG *pstGammaCfg);
FH_SINT32 API_ISP_GetGammaCfg(ISP_GAMMA_CFG *pstGammaCfg);
/**HIST*/
FH_SINT32 API_ISP_GetHist(ISP_HIST_STAT *psthistStat);
/**VPU NR*/
FH_SINT32 API_ISP_SetYnrCfg(ISP_YNR_CFG *pstYnrCfg);
FH_SINT32 API_ISP_GetYnrCfg(ISP_YNR_CFG *pstYnrCfg);
FH_SINT32 API_ISP_SetCnrCfg(ISP_CNR_CFG *pstCnrCfg);
FH_SINT32 API_ISP_GetCnrCfg(ISP_CNR_CFG *pstCnrCfg);

/**PURPLE*/
FH_SINT32 API_ISP_SetAntiPurpleBoundary(ISP_PURPLEFRI_CFG *pstPurplefriCfg);
FH_SINT32 API_ISP_GetAntiPurpleBoundary(ISP_PURPLEFRI_CFG *pstPurplefriCfg);

/**LC*/
FH_SINT32 API_ISP_SetLCCfg(ISP_LC_CFG *pstLCCfg);
FH_SINT32 API_ISP_GetLCCfg(ISP_LC_CFG *pstLCCfg);

/**Debug Interface**/
FH_SINT32 API_ISP_ReadMallocedMem(FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstData);
FH_SINT32 API_ISP_WriteMallocedMem(FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstData);
FH_SINT32 API_ISP_ImportMallocedMem(FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstSrc, FH_UINT32 size);
FH_SINT32 API_ISP_ExportMallocedMem(FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstDst, FH_UINT32 size);

FH_SINT32 API_ISP_MirrorEnable(MIRROR_CFG_S *pMirror);
FH_SINT32 API_ISP_SetMirrorAndflip(FH_BOOL mirror, FH_BOOL flip);
FH_SINT32 API_ISP_SetMirrorAndflipEx(FH_BOOL mirror, FH_BOOL flip,FH_UINT32 bayer);
FH_SINT32 API_ISP_GetMirrorAndflip(FH_BOOL *mirror, FH_BOOL *flip);

FH_SINT32 API_ISP_GetVIState(ISP_VI_STAT_S *pstStat);
FH_SINT32 API_ISP_SetSensorFrameRate(int m);
FH_SINT32 API_ISP_DecendSensorFrameRate(int frameRate);
FH_SINT32 API_ISP_Dump_Param(FH_UINT32 *addr,FH_UINT32 *size);
FH_SINT32 FUNC_DEP API_ISP_GetDebugInfo(ISP_DEBUG_INFO *pstIspDebug);

/**post gain*/
FH_SINT32 API_ISP_SetPostGain(const ISP_POST_GAIN_CFG *pstPostGainCfg);
FH_SINT32 API_ISP_GetPostGain(ISP_POST_GAIN_CFG *pstPostGainCfg);

/**RGBA*/
FH_SINT32 API_ISP_RgbaSendCmd(FH_UINT32 u32Cmd, FH_VOID *param);
FH_SINT32 API_ISP_GetRgbaCfg(RGBA_DEFAULT_CFG *pstRgbaDefaultCfg);
FH_SINT32 API_ISP_SetRgbaLut(RGBA_LUT *pstRgbaLut);
FH_SINT32 API_ISP_GetRgbaInfo(RGBA_CURR_INFO *pstRgbaInfo);
FH_SINT32 API_ISP_GetRgbaStat(RGBA_STAT_INFO *pstRgbaStat);

/**RGBA DPC*/
FH_SINT32 API_ISP_SetRgbaDpc(RGBA_DPC_CFG *pstRgbaDpc);
FH_SINT32 API_ISP_GetRgbaDpc(RGBA_DPC_CFG *pstRgbaDpc);

/**SMART IR**/
FH_SINT32 API_ISP_SetSmartIrCfg(SMART_IR_CFG *pstSmartIrCfg);
FH_SINT32 API_ISP_GetSmartIrCfg(SMART_IR_CFG *pstSmartIrCfg);
/**WDR**/
/**
 * @brief		设置短帧亮度校正曲线的斜率
 *
 * 精度：U.4
 * 范围是6~64倍，转换成.4精度，即（0x60,0x400）
 *
 * @return
 *
 */
FH_SINT32 API_ISP_SetWdrSframeCorrCfg(unsigned int *sframeGain);
FH_SINT32 API_ISP_GetWdrSframeCorrCfg(unsigned int *sframeGain);
/***************************************************************************
 * Function : API_ISP_SetWdrShortFrameMergeCfg
 * Parameters : ISP_WDR_MERGE_CFG* pstWdrMergeCfg
 * Description : 该函数可以配置wdr下短帧的merge曲线，通过配置四对坐标可以配置短帧的merge曲线。
 * Return : FH_RET_OK
****************************************************************************/
FH_SINT32 API_ISP_SetWdrShortFrameMergeCfg(ISP_WDR_MERGE_CFG *pstWdrMergeCfg);
/***************************************************************************
 * Function : API_ISP_SetWdrLongFrameMergeCfg
 * Parameters : ISP_WDR_MERGE_CFG* pstWdrMergeCfg
 * Description : 该函数可以配置wdr下长帧的merge曲线，通过配置四对坐标可以配置长帧的merge曲线。
 * Return : FH_RET_OK
****************************************************************************/
FH_SINT32 API_ISP_SetWdrLongFrameMergeCfg(ISP_WDR_MERGE_CFG *pstWdrMergeCfg);
FH_SINT32 API_ISP_GetWdrCfg(ISP_WDR_CFG *pstWdrCfg);
FH_SINT32 API_ISP_SetWdrCfg(ISP_WDR_CFG *pstWdrCfg);

FH_SINT32 API_ISP_SetCropInfo(int offset_x,int offset_y);

FH_SINT32 API_ISP_RegisterPicStartCallback(ispIntCallback cb);
FH_SINT32 API_ISP_RegisterPicEndCallback(ispIntCallback cb);
FH_SINT32 API_ISP_RegisterIspInitCfgCallback(ispInitCfgCallback cb);
FH_SINT32 API_ISP_SetBlcInitCfg(BLC_INIT_CFG *pstBlcInitCfg);
FH_SINT32 API_ISP_SetWbInitCfg(WB_INIT_CFG *pstWbInitCfg);
FH_SINT32 API_ISP_SetCcmInitCfg(CCM_INIT_CFG *pstCcmInitCfg);
FH_SINT32 API_ISP_SetDpcInitCfg(DPC_INIT_CFG *pstDpcInitCfg);
FH_SINT32 API_ISP_SetApcInitCfg(APC_INIT_CFG *pstApcInitCfg);
FH_SINT32 API_ISP_SetYnrInitCfg(YNR_INIT_CFG *pstYnrInitCfg);
FH_SINT32 API_ISP_SetCtrInitCfg(CTR_INIT_CFG *pstCtrInitCfg);
FH_SINT32 API_ISP_SetSatInitCfg(SAT_INIT_CFG *pstSatInitCfg);
FH_SINT32 API_ISP_SetGammaModeInitCfg(GAMMA_MODE_INIT_CFG *pstGammaModeInitCfg);
FH_SINT32 API_ISP_SetCGammaInitCfg(GAMMA_INIT_CFG *pstCGammaInitCfg);
FH_SINT32 API_ISP_SetYGammaInitCfg(GAMMA_INIT_CFG *pstYGammaInitCfg);
FH_SINT32 API_ISP_SetLtmInitCfg(LTM_INIT_CFG *pstLtmInitCfg);

/**
* FH_ISP_Version
*@brief 按SDK的统一格式定义的版本信息
*@param [in] print_enable:是否打印版本信息
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_CHAR *FH_ISP_Version(FH_UINT32 print_enable);
/**
* FH_ISPCORE_Version
*@brief 按SDK的统一格式定义的版本信息
*@param [in] print_enable:是否打印版本信息
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_CHAR *FH_ISPCORE_Version(FH_UINT32 print_enable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*_ISP_API_H_*/
