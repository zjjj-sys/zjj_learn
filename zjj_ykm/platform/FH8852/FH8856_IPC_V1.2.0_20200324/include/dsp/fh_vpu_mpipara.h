#ifndef __FH_VPU_MPIPARA_H__
#define __FH_VPU_MPIPARA_H__

#include "types/type_def.h"
#include "fh_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

typedef enum
{
	VPU_MODE_ISP            = 0, /**< 从ISP输入模式*/
	VPU_MODE_MEM            = 1, /**< 从MEM输入模式*/
}FH_VPU_VI_MODE;

///VPU 输出模式
typedef enum
{
	VPU_VOMODE_BLK          = 0, /**<宏块格式，编码使用*/
	VPU_VOMODE_SCAN         = 1, /**<光栅格式，用户分析*/
}FH_VPU_VO_MODE;

///YUV格式
typedef enum
{
	PIXEL_FORMAT_NOCHROME   = 0, /**<单色*/
	PIXEL_FORMAT_420        = 1, /**<420*/
	PIXEL_FORMAT_422        = 2, /**<422*/
	PIXEL_FORMAT_444        = 3  /**<444*/
}FH_VPU_PIXELFORMAT;

typedef struct
{
	FH_SIZE                 vi_size;
}FH_VPU_SIZE;

typedef struct
{
	FH_SIZE                 vpu_chn_size;
}FH_VPU_CHN_CONFIG;

typedef struct
{
	FH_SIZE                 pic_size; /**< 图片尺寸 */
	FH_ADDR                 yluma;    /**< 图片的luma地址 */
	FH_ADDR                 chroma;   /**< 图片的chroma地址 */
	FH_UINT32               ystride;  /**< 图片的luma stride */
	FH_UINT32               cstride;  /**< 图片的chroma stride */
}FH_VPU_USER_PIC;

typedef struct
{
	FH_VPU_PIXELFORMAT      pixelFormat;/**< 像素格式 */
	FH_UINT32               stride;     /**< 图像跨度 */
	FH_SIZE                 size;       /**< 图像尺寸 */
	FH_MEM_INFO             yluma;      /**< luma地址*/
	FH_MEM_INFO             chroma;     /**< chroma 地址*/
	FH_UINT64               time_stamp; /**< 时间戳*/
}FH_VPU_STREAM;

typedef struct
{
	FH_SIZE                 pic;
	FH_MEM_INFO             data;
	FH_UINT32               stride;
	FH_UINT64               time_stamp;
}FH_PIC_DATA;

typedef struct
{
	FH_UINT32              masaic_enable; /**<使能，1显示 0 不显示 */
	FH_UINT32              masaic_size;   /**<尺寸0: 16x16，1: 32x32 */
}FH_MASK_MASAIC;

typedef struct
{
	FH_BOOL                 mask_enable[MAX_MASK_AREA]; /**< 覆盖使能 */
	FH_AREA                 area_value[MAX_MASK_AREA];  /**< 屏蔽区域 */
	FH_UINT32               color;                      /**< 显示颜色 */
	FH_MASK_MASAIC          masaic;                     /**< 马赛克属性 */
}FH_VPU_MASK;

typedef struct
{
	FH_UINT32               alpha_value;/**<透明度 */
	FH_UINT32               dtvmode;    /**<0为SDTV模式，1为HDTV模式*/
	FH_UINT32               rgbmode;    /**<0为stdio RGB，1为computer RGB*/
	FH_SIZE                 logo_size;  /**<logo大小 */
}FH_LOGO_CFG;

typedef struct
{
	FH_UINT32               logo_enable;   /**< 图片叠加使能 */
	FH_UINT8               *logo_addr;     /**< logo数据的物理地址 */
	FH_LOGO_CFG             logo_cfg;      /**< logo 配置 */
	FH_POINT                logo_startpos; /**< logo 左上角起始点 */
	FH_POINT                logo_cutpos;   /**<logo切割显示起始点 */
	FH_UINT32               stride_value;  /**<行长度 */
}FH_VPU_LOGO;

typedef struct
{
	FH_UINT32               magic_color_en; /*使用magic_color*/
	FH_UINT32               magic_color;    /*magic_color,16bit,出现此颜色设为透明*/
	FH_UINT32               global_alpha_en;/*全局透明度使能*/
	FH_UINT32               global_alpha;   /*全局透明度*/
	FH_UINT32               rgb16_type;     /*位宽16模式:1:ARGB0565,2:ARGB1555,3:ARGB4444*/
	FH_UINT32               extmode;        /*0为LSB填0，1为MSB复制到LSB*/
	FH_UINT32               dtvmode;        /**<0为SDTV模式，1为HDTV模式*/
	FH_UINT32               rgbmode;        /**<0为stdio RGB，1为computer RGB*/
	FH_SIZE                 logo_size;      /**<logo大小 */
}FH_LOGOV2_CFG;

typedef struct
{
	FH_UINT32               logo_enable;   /**< 图片叠加使能 */
	FH_UINT32               logo_idx;      /**< 图片叠加使能 */
	FH_UINT32               logo_pixdepth; /**< 图片像素位宽，此芯片只支持1,2,4 */
	FH_UINT8               *logo_addr;     /**< logo数据的物理地址 */
	FH_LOGOV2_CFG           logo_cfg;      /**< logo 配置 */
	FH_POINT                logo_startpos; /**< logo 左上角起始点 */
	FH_UINT32               stride_value;  /**< 行长度 */
	FH_UINT32               color[256];    /**< 颜色索引库,ARGB8888 */
}FH_VPU_LOGOV2;

typedef struct
{
	FH_UINT32               Vamp;/*水平放大一倍*/
	FH_UINT32               Hamp;/*垂直放大一倍*/
	FH_UINT32               txtrotate;/*整个字符旋转*/
	FH_UINT32               txtw;/*字符宽度*/
	FH_UINT32               txth;/*字符高度*/
	FH_UINT32               fontsize;/*字体占的内存大小*/
	FH_UINT32               fontw;/*OSD宽度*/
	FH_UINT32               fonth;/*OSD高度*/
}FH_OSD_CFG;

typedef struct
{
	FH_UINT32               norcolor;/*正常的字符颜色*/
	FH_UINT32               invcolor;/*反色的字符颜色*/
}FH_OSD_COLOR;

typedef struct
{
	FH_UINT32               charcolor;
	FH_UINT32               edgecolor;
	FH_UINT32               bkgcolor;
}FH_OSD_HLCOLOR;

typedef struct
{
	FH_UINT32               invert_enable;
	FH_UINT32               text_idex;
	FH_UINT32               invert_word[MAX_INVERT_CNT];
}FH_INVERT_CTRL;

typedef struct
{
	FH_UINT32               hl_enable;
	FH_OSD_HLCOLOR          hl_color;
	FH_AREA                 hl_area;
}FH_HIGHLIGHT_WINDOW;

typedef struct
{
	FH_UINT32               text_idex;
	FH_UINT32               edge_enable;
	FH_UINT32               hlext_enable;
	FH_OSD_HLCOLOR          nonhl_color;
	FH_HIGHLIGHT_WINDOW     hl_window0;
	FH_HIGHLIGHT_WINDOW     hl_window1;
}FH_HIGHLIGHT_CTRL;

typedef struct
{
	FH_UINT32               idex;
	FH_UINT32               osd_enable;

	FH_UINT8               *osdtxtaddr;  /*字符的起始地址*/
	FH_UINT8               *osdfontaddr; /*字符库的地址*/
	FH_INVERT_CTRL          invert_ctl;  /*字符颜色反色控制*/
	FH_OSD_CFG              osd_cfg;     /**< 配置 */
	FH_OSD_COLOR            osd_color;   /**< 字符颜色 */
	FH_OSD_COLOR            osd_blgcolor;/**< 背景颜色 */
	FH_POINT                osd_startpos;/**< 图像中显示的位置 */
}FH_VPU_OSD;

typedef struct
{
	FH_UINT32               idex;
	FH_UINT8               *osdtxtaddr;  /*字符的起始地址*/
	FH_UINT8               *osdfontaddr; /*字符库的地址*/
}FH_VPU_OSD_ADDR;

typedef struct
{
	FH_UINT32               frame_id;
	FH_ADDR_INFO            ymean;
	FH_ADDR_INFO            cmean;
}FH_VPU_YCMEAN;

typedef struct
{
	FH_AREA                 vpu_crop_area;
}FH_VPU_CROP;

typedef struct
{
	FH_UINT32               base;
	void                   *vbase;
	FH_UINT32               size;
}FH_PKG_INFO;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
