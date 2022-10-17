#ifndef __FH_BGM_MPIPARA_H__
#define __FH_BGM_MPIPARA_H__

#include "types/type_def.h"
#include "fh_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */


typedef struct
{
	FH_SIZE         size;
	FH_ADDR         YADDR;//phy addr
	FH_ADDR         CADDR;//phy addr
	FH_UINT64       time_stamp;
}FH_BGM_FRAME;

typedef struct
{
	FH_UINT32       foreground_point_num;
	FH_UINT32       sta_diff_point_num;
	FH_UINT32       frm_diff_point_num;
	FH_UINT32       fg_consist_mb_sum;
	FH_UINT32       bg_consist_mb_sum;
	FH_UINT32       fg_mb_diff_sum;
	FH_UINT32       bg_mb_diff_sum;
	FH_UINT32       valid_mb_num;
	FH_UINT32       bg_point_num[2];
	FH_UINT32       darken_point_num[2];
	FH_UINT32       brighten_point_num[2];
	FH_UINT32       cur_luma_sum[2];
	FH_UINT32       bg_luma_sum[2];
	FH_ADDR_INFO    gau_dis_addr;
	FH_ADDR_INFO    gau_bg_re_pic_addr;
	FH_ADDR_INFO    run_num_addr;
	FH_ADDR_INFO    run0_pos_addr;
	FH_ADDR_INFO    run1_pos_addr;
	FH_ADDR_INFO    diff_addr;
	FH_UINT64       time_stamp;
}FH_BGM_HW_STATUS;

typedef struct
{
	FH_SIZE         size;
	FH_ADDR_INFO    confidence_level;
	FH_ADDR_INFO    mb_consistency;
	FH_UINT32       background_change_flag;
	FH_UINT32       static_frm_flag;
	FH_UINT64       time_stamp;
}FH_BGM_SW_STATUS;

#define MAX_RUNTABLE_RECT 50
typedef struct
{
	FH_UINT32 rect_num;
	FH_UINT32 base_w;
	FH_UINT32 base_h;
	FH_AREA rect[MAX_RUNTABLE_RECT];
	FH_UINT64 timestamp;
}FH_BGM_RUNTB_RECT;

#define MAX_TH_NUM 5
typedef struct
{
	FH_UINT32 GOP_TH_NUM;
	//门限单位为百分比，从小到大，代表从安静到运动
	FH_UINT32 TH_VAL[MAX_TH_NUM];
	//表示小于对应门限时最小的GOP长度。码流可能出现的最长GOP(极端场景下为所以最小GOP长度的和)
	FH_UINT32 MIN_GOP[MAX_TH_NUM+1];
}FH_GOP_TH;

typedef struct
{
	FH_UINT8 refresh_rate;
	FH_UINT8 bkg_th0; /* find match bin threshold,y_diff */
	FH_UINT8 bkg_th1; /* vanish_cnt threshold */
}FH_BKG_INIT_CFG;

typedef struct
{
	FH_UINT16 refresh_rate;
	FH_UINT8  precision;    /* default=0, the bigger, the more fg */
	FH_UINT8  variance_gain;/* U4.4 */
	FH_UINT8  variance_min;
	FH_UINT8  variance_max;
}FH_SINGLE_GAU_CFG;

typedef struct
{
	FH_UINT16 refresh_rate;
	FH_UINT16 refresh_weight_rate;
	FH_UINT8  precision;      /* default=0, the bigger, the stricter condition for the most match gau_core */
	FH_UINT8  variance_gain;
	FH_UINT8  variance_init;  /* the initial value for replace gau_core */
	FH_UINT8  variance_min;
	FH_UINT8  variance_max;
	FH_UINT8  bg_weight_th;   /* the bigger, the more fg */
	FH_UINT8  bg_time_th;     /* the bigger, the more fg */
	FH_UINT8  sel_mode;       /* mode for searching the most match gau_core, 0:weight, 1:weight/variance */
	FH_UINT8  time_update_en; /*update all gau_core time*/
}FH_MULTI_GAU_CFG;

typedef struct
{
	FH_UINT16 refresh_rate;
	FH_UINT8  precision;
	FH_UINT8  variance_th;   /* the less, the more dis, be used to judge dis */
	FH_UINT8  weight_th;     /*the less, the more dis, be used to judge dis */
	FH_UINT8  time_th;       /* the less, the more dis, be used to judge dis */
	FH_UINT8  freq_th;       /* the less, the more dis, be used to judge dis */
	FH_UINT8  freq_time_th;  /* the less, the more dis_freq_cnt */
	FH_UINT8  freq_weight_th;/* the less, the more dis_freq_cnt */
	FH_UINT8  freq_update_en;/* for software use, freq_cnt-1 */
}FH_DIS_CFG;

typedef enum
{
	FH_MULTI_GAU_FG_A  = 0,
	FH_MULTI_GAU_DIS   = 1,
	FH_MULTI_GAU_FG_B  = 2,
	FH_LONG_TERM_FG_A  = 3,
	FH_LONG_TERM_FG_B  = 4,
	FH_LONG_TERM_FG_A1 = 5,
	FH_LONG_TERM_FG_B1 = 6,
}FH_CON_EXPA_IDX;

typedef struct
{
	FH_UINT32 win_mask;
	FH_UINT8  expa_th;       /* the less, the more 1 */
	FH_UINT8  center_en;     /* whether consider the center point */
}FH_CON_EXPA_CFG;

typedef struct
{
	FH_UINT8 diff_th0;       /* for static frame binaryzation */
	FH_UINT8 diff_th1;       /* for frm_diff_num_stat binaryzation */
	FH_UINT8 longTermFgTh0;  /* for run0 table*/
	FH_UINT8 longTermFgTh1;  /* for run1 table*/
	FH_UINT8 sta_regre_val;  /* the less, the more sta_num */
	FH_UINT8 sta_diff_num_th;/* for stat_num stat, the less, the more stat_num */
}FH_FRM_DIFF_CFG;

typedef struct
{
	FH_UINT8 bg_diff_th; /* the bigger, the more consist_mb */
}FH_FRM_DIFF_CONSIST_CFG;

typedef struct
{
	FH_UINT8 bright_th0; /* CHANNEL_A darken brighten threshold */
	FH_UINT8 bright_th1; /* CHANNEL_B darken brighten threshold */
}FH_GLOBAL_BG_LUMA_CFG;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

