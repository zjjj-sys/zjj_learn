#ifndef __FH_VENC_MPIPARA_NEW_H__
#define __FH_VENC_MPIPARA_NEW_H__

#include "types/type_def.h"
#include "fh_common.h"
#include "fh_bgm_mpi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define MAX_NALU_CNT 20

typedef enum
{
	FH_JPEG        = (1 << 0),
	FH_MJPEG       = (1 << 1),
	FH_NORMAL_H264 = (1 << 2),
	FH_SMART_H264  = (1 << 3),
	FH_NORMAL_H265 = (1 << 4),
	FH_SMART_H265  = (1 << 5),
}FH_VENC_TYPE;

typedef enum
{
	FH_RC_MJPEG_FIXQP = 0,
	FH_RC_MJPEG_CBR   = 1,
	FH_RC_MJPEG_VBR   = 2,
	FH_RC_H264_VBR    = 3,
	FH_RC_H264_CBR    = 4,
	FH_RC_H264_FIXQP  = 5,
	FH_RC_H264_AVBR   = 6,
	FH_RC_H265_VBR    = 7,
	FH_RC_H265_CBR    = 8,
	FH_RC_H265_FIXQP  = 9,
	FH_RC_H265_AVBR   = 10,
}FH_VENC_RC_MODE;

typedef enum
{
	FH_STREAM_JPEG  = (1 << 0),
	FH_STREAM_MJPEG = (1 << 1),
	FH_STREAM_H264  = (1 << 2),
	FH_STREAM_H265  = (1 << 3),

	FH_STREAM_ALL   = 0xffffffff,
}FH_STREAM_TYPE;

typedef enum
{
	H264_PROFILE_BASELINE         = 66,/**< baseline  */
	H264_PROFILE_MAIN             = 77,/**< main profile */
}FH_H264_PROFILE;

typedef enum
{
	H265_PROFILE_MAIN = 1,
}FH_H265_PROFILE;

/*
* !!注意
* 因为H264和H265 对帧类型的定义不是完全一致
* H264:0-P 1-B 2-I
* H265:0-B 1-P 2-I
* 这里我们对两个标准使用统一的定义
* 同时我们加入我们对刷新帧的私有定义
*/
typedef enum {
	FH_FRAME_P              = 0,
	FH_FRAME_B              = 1,
	FH_FRAME_I              = 2,
	FH_FRAME_FRESH_P        = 20,
	FH_FRAME_FRESH_B        = 21,
} FH_ENC_FRAME_TYPE;

typedef enum {
	NALU_P_SLICE            = 0,
	NALU_B_SLICE            = 1,
	NALU_I_SLICE            = 2,
	NALU_IDR                = 5,
	NALU_SEI                = 6,
	NALU_SPS                = 7,
	NALU_PPS                = 8,
	NALU_AUD                = 9,
} FH_ENC_NALU_TYPE;

typedef struct
{
	/*编码类型,可以同时支持多种类型(FH_VENC_TYPE)*/
	FH_UINT32 support_type;
	/*最大编码幅面*/
	FH_SIZE   max_size;
	/*对B帧的支持,为保留字段,暂不支持*/
	FH_UINT32 bframe_num;
}FH_VENC_CHN_CAP;

/*H264 编码属性*/
typedef struct
{
	FH_H264_PROFILE profile;
	FH_UINT32       i_frame_intterval;
	FH_SIZE         size;
}FH_VENC_H264_ATTR;

/*H264 智能编码属性*/
typedef struct
{
	FH_H264_PROFILE profile;
	FH_UINT32       refresh_frame_intterval;
	FH_SIZE         size;

	FH_BOOL         smart_en; //使用智能编码
	FH_BOOL         texture_en; //使用纹理映射结果
	FH_BOOL         backgroudmodel_en; //使用背景建模结果
	FH_BOOL         mbconsist_en; //使用宏块一致性结果，解决一些光线变化的场景，会提升码率
	FH_GOP_TH       gop_th; //设置静止帧门限，决定GOP长度
}FH_VENC_S264_ATTR;

/*H265 编码属性*/
typedef struct
{
	FH_H265_PROFILE profile;
	FH_UINT32       i_frame_intterval;
	FH_SIZE         size;
}FH_VENC_H265_ATTR;

/*H265 智能编码属性*/
typedef struct
{
	FH_H265_PROFILE profile;
	FH_UINT32       refresh_frame_intterval;
	FH_SIZE         size;

	FH_BOOL         smart_en; //使用智能编码
	FH_BOOL         texture_en; //使用纹理映射结果
	FH_BOOL         backgroudmodel_en; //使用背景建模结果
	FH_BOOL         mbconsist_en; //使用宏块一致性结果，解决一些光线变化的场景，会提升码率
	FH_GOP_TH       gop_th; //设置静止帧门限，决定GOP长度
}FH_VENC_S265_ATTR;

/*JPEG 编码属性*/
typedef struct
{
	FH_UINT32 qp;
	FH_UINT32 rotate;
	FH_UINT32 encode_speed;
}FH_VENC_JPEG_ATTR;

/*MJPEG 编码属性*/
typedef struct
{
	FH_SIZE   pic_size;
	FH_UINT32 rotate;
	FH_UINT32 encode_speed;
}FH_VENC_MJPEG_ATTR;

typedef struct
{
	FH_VENC_TYPE enc_type;
	union
	{
		FH_VENC_H264_ATTR  h264_attr;
		FH_VENC_S264_ATTR  s264_attr;
		FH_VENC_H265_ATTR  h265_attr;
		FH_VENC_S265_ATTR  s265_attr;
		FH_VENC_JPEG_ATTR  jpeg_attr;
		FH_VENC_MJPEG_ATTR mjpeg_attr;
	};
}FH_VENC_CHN_ATTR;

/*RC相关配置*/
typedef struct
{
	// 输入帧率，作为参考帧率
	FH_FRAMERATE src_frmrate;

	// 是否进行用户自定义丢帧
	FH_UINT32    usrdrop_enable;
	// 输出帧率，输出帧率大于等于设定输入帧率，输出帧率为输入帧率
	FH_FRAMERATE dst_frmrate;

	// 是否允许QP门限触发丢帧
	FH_UINT32    qpdrop_enable;
	// QP门限触发丢帧,QP的门限值,H264/H265范围为0-51,MJPEG为0-98
	FH_UINT32    qpdrop_qpth;
	// QP门限触发丢帧,丢帧后不低于该帧率
	FH_FRAMERATE qpdrop_minfrmrate;

	// 是否允许瞬时码率触发丢帧
	FH_UINT32    InstantRate_enable;
	// 触发瞬时码率丢帧的码率门限,为目标码率的百分比:110-1000
	FH_UINT32    InstantRate_percentth;
	// 瞬时码率的丢帧间隔，丢帧后不低于该帧率
	FH_FRAMERATE InstantRate_minfrmrate;
}FH_DROP_FRAME;

typedef struct
{
	FH_UINT32    iqp;
	FH_UINT32    pqp;
	FH_FRAMERATE FrameRate;
}FH_H264_FIXQP_ATTR;

typedef struct
{
	FH_UINT32    init_qp;
	FH_UINT32    bitrate;
	FH_FRAMERATE FrameRate;
	FH_UINT32    maxrate_percent;
	FH_UINT32    IFrmMaxBits;
	FH_SINT32    IP_QPDelta;
	FH_SINT32    I_BitProp;
	FH_SINT32    P_BitProp;
	FH_SINT32    fluctuate_level;
}FH_H264_CBR_ATTR;

typedef struct
{
	FH_UINT32    init_qp;
	FH_UINT32    bitrate;
	FH_UINT32    IminQP;
	FH_UINT32    ImaxQP;
	FH_UINT32    PminQP;
	FH_UINT32    PmaxQP;
	FH_FRAMERATE FrameRate;
	FH_UINT32    maxrate_percent;
	FH_UINT32    IFrmMaxBits;
	FH_SINT32    IP_QPDelta;
	FH_SINT32    I_BitProp;
	FH_SINT32    P_BitProp;
	FH_SINT32    fluctuate_level;
}FH_H264_VBR_ATTR;

typedef struct
{
	FH_UINT32    init_qp;
	FH_UINT32    bitrate;
	FH_UINT32    IminQP;
	FH_UINT32    ImaxQP;
	FH_UINT32    PminQP;
	FH_UINT32    PmaxQP;
	FH_FRAMERATE FrameRate;
	FH_UINT32    maxrate_percent;
	FH_UINT32    IFrmMaxBits;
	FH_SINT32    IP_QPDelta;
	FH_SINT32    I_BitProp;
	FH_SINT32    P_BitProp;
	FH_SINT32    fluctuate_level;
	FH_UINT32    stillrate_percent;
	FH_UINT32    maxstillqp;
}FH_H264_AVBR_ATTR;

typedef struct
{
	FH_UINT32    iqp;
	FH_UINT32    qp;
	FH_FRAMERATE FrameRate;
}FH_H265_FIXQP_ATTR;

typedef struct
{
	FH_UINT32    init_qp;
	FH_UINT32    bitrate;
	FH_FRAMERATE FrameRate;
	FH_UINT32    maxrate_percent;
	FH_UINT32    IFrmMaxBits;
	FH_SINT32    IP_QPDelta;
	FH_SINT32    I_BitProp;
	FH_SINT32    P_BitProp;
	FH_SINT32    fluctuate_level;
}FH_H265_CBR_ATTR;

typedef struct
{
	FH_UINT32    init_qp;
	FH_UINT32    bitrate;
	FH_UINT32    IminQP;
	FH_UINT32    ImaxQP;
	FH_UINT32    PminQP;
	FH_UINT32    PmaxQP;
	FH_FRAMERATE FrameRate;
	FH_UINT32    maxrate_percent;
	FH_UINT32    IFrmMaxBits;
	FH_SINT32    IP_QPDelta;
	FH_SINT32    I_BitProp;
	FH_SINT32    P_BitProp;
	FH_SINT32    fluctuate_level;
}FH_H265_VBR_ATTR;

typedef struct
{
	FH_UINT32    init_qp;
	FH_UINT32    bitrate;
	FH_UINT32    IminQP;
	FH_UINT32    ImaxQP;
	FH_UINT32    PminQP;
	FH_UINT32    PmaxQP;
	FH_FRAMERATE FrameRate;
	FH_UINT32    maxrate_percent;
	FH_UINT32    IFrmMaxBits;
	FH_SINT32    IP_QPDelta;
	FH_SINT32    I_BitProp;
	FH_SINT32    P_BitProp;
	FH_SINT32    fluctuate_level;
	FH_UINT32    stillrate_percent;
	FH_UINT32    maxstillqp;
}FH_H265_AVBR_ATTR;

typedef struct
{
	FH_UINT32    qp;
	FH_FRAMERATE FrameRate;
}FH_MJPEG_FIXQP_ATTR;

typedef struct
{
	FH_UINT32    initqp;
	FH_UINT32    bitrate;
	FH_FRAMERATE FrameRate;
}FH_MJPEG_CBR_ATTR;

typedef struct
{
	FH_UINT32    initqp;
	FH_UINT32    bitrate;
	FH_UINT32    minqp;
	FH_UINT32    maxqp;
	FH_FRAMERATE FrameRate;
}FH_MJPEG_VBR_ATTR;

typedef struct
{
	FH_VENC_RC_MODE rc_type;
	union
	{
		FH_H264_FIXQP_ATTR  h264_fixqp;
		FH_H264_CBR_ATTR    h264_cbr;
		FH_H264_VBR_ATTR    h264_vbr;
		FH_H264_AVBR_ATTR   h264_avbr;

		FH_H265_FIXQP_ATTR  h265_fixqp;
		FH_H265_CBR_ATTR    h265_cbr;
		FH_H265_VBR_ATTR    h265_vbr;
		FH_H265_AVBR_ATTR   h265_avbr;

		FH_MJPEG_FIXQP_ATTR mjpeg_fixqp;
		FH_MJPEG_CBR_ATTR   mjpeg_cbr;
		FH_MJPEG_VBR_ATTR   mjpeg_vbr;
	};
}FH_VENC_RC_ATTR;

typedef struct
{
	FH_VENC_CHN_ATTR chn_attr;
	FH_VENC_RC_ATTR  rc_attr;
}FH_VENC_CHN_CONFIG;

typedef struct
{
	FH_ADDR                 lumma_addr;
	FH_ADDR                 chroma_addr;
	FH_UINT64               time_stamp;
	FH_SIZE                 size;
}FH_ENC_FRAME;

typedef struct
{
	FH_ENC_NALU_TYPE        type;
	FH_UINT32               length;
	FH_ADDR                 start;
}FH_ENC_STREAM_NALU;

typedef struct
{
	FH_UINT32               chan;
	FH_ADDR                 start;
	FH_ENC_FRAME_TYPE       frame_type;
	FH_UINT32               length;
	FH_UINT64               time_stamp;
	FH_UINT32               nalu_cnt;
	FH_ENC_STREAM_NALU      nalu[MAX_NALU_CNT];
}FH_H264_STREAM;

typedef struct
{
	FH_UINT32               chan;
	FH_ADDR                 start;
	FH_ENC_FRAME_TYPE       frame_type;
	FH_UINT32               length;
	FH_UINT64               time_stamp;
	FH_UINT32               nalu_cnt;
	FH_ENC_STREAM_NALU      nalu[MAX_NALU_CNT];
}FH_H265_STREAM;

typedef struct
{
	FH_UINT32               chan;
	FH_ADDR                 start;
	FH_UINT32               length;
	FH_UINT64               time_stamp;
	FH_UINT32               qp;
}FH_JPEG_STREAM;

typedef struct
{
	FH_STREAM_TYPE stmtype;
	union
	{
		FH_H264_STREAM h264_stream;
		FH_H265_STREAM h265_stream;
		FH_JPEG_STREAM jpeg_stream;
		FH_JPEG_STREAM mjpeg_stream;
	};
}FH_VENC_STREAM;

typedef struct
{
	FH_UINT32               lastqp;
	FH_UINT32               lastiqp;
	FH_UINT32               bps;
	FH_UINT32               FrameToEnc; //待编码帧数
	FH_UINT32               framecnt;   //已编码帧数
	FH_UINT32               streamcnt;  //输出队列中的帧数
	FH_UINT32               lostcnt;    //通道的累计丢帧数
	FH_UINT32               stat[5];    //保留变量
}FH_CHN_STATUS;

typedef struct
{
 	FH_UINT32               enable;
	FH_SINT32               qp;
	FH_AREA                 area;
	FH_UINT32               level;
	FH_BOOL                 isdeltaqp;
}FH_ROI;

typedef struct
{
	FH_UINT32               bitrate;
	FH_UINT32               IminQP;
	FH_UINT32               ImaxQP;
	FH_UINT32               PminQP;
	FH_UINT32               PmaxQP;
	FH_FRAMERATE            FrameRate;
}FH_VENC_RC_CHANGEPARAM;

typedef struct
{
	FH_UINT32             mode;   /*0:不支持抽帧 1:单层跳帧 2:双层跳帧*/
	FH_SINT32             svc_m;  /*第一层跳帧的数量，mode=1 or 2有效*/
	FH_SINT32             svc_n;  /*第二层跳帧的数量，mode=2 有效*/
}FH_VENC_REF_MODE;
/*****************编码器的参数调试*********************/
typedef enum
{
	ENCPARAM_CMD_NONE                = 0,
	ENCPARAM_CMD_H264_LINE_RC        = 1,/*only for h264*/
	ENCPARAM_CMD_LINE_RC             = 1,/*for h264&h265*/
	ENCPARAM_CMD_H264_SEARCH_RANGE   = 2,/*only for h264*/
	ENCPARAM_CMD_H264_CHROMAQP_DELTA = 3,/*only for h264*/
	ENCPARAM_CMD_H264_ENCODE_STYLE   = 4,/*only for h264*/
	ENCPARAM_CMD_TEXTUREQP_RANGE     = 5,/*for h264&h265*/
	ENCPARAM_CMD_RC_ADV_PARAM        = 6,/*for h264&h265*/
}FH_ENCPARAM_CMD;

typedef struct
{
	FH_UINT32 linerc_en;/*行级码控使能,[0|1]*/
	FH_UINT32 linerc_iadd;/*行级码控I帧QP增加范围,0-51*/
	FH_UINT32 linerc_iminus;/*行级码控I帧QP减少范围,0-51*/
	FH_UINT32 linerc_padd;/*行级码控P帧QP增加范围,0-51*/
	FH_UINT32 linerc_pminus;/*行级码控P帧QP减少范围,0-51*/
}ENCPARAM_H264_LINE_RC;

typedef ENCPARAM_H264_LINE_RC ENCPARAM_LINE_RC;

typedef struct
{
	FH_UINT32 search_x;/*编码搜索范围x,0~3,范围为(-(i+1)*16,(i+1)*16-1).增大搜索范围会导致编码性能下降，默认0*/
	FH_UINT32 search_y;/*编码搜索范围y,0~3,范围为(-(i+1)*16,(i+1)*16-1).增大搜索范围会导致编码性能下降，默认0*/
}ENCPARAM_H264_SEARCH_RANGE;

typedef struct
{
	FH_SINT32 ChromaQPdelta;/*色度QP相对与亮度QP的delta,-12~12*/
}ENCPARAM_H264_CHROMAQP_DELTA_ST;

typedef enum
{
	ENCODE_STYLE_NORMAL = 0,
	ENCODE_STYLE_NIGHT  = 1,
}ENCPARAM_H264_ENCODE_STYLE;

typedef struct
{
	FH_UINT32 text_minqp_minus;/*纹理映射的最小QP在原先RC的最小QP上减少的值,0-51*/
	FH_UINT32 text_maxqp_add;/*纹理映射的最大QP在原先RC的最大QP上的增加的值,0-51*/
}ENCPARAM_TEXTUREQP_RANGE_ST;

typedef struct
{
	FH_SINT32 iqp_weight_tbit;/*I帧QP分配,目标码率的影响权重*/
	FH_SINT32 iqp_weight_pqp;/*I帧QP分配,之前GOP PQP的影响权重*/
	FH_SINT32 pqp_limit;/*gop pqp在I帧QP上允许下降的幅度*/
	FH_UINT32 vbuf_depth;/*码控虚拟缓存深度,含义为平均每帧码率的倍数*/
}ENCPARAM_RC_ADV_PARAM;
/******************H264 专有结构体*********************/
typedef struct
{
	FH_UINT32             entropy_coding_mode; /*0:cavlc 1:cabac baseline不支持cabac*/
	FH_UINT32             cabac_init_idc;      /*0~2*/
}FH_H264_ENTROPY;

typedef struct
{
	FH_UINT32             deblocking_filter;  /*0~1*/
	FH_UINT32             disable_deblocking; /*0~2*/
	FH_SINT32             slice_alpha;        /*-6~+6*/
	FH_SINT32             slice_beta;         /*-6~+6*/
}FH_H264_DBLK;

typedef struct
{
 	FH_UINT32             enable;
 	FH_UINT32             slicesplit; /*每个Slice的宏块行数*/
}FH_H264_SLICE_SPLIT;

typedef struct
{
	FH_UINT32             enable;
	FH_UINT32             fresh_line;
	FH_UINT32             fresh_step;
}FH_H264_INTRA_FRESH;
/******************H265 专有结构体*********************/
typedef struct
{
	FH_UINT32             disable_flag;      /*0~1*/
	FH_SINT32             beta_offset_div2;  /*-6~+6*/
	FH_SINT32             tc_offset_div2;    /*-6~+6*/
}FH_H265_DBLK;

typedef struct
{
 	FH_UINT32             mode;/*0:no multslice 1:slice in line 2:slice in number of byte*/
 	FH_UINT32             slice_arg; /*line number(64-aligned)(mode=1);Byte (mode=2)*/
}FH_H265_SLICE_SPLIT;

typedef struct
{
	FH_UINT32             mode;
	FH_UINT32             fresh_line;
}FH_H265_INTRA_FRESH;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
