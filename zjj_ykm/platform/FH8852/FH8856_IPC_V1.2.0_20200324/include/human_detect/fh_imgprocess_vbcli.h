/**
 * Copyright (c) 2018 Shanghai Fullhan Microelectronics Co., Ltd.
 * All rights reserved
 *
 * image process gvbus client
 */

#ifndef FH_IMGPROCESS_VBCLI_H_
#define FH_IMGPROCESS_VBCLI_H_

#include "types/type_def.h"

// gvbus command id
#define FH_IM_CREATEBUFFERY8_CMD      1101
#define FH_IM_DESTORYBUFFERY8_CMD     1102
#define FH_IM_FILLBUFFERY8_CMD        1103
#define FH_IM_CROPIMAGEY8_CMD         1104
#define FH_IM_EXTENDBORDERY_CMD       1105
#define FH_IM_RESIZEBILINEAR_CMD      1106
#define FH_IM_CREATEBUFFERY8_EXT_CMD  1107
#define FH_IM_DESTORYBUFFERY8_EXT_CMD 1108
#define FH_IM_FILLBUFFERY8_EXT_CMD    1109

// ERROR CODE
#define FH_IM_ERR_BASE (-1100)

#define FH_IM_SUCCESS (0)
#define FH_IM_FAILED (FH_IM_ERR_BASE - 1)
#define FH_IM_NULL_PTR (FH_IM_ERR_BASE - 2)
#define FH_IM_INV_PARAM (FH_IM_ERR_BASE - 3)

// structure for mono 8bpp image in raster scan order
typedef struct FH_imgY8 {
    FH_UINT8 *img;     // image buffer poFH_SINT32er
    FH_UINT16 width;   // image width
    FH_UINT16 height;  // image height
    FH_SINT32  stride;  // image buffer stride
} FH_imgY8_t;

typedef struct FH_subImgY8 {
    FH_imgY8_t *org;   // original imgY8
    FH_UINT8 *   addr;  // sub image start address
    FH_UINT16    x;     // up-left corner x
    FH_UINT16    y;     // up-left corner y
    FH_UINT16    w;     // sub image w
    FH_UINT16    h;     // sub image h
} FH_subImgY8_t;

/**
 * image resize for mono 8bpp image in linear order
 * !!! BUFFER SHOULD BE ALLOCATED BEFORE FUNCTION CALL
 *
 * input:   *in         input image
 * inout:   *out        output image
 *                      output buffer should allocated
 *                      width height stride should be set
 *                      output image stored in out->img
 * return:  FH_IM_SUCCESS
 *          FH_IM_INV_PARAM
 *          FH_IM_NULL_PTR
 */
FH_SINT32 VB_IM_resizeBilinearY8(FH_imgY8_t *in, FH_SINT32 src_stride, FH_imgY8_t *out);

/**
 * create buffer for mono 8bpp image in raster scan order
 *
 * input:   width       input width
 *          height      input height
 * return:  FH_imgY8_t*    buffer handle
 */
FH_imgY8_t *VB_IM_createBufferY8(FH_SINT32 width, FH_SINT32 height);

/**
 * create Y8 infomation for mono 8bpp image in raster scan order
 * !!! the image data buffer is not malloced inside, users should
 *     malloc it outside and set it by VB_IM_fillBufferY8_ext
 *
 * input:   width       input width
 *          height      input height
 * return:  FH_imgY8_t*    buffer handle
 */
FH_imgY8_t *VB_IM_createBufferY8_ext(FH_SINT32 width, FH_SINT32 height);

/**
 * destroy buffer for mono 8bpp image in raster scan order
 *
 * input:   buf         buffer handle
 * return:  FH_IM_SUCCESS
 *          FH_IM_FAILED
 */
FH_SINT32 VB_IM_destroyBufferY8(FH_imgY8_t *buf);

/**
 * destroy buffer for mono 8bpp image created by VB_IM_createBufferY8_ext
 * !!! this API does not free image data buffer inside
 *
 * input:   buf         buffer handle
 * return:  FH_IM_SUCCESS
 *          FH_IM_FAILED
 */
FH_SINT32 VB_IM_destroyBufferY8_ext(FH_imgY8_t *buf);

/**
 * fill imgY8 buffer
 * copy image data to Y8 buffer
 * !!! the size of addr will not be checked inside
 *
 * input:   buf         buffer handle
 *          addr        源图像首地址
 * return:  FH_IM_SUCCESS
 *          FH_IM_FAILED
 */
FH_SINT32 VB_IM_fillBufferY8(FH_imgY8_t *buf, FH_UINT8 *addr);

/**
 * fill imgY8 buffer
 * set imgY8 data buffer
 * !!! the size of addr will not be checked inside
 * !!! the addr should be readable by arc
 *
 * input:   buf         buffer handle
 *          addr        源图像首地址
 * return:  FH_IM_SUCCESS
 *          FH_IM_FAILED
 */
FH_SINT32 VB_IM_fillBufferY8_ext(FH_imgY8_t *buf, FH_UINT8 *addr);

/**
 * crop image for mono 8bpp image in raster scan order
 *
 * input:   org         origin image
 *          x           up-left corner x
 *          y           up-left corner y
 *          w           crop width in pixels
 *          h           crop height in pixels
 * output:  out*        output sub image
 * return:  FH_IM_SUCCESS
 *          FH_IM_FAILED
 */
FH_SINT32 VB_IM_cropImageY8(FH_imgY8_t *org, FH_SINT32 x, FH_SINT32 y, FH_SINT32 w, FH_SINT32 h, FH_subImgY8_t *out);

/**
 * border extension
 * 边界扩展，将输入子画面向外扩充
 *
 * input:   in          origin image
 *          bx          border in x direction
 *          by          border in y direction
 * output:  out*        output sub image
 * return:  FH_IM_SUCCESS
 *          FH_IM_FAILED
 */
FH_SINT32 VB_IM_extendBorderY8(FH_subImgY8_t *in, FH_SINT32 bx, FH_SINT32 by, FH_subImgY8_t *out);

/**
 * 获取库版本信息
 * input:   print_enable 打印使能
 * return:  库版本信息
 */
FH_CHAR* VB_IM_CLI_Version(FH_UINT32 print_enable);

#endif  // !FH_IMGPROCESS_VBCLI_H_
