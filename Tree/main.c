#include <stdio.h>
#include <stdlib.h>

#include "GTree.h"

void printf_data(GTreeData* data) {
  printf("%c", (char)data);
}

int main(int argc, char *argv[]) {
  GTree* tree = GTree_Create();
  int i = 0;

/*   for (i = 0; i < 10; i++) {

  }
 */
  GTree_Insert(tree, (GTreeData*)'A', -1);
  GTree_Insert(tree, (GTreeData*)'B', 0);
  GTree_Insert(tree, (GTreeData*)'C', 0);
  GTree_Insert(tree, (GTreeData*)'D', 0);
  GTree_Insert(tree, (GTreeData*)'E', 1);
  GTree_Insert(tree, (GTreeData*)'F', 1);
  GTree_Insert(tree, (GTreeData*)'H', 3);
  GTree_Insert(tree, (GTreeData*)'I', 3);
  GTree_Insert(tree, (GTreeData*)'J', 3);

  GTree_Display(tree, printf_data, 2,' ');

  //GTree_Delete(tree, 3);

  printf("Get Tree Data: \n");

  for (i = 0; i < GTree_Count(tree); i++) {
    printf_data(GTree_Get(tree, i));
    printf("\n");
  }

  printf("After Deleting D: \n");

  GTree_Display(tree, printf_data, 2,'-');

  GTree_Clear(tree);

  printf("After Clear : \n");

  GTree_Display(tree, printf_data, 2,'-');

  GTree_Destroy(tree);
  system("pause");
  return 0;
}