/*
该线性链表能够任意数量的数据，其实现方法通过地址链完成对所有插入数据的连接；
该线性链表能够存储任何类型的数据，但要求数据类型为一个结构体，如下：
　　struct Value
　　{
　　　LinkListNode header;
　　　(任意类型) v;//这个就是要存储的数据
　　}
该链表有一个链表头，头部的LinkListNode指针指向第0个LinkListNode（数据从第0个下标开始算），同时链表头记录了已存储的数据个数；
获取链表中的数据，需要对其数据类型进行转换。
传入的参数LinkList实则是void类型，在函数内都需要类型转换成 TLinkList； 而传入的参数LinkListNode ，
其实是一个含有一个指向LinkListNode 类型的指针成员的结构体，将其转换成Value 类型，就能够获取其存储的数据V。
*/


#include <stdio.h>
#include <malloc.h>

#include "LinkList.h"

typedef struct _tag_LinkList
{
    LinkListNode header;
    int length;
} TLinkList;

//指定顺序表的最大容量
/* 该方法用于创建并且返回一个空的线性表 */
LinkList* LinkList_Create() //O(1) :时间复杂度只考虑最坏情况
{
    TLinkList* ret = (TLinkList*)malloc(sizeof(TLinkList));

    if(ret != NULL)
    {
        ret->length = 0;
        ret->header.next = NULL;
    }

    return ret;
}

/* 该方法用于销毁一个线性表list */
void LinkList_Destroy(LinkList* list) //O(1)
{
    free(list);
}

/* 该方法用于将一个线性表list中的所有元素清空使得线性表回到创建时的初始状态 */
void LinkList_Clear(LinkList* list) //O(1)
{
    //强制类型转换
    TLinkList* sList = (TLinkList*)list;

    if ( sList != NULL )
    {
        //若线性表为空，则头结点的指针域为空
        sList->length = 0;
        sList->header.next = NULL;
    }
}

/* 该方法用于返回一个线性表list中的所有元素个数 */
int LinkList_Length(LinkList* list) //O(1)
{
    TLinkList* sList = (TLinkList*)list;
    int ret = -1;

    if(sList != NULL)
    {
        ret = sList->length;
    }

    return ret;
}

/* 该方法用于向一个线性表list的pos位置处插入新元素node
   返回值为1表示插入成功，0表示插入失败
*/
int LinkList_Insert(LinkList* list, LinkListNode* node, int pos) //O(1)
{
    //最好情况插入第一个位置O(1)， 最差插入尾部//O(n)
    TLinkList* sList = (TLinkList*)list;
    //链表不能为空，位置不能小于0，结点不能为空
    int ret = (sList != NULL) && (pos >= 0) && (node != NULL);
    int i = 0;

    if( ret )
    {
        //定义一个指针指向表头结点
        LinkListNode* current = (LinkListNode*)sList;

        for(i = 0; (i < pos) && (current->next != NULL); i++)
        {
            current = current->next;
        }

        node->next = current->next;
        current->next = node;

        sList->length++;
    }

    return ret;
}

/* 该方法用于获取一个线性表list的pos位置处的元素
   返回值为pos位置处的元素， NULL表示获取失败
*/
LinkListNode* LinkList_Get(LinkList* list, int pos)  ////O(1), O(n)
{
    TLinkList* sList = (TLinkList*)list;
    //返回值初始化为空，只要没有获取就返回空
    LinkListNode* ret = NULL;
    int i;

    if( (sList != NULL) && (pos >= 0) && (pos < sList->length) )
    {
        LinkListNode* current = (LinkListNode*)sList;

        for(i = 0; i < pos ; i++)
        {
            current = current->next;
        }

        ret = current->next;
    }

    return ret;
}

/* 该方法用于删除一个线性表list的pos位置处的元素
   返回值为被删除的元素，NULL表示获取失败
*/
LinkListNode* LinkList_Delete(LinkList* list, int pos) //O(1), O(n)
{
    TLinkList* sList = (TLinkList*)list;
    //返回值初始化为空，只要没有获取就返回空
    LinkListNode* ret = NULL;
    int i;

    if( (sList != NULL) && (pos >= 0) && (pos < sList->length) )
    {
        LinkListNode* current = (LinkListNode*)sList;

        for(i = 0; i < pos ; i++)
        {
            current = current->next;
        }

        ret = current->next;
        current->next = ret->next;

        sList->length--;
    }

    return ret;
}


