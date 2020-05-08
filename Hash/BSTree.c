#include "BSTree.h"

#include <malloc.h>
#include <stdio.h>

typedef struct _tag_BSTree TBSTree;
struct _tag_BSTree {
  int count;
  BSTreeNode* root;
};

static void recursive_display(BSTreeNode* node, BSTree_Printf* pFunc,
                              int format, int gap, char div)  // O(n)
{
  int i = 0;

  if ((node != NULL) && (pFunc != NULL)) {
    for (i = 0; i < format; i++) {
      printf("%c", div);
    }

    pFunc(node);

    printf("\n");

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

static int recursive_count(BSTreeNode* root)  // O(n)
{
  int ret = 0;

  if (root != NULL) {
    ret = recursive_count(root->left) + 1 + recursive_count(root->right);
  }

  return ret;
}

static int recursive_height(BSTreeNode* root)  // O(n)
{
  int ret = 0;

  if (root != NULL) {
    int lh = recursive_height(root->left);
    int rh = recursive_height(root->right);

    ret = ((lh > rh) ? lh : rh) + 1;
  }

  return ret;
}

static int recursive_degree(BSTreeNode* root)  // O(n)
{
  int ret = 0;

  if (root != NULL) {
    if (root->left != NULL) {
      ret++;
    }

    if (root->right != NULL) {
      ret++;
    }

    if (ret == 1) {
      int ld = recursive_degree(root->left);
      int rd = recursive_degree(root->right);

      if (ret < ld) {
        ret = ld;
      }

      if (ret < rd) {
        ret = rd;
      }
    }
  }

  return ret;
}

//node要插入的结点
static int recursive_insert(BSTreeNode* root, BSTreeNode* node, BSTree_Compare* compare) {
  int ret = 0;
  int r = compare(node->key, root->key);

  //不允许有相同的值出现在二叉排序树中，返回失败
  if (r == 0) {
    ret = 0;
  } else if (r < 0) {
    //当根结点的左子树不为空时
    if (root->left != NULL) {
      //递归，左子树和node继续比较
      ret = recursive_insert(root->left, node, compare);
    } else {
      root->left = node;
    }
  } else if (r > 0) {
    if (root->right != NULL) {
      ret = recursive_insert(root->right, node, compare);
    } else {
      root->right = node;
    }
  }

  return ret;
}

//key要查找的值
static BSTreeNode* recursive_get(BSTreeNode* root, BSKey* key, BSTree_Compare* compare) {
  BSTreeNode* ret = NULL;

  if (root != NULL) {
    int r = compare(key, root->key);

    if (r == 0) {
      ret = root;
    } else if (r < 0) {
      ret = recursive_get(root->left, key, compare);
    } else if (r > 0) {
      ret = recursive_get(root->key, key, compare);
    }
  }

  return ret;
}

static BSTreeNode* delete_node(BSTreeNode** pRoot) {
  BSTreeNode* ret = *pRoot;

  if ((*pRoot)->right == NULL) {
    *pRoot = (*pRoot)->left;
  } else if ((*pRoot)->left == NULL) {
    *pRoot = (*pRoot)->right;
  } else {
    BSTreeNode* g = *pRoot;
    BSTreeNode* c = (*pRoot)->left;

    while (c->right != NULL) {
      g = c;
      c = c->right;
    }

    if (g != *pRoot) {
      g->right = c->left;
    } else {
      g->left = c->left;
    }

    c->left = (*pRoot)->left;
    c->right = (*pRoot)->right;

    *pRoot = c;
  }

  return ret;
}

//删除pRoot指向的结点
static BSTreeNode* recursive_delete(BSTreeNode** pRoot, BSKey* key, BSTree_Compare* compare) {
  BSTreeNode* ret = NULL;
  if ((pRoot != NULL) && (*pRoot != NULL)) {
    int r = compare(key, (*pRoot)->key);

    if (r == 0) {

    } else if (r < 0) {
      ret = recursive_delete(&((*pRoot)->left), key, compare);
    } else if (r > 0) {
      ret = recursive_delete(&((*pRoot)->right), key, compare);
    }
  }

  return ret;
} 

BSTree* BSTree_Create()  // O(1)
{
  TBSTree* ret = (TBSTree*)malloc(sizeof(TBSTree));

  if (ret != NULL) {
    ret->count = 0;
    ret->root = NULL;
  }

  return ret;
}

void BSTree_Destroy(BSTree* tree)  // O(1)
{
  free(tree);
}

void BSTree_Clear(BSTree* tree)  // O(1)
{
  TBSTree* btree = (TBSTree*)tree;

  if (btree != NULL) {
    btree->count = 0;
    btree->root = NULL;
  }
}

/**/
int BSTree_Insert(BSTree* tree, BSTreeNode* node, BSTree_Compare* compare) {
  TBSTree* btree = (TBSTree*)tree;
  int ret = (btree != NULL) && (node != NULL) && (compare != NULL);

  if (ret) {
    /**
     * 每次插入的结点是叶子结点所以左右子树是空的
    */
    node->left = NULL;
    node->right = NULL;

    if (btree->root == NULL) {
      btree->root = node;
    } else {
      ret = recursive_insert(btree->root, node, compare);
    }

    //插入成功
    if (ret) {
      btree->count++;
    }
  }

  return ret;
}

//删除A位置的B结点要将中序遍历中B结点的前驱放置A位置中
BSTreeNode* BSTree_Delete(BSTree* tree, BSKey* key, BSTree_Compare* compare) {
  TBSTree* btree = (TBSTree*)tree;
  BSTreeNode* ret = NULL;

  if ((btree != NULL) && (key != NULL) && (compare != NULL)) {
    ret = recursive_delete(&btree->root, key, compare);

  }

  return ret;
}

BSTreeNode* BSTree_Get(BSTree* tree, BSKey* key, BSTree_Compare* compare) {
  TBSTree* btree = (TBSTree*)tree;
  BSTreeNode* ret = NULL;

  if ((btree != NULL) && (key != NULL) && (compare != NULL)) {
    ret = recursive_get(btree->root, key, compare);
  }

  return ret;
}

BSTreeNode* BSTree_Root(BSTree* tree)  // O(1)
{
  TBSTree* btree = (TBSTree*)tree;
  BSTreeNode* ret = NULL;

  if (btree != NULL) {
    ret = btree->root;
  }

  return ret;
}

int BSTree_Height(BSTree* tree)  // O(n)
{
  TBSTree* btree = (TBSTree*)tree;
  int ret = 0;

  if (btree != NULL) {
    ret = recursive_height(btree->root);
  }

  return ret;
}

int BSTree_Count(BSTree* tree)  // O(1)
{
  TBSTree* btree = (TBSTree*)tree;
  int ret = 0;

  if (btree != NULL) {
    ret = btree->count;
  }

  return ret;
}

int BSTree_Degree(BSTree* tree)  // O(n)
{
  TBSTree* btree = (TBSTree*)tree;
  int ret = 0;

  if (btree != NULL) {
    ret = recursive_degree(btree->root);
  }

  return ret;
}

void BSTree_Display(BSTree* tree, BSTree_Printf* pFunc, int gap,
                    char div)  // O(n)
{
  TBSTree* btree = (TBSTree*)tree;

  if (btree != NULL) {
    recursive_display(btree->root, pFunc, 0, gap, div);
  }
}
