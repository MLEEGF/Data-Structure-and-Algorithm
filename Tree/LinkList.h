#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

typedef void LinkList;
typedef struct _tag_LinkListNode LinkListNode;

struct _tag_LinkListNode
{
    LinkListNode *next;
};

//ָ��˳�����������
/* �÷������ڴ��ܲ��ҷ���һ���յ����Ա� */
LinkList* LinkList_Create();

/* �÷�����������һ�����Ա�list */
void LinkList_Destroy(LinkList* list);

/* �÷������ڽ�һ�����Ա�list�е�����Ԫ�����ʹ�����Ա�ص�����ʱ�ĳ�ʼ״̬ */
void LinkList_Clear(LinkList* list);

/* �÷������ڷ���һ�����Ա�list�е�����Ԫ�ظ��� */
int LinkList_Length(LinkList* list);

/* �÷���������һ�����Ա�list��posλ�ô�������Ԫ��node
   ����ֵΪ1��ʾ����ɹ���0��ʾ����ʧ��
*/
int LinkList_Insert(LinkList* list, LinkListNode* node, int pos);

/* �÷������ڻ�ȡһ�����Ա�list��posλ�ô���Ԫ��
   ����ֵΪposλ�ô���Ԫ�أ� NULL��ʾ��ȡʧ��
*/
LinkListNode* LinkList_Get(LinkList* list, int pos);

/* �÷�������ɾ��һ�����Ա�list��posλ�ô���Ԫ��
   ����ֵΪ��ɾ����Ԫ�أ�NULL��ʾ��ȡʧ��
*/
LinkListNode* LinkList_Delete(LinkList* list, int pos);


#endif // LINKLIST_H_INCLUDED
