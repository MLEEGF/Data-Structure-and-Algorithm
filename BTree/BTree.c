#include "BTree.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _tag_BTree TBTree;
struct _tag_BTree {
  int count;  //结点数
  BTreeNode* root;
};

static void recursive_display(BTreeNode* node, BTree_Printf* pFunc, int format,
                              int gap, char div) {
  int i = 0;

  if ((node != NULL) && (pFunc != NULL)) {
    for (i = 0; i < format; i++) {
      printf("%c", div);
    }

    pFunc(node);

    printf("\n");

    //为了避免
    if ((node->left != NULL) || (node->right != NULL)) {
      recursive_display(node->left, pFunc, format + gap, gap, div);
      recursive_display(node->right, pFunc, format + gap, gap, div);
    }
  } else {
    for (i = 0; i < format; i++) {
      printf("%c", div);
    }
    printf("\n");
  }
}

//计算该树的结点数
static int recursive_count(BTreeNode* root) {
  int ret = 0;

  //  左子树+右子树+根结点
  if (root != NULL) {
    ret = recursive_count(root->left) + recursive_count(root->right) + 1;
  }
}

static int recursive_height(BTreeNode* root) {
  int ret = 0;

  //求左右子树中最大的高度 + 1
  if (root != NULL) {
    int lheight = recursive_height(root->left);
    int rheight = recursive_height(root->right);

    ret = ((lheight > rheight) ? lheight : rheight) + 1;
  }

  return ret;
}

/**
 * 二叉树的度只有0,1,2
 * 通过判断一个结点的度来确定整个树的度
 * 从根结点出发，如果有左子树和右子树那么就为2
 * 当某个结点度为1时进行递归
 */
static int recursive_degree(BTreeNode* root) {
  int ret = 0;

  if (root != NULL) {
    if (root->left != NULL) {
      if (root->left != NULL) {
        ret++;
      }

      if (root->right) {
        ret++;
      }

      if (ret == 1) {
        int ldegree = recursive_degree(root->left);
        int rdegree = recursive_degree(root->right);

        if (ret < ldegree) {
          ret = ldegree;
        }

        if (ret < rdegree) {
          ret = rdegree;
        }
      }
    }
  }

  return ret;
}

BTree* BTree_Create() {
  TBTree* ret = (BTree*)malloc(sizeof(TBTree));

  if (ret != NULL) {
    ret->count = 0;
    ret->root = NULL;
  }

  return ret;
}

void BTree_Destroy(BTree* tree) { free(tree); }

void BTree_Clear(BTree* tree) {
  TBTree* btree = (TBTree*)malloc(sizeof(TBTree));

  if (btree != NULL) {
    btree->count = 0;
    btree->root = NULL;
  }
}
/**
 * 将结点的左边标记为0，右边标记为1
 * pos是从根结点到目的结点的路标 011， 10010
 * count是要移动多少次到达插入的位置
 * flag是标记被取代位置元素(子树)插入node的左边还是右边
 */
int BTree_Insert(BTree* tree, BTreeNode* node, BTPos pos, int count, int flag) {
  TBTree* btree = (TBTree*)tree;
  int ret = (btree != NULL) && (node != NULL) &&
            ((flag == BT_LEFT) || (flag == BT_RIGHT));
  int bit = 0;

  if (ret) {
    BTreeNode* parent = NULL;
    BTreeNode* current =
        btree->root;  //将current指向根结点, 从根结点出发到达插入的位置

    node->left = NULL;
    node->right = NULL;

    while ((count > 0) && (current != NULL)) {
      bit = pos & 1;
      pos = pos >> 1;

      //记录当前的双亲结点，插入parent的lef or right
      parent = current;

      if (bit == BT_LEFT) {
        current = current->left;
      } else if (bit == BT_RIGHT) {
        current = current->right;
      }

      count--;
    }

    /**
     * 1、先解插入位置的元素和node之间的关系
     * 2、再判断parent指针是否为空，为空说明当前插入的是根结点，直接将
     * btree->root = node;
     */

    // current指向node插入的位置，current不为空需指定当前元素插入node的左边还是右边
    if (flag == BT_LEFT) {
      node->left = current;
    } else if (flag == BT_RIGHT) {
      node->right = current;
    }

    if (parent != NULL) {
      if (bit == BT_LEFT) {
        parent->left = node;
      } else if (bit == BT_RIGHT) {
        parent->right = node;
      }
    } else {
      btree->root = node;
    }

    btree->count++;
  }

  return ret;
}

void BTree_Display(BTree* tree, BTree_Printf* pFunc, int gap, char div) {
  TBTree* btree = (TBTree*)tree;

  if (btree != NULL) {
    recursive_display(btree->root, pFunc, 0, gap, div);
  }
}

BTreeNode* BTree_Delete(BTree* tree, BTPos pos, int count) {
  TBTree* btree = (TBTree*)tree;
  void* ret = NULL;
  int bit = 0;

  if (btree != NULL) {
    BTreeNode* parent = NULL;
    BTreeNode* current = btree->root;

    //遍历找到要删除的元素
    while ((count > 0) && (current != NULL)) {
      bit = pos & 1;
      pos = pos >> 1;

      parent = current;

      if (bit == BT_LEFT) {
        current = current->left;
      } else if (bit == BT_RIGHT) {
        current = current->right;
      }

      count--;
    }

    //找到被删除元素后判断其双亲时候存在，不存在则是根结点
    if (parent != NULL) {
      if (bit == BT_LEFT) {
        parent->left = NULL;
      } else if (bit == BT_RIGHT) {
        parent->right = NULL;
      }
    } else {
      btree->root = NULL;
    }

    ret = current;

    //删除结点时，删除该结点的所有孩子
    btree->count = btree->count - recursive_count(ret);
  }

  return ret;
}

BTreeNode* BTree_Get(BTree* tree, BTPos pos, int count) {
  TBTree* btree = (TBTree*)tree;
  BTreeNode* ret = NULL;
  int bit = 0;

  if (btree != NULL) {
    BTreeNode* current = btree->root;

    while ((count > 0) && (current != NULL)) {
      bit = pos & 1;
      pos = pos >> 1;

      if (bit == BT_LEFT) {
        current = current->left;
      } else if (bit == BT_RIGHT) {
        current = current->right;
      }

      count--;
    }

    ret = current;
  }

  return ret;
}

BTreeNode* BTree_Root(BTree* tree) {
  TBTree* btree = (TBTree*)tree;
  BTreeNode* ret = NULL;

  if (btree != NULL) {
    ret = btree->root;
  }

  return ret;
}

int BTree_Height(BTree* tree) {
  TBTree* btree = (TBTree*)tree;
  int ret = 0;

  if (btree != NULL) {
    ret = recursive_height(btree->root);
  }
}

int BTree_Degree(BTree* tree) {
  TBTree* btree = (TBTree*)tree;
  int ret = 0;

  if (btree != NULL) {
    ret = recursive_degree(btree->root);
  }

  return ret;
}

int BTree_Count(BTree* tree) {
  TBTree* btree = (TBTree*)tree;
  int ret = 0;

  if (btree != NULL) {
    ret = btree->count;
  }

  return ret;
}