#include "Hash.h"
#include "BSTree.h"

#include <stdio.h>
#include <stdlib.h>

//二叉排序树需要一个比较函数
//那么就需要定义一个比较函数
//哈希表中的一个元素，因为是用二叉排序树实现的，所以定义一个header里面包含key和左右子树
//value是值的地址？
typedef struct _tag_HashNode HashNode;
struct _tag_HashNode {
  BSTreeNode header;
  HashValue* value;
};

void recuisive_clear(BSTreeNode* node) {
  if (node != NULL) {
    recuisive_clear(node->left);
    recuisive_clear(node->right);

    free(node);
  }
}

Hash* Hash_Create() {
  return BSTree_Create();
}

void Hash_Destroy(Hash* hash) {
  Hash_Clear(hash);
  BSTree_Destroy(hash);
}

void Hash_Clear(Hash* hash) {
  //先将申请出来的结点删除
  recuisive_clear(BSTree_Root(hash));
  //然后将二叉树中的结点删除
  BSTree_Clear(hash);
}

//Hash_Add不用做合法性判断是因为BSTree_Insert这个函数已经做了合法性判断了
//这个哈希表是在二叉排序树的基础上实现的，所以要将HashNode插入的二叉排序树中
int Hash_Add(Hash* hash, HashKey* key, HashValue* value, Hash_Compare* compare) {
  int ret = 0;
  HashNode* node = (HashNode*)malloc(sizeof(HashNode));

  //判断内存是否申请成功
  if (ret = (node != NULL)) {
    node->header.key = key;
    node->value = value;

    ret = BSTree_Insert(hash, (BSTreeNode*)node, compare);

    if (!ret) {
      free(node);
    }
  }

  return ret;
}

HashValue* Hash_Remove(Hash* hash, HashKey* key, Hash_Compare* compare) {
  HashValue* ret = NULL;
  HashNode* node = (HashNode*)BSTree_Delete(hash, key, compare);

  if (node != NULL) {
    ret = node->value;

    free(node);
  }

  return ret;
}

HashValue* Hash_Get(Hash* hash, HashKey* key, Hash_Compare* compare) {
  HashValue* ret = NULL;
  HashNode* node = (HashNode*)BSTree_Get(hash, key, compare);

  if (node != NULL) {
    ret = node->value;
  }

  return ret;
}

int Hash_Count(Hash* hash) {
  return BSTree_Count(hash);
}
