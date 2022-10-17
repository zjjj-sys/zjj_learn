#ifndef _ISP_FUNC_DEF_H_
#define _ISP_FUNC_DEF_H_

#define FH_ISP_CORE_ERR_BASE            (-1000)
#define FH_API_ERR_BASE					(-3000)

#define FH_RET_OK						(0)

#define FH_ERR_ISP_NOT_INITED			(FH_ISP_CORE_ERR_BASE - 5)
#define FH_ERR_WAIT_PICEND_FAILED		(FH_ISP_CORE_ERR_BASE - 8)
#define FH_ERR_ISP_RAW_BUFF_NOTENOUGH	(FH_ISP_CORE_ERR_BASE - 9)
#define FH_ERR_ISP_SET_CIS_CLK			(FH_ISP_CORE_ERR_BASE - 10)
#define FH_ERR_ISP_UNEXPECTED_PIC_SIZE	(FH_ISP_CORE_ERR_BASE - 11)
#define FH_ERR_ISP_MEM_NOT_INITED       (FH_ISP_CORE_ERR_BASE - 12)

#define FH_ERR_MEMSIZE_UNDERFLOW		(FH_API_ERR_BASE-1)
#define FH_ERR_NULL_POINTER				(FH_API_ERR_BASE-2)
#define FH_ERR_ISP_INIT					(FH_API_ERR_BASE-3)
#define FH_ERR_ISP_INVALID				(FH_API_ERR_BASE-4)
#define FH_ERR_ISP_NO_SUPPORT_FORMAT	(FH_API_ERR_BASE-5)
#endif
