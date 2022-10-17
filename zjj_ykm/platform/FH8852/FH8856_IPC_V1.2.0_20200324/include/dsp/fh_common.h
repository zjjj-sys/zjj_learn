#ifndef __FH_COMMON_H__
#define __FH_COMMON_H__
#include "types/type_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

// #define API_PRT
#ifdef API_PRT
#define API_DEBUG(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#define API_NOTICE(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#else
#define API_DEBUG(...)
#define API_NOTICE(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#endif

#define RETURN_NULL                         (0)
#define RETURN_OK                           (0)
#define NO_DEVICE                           (-1001)
#define OPEN_DEVICE_ERR                     (-1001)
#define CLOSE_DEVICE_ERR                    (-1002)
#define FIND_DEVICE_ERR                     (-1003)
#define PARAM_NULL                          (-1004)
#define PARAM_ERR                           (-1005)
#define ALIGN_ERR                           (-1006)
#define MODULE_ENABLE_ERR                   (-1007)
#define CHAN_ERR                            (-1008)
#define MEM_NULL                            (-1009)
#define GET_STREAM_EMPTY                    (-1010)
#define HAS_CREATED                         (-1011)
#define SDK_ERR                             (-1012)
#define NOT_SUPPORT                         (-1013)
#define NOT_READY                           (-1014)
#define NOT_INIT                            (-1015)

#define MAX_OSD_LINE                         (8)
#define MAX_INVERT_CNT                       (8)
#define MAX_MASK_AREA                        (8)
#define MAX_GBOX_AREA                        (16)
#define DEFALT_ALIGN                         (8)
#define MAX_VPU_CHANNO                       (4)
#define MAX_ENC_CHANNO                       (8)

#define MALLOCED_MEM_BASE_DSP                (1)
#define MALLOCED_MEM_VPUPKG                  (0)

typedef enum
{
	FH_RO_OPS_0     = 0,
	FH_RO_OPS_90    = 1,
	FH_RO_OPS_180   = 2,
	FH_RO_OPS_270   = 3
}FH_ROTATE_OPS;

typedef struct fhVERSION_INFO_
{
	FH_UINT32           build_date; /**<构建号*/
	FH_UINT32           sw_version; /**<软件版本号*/
	FH_UINT32           hw_version; /**<硬件驱动版本号*/
}FH_VERSION_INFO;

typedef struct fhPOINT_
{
	FH_UINT32           u32X; /**< 水平坐标 */
	FH_UINT32           u32Y; /**< 垂直坐标 */
}FH_POINT;

typedef struct fhSIZE_S
{
	FH_UINT32           u32Width; /**< 宽度像素  */
	FH_UINT32           u32Height; /**<高度像素  */
} FH_SIZE;

typedef struct fhRECT_S
{
	FH_UINT32           u32X; /**< 起始点水平坐标 */
	FH_UINT32           u32Y; /**< 起始点垂直坐标*/
	FH_UINT32           u32Width; /**< 区域宽度*/
	FH_UINT32           u32Height; /**< 区域高度 */
}FH_AREA;

typedef struct
{
	FH_ADDR             addr;
	FH_UINT32           size;
}FH_ADDR_INFO;

typedef struct
{
	unsigned int        base; /**< 物理地址 */
	void *              vbase; /**< 虚拟地址 */
	unsigned int        size; /**< 内存大小 */
}FH_MEM_INFO;

typedef struct
{
	FH_UINT16           frame_count; /**< 帧数 */
	FH_UINT16           frame_time; /**< 统计时间 (s)*/
} FH_FRAMERATE;

typedef struct
{
	FH_UINT32           y;
	FH_UINT32           cb;
	FH_UINT32           cr;
	FH_UINT32           alpha;
} FH_YC_COLOR;

typedef struct
{
	FH_UINT32 avgTime;
	FH_UINT32 maxTime;
	FH_UINT32 win_size;
}FH_HW_AVG_TIME;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _FH_COMMON_H_ */
