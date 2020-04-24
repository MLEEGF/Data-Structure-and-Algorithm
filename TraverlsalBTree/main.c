#include <stdio.h>
#include <stdlib.h>

#include "BTree.h"
#include "LinkQueue.h"

struct Node {
  BTreeNode header;
  char v;
};

void printf_data(BTreeNode* node) {
  if (node != NULL) {
    printf("%c", ((struct Node*)node)->v);
  }
}

//前序遍历
void pre_order_traversal(BTreeNode* root) {
  if (root != NULL) {
    printf("%c, ", ((struct Node*)root)->v);

    pre_order_traversal(root->left);
    pre_order_traversal(root->right);
    
  }
}

//中序遍历
void middle_order_traversal(BTreeNode* root) {
  if (root != NULL) {
    middle_order_traversal(root->left);

    printf("%c, ", ((struct Node*)root)->v);

    middle_order_traversal(root->right);
  }
}

//后序遍历
void post_order_traversal(BTreeNode* root) {
  if (root != NULL) {
    post_order_traversal(root->left);

    post_order_traversal(root->right);

    printf("%c, ", ((struct Node*)root)->v);
  }
}

//层次遍历
void level_order_traversal(BTreeNode* root) {
  if (root != NULL) {
    LinkQueue* queue = LinkQueue_Create();

    if (queue != NULL) {
      //将根结点(第一层的结点)压入栈中
      LinkQueue_Append(queue, root);

      while (LinkQueue_Length(queue) > 0) {
        //将第一层的结点出队
        struct Node* node = (struct Node*)LinkQueue_Retrieve(queue);

        printf("%c, ", node->v);

        //将第二(三...)层的结点入队
        LinkQueue_Append(queue, node->header.left);
        LinkQueue_Append(queue, node->header.right);
      }
    }
  }
}

int main(int argc, char *argvp[]) {
  BTree* tree = BTree_Create();

  struct Node n1 = {{NULL, NULL}, 'A'};
  struct Node n2 = {{NULL, NULL}, 'B'};
  struct Node n3 = {{NULL, NULL}, 'C'};
  struct Node n4 = {{NULL, NULL}, 'D'};
  struct Node n5 = {{NULL, NULL}, 'E'};
  struct Node n6 = {{NULL, NULL}, 'F'};

  BTree_Insert(tree, (BTreeNode*)&n1, 0, 0, 0);
  BTree_Insert(tree, (BTreeNode*)&n2, 0x00, 1, 0);
  BTree_Insert(tree, (BTreeNode*)&n3, 0x01, 1, 0);
  BTree_Insert(tree, (BTreeNode*)&n4, 0x00, 2, 0);
  BTree_Insert(tree, (BTreeNode*)&n5, 0x02, 2, 0);
  BTree_Insert(tree, (BTreeNode*)&n6, 0x02, 3, 0);

  printf("Full Tree: \n");

  BTree_Display(tree, printf_data, 4, '-');

  printf("Pre Order Traversal: \n");

  pre_order_traversal(BTree_Root(tree));

  printf("\n");

  printf("Middle Order Traversal: \n");

  middle_order_traversal(BTree_Root(tree));

  printf("\n");

  printf("Post Order Traversal: \n");

  post_order_traversal(BTree_Root(tree));

  printf("\n");

  printf("Leveel Orader Traversal: \n");

  level_order_traversal(BTree_Root(tree));

  printf("\n");

  BTree_Destroy(tree);

  return 0;
}