#include <stdio.h>
#include <stdlib.h>

#include "GTree.h"
#include "LinkList.h"

typedef struct _tag_GTreeNode GTreeNode;
struct _tag_GTreeNode {
  GTreeData* data;
  GTreeNode* parent;
  LinkList* child;  //孩子链表的地址
};

//代表链表的结点类型
typedef struct _tag_TLNode TLNode;
struct _tag_TLNode {
  LinkListNode header; //结点的后继指针
  GTreeNode* node;  //结点的存放的数据元素域是树结点的地址
};

static void recursive_display(GTreeNode* node, GTree_Printf* pFunc, int format, int gap, char div) {
  int i = 0;

  if ((node != NULL) && (pFunc != NULL)) {
    for (i = 0; i < format; i++) {
      printf("%c", div);
    }

    pFunc(node->data);

    printf("\n");
    

    for (i = 0; i < LinkList_Length(node->child); i++) {
      TLNode* trNode = (TLNode*)LinkList_Get(node->child, i);

      recursive_display(trNode->node, pFunc, format + gap, gap, div);
    }
  }
}

//递归删除
//删除组织链表、孩子链表中的结点
static void recursive_delete(LinkList* list, GTreeNode* node) {
  if ((list != NULL) && (node != NULL)) {
    GTreeNode* parent = node->parent;
    int index = -1;
    int i = 0;

    //从组织链表中删除
    for (i = 0; i < LinkList_Length(list); i++) {
      TLNode* trNode = (TLNode*)LinkList_Get(list, i);

      if (trNode->node == node) {
        LinkList_Delete(list, i);

        free(trNode);

        index = i;

        break;
      }
    }
    
    //从双亲结点的孩子链表中删除
    if (index >= 0) {
      if (parent != NULL) {
        for (i = 0; i < LinkList_Length(parent->child); i++) {
          TLNode* trNode = (TLNode*)LinkList_Get(parent->child, i);

          if (trNode->node == node) {
            LinkList_Delete(parent->child, i);

            free(trNode);

            break;
          } 
        }
      }

      //将该结点的孩子删除
      while (LinkList_Length(node->child) > 0) {
        TLNode* trNode = (TLNode*)LinkList_Get(node->child, 0);

        recursive_delete(list, trNode->node);
      }

      LinkList_Destroy(node->child);

      free(node); //node在Insert中被malloc出来的
    }
  }
}

static int recursive_height(GTreeNode* node) {
  int ret = 0; 

  if (node != NULL) {
    int subHeight = 0;
    int i = 0;

    for (i = 0; i < LinkList_Length(node->child); i++) {
      TLNode* trNode = (TLNode*)LinkList_Get(node->child, i);

      subHeight = recursive_height(trNode->node);

      //边求子树高度边比较
      //求出一个赋值一次跟下一次的进行比较
      if (ret < subHeight) {
        ret = subHeight;
      }
    }

    ret = ret + 1;
  }

  return ret;
}

static int recursive_degree(GTreeNode* node) {
  int ret = 0;

  if (node != NULL) {
    int subDegree = 0;
    int i = 0;

    //根结点的度数就是孩子链表的度数
    ret = LinkList_Length(node->child);

    for (i = 0; i < LinkList_Length(node->child); i++) {
      TLNode* trNode = (TLNode*)LinkList_Get(node->child, i);

      subDegree = recursive_degree(trNode->node);

      if (ret < subDegree) {
        ret = subDegree;
      }
    }
  }

  return ret;
}

//返回组织链表，就可以访问每一个结点
GTree* GTree_Create() {
  return LinkList_Create();
}

void GTree_Destroy(GTree* tree) {
  GTree_Clear(tree);
  LinkList_Destroy(tree);
}

//清空树
void GTree_Clear(GTree* tree) {
  GTree_Delete(tree, 0);
}

//要插入的不是一个结点而是一个数据
//如何实现给数据分配一个结点->动态申请一个结构体存放在结构体的数据域
//用户是不知道内部是如何实现的，他看到的是树就行，我们实现用链表实现
//合法性判断中位置如何确定尤其重要
//要插入的树中的接结点有两种情况：1、要么当前是空树，插入的是根结点，无双亲，孩子
//2、插入的是某个结点的孩子结点(必定属于某个结点)
//给data分配一个结点属于GTreeNode中的GTreeData
//pPos是这个data的双亲结点的位置
int GTree_Insert(GTree* tree, GTreeData* data, int pPos) {
  LinkList* list = (LinkList*)tree;
  //pPos < LinkList_Length(list)是因为我们已经把树的结构、逻辑等关系已经明确
  int ret = (list != NULL) && (data != NULL) && (pPos < LinkList_Length(list)); //C语言中不为0就为真

  if (ret) {
    GTreeNode* cNode = (GTreeNode*)malloc(sizeof(GTreeNode)); //给data分配结点
    //如果当前插入的是根节点那么pNode就会为空
    //创建 trNode cldNode 是因为要插入的结点要存放在两个链表中
    //一个是创建的链表，一个是双亲的孩子链表中
    TLNode* trNode = (TLNode*)malloc(sizeof(TLNode));
    TLNode* cldNode = (TLNode*)malloc(sizeof(TLNode));
    //pPos所代表的双亲结点是在链表的pPos位置将双亲结点取出
    //链表结点类型是TLNode
    //如果当前插入的是根节点那么pNode就会为空
    TLNode* pNode = (TLNode*)LinkList_Get(list, pPos);

    ret = (cNode != NULL) && (trNode != NULL) && (cldNode != NULL);

    if (ret) {
      cNode->data = data;
      //双亲指针是根据pPos位置的结点来决定的
      //双亲结点的地址
      cNode->parent = NULL;
      //此结点的孩子结点创建链表存放，第一个孩子结点的地址，就是链表的第一个结点
      cNode->child = LinkList_Create();

      //放入组织链表中
      trNode->node = cNode;
      //放入孩子链表中
      cldNode->node = cNode;

      //将cNode插入到组织链表中
      LinkList_Insert(list, (LinkListNode*)trNode, LinkList_Length(list));
      //将cNode插入到双亲结点的child链表
      //判断双亲结点是不是为空，为空那么这个结点就是组织结点的第一个结点，也是树的根结点
      if (pNode != NULL) {
        //保存双亲结点的指针
        cNode->parent = pNode->node;
        //插入孩子链表中
        LinkList_Insert(pNode->node->child, (LinkListNode*)cldNode, LinkList_Length(pNode->node->child));
      }else {
        free(cldNode); //插入的是根结点不属于任何的孩子
      }

    }
    else {
      free(trNode);
      free(cldNode);
      free(cNode);
    }
  }
  
  return ret;
}

//删除1、从组织链表中删除
//2、从孩子链表中删除
//删除结点的时候要先删除该结点的孩子结点、孙结点(递归操作)
GTreeData* GTree_Delete(GTree* tree, int pos) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, pos);
  GTreeData* ret = NULL;

  if (trNode != NULL) {
    ret = trNode->node->data;

    recursive_delete(tree, trNode->node);
  }

  return ret;
}

//将组织链表中pos位置树结点中的数据返回
GTreeData* GTree_Get(GTree* tree, int pos) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, pos);
  GTreeData* ret = NULL;

  if (trNode != NULL) {
    ret = trNode->node->data;
  }

  return ret;
}

GTreeData* GTree_Root(GTree* tree) {
  return GTree_Get(tree, 0);
}

//求树的高度先求子树的高度然后选择 MAX,加上1
int GTree_Height(GTree* tree) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);
  int ret = 0;

  //递归
  if (trNode != NULL) {
    ret = recursive_height(trNode->node);
  }
}

int GTree_Count(GTree* tree) {
  return LinkList_Length(tree);
}

//度数
int GTree_Degree(GTree* tree) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);
  int ret = 0;

  if (trNode != NULL) {
    ret = recursive_degree(trNode->node);
  } 

  return ret;
}

//利用文本显示加上缩进的方法显示
//传入打印树结点的函数指针
//gap控制缩进大小， div是缩进的符号
void GTree_Display(GTree* tree, GTree_Printf* pFunc,int gap, char div) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);

  if ((trNode != NULL) && (pFunc != NULL)) {
    recursive_display(trNode->node, pFunc, 0, gap, div);
  }
}