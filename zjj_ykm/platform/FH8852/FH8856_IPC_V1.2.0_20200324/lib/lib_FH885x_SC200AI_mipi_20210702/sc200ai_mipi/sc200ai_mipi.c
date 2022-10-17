/*
 * sc200ai_mipi_mipi.c
 *
 *  Created on: Sep 14, 2015
 *      Author: duobao
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fh_defs.h"
#include "isp_func_def.h"

#include "isp_sensor_if.h"
#include "sensor_ops.h"

#include "isp_enum.h"
#include "sc200ai_mipi.h"
#include "clock_ops.h"
#include "mipi_ctrl.h"

#ifndef OS_LINUX
#include <rtthread.h>
#endif
extern unsigned int NAME(ImageParam)[4],NAME(contrast)[12],NAME(saturation)[12],NAME(sharpness)[12],NAME(MirrorFlipBayerFormat)[4],NAME(AwbGain)[4][3],
NAME(LtmMapping00)[128],NAME(LtmMapping01)[128],NAME(LtmMapping02)[128],NAME(LtmMapping03)[128],NAME(LtmMapping04)[128],NAME(LtmMapping05)[128],
NAME(LtmMapping06)[128],NAME(LtmMapping07)[128],NAME(LtmMapping08)[128],NAME(LtmMapping09)[128],NAME(LtmMapping10)[128];

extern unsigned int NAME(ImageParamWdr)[4];
extern unsigned int NAME(contrastWdr)[12];
extern unsigned int NAME(saturationWdr)[12];
extern unsigned int NAME(sharpnessWdr)[12];
extern unsigned int NAME(MirrorFlipBayerFormatWdr)[4];
extern unsigned int NAME(AwbGainWdr)[4][3];

static FH_BOOL inited=0;

static FH_UINT32 sensor_fmt;
static FH_UINT32 m_gain = 0;
static int wdr_flag;
static int curr_exposure_ratio = 96;
static FH_UINT32 l_intt;
static FH_UINT32 m_intt;

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define intt_step_max 0x10

static int GetSensorViAttr(ISP_VI_ATTR_S *vi_attr)
{

	if(vi_attr == NULL)
		return FH_ERR_NULL_POINTER;

	switch (sensor_fmt)
	{	
        case FORMAT_1080P15://1080p15
            vi_attr->u16WndWidth = FRAM_W_1080P15;
            vi_attr->u16WndHeight = FRAM_H_1080P15;
            vi_attr->u16InputWidth = ACTIVE_W_1080P15;
            vi_attr->u16InputHeight = ACTIVE_H_1080P15;
            vi_attr->u16PicWidth = PIC_IN_W_1080P15;
            vi_attr->u16PicHeight = PIC_IN_H_1080P15;
            vi_attr->u16OffsetX = OFFSET_X_1080P15;
            vi_attr->u16OffsetY = OFFSET_Y_1080P15;
            vi_attr->enBayerType = BAYER_BGGR;
            break; 
    
		case FORMAT_1080P30:
			vi_attr->u16WndWidth = FRAM_W_1080P30;
			vi_attr->u16WndHeight = FRAM_H_1080P30;
			vi_attr->u16InputWidth = ACTIVE_W_1080P30;
			vi_attr->u16InputHeight = ACTIVE_H_1080P30;
			vi_attr->u16PicWidth = PIC_IN_W_1080P30;
			vi_attr->u16PicHeight = PIC_IN_H_1080P30;
			vi_attr->u16OffsetX = OFFSET_X_1080P30;
			vi_attr->u16OffsetY = OFFSET_Y_1080P30;
			vi_attr->enBayerType = BAYER_BGGR;
			break;
		case FORMAT_1080P25:
			vi_attr->u16WndWidth = FRAM_W_1080P25;
			vi_attr->u16WndHeight = FRAM_H_1080P25;
			vi_attr->u16InputWidth = ACTIVE_W_1080P25;
			vi_attr->u16InputHeight = ACTIVE_H_1080P25;
			vi_attr->u16PicWidth = PIC_IN_W_1080P25;
			vi_attr->u16PicHeight = PIC_IN_H_1080P25;
			vi_attr->u16OffsetX = OFFSET_X_1080P25;
			vi_attr->u16OffsetY = OFFSET_Y_1080P25;
			vi_attr->enBayerType = BAYER_BGGR;
			break;
        case FORMAT_1080P60://1080p25
            vi_attr->u16WndWidth = FRAM_W_1080P60;
            vi_attr->u16WndHeight = FRAM_H_1080P60;
            vi_attr->u16InputWidth = ACTIVE_W_1080P60;
            vi_attr->u16InputHeight = ACTIVE_H_1080P60;
            vi_attr->u16PicWidth = PIC_IN_W_1080P60;
            vi_attr->u16PicHeight = PIC_IN_H_1080P60;
            vi_attr->u16OffsetX = OFFSET_X_1080P60;
            vi_attr->u16OffsetY = OFFSET_Y_1080P60;
            vi_attr->enBayerType = BAYER_BGGR;
            break;  
#ifndef LB2
        case FORMAT_1080P20://1080p20
            vi_attr->u16WndWidth = FRAM_W_1080P20;
            vi_attr->u16WndHeight = FRAM_H_1080P20;
            vi_attr->u16InputWidth = ACTIVE_W_1080P20;
            vi_attr->u16InputHeight = ACTIVE_H_1080P20;
            vi_attr->u16PicWidth = PIC_IN_W_1080P20;
            vi_attr->u16PicHeight = PIC_IN_H_1080P20;
            vi_attr->u16OffsetX = OFFSET_X_1080P20;
            vi_attr->u16OffsetY = OFFSET_Y_1080P20;
            vi_attr->enBayerType = BAYER_BGGR;
            break;
        
        case FORMAT_1080P50://1080p25
            vi_attr->u16WndWidth = FRAM_W_1080P50;
            vi_attr->u16WndHeight = FRAM_H_1080P50;
            vi_attr->u16InputWidth = ACTIVE_W_1080P50;
            vi_attr->u16InputHeight = ACTIVE_H_1080P50;
            vi_attr->u16PicWidth = PIC_IN_W_1080P50;
            vi_attr->u16PicHeight = PIC_IN_H_1080P50;
            vi_attr->u16OffsetX = OFFSET_X_1080P50;
            vi_attr->u16OffsetY = OFFSET_Y_1080P50;
            vi_attr->enBayerType = BAYER_BGGR;
            break;  
		case FORMAT_WDR_1080P30:
			vi_attr->u16WndWidth = FRAM_W_1080P30_WDR;
			vi_attr->u16WndHeight = FRAM_H_1080P30_WDR;
			vi_attr->u16InputWidth = ACTIVE_W_1080P30_WDR;
			vi_attr->u16InputHeight = ACTIVE_H_1080P30_WDR;
			vi_attr->u16PicWidth = PIC_IN_W_1080P30_WDR;
			vi_attr->u16PicHeight = PIC_IN_H_1080P30_WDR;
			vi_attr->u16OffsetX = OFFSET_X_1080P30_WDR;
			vi_attr->u16OffsetY = OFFSET_Y_1080P30_WDR;
			vi_attr->enBayerType = BAYER_BGGR;
			printf("\nread config wdr 30 frame ok\n");
			break;
		case FORMAT_WDR_1080P25:
			vi_attr->u16WndWidth = FRAM_W_1080P25_WDR;
			vi_attr->u16WndHeight = FRAM_H_1080P25_WDR;
			vi_attr->u16InputWidth = ACTIVE_W_1080P25_WDR;
			vi_attr->u16InputHeight = ACTIVE_H_1080P25_WDR;
			vi_attr->u16PicWidth = PIC_IN_W_1080P25_WDR;
			vi_attr->u16PicHeight = PIC_IN_H_1080P25_WDR;
			vi_attr->u16OffsetX = OFFSET_X_1080P25_WDR;
			vi_attr->u16OffsetY = OFFSET_Y_1080P25_WDR;
			vi_attr->enBayerType = BAYER_BGGR;
			printf("\nread config wdr 25 frame ok\n");
			break;
#endif
		default:
			return FH_ERR_ISP_NO_SUPPORT_FORMAT;
	}
	return 0;
}

static void SensorReset(void)
{
	return;
}

static int GetSensorGain(FH_UINT32 *u32Gain)		//gain U10.6
{
    
	*u32Gain = m_gain;
    return 0;

}

static int SetSensorGain(FH_UINT32 gain)		//gain U10.6
{
    unsigned char  gain_0x3e06 = 0x00;//初始dgain
    unsigned char  gain_0x3e07 = 0x80;
    unsigned char  gain_0x3e08 = 0x03;//初始again
    unsigned char  gain_0x3e09 = 0x40;

    if(gain <= 20*64)
	{
		Sensor_Write(0x5799,0x00);
	}
	else if (gain >= 30*64)
	{
		Sensor_Write(0x5799,0x07);
	}
	
	m_gain = gain;
    if(gain < 64*2)
    {
        gain_0x3e08 = 0x03;
        gain_0x3e09 = gain;
        gain_0x3e06 = 0x00;
        gain_0x3e07 = 0x80;
    }
    else if(gain <= 64*3.375)
    {
        gain_0x3e08 = 0x07;
        gain_0x3e09 = gain/2; 
        gain_0x3e06 = 0x00;
        gain_0x3e07 = 0x80;
    }
    else if(gain <= 64*3.375*2)
    {
        gain_0x3e08 = 0x23;
        gain_0x3e09 = gain/3.375; 
        gain_0x3e06 = 0x00;
        gain_0x3e07 = 0x80;
    }
    else if(gain <= 64*3.375*2*2)
    {
        gain_0x3e08 = 0x27;
        gain_0x3e09 = gain/3.375/2; 
        gain_0x3e06 = 0x00;
        gain_0x3e07 = 0x80;
    }
    else if(gain <= 64*3.375*2*2*2)
    {
        gain_0x3e08 = 0x2f;
        gain_0x3e09 = gain/3.375/4;
        gain_0x3e06 = 0x00;
        gain_0x3e07 = 0x80;
    }
    else if(gain <= 64*3.375*2*2*2*2) //54x
    {
        gain_0x3e08 = 0x3f;
        gain_0x3e09 = gain/3.375/8;
        gain_0x3e06 = 0x00;
        gain_0x3e07 = 0x80;
    }
    else
    {
        gain_0x3e08 = 0x3f;
        gain_0x3e09 = 0x7f; 
        gain_0x3e06 = 0x00;
        gain_0x3e07 = 0x80;
    }
    
    Sensor_Write(0x3e09, gain_0x3e09);
    Sensor_Write(0x3e08, gain_0x3e08);
	Sensor_Write(0x3e06, gain_0x3e06);
    Sensor_Write(0x3e07, gain_0x3e07);
    return 0;
}

static int GetSensorIntt(FH_UINT32 *intt)
{
	*intt=l_intt;
	// *intt=0x40;
	return 0;
}

static int SetSensorIntt(FH_UINT32 intt)
{
	if(wdr_flag)
	{
		intt = (MAX(8,intt)) << 1;
	}		
	else
	{
		intt = (MAX(1,intt)) << 1;
	}
	
	l_intt = intt >> 1;
	
	Sensor_Write(0x3e00, (intt>>12) & 0xf);
	Sensor_Write(0x3e01, (intt>>4) & 0xff);
	Sensor_Write(0x3e02, (intt & 0xf) << 4);
	
	// printf("\nl_intt:%d\n",l_intt);
    return 0;
}

static int SetExposureRatio(FH_UINT32 exposure_ratio)
{
    // return 0;
	FH_UINT32 inttSH,inttSM,inttSL;
	//printf("l_intt:%d\t\t",l_intt);
	m_intt = MAX(((((l_intt << 1) << 4) + (exposure_ratio >> 1)) / exposure_ratio), 4);
	//printf("m_intt:%d\t\t",m_intt);	
	inttSH = (m_intt >> 12) & 0xf;
	inttSM = (m_intt >> 4) & 0xff;
	inttSL = (m_intt & 0xf) << 4;
   
	Sensor_Write(0x3e03, inttSH);
	Sensor_Write(0x3e04, inttSM);
	Sensor_Write(0x3e05, inttSL);
    curr_exposure_ratio=(l_intt << 4) / (m_intt >> 1);
    //printf("curr_exposure_ratio:%d\n",curr_exposure_ratio);
	// printf("exposure_ratio:%d\n\n",curr_exposure_ratio);
    return 0;
}

static int GetExposureRatio(FH_UINT32 *exposure_ratio)
{
    *exposure_ratio = curr_exposure_ratio;
	// *exposure_ratio = 0x10;
    return 0;
}

static int SetSensorFrameHeight(FH_UINT32 multiple)
{
	FH_UINT32 frame_height;
	ISP_VI_ATTR_S vi_attr;

	GetSensorViAttr(&vi_attr);

	frame_height = vi_attr.u16WndHeight * multiple;
	//printf("multiple:%d\n",multiple);
	//printf("vi_attr.u16WndHeight:%d\n",vi_attr.u16WndHeight);

	Sensor_Write(0x320f, (frame_height & 0xff));
	Sensor_Write(0x320e, (frame_height >> 8));

    return 0;
}

static unsigned short sc200ai_i2c_addr = 0x60;
static int Sensor_Isconnect(void)
{
    unsigned short pid1, pid2;
    unsigned short i2c_addr[4] = {0x60, 0x64,0x30,0x32};
    int i;

    for(i = 0; i < 4; i ++)
    {
        SensorDevice_Init((i2c_addr[i]>>1), 2);
    
        pid1 = Sensor_Read(0x3107);
        pid2 = Sensor_Read(0x3108);
        SensorDevice_Close();
        //printf("\n\n\n==========%x%x\n\n\n",pid1,pid2);
        if (pid1 == 0xcb && pid2 == 0x1c)
        {
            sc200ai_i2c_addr = i2c_addr[i];
            printf("sc200ai_i2c_addr is %x\n",sc200ai_i2c_addr);
            return 1;
        }
        else
        {
            continue;
        }
    }
    return 0;
}
static int Sensor_Init(void)
{
	//set_clk_rate(cis_clk,CLK_27M);
    Sensor_Isconnect();
	SensorDevice_Init((sc200ai_i2c_addr>>1), 2);

	SensorReset();
    inited = 1;
	return 0;
}

static int Sensor_DeInit(void)
{
	SensorReset();

	return SensorDevice_Close();
}

static void SetSensorMipiCfg(void)
{
    struct mipi_conf config;
    
    config.sensor_mode = NOT_SONY_WDR_USE_WDR;
    config.lane_num = 2;

    if (wdr_flag) {
        config.sf_vc_id = 1;
        config.lf_vc_id = 0;
		config.frq_range = R_700_749;
		config.raw_type = RAW10;
		// printf("\nmipi config ok\n\n");
    }
    else
    {
        config.sf_vc_id = 0;
        config.lf_vc_id = 0;
		config.frq_range = R_400_449;
		config.raw_type = RAW10;
    }

    mipi_init(&config);
    return;
}

static int SetSensorFmt(int format)
{
	sensor_fmt = format;
	wdr_flag = (format >> 16) & 0x1;
	printf("wdr_flag:%d\n",wdr_flag);
	l_intt = 0xca;
	// m_intt = 0x16;
	m_gain = 0x40;
	inited = 1;
	SetSensorMipiCfg();
	//SensorReset();

	if(inited)
	{
		int i;
    printf("\n\nflag\n");
		switch(sensor_fmt)
        {
        case FORMAT_1080P15:
            for(i=0; i<sizeof(Sensor_Cfg_SC200AI_MIPI_1080P15)/4; i++)
            {
                Sensor_Write(Sensor_Cfg_SC200AI_MIPI_1080P15[2*i], Sensor_Cfg_SC200AI_MIPI_1080P15[2*i+1]);
            }
            printf("\n\n1080p15\n\n");
            break;
        
        case FORMAT_1080P25:
            for(i=0; i<sizeof(Sensor_Cfg_SC200AI_MIPI_1080P25)/4; i++)
            {
                Sensor_Write(Sensor_Cfg_SC200AI_MIPI_1080P25[2*i], Sensor_Cfg_SC200AI_MIPI_1080P25[2*i+1]);
            }
            printf("\n\n1080p25\n\n");
            break;
        case FORMAT_1080P30:
            for(i=0; i<sizeof(Sensor_Cfg_SC200AI_MIPI_1080P30)/4; i++)
            {
                Sensor_Write(Sensor_Cfg_SC200AI_MIPI_1080P30[2*i], Sensor_Cfg_SC200AI_MIPI_1080P30[2*i+1]);
            }
            break;
        case FORMAT_1080P60:
            for(i=0; i<sizeof(Sensor_Cfg_SC200AI_MIPI_1080P60)/4; i++)
            {
                Sensor_Write(Sensor_Cfg_SC200AI_MIPI_1080P60[2*i], Sensor_Cfg_SC200AI_MIPI_1080P60[2*i+1]);
            }
            break;
#ifndef LB2
        case FORMAT_1080P20:
            for(i=0; i<sizeof(Sensor_Cfg_SC200AI_MIPI_1080P20)/4; i++)
            {
                Sensor_Write(Sensor_Cfg_SC200AI_MIPI_1080P20[2*i], Sensor_Cfg_SC200AI_MIPI_1080P20[2*i+1]);
            }
            break;
        case FORMAT_1080P50:
            for(i=0; i<sizeof(Sensor_Cfg_SC200AI_MIPI_1080P50)/4; i++)
            {
                Sensor_Write(Sensor_Cfg_SC200AI_MIPI_1080P50[2*i], Sensor_Cfg_SC200AI_MIPI_1080P50[2*i+1]);
            }
            break;
        case FORMAT_WDR_1080P30:
            for(i=0; i<sizeof(Sensor_Cfg_SC200AI_MIPI_WDR_1080P30)/4; i++)
            {
                Sensor_Write(Sensor_Cfg_SC200AI_MIPI_WDR_1080P30[2*i], Sensor_Cfg_SC200AI_MIPI_WDR_1080P30[2*i+1]);
            }
            break;
        case FORMAT_WDR_1080P25:
            for(i=0; i<sizeof(Sensor_Cfg_SC200AI_MIPI_WDR_1080P25)/4; i++)
            {
                Sensor_Write(Sensor_Cfg_SC200AI_MIPI_WDR_1080P25[2*i], Sensor_Cfg_SC200AI_MIPI_WDR_1080P25[2*i+1]);
            }
            break;
#endif
        default:
            return -1;
            break;
			
		}
	}

	SetSensorGain(0x40);
	SetSensorIntt(1000);
	return 0;
}

static int GetSensorAttribute(char * name, FH_UINT32 *value)
{
    if (wdr_flag) {
        if (strcmp(name, "WDR") == 0) {
            *value = 1;
            return 0;
        }
    }

    return -1;
}

static int SetSensorReg(unsigned short addr, unsigned short data)
{
	Sensor_Write(addr, data);
	return 0;
}
#ifndef LB2
static int GetSensorReg(unsigned short addr, unsigned short *data)
{
	*data = Sensor_Read(addr);
	return 0;
}
#endif
static int SetSensorFlipMirror(FH_UINT32 sensor_en_stat)
{
	FH_UINT32 mirror, flip;
	mirror = (sensor_en_stat >> 1) & 0x1;
	flip   = sensor_en_stat & 0x1;
	int reg_3221;
	
	reg_3221 = Sensor_Read(0x3221);
	reg_3221 = reg_3221 | (flip << 6) | (flip << 5) | (mirror << 2) | (mirror << 1); 

	Sensor_Write(0x3221, reg_3221);
	
	return 0;
}
static int GetSensorFlipMirror(FH_UINT32 *sensor_en_stat)
{
	FH_UINT8 mirror, flip;

    flip = (Sensor_Read(0x3221)) >> 6 & 0x1;
    mirror = (Sensor_Read(0x3221) >> 2 & 0x1);
    *sensor_en_stat = (mirror << 1) | flip;
	return 0;
}

int GetViMode(int * vi_mode)
{
    * vi_mode=5;
    return 0;
}

FH_UINT32* NAME(GetDefaultParam)()
{
    if (wdr_flag)
        return NAME(ImageParamWdr);
    else
        return NAME(ImageParam);
}

FH_UINT32* NAME(GetContrast)()
{
    if (wdr_flag)
        return NAME(contrastWdr);
    else
        return NAME(contrast);
}

FH_UINT32* NAME(GetSaturation)()
{
    if (wdr_flag)
        return NAME(saturationWdr);
    else
        return NAME(saturation);
}
FH_UINT32* NAME(GetSharpness)()
{
    if (wdr_flag)
        return NAME(sharpnessWdr);
    else
        return NAME(sharpness);
}

FH_UINT32 NAME(*GetMirrorFlipBayerFormat)()
{
    if (wdr_flag)
        return NAME(MirrorFlipBayerFormatWdr);
    else
        return NAME(MirrorFlipBayerFormat);
}

FH_UINT32* NAME(GetSensorAwbGain)(int idx)
{
    if (wdr_flag)
        return NAME(AwbGainWdr)[idx];
    else
        return NAME(AwbGain)[idx];
}

FH_UINT32* NAME(GetSensorLtmCurve)(int idx)
{
    if (!wdr_flag)
    {
        switch (idx)
        {
        case 0:
            return NAME(LtmMapping00);
            break;
        case 1:
            return NAME(LtmMapping01);
            break;
        case 2:
            return NAME(LtmMapping02);
            break;
        case 3:
            return NAME(LtmMapping03);
            break;
        case 4:
            return NAME(LtmMapping04);
            break;
        case 5:
            return NAME(LtmMapping05);
            break;
        case 6:
            return NAME(LtmMapping06);
            break;
        case 7:
            return NAME(LtmMapping07);
            break;
        case 8:
            return NAME(LtmMapping08);
            break;
        case 9:
            return NAME(LtmMapping09);
            break;
        case 10:
            return NAME(LtmMapping10);
            break;
        }
        return NAME(LtmMapping00);
    }
    return 0;
}



#define SENSOR_SC200AI_MIPI	"sc200ai_mipi"
struct isp_sensor_if sc200ai_mipi;

struct isp_sensor_if* NAME(Sensor_Create)()
{
  if (!Sensor_Isconnect())
    {
#if MULTI_SENSOR
        return 0;
#endif
    }

	memset(&sc200ai_mipi,0,sizeof(struct isp_sensor_if));
	sc200ai_mipi.name = SENSOR_SC200AI_MIPI;
	sc200ai_mipi.init = Sensor_Init;
	sc200ai_mipi.get_vi_attr = GetSensorViAttr;
	sc200ai_mipi.set_sns_fmt = SetSensorFmt;
	sc200ai_mipi.set_gain = SetSensorGain;
	sc200ai_mipi.get_gain = GetSensorGain;
	sc200ai_mipi.reset    = SensorReset;
	sc200ai_mipi.get_intt = GetSensorIntt;
	sc200ai_mipi.set_intt = SetSensorIntt;
	sc200ai_mipi.set_sns_reg = SetSensorReg;
	sc200ai_mipi.set_frame_height = SetSensorFrameHeight;
	sc200ai_mipi.set_flipmirror = SetSensorFlipMirror;
	sc200ai_mipi.get_flipmirror = GetSensorFlipMirror;
	sc200ai_mipi.set_exposure_ratio =SetExposureRatio;
	sc200ai_mipi.get_exposure_ratio =GetExposureRatio;
	sc200ai_mipi.get_sensor_attribute = GetSensorAttribute;
#ifndef LB2
	sc200ai_mipi.get_sns_reg = GetSensorReg;
#endif
	sc200ai_mipi.deinit   = Sensor_DeInit;
    sc200ai_mipi.get_vi_mode =GetViMode;
	return &sc200ai_mipi;
}

void NAME(Sensor_Destory)(struct isp_sensor_if* s_if)
{
	sc200ai_mipi.name = 0;
	sc200ai_mipi.init = 0;
	sc200ai_mipi.get_vi_attr = 0;
	sc200ai_mipi.set_sns_fmt = 0;
	sc200ai_mipi.set_gain = 0;
	sc200ai_mipi.get_gain = 0;
	sc200ai_mipi.reset    = 0;
	sc200ai_mipi.get_intt = 0;
	sc200ai_mipi.set_intt = 0;
	sc200ai_mipi.set_sns_reg = 0;
	sc200ai_mipi.set_frame_height = 0;
	sc200ai_mipi.set_flipmirror = 0;
	sc200ai_mipi.get_flipmirror = 0;
	sc200ai_mipi.set_exposure_ratio =0;
	sc200ai_mipi.get_exposure_ratio =0;
	sc200ai_mipi.get_sensor_attribute = 0;
#ifndef LB2
	sc200ai_mipi.get_sns_reg = 0;
#endif
	sc200ai_mipi.deinit   = 0;
}