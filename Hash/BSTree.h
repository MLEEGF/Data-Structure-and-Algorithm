#ifndef _BSTREE_H_
#define _BSTREE_H_

/**
 * 1、插入和删除都需要根据key值去删除
 * 但是这个key值是int还是什么类型交由使用者决定，所以做一个数据封装定义为void
 * 2、但是插入和删除，获取都要比较，那么需要通过一个比较函数通过key(可以使任意类型)值
 * 如果key值是int只需要比较大小，但是字符串如何比较，这时就需要一个比较函数
*/

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