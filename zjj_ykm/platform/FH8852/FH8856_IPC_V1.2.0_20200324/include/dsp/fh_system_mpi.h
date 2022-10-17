#ifndef __FH_SYSTEM_MPI_H__
#define __FH_SYSTEM_MPI_H__

#include "types/type_def.h"
#include "fh_common.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
* FH_SYS_Init
*@brief DSP 系统初始化，完成打开驱动设备及分配系统内存
*@param [in] 无
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32  FH_SYS_Init(void);

//把初始化分成2步，方便分段加载
FH_SINT32 FH_SYS_Init_Pre(void);
FH_SINT32 FH_SYS_Init_Post(void);

/**
* FH_SYS_Exit
*@brief DSP 系统退出
*@param [in] 无
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32  FH_SYS_Exit(void);


/**
* FH_SYS_BindVpu2Enc
*@brief 数据源绑定到H264编码通道
*@param [in] srcchn(VPU 通道),取值为0 - 2
*@param [in] dstschn(ENC 通道)，取值为0 - 7
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32  FH_SYS_BindVpu2Enc(FH_UINT32 srcchn,FH_UINT32 dstschn);


/**
* FH_SYS_BindVpu2Bgm
*@brief 数据源绑定到背景建模分析模块
*@param [in] 无
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_SYS_BindVpu2Bgm(void);

/**
* FH_SYS_GetBindbyDest
*@brief 获取H264编码通道的绑定对象
*@param [in] dstschn(ENC 通道)，取值为0 - 7
*@param [out] srcchn(VPU 通道),取值为0 - 2
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_SYS_GetBindbyDest(FH_UINT32 *srcchn,FH_UINT32 dstschn);

/**
* FH_SYS_UnBindbySrc
*@brief 解除数据绑定关系,将解绑到该源的目标
*@param [in] srcchn(VPU 通道),取值为0 - 2
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32  FH_SYS_UnBindbySrc(FH_UINT32 srcchn);

/**
* FH_SYS_UnBindbyDst
*@brief 解除数据绑定关系，将解绑改目标的数据源
*@param [in] dstchn(ENC  通道),取值为0 - 7
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_SYS_UnBindbyDst(FH_UINT32 dstchn);

/**
* FH_SYS_GetVersion
*@brief 获取DSP驱动版本信息
*@param [in] 无
*@param [out] pstSystemversion 版本信息
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32  FH_SYS_GetVersion(FH_VERSION_INFO *pstSystemversion);

/**
* FH_DSP_Version
*@brief 按SDK的统一格式定义的版本信息
*@param [in] print_enable:是否打印版本信息
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_CHAR *FH_DSP_Version(FH_UINT32 print_enable);

/**
* FH_SYS_SetReg
*@brief 设置寄存器值
*@param [in] addr 寄存器物理地址
*@param [in] value 设置寄存器值
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_SYS_SetReg(FH_UINT32 addr, FH_UINT32 value);

/**
* FH_SYS_GetReg
*@brief 获取寄存器的值
*@param [in] u32Addr 寄存器物理地址
*@param [out] pu32Value 寄存器的值
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_SYS_GetReg(FH_UINT32 u32Addr, FH_UINT32 *pu32Value);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__MPI_VO_H__ */

