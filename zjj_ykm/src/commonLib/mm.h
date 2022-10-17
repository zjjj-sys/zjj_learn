#ifndef __MM_H__
#define __MM_H__



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */



#include <assert.h>
#include <pthread.h>
#include "__list.h"

#define MM_BLK_IO_BLOCK 	(1 << 0)
#define MM_BLK_IO_NO_BLOCK 	(1 << 1)


typedef struct {
	unsigned char * buf;
	unsigned int size;
	struct list_head list;
}__attribute__((packed))mem_block;
#define MAX_CTX_NAME_LEN 32
typedef struct{
	char  name[MAX_CTX_NAME_LEN];
	pthread_mutex_t  mutex;
	unsigned int flag;
	void * mem_block_addr;
	void * mem_block_content_addr;
	void * frame_header_addr;
	struct list_head free_list;
	struct list_head frame_list;
	struct list_head free_frame_list;
	struct list_head ctx_list;
	unsigned int resume;
	unsigned int free_frame_header_num;
	unsigned int used_frame_header_num;
	unsigned int free_blk_num;
	unsigned int used_blk_num;
	unsigned int block_size;
	unsigned int user_map;
}__attribute__((packed))mem_block_ctx;


#define PRODUCTOR_INDEX 32

typedef struct{
	mem_block_ctx * ctx;
	unsigned int index;
}__attribute__((packed))mem_block_user;


typedef struct{
	unsigned int ts;
	unsigned int frame_size;
	struct list_head frame_list;
	struct list_head mem_block_list_head;
	unsigned char ref;
	unsigned char key_frame;
	unsigned char ext_malloc:1; // 1:extern malloc mem, 0:default mem.
	unsigned char res2;
	unsigned int user_map;
	unsigned int frame_type;
}__attribute__((packed))frame_header;



#if 0
mem_block_ctx * create_mm_blk_ctx(const char * name,unsigned int flag,
	unsigned int mem_block_size,unsigned int mem_block_num,
	unsigned int frame_header_num);

void destory_mem_blk_ctx(mem_block_ctx * ctx);

int get_frame(mem_block_ctx * ctx,unsigned int * key_frame,unsigned int * ts,
	unsigned char * buf_data,unsigned int buf_size);

int put_frame(mem_block_ctx * ctx,unsigned int key_frame,unsigned char * frame_data,
	unsigned int frame_size);
int put_frame2(mem_block_ctx * ctx,unsigned int key_frame,unsigned int ts,unsigned char * frame_data,
	unsigned int frame_size);


#else

mem_block_user * create_mm_blk_user(const char * name,unsigned int flag,
	unsigned int mem_block_size,unsigned int mem_block_num,
	unsigned int frame_header_num);

void destory_mem_blk_user(mem_block_user * user);
#if 0
int get_frame(mem_block_user * user,unsigned int * key_frame,unsigned int * ts,
	unsigned char * buf_data,unsigned int buf_size);

int put_frame(mem_block_user * user,unsigned int key_frame,unsigned char * frame_data,
	unsigned int frame_size);
#endif 
int put_frame2(mem_block_user * user,unsigned int key_frame,unsigned int ts,unsigned char * frame_data,
	unsigned int frame_size);


int get_frame_ext(mem_block_user * user,unsigned int * key_frame,unsigned int * ts,
	unsigned char * buf_data,unsigned int buf_size,unsigned int * frame_type);

int put_frame_ext(mem_block_user * user,unsigned int key_frame,unsigned int ts,
	unsigned char * frame_data,	unsigned int frame_size,unsigned int frame_type);

#endif




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif // __MM_H__



