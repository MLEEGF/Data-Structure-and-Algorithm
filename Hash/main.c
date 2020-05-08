#include <stdio.h>
#include <stdlib.h>

#include "Hash.h"

struct Student {
  char* id;
  char* name;
  int age;
};

int compare_id(HashKey* k1, HashKey* k2) {
  return strcmp((char*)k1, (char*)k2);
}

int main(int argc, char* argv) {
  Hash* hash = Hash_Create();

  struct Student s1 = {"9001201", "Pointers", 30};
  struct Student s2 = {"0xCC", "Java", 50};
  struct Student s3 = {"taobao", "C++", 80};
  struct Student s4 = {"!@#$", "C#", 20};
  struct Student s5 = {"Python", "Python", 40};
  struct Student* ps = NULL;

  Hash_Add(hash, s1.id, &s1, compare_id);
  Hash_Add(hash, s2.id, &s2, compare_id);
  Hash_Add(hash, s3.id, &s3, compare_id);
  Hash_Add(hash, s4.id, &s4, compare_id);
  Hash_Add(hash, s5.id, &s5, compare_id);

  ps = Hash_Get(hash, "taobao", compare_id);

  printf("ID: %s\n", ps->id);
  printf("NAME: %s\n", ps->name);
  printf("AGE: %d\n", ps->age);

  Hash_Destroy(hash);

  return 0;
}