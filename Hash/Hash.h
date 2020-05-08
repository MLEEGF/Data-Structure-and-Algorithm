#ifndef _HASH_H_
#define _HASH_H_

typedef void Hash;

//关键字 将HashKey定义为void，键值对里的键可以是任何类型，
//如何比较大小，比较大小的工作交给使用这个结构的程序员
typedef void HashKey;
typedef void HashValue; //数据元素

//比较函数
typedef int (Hash_Compare)(HashKey*, HashKey*);

Hash* Hash_Create();

void Hash_Destroy(Hash* hash);

void Hash_Clear(Hash* hash);

int Hash_Add(Hash* hash, HashKey* key, HashValue* value, Hash_Compare* compare);

HashValue* Hash_Remove(Hash* hash, HashKey* key, Hash_Compare* compare);

HashKey* Hash_Get(Hash* hash, HashKey* key, Hash_Compare* compare);

int Hash_Count(Hash* hash);

#endif