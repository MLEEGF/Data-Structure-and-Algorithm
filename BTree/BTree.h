#ifndef _BTREE_H_
#define _BTREE_H_

#define BT_LEFT 0
#define BT_RIGHT 1

typedef void BTree;

typedef unsigned long long BTPos;

typedef struct _tag_BTreeNode BTreeNode;
struct _tag_BTreeNode {
  BTreeNode* left;
  BTreeNode* right;
};

typedef void(BTree_Printf)(BTreeNode*);

//创建
BTree* BTree_Create();

//销毁
void BTree_Destroy(BTree* tree);

//清空
void BTree_Clear(BTree* tree);

//插入
int BTree_Insert(BTree* tree, BTreeNode* node, BTPos pos, int count, int flag);

//删除
BTreeNode* BTree_Delete(BTree* tree, BTPos, int count);

//获取结点
BTreeNode* BTree_Get(BTree* tree, BTPos pos, int count);

//获取根结点
BTreeNode* BTree_Root(BTree* tree);

//获取树的高度
int BTree_Height(BTree* tree);

//获取树的结点数
int BTree_Count(BTree* tree);

//获取树的度
int BTree_Degree(BTree* tree);

//显示打印结构
void BTree_Display(BTree* tree, BTree_Printf* pFunc, int gap, char div);

#endif