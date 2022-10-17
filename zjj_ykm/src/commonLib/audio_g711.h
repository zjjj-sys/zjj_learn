#ifndef __AUDIO_G711_H__
#define __AUDIO_G711_H__



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */













unsigned ALawEncode(uint8_t* dst, int16_t* src, size_t srcSize);
unsigned ALawDecode(int16_t* dst, const uint8_t* src, size_t srcSize);
unsigned ULawEncode(uint8_t* dst, int16_t* src, size_t srcSize);
unsigned ULawDecode(int16_t* dst, const uint8_t* src, size_t srcSize);
unsigned ALawToULaw(uint8_t* dst, const uint8_t* src, size_t srcSize);
unsigned ULawToALaw(uint8_t* dst, const uint8_t* src, size_t srcSize);




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */



#endif //__AUDIO_G711_H__

