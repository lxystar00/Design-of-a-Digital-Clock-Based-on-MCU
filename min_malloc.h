/*
min_malloc: min_malloc.h
*/

#ifndef MIN_MALLOC_H_
#define MIN_MALLOC_H_

#include <stdio.h>
#include <stdlib.h>

//#define FootLoc(p) p+p->size-1 	//ָ��p��ָ��Ľڵ�ĵײ�
#define SIZE (sizeof(struct M_LINK))  //������Ϣͷ����

#define hashsize 101
#define hashkey 100

typedef struct M_LINK       //�ڴ��������ṹ
{
    struct M_LINK *llink;
    struct M_LINK *rlink;
    int tag;
    int size;
}M_LINK;

/*
typedef struct M_LINK		//�ڴ��������ṹ
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
��������int min_init(void *start, unsigned long size)
�������ܣ���ʼ�������Լ����ڴ����������ָ����������Ҫ����
		  ���ڴ����򣬳�ʼ���ɹ����� 0�� ��ʼ��ʧ�ܷ��� 1
*****************************************************************/
int min_init(void *start, unsigned long size);

/****************************************************************                                                                     
�������� void* min_malloc(size_t size)
�������ܣ�����һ��ָ��ָ��size��С���ڴ棬���û���㹻���ڴ�ռ�
		   �򷵻� NULL
*****************************************************************/
void* min_malloc(size_t size);

/****************************************************************
 ��������void min_free(void *p)
 �������ܣ����ָ��pΪ�գ���ʲô��������ָ��pָ��ĵ�ַ������
		   min_malloc����ĵ�ַ�������쳣
*****************************************************************/
void min_free(void *p);


#endif
