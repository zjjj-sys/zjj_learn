#ifndef __CRC_SUM_H__
#define __CRC_SUM_H__



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */



#include <stdint.h>



uint32_t CRC32(void * pData,uint32_t nDataSize);


uint32_t CRC32_Start();
uint32_t CRC32_Calu(uint32_t nCaluVal,void *pStart, uint32_t uSize);
uint32_t CRC32_End(uint32_t nCaluVal);







#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif //__CRC_SUM_H__

