#ifndef _BSTREE_H_
#define _BSTREE_H_

typedef void BSTree;
typedef void BSKey;  //

typedef struct _tag_BSTreeNode BSTreeNode;
struct _tag_BSTreeNode {
  BSKey* key;  // key指针
  BSTreeNode* left;
  BSTreeNode* right;
};

typedef void(BSTree_Printf)(BSTreeNode*);
//左边和右边相减大于0，返回1，小于0，返回小于0的数
typedef int(BSTree_Compare)(BSKey*, BSKey*);  // 比较函数

//创建
BSTree* BSTree_Create();

//销毁
void BSTree_Destroy(BSTree* tree);

//清空
void BSTree_Clear(BSTree* tree);

//插入
int BSTree_Insert(BSTree* tree, BSTreeNode* node, BSTree_Compare* compare);

//删除
BSTreeNode* BSTree_Delete(BSTree* tree, BSKey* key, BSTree_Compare* compare);

//获取结点
BSTreeNode* BSTree_Get(BSTree* tree, BSKey* key, BSTree_Compare* compare);

//获取根结点
BSTreeNode* BSTree_Root(BSTree* tree);

//获取树的高度
int BSTree_Height(BSTree* tree);

//获取树的结点数
int BSTree_Count(BSTree* tree);

//获取树的度
int BSTree_Degree(BSTree* tree);

//显示打印结构
void BSTree_Display(BSTree* tree, BSTree_Printf* pFunc, int gap, char div);

#endif
