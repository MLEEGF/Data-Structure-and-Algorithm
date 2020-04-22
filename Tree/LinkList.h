#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

typedef void LinkList;
typedef struct _tag_LinkListNode LinkListNode;

struct _tag_LinkListNode
{
    LinkListNode *next;
};

//指定顺序表的最大容量
/* 该方法用于床架并且返回一个空的线性表 */
LinkList* LinkList_Create();

/* 该方法用于销毁一个线性表list */
void LinkList_Destroy(LinkList* list);

/* 该方法用于将一个线性表list中的所有元素清空使得线性表回到创建时的初始状态 */
void LinkList_Clear(LinkList* list);

/* 该方法用于返回一个线性表list中的所有元素个数 */
int LinkList_Length(LinkList* list);

/* 该方法用于向一个线性表list的pos位置处插入新元素node
   返回值为1表示插入成功，0表示插入失败
*/
int LinkList_Insert(LinkList* list, LinkListNode* node, int pos);

/* 该方法用于获取一个线性表list的pos位置处的元素
   返回值为pos位置处的元素， NULL表示获取失败
*/
LinkListNode* LinkList_Get(LinkList* list, int pos);

/* 该方法用于删除一个线性表list的pos位置处的元素
   返回值为被删除的元素，NULL表示获取失败
*/
LinkListNode* LinkList_Delete(LinkList* list, int pos);


#endif // LINKLIST_H_INCLUDED
