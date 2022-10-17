#ifndef __74HC595_H__
#define __74HC595_H__





typedef struct{
	uint32_t x;
	uint32_t y;
}PTZ_POS;


typedef struct{
	struct {
		uint32_t dir;		//PTZ_DIR_XXXX
		uint32_t steps;		// 
	}h,v;
}PTZ_RUN_PARAM;


enum{
	PTZ_SPEED_VERY_SLOW	= 0,
	PTZ_SPEED_SLOW,
	PTZ_SPEED_MID,
	PTZ_SPEED_HEIGH,
	PTZ_SPEED_VERY_HEIGH,
};


enum{
	PTZ_DIR_FORWARD 	= 0,
	PTZ_DIR_BACKWARD,
	PTZ_DIR_UP,
	PTZ_DIR_DOWN,
};

enum {
	PTZ_STATUS_STOP 	= 0,
	PTZ_STATUS_RUNNING,
};


/***************74HC595 ioctl cmd********************/
#define IOC_TYPE_74HC595 'H'




typedef enum {
	IOC_NR_74HC595_SET_BIT		 = 0,
	IOC_NR_74HC595_GET_BIT,
	IOC_NR_74HC595_SET_VALUE,
	IOC_NR_74HC595_GET_VALUE,

}PTZ_IOCTL_E;

#define HC595_CMD_SET_GPO_STATUS \
	_IOW(IOC_TYPE_74HC595,IOC_NR_74HC595_SET_BIT,unsigned int)

#define HC595_CMD_GET_GPO_STATUS \
	_IOR(IOC_TYPE_74HC595,IOC_NR_74HC595_GET_BIT,unsigned int  *)


#define HC595_CMD_SET_ALL_GPO_STAUTS \
	_IOW(IOC_TYPE_74HC595,IOC_NR_74HC595_SET_VALUE,unsigned int)

#define HC595_CMD_GET_ALL_GPO_STATUS \
	_IOR(IOC_TYPE_74HC595,IOC_NR_74HC595_GET_VALUE,unsigned int *)











#define MAX_GPIO_COUNT 16

























#endif //__74HC595_H__



