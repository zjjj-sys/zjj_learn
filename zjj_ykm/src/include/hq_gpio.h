/* 
* CopyRight (C) Tianxx 2019 tianxx@hqvt.net 
* 
* Filename: hq_gpio.h 
* 
*/
#ifndef _HQ_GPIO_H
#define _HQ_GPIO_H


// 复位按键 GPIO2_0
#define	CMD_RESET_POWER         0x51
#define	CMD_READ_RESETKEY       0x52
//设置韦根输入模式: data =  26位（默认）34位 废弃
#define	CMD_WIEGAND_MODE	0x70
// 获取韦根输入数据 GPIO8_2/GPIO8_3
#define CMD_GET_WGDATA          0x71
// 韦根输出 GPIO0_5/GPIO0_6
#define CMD_WIEGAND_DATA26      0x31			 		 
#define CMD_WIEGAND_DATA34      0x32	
#define CMD_WIEGAND_DATA37      0x33 /* 暂时未实现 */
// 报警输入1 GPIO8_4 目前用作火灾报警输入，以前用作人体红外感应检测
#define CMD_ALM1_READ			0x60
// 开闸IO GPIO8_0				
#define CMD_DOOR_CTRL           0x30		
// LCD屏电源控制 GPIO8_1
#define CMD_LCD_POWER           0x7D
// LCD屏背光使能控制 GPIO2_2
#define CMD_LCD_BL              0x7C
//GPIO6_7 PWM1	LCD屏背光亮度调节
// 光敏感应输入	GPIO10_3
#define CMD_LIGHT_SENSING		0x40
// IRCUT控制 GPIO4_6 
#define CMD_IRCUT_CTRL			0x4A /* 暂时未使用，无IRCUT */
// 白光灯控制使能 GPIO10_4
#define CMD_LIGHT_CTRL                  0x41
//GPIO6_6 PWM0 白光调节
// 4G使能开关
#define CMD_MOBILE_CTRL                 0xa3 // 0:关闭电源 1:开启电源 
// 开门开关输入
#define CMD_ALM4_READ                   0x63
//获取中断源 0:报警输入 26:韦根26输入 34:韦根34输入 2:触摸按键中断输入
#define	CMD_GET_IRQ_SOURCE	0x7A
// UART0 Debug
// UART1 RF读卡
// UART2 Bluetooth
// UART3 RS485// 报警输出
#define CMD_ALM1_CTRL                   0x80 
// 0:低电平   1:高电平
// 红外灯开关 GPIO3_3	
#define CMD_IRLIGHT_CTRL                0x4B
// RS485收发控制(UART3) 1:发送  0:接收
#define	CMD_RS485_TX		0x21
// 喇叭功放控制	1: 开  0:关
#define	CMD_SPEAKER_CTRL	0x20

#define HQ_GPIO_NODE      "/dev/hqvt_gpio"



#endif /* end of '#ifndef _HQ_GPIO_H' */
