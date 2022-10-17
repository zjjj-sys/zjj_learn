#ifndef __MEDIA_BUFFER_H__
#define __MEDIA_BUFFER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include <stdint.h>
#include "MediaBufferConf.h"

#include <pthread.h>
#include <assert.h>
typedef struct tagMediaPage{
	uint16_t i_next;	// index of next page
//	uint16_t i_prev;	// index of prev page
	uint16_t i_page;	// index of curr page
//	uint16_t res;		// reserve .
}__attribute__((packed))MediaPage;

typedef struct tagMediaFrame{
	uint32_t	offset_head;
	uint32_t 	offset_tail;
	uint32_t 	key_frame;
	
}__attribute__((packed))MediaFrame;

typedef struct tagMediaFrameConsumer{
	char name[CONFIG_MEM_NAME_SIZE];
	uint32_t	used : 1;
	uint32_t    waitKeyFrame : 1;
	uint32_t    reserved:30;
	uint32_t	offset_head;
	uint32_t 	offset_tail;
}__attribute__((packed))MediaFrameConsumer;
typedef struct tagMediaFrameProductor{
	char name[CONFIG_MEM_NAME_SIZE];
	uint32_t	offset_head;
	uint32_t 	offset_tail;
}__attribute__((packed))MediaFrameProductor;

typedef struct tagMediaShareMem{
	char name[CONFIG_MEM_NAME_SIZE];
	MediaFrameConsumer consumers[CONFIG_CONSUMER_NR];
	MediaFrameProductor productor;
	pthread_mutex_t mutex;
	uint32_t data_size;
	uint8_t data[0];
}__attribute__((packed))MediaShareMem;

typedef enum {
	MEDIA_MEM_PRODUCTOR 	= 0,
	MEDIA_MEM_CONSUMER,
}__attribute__((packed))MEDIA_MEM_TYPE;
struct tagMediaShareMemCtx ;
typedef struct tagMediaShareMemOperation{
	void * 	(*create_share_mem)(const char * /*share mem name */,uint32_t /*data size*/);
	void 	(*distroy_share_mem)(void * /* share mem data pointer*/);
	void 	(*lock_init)(struct tagMediaShareMemCtx *);
	void 	(*lock)(struct tagMediaShareMemCtx *);
	void 	(*unlock)(struct tagMediaShareMemCtx *);
	void 	(*lock_deinit)(struct tagMediaShareMemCtx *);
}__attribute__((packed))MediaShareMemOps;

typedef struct tagMediaShareMemCtx{
	MediaShareMem * 	mem;
	MediaShareMemOps * 	ops;
	union {
		uint32_t i_consumer;
		uint32_t productor;
	};
	int lock_fd;
}__attribute__((packed))MediaShareMemCtx;

MediaShareMemCtx * create_media_mem_ctx(const char * /*user name */,const char * /*share mem name */,
	uint32_t /*data size*/,MEDIA_MEM_TYPE );
void distroy_media_mem_ctx(MediaShareMemCtx * );

typedef struct tagFrame{
	uint32_t isVideo:1;
	uint32_t key_frame:1;
	uint32_t data_size:30;
	uint32_t data_type;
	uint64_t timestamp;
	uint8_t  data[0];
}__attribute__((packed))FRAME;
#define INVALID_CONSUMER_MAGIC 0xffff
#if 0

int get_frame(MediaShareMemCtx * ctx,FRAME * data);
int put_frame(MediaShareMemCtx * ctx,FRAME * data);

#endif
int AH_MM_Get_Frame(void * ctx,void * buf,unsigned int size);
int AH_MM_Put_Frame(void * ctx,void * buf,unsigned int size);
int AH_MM_Put_FrameBlocked(void * ctx,void * buf,unsigned int size);

void * AH_MM_Create_Shm(const char * /*user name */,
								const char * /*share mem name */,
								uint32_t /*data size*/,
								MEDIA_MEM_TYPE );

void AH_MM_Distroy_Shm(void * ctx);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __MEDIA_BUFFER_H__ */
