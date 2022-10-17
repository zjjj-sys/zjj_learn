/**
 * @file     fh_gvbus_vbcli.h
 * @brief    gvbus client
 * @version  V0.3.4
 * @date     12-Dec-2018
 * @author   Software Team
 *
 * @note
 * Copyright (C) 2018 Shanghai Fullhan Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * @par
 * Fullhan is supplying this software which provides customers with programming
 * information regarding the products. Fullhan has no responsibility or
 * liability for the use of the software. Fullhan not guarantee the correctness
 * of this software. Fullhan reserves the right to make changes in the software
 * without notification.
 *
 */

#ifndef FH_GVBUS_CLIENT_H_
#define FH_GVBUS_CLIENT_H_

#include "types/type_def.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef RTTHREAD
#define __RTTHREAD_OS__ 1
#define __LINUX_OS__ 0
#elif defined(LINUX)
#define __RTTHREAD_OS__ 0
#define __LINUX_OS__ 1
#endif

#define GENERAL_VBUS_SERVICE_NAME "usr_vbus_serv"
#define GENERAL_VBUS_SERVICE_PRIO 120

/**
 * 初始化一个 gvbus 客户端
 * input:   none
 * return:  0 成功
            1 失败，查看打印信息
 */
FH_SINT32 FH_GVBUSCLI_init(FH_VOID);

/**
 * 反初始化一个 gvbus 客户端
 * input:   none
 * return:  0 成功
            1 失败，查看打印信息
 */
FH_SINT32 FH_GVBUSCLI_deinit(FH_VOID);

/**
 * 发送 vbus 命令
 * input:   cmd     需要运行的服务命令
 *          iobuf   输入输出缓冲指针
 *          iolen   输入输出缓冲大小
 * return:  0 成功
            1 失败，查看打印信息
 */
FH_SINT32 FH_GVBUSCLI_sendCmd(FH_UINT32 cmd, FH_UINT8 *iobuf, FH_SINT32 iolen);

/**
 * 获取库版本信息
 * input:   print_enable 打印使能
 * return:  库版本信息
 */
FH_CHAR* FH_GVBUSCLI_Version(FH_UINT32 print_enable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  // !FH_GVBUS_CLIENT_H_
