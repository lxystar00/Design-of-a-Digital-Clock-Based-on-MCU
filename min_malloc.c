/*
min_malloc: min_malloc.c
*/

#include "min_malloc.h"

M_LINK FREEHASH[hashsize]; //定义哈希表

int keyhash(size_t size)
{
    return (size/hashkey%hashkey);
}

void add_into_hash(M_LINK *p)
{
    int key;
    if(p == NULL)
    {
        printf("Add to hash Error!!\n");
        return;
    }
    else
    {
        p->tag = 0;//空闲标志

        if(p->size >= 10000)//判断内存块大小，选择其在哈希表中的位置
        {
            key = hashsize;
        }
        else
        {
            key = keyhash(p->size);
        }

        if(FREEHASH[key].rlink == NULL)//选择哈希表位置为空
        {
            printf("ttt\n");
            FREEHASH[key].rlink = p;//直接添加
        }
        else  //选择哈希表位置不为空
        {
            printf("aaa\n");
            p->rlink = FREEHASH[key].rlink;//链表指针交换
            p->llink = FREEHASH[key].rlink->llink;
            FREEHASH[key].rlink->llink->rlink = p;
            FREEHASH[key].rlink->llink = p;
            FREEHASH[key].rlink = p;
        }
    }
}

M_LINK* search_hash(size_t size)
{
    int key;
    int temp;
    M_LINK *p = NULL;
    char *s = NULL;
    M_LINK *t = NULL;

    if(size >= 10000)
    {
        key = hashsize;
    }
    else
    {
        key = keyhash(size);
    }
    
    while(key < hashsize)//查找合适的内存块
    {
        if(FREEHASH[key].rlink == NULL)
        {
            ++key;
        }
        else
        {
            p = FREEHASH[key].rlink;
            while((p->rlink) != (FREEHASH[key].rlink))
            {
                if(p->size >= size)//内存块不符合要求，寻找下一个
                {
                    //所选内存块分配后空间小于SIZE，把整个内存块分配出
                    if(p->size - size < SIZE)
                    {
                        if(p == (FREEHASH[key].rlink))
                        {
                            p->rlink->llink = p->llink;
                            p->llink->rlink = p->rlink;
                            t = FREEHASH[key].rlink;
                            FREEHASH[key].rlink = p->rlink;
                            p->llink = p->rlink = t;
//                            p->llink = p->rlink = &p;
                            p->tag = 1; //已分配标志

                            return p;
                        }
                        else
                        {
                            t = (p->llink->rlink);
                            p->rlink->llink = p->llink;
                            p->llink->rlink = p->rlink;
                            p->llink = p->rlink = t;
//                            p->llink = p->rlink = &p;
                            p->tag = 1; //已分配标志

                            return p;
                        }
                    }
                    else//所选内存块可分配后保留足够的空间
                    {
                        temp = p->size;
                        printf("!!!!!!!\n");
                        s =(char *)(p) + (temp - SIZE - size);
                        p->size = temp - SIZE -size;
                        p = (M_LINK *)s;
                        p->llink = p->rlink = p;
                        p->size = size;
                        p->tag = 1;  //已分配标志

                        return p;
                    }

                }
                else
                {
                    p = p->rlink;
                }
            }
            ++key;
        }
    }

    printf("Can not find the memory!!!\n");
    p = NULL;
    return p;
}


int min_init(void *start, unsigned long size)
{
    M_LINK *L = NULL;
    if(start == NULL)
    {
        printf("Malloc Init fail!!\n");
        return 1;
    }
    else
    {
       L = (M_LINK*)(start);
       L->tag = 0;
       L->size = size - SIZE;
       L->rlink = L;
       L->llink = L;
       add_into_hash(L);
       printf("Malloc Init OK!\n");
       return 0;
    }
}

void* min_malloc(size_t size)
{
    void *p;
    M_LINK *s;

    if(size == 0)
    {
        return p;
    }
    else
    {
        s = search_hash(size);
        if(s == NULL)
        {
            p = NULL;
            
            return p;
        }
        else
        {
            s = s + 1;
            
            return (void *)s;
        }
    }
}

void min_free(void *p)
{
    M_LINK *s;

    if(p == NULL)
    {
        printf("The P is Empty!!\n");
        return;
    }
    else
    {
        s = (M_LINK *)p;
        s = s - 1;
        if(s->tag == 1)
        {
            s->tag = 0;
            add_into_hash(s);
        }
        else
        {
            printf("Free Error\n");
            return;
        }
    }

}
