#include <stdio.h>
#include <stdlib.h>

#include "memory_node.h"
#include "vector.h"

void printError(int error_code) {
  switch (error_code) {
    case 0: printf("No error\n");
    break;
  }
}

int main(int argc, char **argv) {
  int error_code = 0;
  int *type1test;
  int *type2test;
  int *type3test = new int();
  int *type4[100];

  for (int i = 0; i < 100; ++i)
  {
    type4[i] = (int*)malloc(sizeof(int));
    *type4[i] = i;
  }
  
  //MEMORY NODE TEST
  MemoryNode ops;
  MemoryNode *test1 = nullptr;
  MemoryNode *test2 = nullptr;
  MemoryNode *test3 = nullptr;
  Vector *vec1 = nullptr;

  test2 = new MemoryNode();
  vec1 = new Vector(100);

  vec1->insertFirst(type3test);

  delete vec1;


  return 0;
}