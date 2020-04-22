#include <stdio.h>
#include <stdlib.h>

#include "GTree.h"
#include "LinkList.h"

typedef struct _tag_GTreeNode GTreeNode;
struct _tag_GTreeNode {
  GTreeData* data;
  GTreeNode* parent;
  LinkList* child;  //��������ĵ�ַ
};

//��������Ľ������
typedef struct _tag_TLNode TLNode;
struct _tag_TLNode {
  LinkListNode header; //���ĺ��ָ��
  GTreeNode* node;  //���Ĵ�ŵ�����Ԫ�����������ĵ�ַ
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

//�ݹ�ɾ��
//ɾ����֯�������������еĽ��
static void recursive_delete(LinkList* list, GTreeNode* node) {
  if ((list != NULL) && (node != NULL)) {
    GTreeNode* parent = node->parent;
    int index = -1;
    int i = 0;

    //����֯������ɾ��
    for (i = 0; i < LinkList_Length(list); i++) {
      TLNode* trNode = (TLNode*)LinkList_Get(list, i);

      if (trNode->node == node) {
        LinkList_Delete(list, i);

        free(trNode);

        index = i;

        break;
      }
    }
    
    //��˫�׽��ĺ���������ɾ��
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

      //���ý��ĺ���ɾ��
      while (LinkList_Length(node->child) > 0) {
        TLNode* trNode = (TLNode*)LinkList_Get(node->child, 0);

        recursive_delete(list, trNode->node);
      }

      LinkList_Destroy(node->child);

      free(node); //node��Insert�б�malloc������
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

      //���������߶ȱ߱Ƚ�
      //���һ����ֵһ�θ���һ�εĽ��бȽ�
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

    //�����Ķ������Ǻ�������Ķ���
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

//������֯�����Ϳ��Է���ÿһ�����
GTree* GTree_Create() {
  return LinkList_Create();
}

void GTree_Destroy(GTree* tree) {
  GTree_Clear(tree);
  LinkList_Destroy(tree);
}

//�����
void GTree_Clear(GTree* tree) {
  GTree_Delete(tree, 0);
}

//Ҫ����Ĳ���һ��������һ������
//���ʵ�ָ����ݷ���һ�����->��̬����һ���ṹ�����ڽṹ���������
//�û��ǲ�֪���ڲ������ʵ�ֵģ����������������У�����ʵ��������ʵ��
//�Ϸ����ж���λ�����ȷ��������Ҫ
//Ҫ��������еĽӽ�������������1��Ҫô��ǰ�ǿ�����������Ǹ���㣬��˫�ף�����
//2���������ĳ�����ĺ��ӽ��(�ض�����ĳ�����)
//��data����һ���������GTreeNode�е�GTreeData
//pPos�����data��˫�׽���λ��
int GTree_Insert(GTree* tree, GTreeData* data, int pPos) {
  LinkList* list = (LinkList*)tree;
  //pPos < LinkList_Length(list)����Ϊ�����Ѿ������Ľṹ���߼��ȹ�ϵ�Ѿ���ȷ
  int ret = (list != NULL) && (data != NULL) && (pPos < LinkList_Length(list)); //C�����в�Ϊ0��Ϊ��

  if (ret) {
    GTreeNode* cNode = (GTreeNode*)malloc(sizeof(GTreeNode)); //��data������
    //�����ǰ������Ǹ��ڵ���ôpNode�ͻ�Ϊ��
    //���� trNode cldNode ����ΪҪ����Ľ��Ҫ���������������
    //һ���Ǵ���������һ����˫�׵ĺ���������
    TLNode* trNode = (TLNode*)malloc(sizeof(TLNode));
    TLNode* cldNode = (TLNode*)malloc(sizeof(TLNode));
    //pPos�������˫�׽�����������pPosλ�ý�˫�׽��ȡ��
    //������������TLNode
    //�����ǰ������Ǹ��ڵ���ôpNode�ͻ�Ϊ��
    TLNode* pNode = (TLNode*)LinkList_Get(list, pPos);

    ret = (cNode != NULL) && (trNode != NULL) && (cldNode != NULL);

    if (ret) {
      cNode->data = data;
      //˫��ָ���Ǹ���pPosλ�õĽ����������
      //˫�׽��ĵ�ַ
      cNode->parent = NULL;
      //�˽��ĺ��ӽ�㴴�������ţ���һ�����ӽ��ĵ�ַ����������ĵ�һ�����
      cNode->child = LinkList_Create();

      //������֯������
      trNode->node = cNode;
      //���뺢��������
      cldNode->node = cNode;

      //��cNode���뵽��֯������
      LinkList_Insert(list, (LinkListNode*)trNode, LinkList_Length(list));
      //��cNode���뵽˫�׽���child����
      //�ж�˫�׽���ǲ���Ϊ�գ�Ϊ����ô�����������֯���ĵ�һ����㣬Ҳ�����ĸ����
      if (pNode != NULL) {
        //����˫�׽���ָ��
        cNode->parent = pNode->node;
        //���뺢��������
        LinkList_Insert(pNode->node->child, (LinkListNode*)cldNode, LinkList_Length(pNode->node->child));
      }else {
        free(cldNode); //������Ǹ���㲻�����κεĺ���
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

//ɾ��1������֯������ɾ��
//2���Ӻ���������ɾ��
//ɾ������ʱ��Ҫ��ɾ���ý��ĺ��ӽ�㡢����(�ݹ����)
GTreeData* GTree_Delete(GTree* tree, int pos) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, pos);
  GTreeData* ret = NULL;

  if (trNode != NULL) {
    ret = trNode->node->data;

    recursive_delete(tree, trNode->node);
  }

  return ret;
}

//����֯������posλ��������е����ݷ���
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

//�����ĸ߶����������ĸ߶�Ȼ��ѡ�� MAX,����1
int GTree_Height(GTree* tree) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);
  int ret = 0;

  //�ݹ�
  if (trNode != NULL) {
    ret = recursive_height(trNode->node);
  }
}

int GTree_Count(GTree* tree) {
  return LinkList_Length(tree);
}

//����
int GTree_Degree(GTree* tree) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);
  int ret = 0;

  if (trNode != NULL) {
    ret = recursive_degree(trNode->node);
  } 

  return ret;
}

//�����ı���ʾ���������ķ�����ʾ
//�����ӡ�����ĺ���ָ��
//gap����������С�� div�������ķ���
void GTree_Display(GTree* tree, GTree_Printf* pFunc,int gap, char div) {
  TLNode* trNode = (TLNode*)LinkList_Get(tree, 0);

  if ((trNode != NULL) && (pFunc != NULL)) {
    recursive_display(trNode->node, pFunc, 0, gap, div);
  }
}