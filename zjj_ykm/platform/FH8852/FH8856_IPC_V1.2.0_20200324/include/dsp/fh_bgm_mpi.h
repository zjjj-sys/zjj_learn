#ifndef __FH_BGM_MPI_H__
#define __FH_BGM_MPI_H__

#include "types/type_def.h"
#include "fh_common.h"
#include "fh_bgm_mpipara.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
* FH_BGM_InitMem
*@brief bgm内存初始化
*@param [in] Bgmwidth:处理的最大图像宽
*@param [in] Bgmheight:处理的最大图像高
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_BGM_InitMem(FH_UINT32 Bgmwidth,FH_UINT32 Bgmheight);

/**
* FH_BGM_SetConfig
*@brief 设置bgm配置
*@param [in] pstBgmconfig:BGM配置
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_BGM_SetConfig(const FH_SIZE *pstBgmconfig);

/**
* FH_BGM_GetConfig
*@brief 获取bgm配置
*@param [in] 无
*@param [out] pstBgmconfig:BGM配置
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_BGM_GetConfig(FH_SIZE *pstBgmconfig);

/**
* FH_BGM_Enable
*@brief 开启bgm使能
*@param [in] 无
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_BGM_Enable(void);

/**
* FH_BGM_Disable
*@brief 关闭bgm使能
*@param [in] 无
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_BGM_Disable(void);

/**
* FH_BGM_SubmitFrame
*@brief 向BGM提交待分析帧
*@param [in] pstframe　帧信息
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_BGM_SubmitFrame(const FH_BGM_FRAME *pstframe);

/**
* FH_BGM_GetSWStatus
*@brief 获取软件处理结果
*@param [in] 无
*@param [out] pstframe　帧信息
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_BGM_GetSWStatus(FH_BGM_SW_STATUS *pststatus);

FH_SINT32 FH_BGM_GetRunTableRect(FH_BGM_RUNTB_RECT *prunrect);

//显性的重新初始化背景建模,一般情况下用户无需调用.
FH_SINT32 FH_BGM_BkgReinit(void);

FH_SINT32 fh_bgm_setgopth(const FH_GOP_TH *pgopth);
FH_SINT32 fh_bgm_getgopth(FH_GOP_TH *pgopth);

FH_SINT32 FH_BGM_ADV_SetBkgInitCount(FH_UINT32 count);
FH_SINT32 FH_BGM_ADV_SetUpdateSigGauCount(FH_UINT32 count);
FH_SINT32 FH_BGM_ADV_SetBkgInitAttr(const FH_BKG_INIT_CFG *pbkginitcfg);
FH_SINT32 FH_BGM_ADV_GetBkgInitAttr(FH_BKG_INIT_CFG *pbkginitcfg);
FH_SINT32 FH_BGM_ADV_SetSigGauAttr(const FH_SINGLE_GAU_CFG *psiggaucfg);
FH_SINT32 FH_BGM_ADV_GetSigGauAttr(FH_SINGLE_GAU_CFG *psiggaucfg);
FH_SINT32 FH_BGM_ADV_SetMulGauAttr(const FH_MULTI_GAU_CFG *pmulgaucfg);
FH_SINT32 FH_BGM_ADV_GetMulGauAttr(FH_MULTI_GAU_CFG *pmulgaucfg);
FH_SINT32 FH_BGM_ADV_SetDisAttr(const FH_DIS_CFG *pdiscfg);
FH_SINT32 FH_BGM_ADV_GetDisAttr(FH_DIS_CFG *pdiscfg);
FH_SINT32 FH_BGM_ADV_SetConExpaAttr(FH_CON_EXPA_IDX conidx,const FH_CON_EXPA_CFG *pconexpacfg);
FH_SINT32 FH_BGM_ADV_GetConExpaAttr(FH_CON_EXPA_IDX conidx,FH_CON_EXPA_CFG *pconexpacfg);
FH_SINT32 FH_BGM_ADV_SetFrmDiffAttr(const FH_FRM_DIFF_CFG *pfrmdiffcfg);
FH_SINT32 FH_BGM_ADV_GetFrmDiffAttr(FH_FRM_DIFF_CFG *pfrmdiffcfg);
FH_SINT32 FH_BGM_ADV_SetFrmDiffConsistAttr(const FH_FRM_DIFF_CONSIST_CFG *pfrmconsistcfg);
FH_SINT32 FH_BGM_ADV_GetFrmDiffConsistAttr(FH_FRM_DIFF_CONSIST_CFG *pfrmconsistcfg);
FH_SINT32 FH_BGM_ADV_SetGlbBgLumaAttr(const FH_GLOBAL_BG_LUMA_CFG *pbglumacfg);
FH_SINT32 FH_BGM_ADV_GetGlbBgLumaAttr(FH_GLOBAL_BG_LUMA_CFG *pbglumacfg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__MPI_VO_H__ */
