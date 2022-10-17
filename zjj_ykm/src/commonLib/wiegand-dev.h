#ifndef __WIEGAND_DEV_H__
#define __WIEGAND_DEV_H__





/***************WIEGAND_DEV ioctl cmd********************/
#define IOC_TYPE_WIEGAND_DEV 'W'


typedef enum{
	enum_wiegand_26 	= 26,
	enum_wiegand_34     = 34,
}ENUM_WIEGAND_MODE;

typedef enum {
	IOC_NR_WIEGAND_DEV_SET_DATA0_DATA1_GPIO		 = 0,
	IOC_NR_WIEGAND_DEV_GET_DATA0_DATA1_GPIO	,
	IOC_NR_WIEGAND_DEV_SET_OUTPUT_VAL,

}WIEGAND_DEV_IOCTL_E;

struct WIEGAND_DEV_GPIO_GROUP{
	int data0;
	int data1;
};



struct WIEGAND_DEV_OUTPUT_REQ{
	uint32_t bits; // 26 : wiegand 26; 34 wiegand 34
	uint32_t val;  // low 32bit
	uint32_t val2; // higt 32bit
};

struct WIEGAND_DEV_CURRENT_OUTPUT_CONTEXT{
	uint32_t enable;
	uint32_t irq_cnt;
	uint32_t irq_max_cnt;
	struct WIEGAND_DEV_OUTPUT_REQ req;
};

#define CONFIG_MAX_WIEGAND_DEV_OUTPUT_REQ_CNT 4
struct WIEGAND_DEV_OUTPUT_REQ_QUEUE{
	struct WIEGAND_DEV_OUTPUT_REQ queue[CONFIG_MAX_WIEGAND_DEV_OUTPUT_REQ_CNT];
	uint32_t count;
};

#define WIEGAND_DEV_CMD_SET_DATA0_DATA1_GPIO \
	_IOW(IOC_TYPE_WIEGAND_DEV,IOC_NR_WIEGAND_DEV_SET_DATA0_DATA1_GPIO,struct WIEGAND_DEV_GPIO_GROUP *)

#define WIEGAND_DEV_CMD_GET_DATA0_DATA1_GPIO \
	_IOR(IOC_TYPE_WIEGAND_DEV,IOC_NR_WIEGAND_DEV_GET_DATA0_DATA1_GPIO,struct WIEGAND_DEV_GPIO_GROUP *)

#define WIEGAND_DEV_CMD_SET_OUTPUT_VAL \
	_IOW(IOC_TYPE_WIEGAND_DEV,IOC_NR_WIEGAND_DEV_SET_OUTPUT_VAL,struct WIEGAND_DEV_OUTPUT_REQ)


#endif //__WIEGAND_DEV_H__

