#ifndef __CPRODUCT_H__
#define __CPRODUCT_H__


#include <fstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <pthread.h>

#include "common.h"



typedef enum{
	SENSOR_TYPE_OV9712 = 0,
	SENSOR_TYPE_OV9732,		// 1
	SENSOR_TYPE_H22,		// 2
	SENSOR_TYPE_H42,		// 3
	SENSOR_TYPE_SC1135,		// 4
	SENSOR_TYPE_SC1045,		// 5
	SENSOR_TYPE_SC2135,		// 6
	SENSOR_TYPE_AR0130,		// 7
	SENSOR_TYPE_DC_SC2135,  // 8
	SENSOR_TYPE_MIPI_SC2135,// 9
	SENSOR_TYPE_DC_F22,		// 10
	SENSOR_TYPE_MIPI_F22,	// 11
	SENSOR_TYPE_DC_PS5250,	// 12
	SENSOR_TYPE_MIPI_PS5270,// 13
	SENSOR_TYPE_DC_IMX323,	// 14
	SENSOR_TYPE_MIPI_PS5280,// 15
	SENSOR_TYPE_MIPI_PS5510, //16
	SENSOR_TYPE_MIPI_GC2053, //17
	SENSOR_TYPE_MIPI_IMX307, // 18
	SENSOR_TYPE_MIPI_IMX307_2L, // 19
	SENSOR_TYPE_MIPI_SC4236,    //20  2048x1536 => 1536x1536
	SENSOR_TYPE_MIPI_GC2063,    // 21 FH8852 Soc 
	SENSOR_TYPE_MIPI_SC200AI = 22,
	SENSOR_TYPE_MIPI_GC4663  = 23, // 2560x1440
}SENSOR_TYPE;



typedef enum{
	MODEL_MTC100 = 0x1000,		// hi3518ev200 + sp1047,card camera
	MODEL_MTC130,				// // hi3518ev200 + sc1135,card camera
	MODEL_MTC200,				// // hi3518ev200 + sc2135,card camera
	MODEL_MTC130A,				// // hi3518ev200 + ar0130,card camera



	MODEL_MTI100 = 0x2000,		// hi3518ev200 + sp1407 ,wifi + wire ip camera...


	MODEL_MI_2135 		= 0x3000,		// (base)MSC313E + SC2135,wire ip onvif camera
	MODEL_MI_F22 		= 0x3001,		// (base)MSC313E + F22,wire + wifi ip onvif camera
	MODEL_MI_PS5250  	= 0x3002,		// (base)MSC313E + PS5250,wire + wifi ip onvif camera
	MODEL_HA_8403M		= 0x3003,		// (base)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker
	MODEL_HA_8403MV2	= 0x3003,		// (base)Same with MODEL_HA_8403M,except wifi (9083H)
	MODEL_HA_8403MV3	= 0x3003,		// (base)Same with MODEL_HA_8403M,except wifi (mt7601)
	MODEL_HA_8403MV4	= 0x3003,		// (base)Same with MODEL_HA_8403M,except wifi (rtl8188ftv)
	MODEL_HA_8501M		= 0x3004,		// (base)MSC313E + F22,wire + wifi ip onvif camera
	MODEL_HA_8501MV2	= 0x3005,		// (base)MSC313E + PS5250,wire + wifi ip onvif camera
	MODEL_HA_8303M		= 0x3006,		// (base)MSC313E + PS5270,wire + wifi ip onvif camera,fisheye camera...
	MODEL_HA_8203M		= 0x3007,		// (base)MSC313E + F22,wire + wifi + pt ip onvif camera
	MODEL_HA_8203MV2	= 0x3007,		// (base)Hardware is same with HA-8203M, except WIFI(9083H)
	MODEL_HA_8204M		= 0x3008,		// (base)MSC313E + F22,wire + wifi + pt + alarm host ip onvif camera
	MODEL_HA_8403MS		= 0x3009,		// (base)MSC313E + IMX323,wire + wifi ip onvif camera ,no mic ,no speaker ,HA-8403MS,M - MStar, S : star light level ipcam
	MODEL_HA_8250M		= 0x300a,		// (base)MSC313E + F22,wire + wifi  ip onvif camera,IP Card camera....
	MODEL_HA_8205M		= 0x300b,		// (base)MSC313E + F22,wire + wifi + pt(just 1 moto) + alarm host ip onvif camera,IP Card camera.... just one moto
	MODEL_HA_8501ME		= 0x300c,		// (english)MSC313E + F22,wire + wifi ip onvif camera
	MODEL_HA_8403ME		= 0x300d,		// (english)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker
	MODEL_HA_8403MEV2	= 0x300d,		// (english)Same with MODEL_HA_8403M,except wifi (9083H)
	MODEL_HA_8403MEV3	= 0x300d,		// (english)Same with MODEL_HA_8403M,except wifi (mt7601)
	MODEL_HA_8402M		= 0x300e,		// (base:IPCam Module)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker,no light AD
	MODEL_HA_8250MV2	= 0x300f,		// (base)(MODEL_HA_8250M V2)MSC313E + F22,wire + wifi  ip onvif camera,IP Card camera....
	MODEL_HA_8303MV2	= 0x3010,		// (base)HA-8303M Cost down version,NO eth.MSC313E + PS5270,wire + wifi ip onvif camera,fisheye camera...
	MODEL_HA_8501MV3	= 0x3011,		// (base)MSC313E + F22,wire ,(no wifi) ip onvif camera
	MODEL_HA_8403MSV2	= 0x3012,		// (base)MSC313E + PS5280,wire + wifi ip onvif camera ,no mic ,no speaker ,HA-8403MSV2,M - MStar, S : star light level ipcam,V2 : PS5280
	MODEL_HA_8405M		= 0x3013,		// Fake Hikvision model IPCam. (base)MSC313E + F22,wire + wifi ip onvif camera
	MODEL_HA_9201M      = 0x3014,       // (base)MSC313E + F22,wire + wifi ip onvif camera
	MODEL_HA_8402ME		= 0x3015,		// ((english):IPCam Module)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker,no light AD
	MODEL_HA_8203ME		= 0x3016,		// (english)MSC313E + F22,wire + wifi + pt ip onvif camera	, No prompt tone
	MODEL_HA_8203MEV2	= 0x3016,		// (english)Hardware is same with HA-8203ME, except WIFI(9083H)
	MODEL_HA_8303MV3	= 0x3017,		// (base)MSC313E + PS5270,wire + wifi mt7601 ip onvif camera,fisheye camera...
	MODEL_HA_8303MEV3	= 0x3018,		// (english)MSC313E + PS5270,wire + wifi mt7601 ip onvif camera,fisheye camera...
	MODEL_HA_8404MEV1	= 0x3019,		// ((english):IPCam Module)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker, light AD
	MODEL_HA_8404MV2	= 0x301a,		// ((base):IPCam Module)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker, light AD
	MODEL_HA_8404MEV2	= 0x301b,		// ((english):IPCam Module)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker, light AD
	MODEL_HA_8303MV4	= 0x301c,		// (base)MSC313E + PS5270,wire + wifi mt7601 ip onvif camera,fisheye camera...
	MODEL_HA_8303MEV4	= 0x301d,		// (english)MSC313E + PS5270,wire + wifi mt7601 ip onvif camera,fisheye camera...
	MODEL_HA_8205MV1	= 0x301e,		// (base GM)MSC313E + F22,wire + wifi + pt(just 1 moto) + alarm host ip onvif camera,IP Card camera.... just one moto  
	MODEL_HA_8205MV2	= 0x301e,		// (base GM)Same with 8205MV1, instead of Wifi(mt7601)
	MODEL_HA_8402MS     = 0x301f,       // (base)MSC313E + PS5280,wire + wifi ip onvif camera ,no mic ,no speaker ,HA-8402MS,M - MStar, S : star light level ipcam : PS5280
	MODEL_HA_8405ME		= 0x3020,		// (english)Fake Hikvision model IPCam. (base)MSC313E + F22,wire + wifi ip onvif camera
	MODEL_HA_8404MV3	= 0x3021,		// ((base):IPCam Module)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker, light AD positive feedback
	MODEL_HA_8404MEV3	= 0x3022,		// ((english):IPCam Module)MSC313E + F22,wire + wifi ip onvif camera ,no mic ,no speaker, light AD positive feedback
	MODEL_HA_8302M	    = 0x3023,		// (base)MSC313E + PS5270,wire + wifi ip onvif camera,fisheye camera...
	MODEL_HA_8204MT		= 0x3024,		// (thailand)MSC313E + F22,wire + wifi + pt + alarm host ip onvif camera  T:Thailand
	MODEL_HA_8303MEV2	= 0x3025,		// (english)HA-8303M Cost down version,NO wifi. MSC313E + PS5270,wire ip onvif camera,fisheye camera...
	MODEL_HA_8501MV4	= 0x3026,		// (base)MSC313E + F22,wire + wifi mt7601 ip onvif camera
	MODEL_HA_8501MEV4	= 0x3027,		// (english)MSC313E + F22,wire + wifi mt7601 ip onvif camera
	MODEL_HA_8501MEV3	= 0x3028,		// (english)MSC313E + F22,wire ,(no wifi) ip onvif camera
	MODEL_HA_8304M		= 0x3029,		// (base)MSC313E + PS5270,wire + wifi mt7601 ip onvif camera,fisheye camera...no light AD,no Alarm host
	MODEL_HA_8304MV2	= 0x3029,		// (base) The same with MODEL_HA_8304M except wifi:(8188etv)
	MODEL_HA_8303MV5	= 0x302a,		// (base)MSC313E + PS5270,wire + wifi rtl8188 ip onvif camera,fisheye camera...
	MODEL_HA_8406M      = 0x302b,		// (base)MSC313E + F22,wire + wifi mt7601 ip onvif camera
	MODEL_HA_8303MRV5	= 0x302c,		// (Russian Vidos)MSC313E + PS5270,wire + wifi rtl8188 ip onvif camera,fisheye camera...
	MODEL_HA_8303MRV4	= 0x302c,		// (Russian Vidos)The same with MODEL_HA_8303MRV5, except wifi(mt7601)
	MODEL_HA_8404MV4	= 0x302d,		// ((base):IPCam Module)MSC313E + GC2053,wire + wifi mt7601 ip onvif camera ,no mic ,no speaker, light AD positive feedback
	MODEL_HA_8404MV5	= 0x302d,		// ((base):IPCam Module)The Same With 8404MV4 except wifi use(S9083H)
	MODEL_HB_8404MV5	= 0x302d,		// ((base):IPCam Module)The Same With MODEL_HA_8404MV5 HB:flash 8M
	MODEL_HA_830XM      = 0x302e,		// (base HaoCheng)MSC313E + PS5270,wire + wifi rtl8188 ip onvif camera,fisheye camera...
	MODEL_HA_8303MV5D	= 0x302f,		// (DaoJianChou)MSC313E + PS5270,wire + wifi rtl8188 ip onvif camera,fisheye camera...
	MODEL_HA_8501MEV5	= 0x3030,		// (english)MSC313E + GC2053,wire + wifi S9083H ip onvif camera   (8M flash)
	MODEL_HA_8204ME		= 0x3031,		// (english)MSC313E + F22,wire + wifi + pt + alarm host ip onvif camera
	MODEL_HA_8406MV1    = 0x3032,		// (base)MSC313E + F22,wire + wifi S9083H ip onvif camera
	MODEL_HA_8407M      = 0x3032,		// (base)MSC313E + F22,wire + wifi S9083H ip onvif camera
	MODEL_HA_8402MSV2   = 0x3033,       // (base)MSC313E + PS5280,wire + wifi ip onvif camera ,no mic ,no speaker,no light AD
	MODEL_HA_8303MV6	= 0x3034,		// (base)Hardware is same with HA-8303MV2, Add wifi and 4G modules
	MODEL_HA_8303MV7	= 0x3034,		// (base)Hardware is same with HA-8303MV2, Add wifi (9083H) and 4G modules
	MODEL_HA_8303MEV6	= 0x3035,		// (english)Hardware is same with HA-8303MEV2, Add wifi (8188) and 4G modules
	MODEL_HA_8303MEV7	= 0x3035,		// (english)Hardware is same with HA-8303MEV2, Add wifi (9083H) and 4G modules
	MODEL_HA_8406ME     = 0x3036,		// (english)MSC313E + F22,wire + wifi mt7601 ip onvif camera
	MODEL_HA_8406MEV1   = 0x3037,		// (english)MSC313E + F22,wire + wifi S9083H ip onvif camera
	MODEL_HA_8407ME     = 0x3037,		// (english)MSC313E + F22,wire + wifi S9083H ip onvif camera
	MODEL_HA_8303MV6G	= 0x3038,		// (GuangDian)Hardware is same with HA_8303MV6
	MODEL_HA_8303MV4G	= 0x3039,		// (GuangDian)Hardware is same with HA_8303MV4  wifi:(mt7601)
	MODEL_HA_8303MV5G	= 0x303a,		// (GuangDian)Hardware is same with HA_8303MV5  wifi:(rtl8188)
	MODEL_HA_8205MEV1	= 0x303b,		// (english GM)MSC313E + F22,wire + wifi + pt(just 1 moto) + alarm host ip onvif camera,IP Card camera.... just one moto  
	MODEL_HA_8205MEV2	= 0x303b,		// (english GM)Same with 8205MEV1, instead of Wifi(mt7601) moto  
	MODEL_HB_8404MGV5	= 0x303c,		// ((base Greece):IPCam Module)The Same With MODEL_HB_8404MV5 HB:flash 8M  H.264
	MODEL_HB_8404MEV5	= 0x303d,		// ((english):IPCam Module)The Same With MODEL_HB_8404MV5 HB:flash 8M
	MODEL_HA_8304ME		= 0x303e,		// (english)MSC313E + PS5270,wire + wifi mt7601 ip onvif camera,fisheye camera...no light AD,no Alarm host
	MODEL_HA_8304MEV2	= 0x303e,		// (english)The same with MODEL_HA_8304ME except wifi(8188etv)
	MODEL_HA_8303MV6H	= 0x303f,		// (base HaoCheng)Hardware is same with HA-8303MV2, Add wifi and 4G modules
	MODEL_HA_8303MV4D	= 0x3040,		// (DaoJianChou)MSC313E + PS5270,wire + wifi mt7601 ip onvif camera,fisheye camera...
	MODEL_HA_8303MV6D	= 0x3041,		// (DaoJianChou)Hardware is same with HA-8303MV2, Add wifi rtl8188
	MODEL_HA_8303MV4I	= 0x3042,		// (Indian)Same with HA-8303MEV4 except wifi:(9083) Zone info:(Calcutta)   
	MODEL_HA_8404MV6	= 0x3043,		// ((base):The same with MODEL_HA_8404MV4 except light AD Control
	MODEL_HA_8404MV7	= 0x3043,		// ((base):The same with MODEL_HA_8404MV4 except wifi(8188etv) light AD Control
	MODEL_HA_8404MEV6	= 0x3044,		// ((base):The same with MODEL_HA_8404MV4 except light AD Control
	MODEL_HA_8404MEV7	= 0x3044,		// ((base):The same with MODEL_HA_8404MV4 except wifi(8188etv) light AD Control
	MODEL_HA_8304MR		= 0x3045,		// (Russian Vidos)MSC313E + PS5270,wire + wifi mt7601 ip onvif camera,fisheye camera...no light AD,no Alarm host
	MODEL_HA_8304MRV2	= 0x3045,		// (Russian Vidos)The same with MODEL_HA_8304MR except wifi(8188etv)
	MODEL_HA_8404MRV6	= 0x3046,		// (Russian Vidos):The same with MODEL_HA_8404MEV6 except TimeZone:GMT+3
	MODEL_HA_8403MIV2	= 0x3047,		// (Italy)Same with MODEL_HA_8403M,except wifi (9083H)
	MODEL_HA_8403MI 	= 0x3047,		// (Italy)Same with MODEL_HA_8403M,except wifi (8188eus)

	

	MODEL_HA_8406S      = 0x3301,       // (base)SSC335+SC4236,wire + wifi(rtl8188fu) ip onvif camera
	MODEL_HA_8406SV1    = 0x3301,       // (base)Same with MODEL_HA_8406S , except wifi:rtl8188etv
	MODEL_HA_8501S      = 0x3302,       // (base)SSC335+GC2053,wire + wifi(rtl8188etv) ip onvif camera
	MODEL_HA_8501SV1    = 0x3302,       // (base)Same with MODEL_HA_8501S , except wifi:rtl8188ftv
	MODEL_HA_8306S      = 0x3303,       // (base)SSC335+SC4236,wire + wifi(rtl8188etv) + alarm host ip onvif camera
	MODEL_HA_8306SV1    = 0x3303,       // (base)Same With MODEL_HA_8306S,  wifi:rtl8188ftv
	MODEL_HA_8206S      = 0x3304,       // (base)SSC335+GC2053,wire + wifi(rtl8188etv)+ pt ip onvif camera
	MODEL_HA_8206SV1    = 0x3304,       // (base)Same with MODEL_HA_8206S , except wifi:rtl8188ftv
	MODEL_HA_8206STV1   = 0x3304,       // (base)Same with MODEL_HA_8206SV1, Tuya Version
	MODEL_HA_8207S      = 0x3304,       // (base)Same with MODEL_HA_8206S
	MODEL_HA_8207SV1    = 0x3304,       // (base)Same with MODEL_HA_8206S , except wifi:rtl8188ftv
	MODEL_HA_8207STV1   = 0x3304,       // (base)Same with MODEL_HA_8206SV1, Tuya Version
	MODEL_HA_8404S      = 0x3305,       // (base)SSC335+GC2053,wire + wifi(rtl8188etv) ip onvif camera
	MODEL_HA_8404SV1    = 0x3305,       // (base)Same with MODEL_HA_8404S , except wifi:rtl8188ftv
	MODEL_HA_8706S      = 0x3306,       // (base)SSC335+GC2053,wire + wifi(rtl8188ftv) + Emergency Button ip onvif camera
	MODEL_HA_8405S      = 0x3307,       // (base)SSC335+GC2053,wire + wifi(rtl8188ftv)
	MODEL_HA_8501SEV1   = 0x3308,       // (english)SSC335+GC2053,wire + wifi(rtl8188ftv) ip onvif camera
	MODEL_HA_8407S      = 0x3309,       // (base)SSC335+GC2053,wire + wifi(rtl8188ftv) ip onvif camera
	MODEL_HA_8501SIV1   = 0x330a,       // (Italy)SSC335+GC2053,wire + wifi(rtl8188ftv) ip onvif camera
	MODEL_HA_8404SEV1   = 0x330b,       // (english)SSC335+GC2053,wire + wifi(rtl8188etv) ip onvif camera
	MODEL_HA_8207SEV1   = 0x330c,       // (english)SSC335+GC2053,wire+wifi(rtl8188ftv)+pt ip onvif camera 
	MODEL_HA_8207STEV1  = 0x330c,       // (english)Same with MODEL_HA_8207SEV1, Tuya Version


	MODEL_HA_8402M5M    = 0x4000,        // (base)MSC316DM + PS5510 (5M), wire + wifi ip onvif camera ,no mic ,no speaker

	MODEL_HA_8501H		= 0x4100,		// (base)HI3516EV200 + GC2053,wire + wifi ip onvif camera
	MODEL_HA_8404H		= 0x4101,		// (base)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8501HV2	= 0x4102,		// (base)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8501HV3	= 0x4102,		// (base)The same as MODEL_HA_8501HV2, except wifi (mt7601)
	MODEL_HA_8501HV4	= 0x4102,		// (base)The same as MODEL_HA_8501HV2, except wifi (rtl8188fu)
	MODEL_HA_8404HE		= 0x4103,		// (english)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8501HEV2	= 0x4104,		// (english)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8501HEV3	= 0x4104,		// (base)The same as MODEL_HA_8501HEV2, except wifi (mt7601)
	MODEL_HA_8501HEV4	= 0x4104,		// (base)The same as MODEL_HA_8501HEV2, except wifi (rtl8188fu)
	MODEL_HA_8406H	    = 0x4105,		// (base)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8406HE	    = 0x4106,		// (english)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8404HG		= 0x4107,		// (base Greece)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif  H.264 camera
	MODEL_HA_8405H      = 0x4108,       // (base)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8405HE     = 0x4109,       // (base)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8705H      = 0x410a,       // (base)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8705HE     = 0x410b,       // (english)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8306H      = 0x410c,       // (base)16EV200+SC4236, fisheye wire+wifi(9083H)+4G(EC20) ip onvif camera
	MODEL_HA_8407HE	    = 0x410d,		// (english)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera
	MODEL_HA_8501HRV4	= 0x410e,		// (Russian Vidos)HI3516EV200 + GC2053,wire + wifi (rtl8188fu) ip onvif camera
	MODEL_HA_8406HI	    = 0x410f,		// (Italy)HI3516EV200 + GC2053,wire + wifi (9083H) ip onvif camera


	MODEL_HB_8405H		= 0x4200,		// (base)HI3518EV300 + GC2053,wifi ip onvif camera
	MODEL_HB_8406H		= 0x4201,		// (base)HI3518EV300 + GC2053,wifi (9083H) ip onvif camera
	MODEL_HB_8406HV2	= 0x4202,		// (base)HI3518EV300 + GC2053,wifi (8188eus) ip onvif camera
	MODEL_HB_8407H	    = 0x4203,		// (base)HI3518EV300 + GC2053,wifi (8188eus) ip onvif camera
	MODEL_HB_8407HE	    = 0x4204,		// (english)HI3518EV300 + GC2053,wifi (8188eus) ip onvif camera
	MODEL_HB_8406HEV2	= 0x4205,		// (english)HI3518EV300 + GC2053,wifi (8188eus) ip onvif camera


	MODEL_HA_8405HA		= 0x4300,		// (base)HI3516CV500 + GC2053,DDR:256MiB,Nand flash:256MiB,HA:hisilicon advance Soc,Ai + wifi ip onvif camera
	MODEL_HA_8405HAV2	= 0x4301,		// (base)HI3516CV500 + IMX307,DDR:256MiB,Nand flash:256MiB,HA:hisilicon advance Soc,Ai + wifi ip onvif camera
	MODEL_HA_8705HB		= 0x4302,		// (base)(HB : hisilicon soc + body detect)Sensetime body detect func  : HI3516CV500 + GC2053,DDR:256MiB,Nand flash:256MiB,HA:hisilicon advance Soc,Ai + wifi ip onvif camera

	MODEL_HA_7100HAD	= 0x4400,		// (base)HI3516DV300 + 2 IMX307,DDR:512MiB,eMMC:8GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...

	MODEL_HA_7100HADV2	= 0x4401,		// (base)HI3516DV300 + 2 IMX307,DDR:512MiB,eMMC:8GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// meian 1GiB ddr

	MODEL_HA_7100HADV3	= 0x4402,		// (base)HI3516DV300 + 2 IMX307,DDR:512MiB,eMMC:8GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr
	MODEL_HA_7100HADV4	= 0x4403,		// (base)HI3516DV300 + 2 IMX307,DDR:512MiB,eMMC:8GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 1024*600...
										// haiqing 1GiB ddr	
	MODEL_HA_7100HADV5	= 0x4404,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ body temperature sensor module

	MODEL_HA_7100HADV6	= 0x4405,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module

	MODEL_HA_7100HADV7	= 0x4406,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module +  body temperature sensor module
										// LCD param same with MODEL_HA_7100HADV6

	MODEL_HA_7100HADV8	= 0x4406,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module +  body temperature sensor module
										// LCD param same with MODEL_HA_7100HADV5

	// same with MODEL_HA_7100HADV2
	MODEL_HA_7100HADV9	= 0x4401,		// (base)HI3516DV300 + 2 IMX307,DDR:512MiB,eMMC:8GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 480*854... size : 5Inch
										// input : touchscreen...
										// meian 512MiB ddr
	
	MODEL_HA_7100HADVA	= 0x4405,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module
										// product name : HA-7100HAA
	MODEL_HA_7100HADVB	= 0x4406,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module +  body temperature sensor module
										// LCD param same with MODEL_HA_7100HADVA
										// product name : HA-7100HAB

	MODEL_HA_7100HADVC	= 0x4407,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module +  body temperature sensor module
										// product name : HA-7100HAC
										// AP6256 SDIO interface wifi + bluetooth module

	MODEL_HA_7100HADVE	= 0x4408,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module {Same with MODEL_HA_7100HADVC,NO BODY TEMPERATURE}
										// product name : HA-7100HAC
										// AP6256 SDIO interface wifi + bluetooth module


	MODEL_HA_7100HADVF	= 0x4409,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module {Same with MODEL_HA_7100HADVE,different: WIFI(Hi3881)}
										// product name : HA-7100HAF
										// Hi3881 SDIO interface wifi + bluetooth module
										// lifan@2021.07.12	
	MODEL_HA_7100HADVG	= 0x440a,		// (base)HI3516DV300 + 2 IMX307,DDR:1GiB,eMMC:16GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...
										// haiqing 1GiB ddr	+ Qr Code module {Same with MODEL_HA_7100HADVC,different: WIFI(Hi3881)}
										// product name : HA-7100HAG, body temperature sensor module
										// Hi3881 SDIO interface wifi + bluetooth module
										// lifan@2021.08.03	

	
	
	////////////////////////////////////////////////////////////////////////////////////////////

	MODEL_HA_7200HA		= 0x4410,		// (base)HI3516DV300 + 2 IMX307,DDR:512MiB,eMMC:8GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280...  size : 10Inch
										// input : touchscreen...
										// meian 512MiB ddr
	MODEL_HA_7201HA		= 0x4411,		// (base)HI3516DV300 + 2 IMX307,DDR:512MiB,eMMC:8GiB,
										// HA:hisilicon advance Soc,Ai + wifi ip onvif camera,
										// Double eyes Access control system
										// MIPI LCD output... 800*1280(MQ080JGI30)... size : 8Inch
										// NO input 
										// meian 512MiB ddr


	MODEL_HA_8403F   	= 0x4500,		// FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// 38*38 board
	MODEL_HA_8406F   	= 0x4501,		//  FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// Reset btn + sound light
	MODEL_HA_8706F   	= 0x4502,		//  FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										//  sound light
	MODEL_HA_8207F   	= 0x4503,		//  FH8852 + SC200AI,PT + WIFI ( RTL8188FU)
										//  no wire RJ-45 interface
	MODEL_HA_8706FV2   	= 0x4504,		//  FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										//  sound light
	MODEL_HA_8501F   	= 0x4505,		//  FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
	MODEL_HA_8501FE   	= 0x4506,		//  (english) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
	MODEL_HA_8403FV2   	= 0x4507,		// FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// smile face model board,
										// no audio input/output
										// no reset btn
										// no sound light
	MODEL_HA_8403FEV2   = 0x4508,		// (english) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// smile face model board
	MODEL_HA_8404FG   	= 0x4509,		// (Greece) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// 38*38 board
										// default Video encode type:H.264
										// Greece time zone ,GMT+2
										// DST(Daylight saving time) ENABLE,
										// see "/mnt/app/zoneinfo/Etc/Athens"

	MODEL_HA_8404FE   	= 0x450a,		// (english) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// 38*38 board
										// NO DST

	MODEL_HA_8406FB   	= 0x450b,		// (english) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// Bengal time zone, GMT+6
										// NO DST
	
	MODEL_HA_8406FE   	= 0x450c,		// (english) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// Bengal time zone, GMT-0
										// NO DST
	MODEL_HA_8406FF   	= 0x450d,		// (english) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// France time zone, GMT+1
										// DST Enabled...


	MODEL_HA_8404FV2   	= 0x450e,		// (4G) FH8852 + SC200AI,Wire + 4G ( AC7680C)
										// 38*48? board


	MODEL_HA_8404FV3   	= 0x450f,		// FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// 38*38 board	

	MODEL_HA_8404FV4   	= 0x4510,		// (4G) FH8852 + GC2063,Wire + 4G ( AC7680C)
										// 38*48? board

	MODEL_HA_8501FI   	= 0x4511,		//  (italy) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// NO DST
	MODEL_HA_8406FI   	= 0x4512,		// (italy) FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										// Bengal time zone, GMT-0
										// NO DST

	MODEL_HA_8404FV5   	= 0x4513,		// FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// 38*38 board	
										// Same with MODEL_HA_8404FV3
										// Just Mirror/flip ON

	MODEL_HA_8404FEV2   = 0x4514,		// (english)FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// 38*38 board	
										// Same with MODEL_HA_8404FV5
										// Just Mirror/flip ON
	MODEL_HA_8404FEV3  	= 0x4515,		// FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// 38*38 board	
										// Same with MODEL_HA_8404FV3
										// Just Mirror/flip ON

	MODEL_HA_8706FEV2   = 0x4516,		//  FH8852 + SC200AI,Wire + WIFI ( RTL8188FU)
										//  sound light
										//  same with MODEL_HA_8706FV2

	MODEL_HA_8207FE   	= 0x4517,		//  FH8852 + SC200AI,PT + WIFI ( RTL8188FU)
										//  no wire RJ-45 interface
										//  same with MODEL_HA_8207F

	MODEL_HA_8404FI   	= 0x4518,		// FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// 38*38 board	
										// Same with MODEL_HA_8404FV5
										// Just Mirror/flip ON
										// copy from MODEL_HA_8404FV5,italy version

	MODEL_HA_8501FV2   	= 0x4519,		//  FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// same with MODEL_HA_8501F,
										// just sensor difference
										// This product use GC2063,
										// MODEL_HA_8501F use SC200AI,
										// lifan@2022.06.08

	MODEL_HA_8406FV2   	= 0x451a,		// FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
									    // Reset btn + sound light
										// same with MODEL_HA_8406F,
										// just sensor difference
										// This product use GC2063,
										// MODEL_HA_8406F use SC200AI,
										// lifan@2022.06.08

	MODEL_HA_8501FIV2   = 0x451b,		//  FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// same with MODEL_HA_8501FI,
										// just sensor difference
										// This product use GC2063,
										// MODEL_HA_8501FI use SC200AI,
										// lifan@2022.06.08
										// italy version
	MODEL_HA_8501FEV2   = 0x451c,		//  FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// same with MODEL_HA_8501FE,
										// just sensor difference
										// This product use GC2063,
										// MODEL_HA_8501FE use SC200AI,
										// lifan@2022.06.08
										// englist version
	
	MODEL_HA_8406FEV2   = 0x451d,		//  FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// same with MODEL_HA_8406FE,
										// just sensor difference
										// This product use GC2063,
										// MODEL_HA_8406FE use SC200AI,
										// lifan@2022.06.08
										// englist version

	
	MODEL_HA_8404FGV2   = 0x451e,		// (Greece) FH8852 + GC2063,Wire + WIFI ( RTL8188FU)
										// 38*38 board
										// default Video encode type:H.264
										// Greece time zone ,GMT+2
										// DST(Daylight saving time) ENABLE,
										// see "/mnt/app/zoneinfo/Etc/Athens"
										// Same with MODEL_HA_8404FV5

	
	/////////////////////////////////////////////////////////////////////////////

	/**************************************************/ 
	/*                FH8852V200 model                */
	/*	FH8852 model version  suffix : 2,3,4,5...F... */
	/*	FH8852V200 model version  suffix : z,y,x....  */
	/**************************************************/ 

	MODEL_HA_8403FVZ   	= 0x4580,		// (base) FH8852V200 + SC200AI,Wire + WIFI ( RTL8188FU)
	MODEL_HA_8404FVZ   	= 0x4581,		// (base) FH8852V200 + GC4663,Wire + 4G Module ( AC7680C) + ALARM Host
	MODEL_HA_8404FVY   	= 0x4582,		// (base) FH8852V200 + GC2063,Wire + WIFI ( RTL8188FU) + ALARM Host


/////////////////////////////////////////////////////////////////////////////

	/**************************************************/ 
	/*                FH8852V201 model                */
	/*	FH8852 model version  suffix : 2,3,4,5...F... */
	/*	FH8852V200 model version  suffix : z,y,x....  */
	/*	FH8852V201 model version  suffix : a1,a2,a3....  */
	/**************************************************/ 

	MODEL_HA_8404FA   	= 0x45A0,		// (base) FH8852V201 + GC2063,Wire + WIFI ( RTL8188FU)
	MODEL_HA_8406FA   	= 0x45A1,		// (base) FH8852V201 + GC2063,Wire + WIFI ( RTL8188FU)
	MODEL_HA_8406FAEC  	= 0x45A2,		// (base) FH8852V201 + GC2063,Wire + WIFI ( RTL8188FU)
										// AREA : ecuador GMT-5 (Beijing GMT+8)
										// Language : english


	
	
	MODEL_HA_QRJMF		= 0x4600,		// FH8626 + EC20 + QrCode reader for jinmao project 
							// lifan @ 2021.06.18 

	//SDK V1.0  BEGIN
	MODEL_HA_8409E      = 0x5000,       // (base)EeasyTech SV823+IMX307
	MODEL_HA_8409EV1    = 0x5001,       // (base)EeasyTech SV823+SC200AI
	MODEL_HA_8706E      = 0x5002,       // (base)EeasyTech SV823+SC200AI
	MODEL_HA_8705E      = 0x5003,       // (base)EeasyTech SV823+SC200AI+4G(A7670C)+Alarm
	MODEL_HA_8706EV2    = 0x5004,       // (base)EeasyTech SV823+GC4663
	MODEL_HA_8705EV2    = 0x5005,       // (base)EeasyTech SV823+SC200AI+POE+Relay+wifi(8188ftv)
	//SDK V1.0  END

	//SDK V1.1
	MODEL_HA_8410E      = 0x5100,       // (base)EeasyTech SV823+SC200AI+Face Detect
	MODEL_HA_8705EV3    = 0x5101,       // (base)EeasyTech SV823+SC200AI+Face Detect +POE+Relay+wifi(8188ftv)
	MODEL_HA_8208E      = 0x5102,       // (base)EeasyTech SV823+SC200AI+Face Detect + PTZ 
	MODEL_HA_8208EV2    = 0x5103,       // (base)EeasyTech SV823+GC4663 +Face Detect + PTZ 
	MODEL_HA_8208EHV2   = 0x5104,       // (base)EeasyTech SV823+GC4663 +Face Detect + PTZ + HuiYun
	MODEL_HA_8206E      = 0x5105,       // (base)EeasyTech SV823+SC200AI+Face Detect + PTZ +4G(A7680C) 
	MODEL_HA_8206EV2    = 0x5106,       // (base)EeasyTech SV823+GC4663 +Face Detect + PTZ +4G(A7680C) 
	MODEL_HA_8206EHV2   = 0x5107,       // (base)EeasyTech SV823+GC4663 +Face Detect + PTZ +4G(A7680C) + HuiYun
	MODEL_HA_8208EH     = 0x5108,       // (base)EeasyTech SV823+SC200AI+Face Detect + PTZ + HuiYun
	MODEL_HA_8206EH     = 0x5109,       // (base)EeasyTech SV823+SC200AI+Face Detect + PTZ +4G(A7680C) + HuiYun
	MODEL_HA_8705EH     = 0x510A,       // (base)EeasyTech SV823+SC200AI+4G(A7670C)+Alarm + HuiYun + Electronic Sentry
	MODEL_HA_8407EH     = 0x510B,       // (base)EeasyTech SV823+SC200AI+4G(A7680C)+Alarm + HuiYun + Electronic Sentry
	MODEL_HA_8208EHV3   = 0x510C,       // (base)EeasyTech SV823+SC200AI+Face Detect + PTZ + HuiYun + Electronic Sentry
	MODEL_HA_8705EV4    = 0x510D,       // (base)EeasyTech SV823+GC4663+Face Detect +POE+Relay+wifi(8188ftv)
	MODEL_HA_8407EHV2   = 0x510E,       // (base)EeasyTech SV823+SC200AI+4G(A7680C)+Alarm + HuiYun + Electronic Sentry
	MODEL_HA_8408EH     = 0x510F,       // (base)EeasyTech SV823+GC4663 + HuiYun
	MODEL_HA_8407EV2    = 0x5110,       // (base)EeasyTech SV823+SC200AI+4G(A7680C)+Alarm
	MODEL_HA_8705EV5    = 0x5111,       // (base)EeasyTech SV823+SC200AI+4G(A7670C)+Alarm
	MODEL_HA_8706EEV3   = 0x5112,       // (english)EeasyTech SV823+GC4663+Face Detect


}MODEL;

typedef enum{
	COUNTRY_TYPE_CHINESE = 0,
	COUNTRY_TYPE_USA,
}COUNTRY;

typedef enum{
	ENUM_WIFI_CHIP_NONE     = 0,
	ENUM_WIFI_CHIP_MT7601U  = 1,
	ENUM_WIFI_CHIP_RTL8188X = 2,
	ENUM_WIFI_CHIP_S9083H   = 3,
	ENUM_WIFI_CHIP_RTL8188FU= 4,
	ENUM_WIFI_CHIP_AP6256_SDIO   = 5, // broadcom Soc,sdio interface ,connected with MMC2 host 
										//lifan@2021.04.21
	ENUM_WIFI_CHIP_HI3881_SDIO   = 6, // Hisilicon Soc,sdio interface ,connected with MMC2 host 
										//lifan@2021.07.12										
}WIIF_CHIP_TYPE;

typedef enum{
	P2P_PLATFORM_TUTK = 0x1000,
	P2P_PLATFORM_TX,
	P2P_PLATFORM_MT,

}P2P_PLATFORM;

typedef enum{
	ENUM_4G_MODULE_NONE = 0,
	ENUM_4G_MODULE_EC20 = 1,
	ENUM_4G_MODULE_A7670C = 2,
	ENUM_4G_MODULE_A7680C = 3,
}ENUM_4G_MODULE_TYPE;

struct CProductConfig
{
public:
	std::string 	name;
	int				model;
	int				sensorChip;
	int				wifiChip;
	int 			country; // ENUM_LANGUAGE_TYPE
	int				supportSdCard;
	int				supportCloudStorage;
	int				supportPt;
	int				supportZoom;
	int				supportAF;
	int				supportAudioCap;
	int				supportTalk;
	int				supportOnvif;
	int				supportCgiCmd;
	int				supportRtsp;
	int				supportRtmp;
	int				p2pPlatform;
	int				flag1;      // ENUM_4G_MODULE_TYPE
	int				flag2;
	int				flag3;
	int				flag4;

public:
    template< class archive >
    void serialize ( archive &ar, const unsigned ver )
    {
        ar &BOOST_SERIALIZATION_NVP ( name );
        ar &BOOST_SERIALIZATION_NVP ( model );
        ar &BOOST_SERIALIZATION_NVP ( sensorChip );
        ar &BOOST_SERIALIZATION_NVP ( wifiChip );
        ar &BOOST_SERIALIZATION_NVP ( country );
        ar &BOOST_SERIALIZATION_NVP ( supportSdCard );
        ar &BOOST_SERIALIZATION_NVP ( supportCloudStorage );
        ar &BOOST_SERIALIZATION_NVP ( supportPt );
        ar &BOOST_SERIALIZATION_NVP ( supportZoom );
        ar &BOOST_SERIALIZATION_NVP ( supportAF );
        ar &BOOST_SERIALIZATION_NVP ( supportAudioCap );
        ar &BOOST_SERIALIZATION_NVP ( supportTalk );
        ar &BOOST_SERIALIZATION_NVP ( supportOnvif );
        ar &BOOST_SERIALIZATION_NVP ( supportCgiCmd );
        ar &BOOST_SERIALIZATION_NVP ( supportRtsp );
        ar &BOOST_SERIALIZATION_NVP ( supportRtmp );
        ar &BOOST_SERIALIZATION_NVP ( p2pPlatform );
        ar &BOOST_SERIALIZATION_NVP ( flag1 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );
        ar &BOOST_SERIALIZATION_NVP ( flag3 );
        ar &BOOST_SERIALIZATION_NVP ( flag4 );
        ar &BOOST_SERIALIZATION_NVP ( flag2 );

    }
};


class CProduct{
public:
	CProduct();
	virtual ~CProduct();
	const char * name();
	int model();
	int sensor();
	int	wifiType();
	int country();
	int	isSupportSdCard();
	int	isSupportCloudStorage();
	int	isSupportPt();
	int	isSupportZoom();
	int	isSupportAF();
	int	isSupportAudioCap();
	int	isSupportTalk();
	int	isSupportOnvif();
	int	isSupportCgiCmd();
	int	isSupportRtsp();
	int	isSupportRtmp();
	int	p2pPlatform();


	
    void loadConfig();
    void saveConfig();
    void genDefConfig();

public:
	struct CProductConfig  m_stConfig;
	static pthread_mutex_t m_lock;
};




typedef enum{
	// See commFunc.cpp COMM_FUNC::isWirelessNVRSuitIPC
	// add by lifan @2022.06.30
	enum_product_flag4_wireless_nvr_suit_ipcam = (1 << 0),  
}ENUM_PRODUCT_FLAG4;





#endif //__CPRODUCT_H__




