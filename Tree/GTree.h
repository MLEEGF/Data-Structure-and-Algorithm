#ifndef _GTree_H_
#define _GTree_H_

//做数据封装是希望直接拿来用就行，不需要知道如何实现的
typedef void GTree;
typedef void GTreeData;
//函数类型
typedef void (GTree_Printf)(GTreeData*);

GTree* GTree_Create();

void GTree_Destroy(GTree* tree);

void GTree_Clear(GTree* tree);

//插入的是数据而不是结点，结点由通用树的实现代码来分配
int GTree_Insert(GTree* tree, GTreeData* data, int pPos);

GTreeData* GTree_Delete(GTree* tree, int pos);

GTreeData* GTree_Get(GTree* tree, int pos);

GTreeData* GTree_Root(GTree* tree);

int GTree_Height(GTree* tree);

int GTree_Count(GTree* tree);

int GTree_Degree(GTree* tree);

//把树的树状结构显示
//树不是线性表，for循环是无法显示的
//函数指针，返回函数地址
void GTree_Display(GTree* tree, GTree_Printf* pFunc, int gap, char div);

#endif