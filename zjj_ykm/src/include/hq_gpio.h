/* 
* CopyRight (C) Tianxx 2019 tianxx@hqvt.net 
* 
* Filename: hq_gpio.h 
* 
*/
#ifndef _HQ_GPIO_H
#define _HQ_GPIO_H


// ��λ���� GPIO2_0
#define	CMD_RESET_POWER         0x51
#define	CMD_READ_RESETKEY       0x52
//����Τ������ģʽ: data =  26λ��Ĭ�ϣ�34λ ����
#define	CMD_WIEGAND_MODE	0x70
// ��ȡΤ���������� GPIO8_2/GPIO8_3
#define CMD_GET_WGDATA          0x71
// Τ����� GPIO0_5/GPIO0_6
#define CMD_WIEGAND_DATA26      0x31			 		 
#define CMD_WIEGAND_DATA34      0x32	
#define CMD_WIEGAND_DATA37      0x33 /* ��ʱδʵ�� */
// ��������1 GPIO8_4 Ŀǰ�������ֱ������룬��ǰ������������Ӧ���
#define CMD_ALM1_READ			0x60
// ��բIO GPIO8_0				
#define CMD_DOOR_CTRL           0x30		
// LCD����Դ���� GPIO8_1
#define CMD_LCD_POWER           0x7D
// LCD������ʹ�ܿ��� GPIO2_2
#define CMD_LCD_BL              0x7C
//GPIO6_7 PWM1	LCD���������ȵ���
// ������Ӧ����	GPIO10_3
#define CMD_LIGHT_SENSING		0x40
// IRCUT���� GPIO4_6 
#define CMD_IRCUT_CTRL			0x4A /* ��ʱδʹ�ã���IRCUT */
// �׹�ƿ���ʹ�� GPIO10_4
#define CMD_LIGHT_CTRL                  0x41
//GPIO6_6 PWM0 �׹����
// 4Gʹ�ܿ���
#define CMD_MOBILE_CTRL                 0xa3 // 0:�رյ�Դ 1:������Դ 
// ���ſ�������
#define CMD_ALM4_READ                   0x63
//��ȡ�ж�Դ 0:�������� 26:Τ��26���� 34:Τ��34���� 2:���������ж�����
#define	CMD_GET_IRQ_SOURCE	0x7A
// UART0 Debug
// UART1 RF����
// UART2 Bluetooth
// UART3 RS485// �������
#define CMD_ALM1_CTRL                   0x80 
// 0:�͵�ƽ   1:�ߵ�ƽ
// ����ƿ��� GPIO3_3	
#define CMD_IRLIGHT_CTRL                0x4B
// RS485�շ�����(UART3) 1:����  0:����
#define	CMD_RS485_TX		0x21
// ���ȹ��ſ���	1: ��  0:��
#define	CMD_SPEAKER_CTRL	0x20

#define HQ_GPIO_NODE      "/dev/hqvt_gpio"



#endif /* end of '#ifndef _HQ_GPIO_H' */
