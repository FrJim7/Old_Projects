/**
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __VECTOR_H__
#define __VECTOR_H__ 1

#include "adt_def.h"
#include "memory_node.h"

class Vector {
 public:
  Vector();
  Vector(u16 capacity);
 ~Vector();

  s16 create(u16 capacity);
  s16 reset();

  bool isEmpty();
  bool isFull();

  void* first();
  void* last();
  void* at(u16 position);

  s16 insertFirst(void* data);
  s16 insertLast(void* data);
  s16 insertAt(void* data, u16 position);

  void* extractFirst();
  void* extractLast();
  void* extractAt(u16 position);

  int length();
  u16 head();
  u16 tail();
  u16 size();
  MemoryNode* storage();

 protected:
  Vector(const Vector &other);

 private:
  MemoryNode *storage_;

  u16 size_;
  u16 head_;
  u16 tail_;
};

#endif//__VECTOR_H__