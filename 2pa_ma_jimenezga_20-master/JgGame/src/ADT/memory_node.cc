/**
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */

#include "memory_node.h"

#include <stdio.h>
#include <stdlib.h>

MemoryNode::MemoryNode() {
  data_ = NULL;
}

MemoryNode::MemoryNode(const MemoryNode &other) {
  data_ = other.data_;
}

MemoryNode::~MemoryNode() {
  data_ = NULL;
}

s16 MemoryNode::reset() {
  data_ = NULL;
  return kErrorCode_OK;
}

s16 MemoryNode::set_data(void *data) {
  if (NULL == data) {
    return kErrorCode_InvalidData;
  }
  data_ = data;
  return kErrorCode_OK;
}

void* MemoryNode::data() {
  return data_;
}