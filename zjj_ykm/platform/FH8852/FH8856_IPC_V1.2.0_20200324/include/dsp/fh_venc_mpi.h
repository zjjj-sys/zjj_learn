

#ifndef __FH_VENC_MPI_H__
#define __FH_VENC_MPI_H__

#include "fh_venc_mpipara.h"
#include "fh_vpu_mpipara.h"
#include "types/type_def.h"
#include "fh_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
* FH_VENC_SysInitMem
*@brief VENC系统内存初始化，供内部调用，用户不需要显性调用
*@param [in] 无
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_SysInitMem();


/**
* FH_VENC_CreateChn
*@brief 创建编码通道，指定通道支持的最大编码幅面，和编码格式。
*@param [in] chan 通道号，取值0-7
*@param [out] stVencChnAttr 通道参数指针
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_CreateChn(FH_UINT32 chan,const FH_VENC_CHN_CAP *stVencChnAttr);

/**
* FH_VENC_StartRecvPic
*@brief 开始接收图片输入进行编码。
*@param [in] chan 通道号，取值0-7
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*@note JPEG通道不支持
*/
FH_SINT32 FH_VENC_StartRecvPic(FH_UINT32 chan);

/**
* FH_VENC_StopRecvPic
*@brief 停止编码。
*@param [in] chan 通道号，取值0-7
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*@note JPEG通道不支持
*/
FH_SINT32 FH_VENC_StopRecvPic(FH_UINT32 chan);

/**
* FH_VENC_Submit_ENC
*@brief VENC没有和VPU进行通道绑定，使用用户提供图片进行编码。
*@param [in] chan 通道号，取值0-7
*@param [in] pstVencsubmitframe 用户提供的图片信息指针
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_Submit_ENC(FH_UINT32 chan,const FH_ENC_FRAME *pstVencsubmitframe);

/*
* FH_VENC_Submit_ENC_Ex
* @brief 向编码通道提交图像数据进行编码,调用此接口时通道不能处于绑定状态
* @param [in] chan,通道号
* @param [in] pstVencsubmitframe,图像数据信息
* @param [in] datamode,图像数据格式
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_Submit_ENC_Ex(FH_UINT32 chan,const FH_ENC_FRAME *pstVencsubmitframe,FH_VPU_VO_MODE datamode);

/**
* FH_VENC_GetChnStatus
*@brief 查询编码器通道状态信息。
*@param [in] chan 通道号，取值0-7
*@param [out] pstVencstatus 编码通道状态信息指针。
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*@note JPEG/MJPEG通道不支持
*/
FH_SINT32 FH_VENC_GetChnStatus(FH_UINT32 chan, FH_CHN_STATUS *pstVencStatus);

/**
* FH_VENC_GetStream
*@brief 获取编码通道码流。非阻塞
*@param [in] request_type 需要获取的码流类型(FH_STREAM_TYPE),可以通过或传入多种类型
*@param [out] pstVencstreamAttr 编码通道码流信息指针。
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*@note
* 该接口不同的码流类型可以被并发调用，但同一码流类型不能被并发获取
*/
FH_SINT32 FH_VENC_GetStream (FH_UINT32 request_type,FH_VENC_STREAM *pstVencstreamAttr);

/**
* FH_VENC_GetStream_Block
*@brief 获取编码通道码流。阻塞模式
*@param [in] request_type 需要获取的码流类型(FH_STREAM_TYPE),可以通过或传入多种类型
*@param [out] pstVencstreamAttr 编码通道码流信息指针。
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*@note
* 该接口不同的码流类型可以被并发调用，但同一码流类型不能被并发获取
*/
FH_SINT32 FH_VENC_GetStream_Block(FH_UINT32 request_type,FH_VENC_STREAM *pstVencstreamAttr);

/**
* FH_VENC_ReleaseStream
*@brief 释放码流缓存。
*@param [in] chan 通道号，取值0-7
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_ReleaseStream(FH_UINT32 chan);

/**
* FH_VENC_SetChnAttr
*@brief 设置编码通道属性。通道创建之后可以通过此接口改变通道属性。
*@param [in] chan 通道号，取值0-7
*@param [in] pstVencChnAttr 编码通道参数指针
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*@note
* 在调用设置通道属性时,所有绑定关系都会被解除，码控和用户设置的编码参数等通道参数都会被重置为默认值
*/
FH_SINT32 FH_VENC_SetChnAttr(FH_UINT32 chan,const FH_VENC_CHN_CONFIG *pstVencChnAttr);

/**
* FH_VENC_GetChnAttr
*@brief 获取编码通道的编码属性。
*@param [in] chan 通道号，取值0-7
*@param [out] pstVencChnAttr 编码通道参数指针
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_GetChnAttr(FH_UINT32 chan, FH_VENC_CHN_CONFIG *pstVencChnAttr);

/**
* FH_VENC_SetRotate
*@brief 设置图像旋转。
*@param [in] chan 通道号，取值0-7
*@param [in] pstVencrotateinfo 旋转信息指针
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_SetRotate(FH_UINT32 chan, FH_ROTATE_OPS pstVencrotateinfo);

/**
* FH_VENC_GetRotate
*@brief 设置图像旋转。
*@param [in] chan 通道号，取值0-7
*@param [out] pstVencrotateinfo 旋转信息指针
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_GetRotate(FH_UINT32 chan, FH_ROTATE_OPS *pstVencrotateinfo);

/**
* FH_VENC_SetRoiCfg
*@brief 设置图像旋转。
*@param [in] chan 通道号，取值0-7
*@param [in] pstVencroiinfo ROI信息指针
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_SetRoiCfg(FH_UINT32 chan,const FH_ROI *pstVencroiinfo);

/**
* FH_VENC_ClearRoi
*@brief 清除编码通道的ROI信息，在第一次设置通道ROI或需要清除旧的设置时调用
*@param [in] chan 通道号，取值0-7
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_ClearRoi(FH_UINT32 chan);

/**
* FH_VENC_RequestIDR
*@brief 请求强制I 帧。
*@param [in] chan 通道号，取值0-7
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_RequestIDR(FH_UINT32 chan);


/**
* 获取当前的系统PTS值
*@brief 设置PTS的时间，供内部调用，用户无需显性调用
*@param [in] 无
*@param [out] Systemcurpts：当前的PTS值
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_GetCurPts(FH_UINT64 *Systemcurpts);

/**
* FH_VENC_SetRCAttr
*@brief 设置码控参数
*@param [in] chan 通道号，取值0-7
*@param [in] pstVencrcattr 码控参数
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_SetRCAttr(FH_UINT32 chan,const FH_VENC_RC_ATTR *pstVencrcattr);

/**
* FH_VENC_GetRCAttr
*@brief 获取码控参数
*@param [in] chan 通道号，取值0-7
*@param [out] pstVencrcattr 码控参数
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_GetRCAttr(FH_UINT32 chan,FH_VENC_RC_ATTR *pstVencrcattr);

/**
* 实时调整码控参数
*@brief 通过该API可以实时调整部分码控参数,不会强制I帧和重新初始化码控,
*       用于一些更加平滑的码率调整运用。
*@param [in] chan,rcparam
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*@note 使用该接口设置码率等参数时，需要注意码率变化的步进和趋势。
*      类似频繁突变的切换码率可能会导致码控无法准确控制。
*/
FH_SINT32 FH_VENC_SetRcChangeParam(FH_UINT32 chan,const FH_VENC_RC_CHANGEPARAM *rcparam);


/**
* FH_VENC_SetLostFrameAttr
*@brief 设置丢帧策略参数
*@param [in] chan 通道号，取值0-7
*@param [in] pstVencdropattr 丢帧参数
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_SetLostFrameAttr(FH_UINT32 chan,const FH_DROP_FRAME *pstVencdropattr);

/**
* FH_VENC_GetLostFrameAttr
*@brief 获取丢帧策略参数
*@param [in] chan 通道号，取值0-7
*@param [out] pstVencdropattr 丢帧参数
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_GetLostFrameAttr(FH_UINT32 chan,FH_DROP_FRAME *pstVencdropattr);
/**********************编码器的参数调试API*****************************/

/**
* 设置背景QP
*@brief 设置背景QP,在智能模式下生效.背景QP与正常QP之间的差值和背景QP的最大值,
＊　　　　当码控QP大于背景QP时，在QP分配上将退化为和普通编码一致;
*@param [in] chan,bkg_delta_qp,bkg_max_qp
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_SetBkgQP(FH_UINT32 chan,FH_UINT32 bkg_delta_qp,FH_UINT32 bkg_max_qp);

/**
* 获取背景QP
*@brief 获取背景QP,获取当前背景QP
*@param [in] chan
*@param [out] bkg_qp
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_GetBkgQP(FH_UINT32 chan,FH_UINT32 *bkg_delta_qp,FH_UINT32 *bkg_max_qp);

/* 编码器参数设置
*@brief 以命令号+参数方式定义一些调试参数
*@param [in] chan
*@param [in] cmd
*@param [in] param
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*@note
* 主要定义一些非常用的功能或者调试参数,目的是为了减少API的数量。
* 对于正常的流程调度或者效果可以不需要调用该API。
*/
FH_SINT32 FH_VENC_SetEncParam(FH_UINT32 chan,FH_ENCPARAM_CMD cmd,void *param);
FH_SINT32 FH_VENC_GetEncParam(FH_UINT32 chan,FH_ENCPARAM_CMD cmd,void *param);

/* 设置加密种子
*@brief 作为生成加密秘钥的信息
*@param [in] hash_seed0
*@param [in] hash_seed1
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*@note
* 部分SDK可能不支持该功能，仅增加一段加密信息在码流中，对码流本身并不产生影响。
* 大部分用户不会使用该功能，如有需要用到该功能的支持人员会告知。
*/
FH_SINT32 FH_VENC_SetEncryptSeed(FH_UINT32 hash_seed0,FH_UINT32 hash_seed1);

/* 设置编码跳帧参考
*@brief 设置编码跳帧参考
*@param [in] chan
*@param [in] pVencrefmode
*@return 是否成功
* - RETURN_OK(0): 成功
* - 其他：失败,错误详见错误号
*/
FH_SINT32 FH_VENC_SetEncRefMode(FH_UINT32 chan,const FH_VENC_REF_MODE *pVencrefmode);
FH_SINT32 FH_VENC_GetEncRefMode(FH_UINT32 chan, FH_VENC_REF_MODE *pVencrefmode);
/**********************H264 专有接口*****************************/
FH_SINT32 FH_VENC_SetH264Entropy(FH_UINT32 chan,const FH_H264_ENTROPY *pstVencentropy);
FH_SINT32 FH_VENC_GetH264Entropy(FH_UINT32 chan,FH_H264_ENTROPY *pstVencentropy);
FH_SINT32 FH_VENC_SetH264Dblk(FH_UINT32 chan,const FH_H264_DBLK *pstVencdblk);
FH_SINT32 FH_VENC_GetH264Dblk(FH_UINT32 chan,FH_H264_DBLK *pstVencdblk);
FH_SINT32 FH_VENC_SetH264SliceSplit(FH_UINT32 chan,const FH_H264_SLICE_SPLIT *pstVencslicesplit);
FH_SINT32 FH_VENC_GetH264SliceSplit(FH_UINT32 chan,FH_H264_SLICE_SPLIT *pstVencslicesplit);
FH_SINT32 FH_VENC_SetH264IntraFresh(FH_UINT32 chan,const FH_H264_INTRA_FRESH *pstVencintrafresh);
FH_SINT32 FH_VENC_GetH264IntraFresh(FH_UINT32 chan, FH_H264_INTRA_FRESH *pstVencintrafresh);

/**********************H265 专有接口*****************************/
FH_SINT32 FH_VENC_SetH265Dblk(FH_UINT32 chan,const FH_H265_DBLK *pstVencdblk);
FH_SINT32 FH_VENC_GetH265Dblk(FH_UINT32 chan,FH_H265_DBLK *pstVencdblk);
FH_SINT32 FH_VENC_SetH265SliceSplit(FH_UINT32 chan,const FH_H265_SLICE_SPLIT *pstVencslicesplit);
FH_SINT32 FH_VENC_GetH265SliceSplit(FH_UINT32 chan,FH_H265_SLICE_SPLIT *pstVencslicesplit);
FH_SINT32 FH_VENC_SetH265IntraFresh(FH_UINT32 chan,const FH_H265_INTRA_FRESH *pstVencintrafresh);
FH_SINT32 FH_VENC_GetH265IntraFresh(FH_UINT32 chan, FH_H265_INTRA_FRESH *pstVencintrafresh);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__MPI_VO_H__ */



