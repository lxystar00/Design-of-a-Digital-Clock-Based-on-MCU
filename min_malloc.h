/*
min_malloc: min_malloc.h
*/

#ifndef MIN_MALLOC_H_
#define MIN_MALLOC_H_

#include <stdio.h>
#include <stdlib.h>

//#define FootLoc(p) p+p->size-1 	//指向p所指向的节点的底部
#define SIZE (sizeof(struct M_LINK))  //链表信息头长度

#define hashsize 101
#define hashkey 100

typedef struct M_LINK       //内存管理链表结构
{
    struct M_LINK *llink;
    struct M_LINK *rlink;
    int tag;
    int size;
}M_LINK;

/*
typedef struct M_LINK		//内存管理链表结构
{
	union
	{
		M_LINK * llink; 
		M_LINK * uplink;
	};
	int tag;
	int size;
	M_LINK *rlink;
}M_LINK;
*/


/****************************************************************
函数名：int min_init(void *start, unsigned long size)
函数功能：初始化我们自己的内存管理器，并指定管理器需要管理
		  的内存区域，初始化成功返回 0， 初始化失败返回 1
*****************************************************************/
int min_init(void *start, unsigned long size);

/****************************************************************                                                                     
函数名： void* min_malloc(size_t size)
函数功能：返回一个指针指向size大小的内存，如果没有足够的内存空间
		   则返回 NULL
*****************************************************************/
void* min_malloc(size_t size);

/****************************************************************
 函数名：void min_free(void *p)
 函数功能：如果指针p为空，则什么都不做，指针p指向的地址必须是
		   min_malloc分配的地址，否则异常
*****************************************************************/
void min_free(void *p);


#endif
