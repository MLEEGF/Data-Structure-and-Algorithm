/*
�����������ܹ��������������ݣ���ʵ�ַ���ͨ����ַ����ɶ����в������ݵ����ӣ�
�����������ܹ��洢�κ����͵����ݣ���Ҫ����������Ϊһ���ṹ�壬���£�
����struct Value
����{
������LinkListNode header;
������(��������) v;//�������Ҫ�洢������
����}
��������һ������ͷ��ͷ����LinkListNodeָ��ָ���0��LinkListNode�����ݴӵ�0���±꿪ʼ�㣩��ͬʱ����ͷ��¼���Ѵ洢�����ݸ�����
��ȡ�����е����ݣ���Ҫ�����������ͽ���ת����
����Ĳ���LinkListʵ����void���ͣ��ں����ڶ���Ҫ����ת���� TLinkList�� ������Ĳ���LinkListNode ��
��ʵ��һ������һ��ָ��LinkListNode ���͵�ָ���Ա�Ľṹ�壬����ת����Value ���ͣ����ܹ���ȡ��洢������V��
*/


#include <stdio.h>
#include <malloc.h>

#include "LinkList.h"

typedef struct _tag_LinkList
{
    LinkListNode header;
    int length;
} TLinkList;

//ָ��˳�����������
/* �÷������ڴ������ҷ���һ���յ����Ա� */
LinkList* LinkList_Create() //O(1) :ʱ�临�Ӷ�ֻ��������
{
    TLinkList* ret = (TLinkList*)malloc(sizeof(TLinkList));

    if(ret != NULL)
    {
        ret->length = 0;
        ret->header.next = NULL;
    }

    return ret;
}

/* �÷�����������һ�����Ա�list */
void LinkList_Destroy(LinkList* list) //O(1)
{
    free(list);
}

/* �÷������ڽ�һ�����Ա�list�е�����Ԫ�����ʹ�����Ա�ص�����ʱ�ĳ�ʼ״̬ */
void LinkList_Clear(LinkList* list) //O(1)
{
    //ǿ������ת��
    TLinkList* sList = (TLinkList*)list;

    if ( sList != NULL )
    {
        //�����Ա�Ϊ�գ���ͷ����ָ����Ϊ��
        sList->length = 0;
        sList->header.next = NULL;
    }
}

/* �÷������ڷ���һ�����Ա�list�е�����Ԫ�ظ��� */
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

/* �÷���������һ�����Ա�list��posλ�ô�������Ԫ��node
   ����ֵΪ1��ʾ����ɹ���0��ʾ����ʧ��
*/
int LinkList_Insert(LinkList* list, LinkListNode* node, int pos) //O(1)
{
    //�����������һ��λ��O(1)�� ������β��//O(n)
    TLinkList* sList = (TLinkList*)list;
    //������Ϊ�գ�λ�ò���С��0����㲻��Ϊ��
    int ret = (sList != NULL) && (pos >= 0) && (node != NULL);
    int i = 0;

    if( ret )
    {
        //����һ��ָ��ָ���ͷ���
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

/* �÷������ڻ�ȡһ�����Ա�list��posλ�ô���Ԫ��
   ����ֵΪposλ�ô���Ԫ�أ� NULL��ʾ��ȡʧ��
*/
LinkListNode* LinkList_Get(LinkList* list, int pos)  ////O(1), O(n)
{
    TLinkList* sList = (TLinkList*)list;
    //����ֵ��ʼ��Ϊ�գ�ֻҪû�л�ȡ�ͷ��ؿ�
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

/* �÷�������ɾ��һ�����Ա�list��posλ�ô���Ԫ��
   ����ֵΪ��ɾ����Ԫ�أ�NULL��ʾ��ȡʧ��
*/
LinkListNode* LinkList_Delete(LinkList* list, int pos) //O(1), O(n)
{
    TLinkList* sList = (TLinkList*)list;
    //����ֵ��ʼ��Ϊ�գ�ֻҪû�л�ȡ�ͷ��ؿ�
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


