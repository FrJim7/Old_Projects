/**
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

Vector::Vector() {
  head_ = 0;
  tail_ = 0;
  size_ = 0;
  storage_ = nullptr;
}

Vector::Vector(u16 capacity) {
  head_ = 0;
  tail_ = 0;
  size_ = capacity;
  storage_ = new MemoryNode[capacity];
}

Vector::Vector(const Vector &other) {
  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;
  storage_ = other.storage_;
}

Vector::~Vector() {
  if (nullptr != storage_) {
    delete[] storage_;
  }
  
  head_ = 0;
  tail_ = 0;
  size_ = 0;
  storage_ = nullptr;
}

s16 Vector::create(u16 capacity) {
  if (capacity <= 0) {
    return kErrorCode_InvalidPos;
  }
  head_ = 0;
  tail_ = 0;
  size_ = capacity;
  storage_ = new MemoryNode[capacity];
  return kErrorCode_OK;
}

s16 Vector::reset() {
  if (nullptr == storage_) {
    return kErrorCode_NullStorage;
  }
  for (int i = head_; i < size_; ++i) {
    storage_[i].reset();
  }
  head_ = 0;
  tail_ = 0;
  return kErrorCode_OK;
}

bool Vector::isEmpty() {
  return head_ == tail_;
}

bool Vector::isFull() {
  return tail_ == size_;
}

void* Vector::first() {
  if (nullptr != storage_) {
    return NULL;
  }
  return storage_[head_].data();
}

void* Vector::last() {
  if (nullptr == storage_) {
    return NULL;
  }
  if (0 != tail_) {
    return storage_[tail_ - 1].data();
  }
  return NULL;
}

void* Vector::at(u16 position) {
  if (nullptr == storage_) {
    return NULL;
  }
  if (tail_ <= position) {
    return NULL;
  }
  return storage_[position].data();
}

s16 Vector::insertFirst(void *data) {
  if (NULL == data) {
    return kErrorCode_NullSource;
  }
  if (nullptr == storage_) {
    return kErrorCode_NullStorage;
  }
  if (isFull()) {
    return kErrorCode_FullVector;
  }
  for (int i = tail_; i > head_; --i) {
    storage_[i].set_data(storage_[i - 1].data());
  }
  storage_[head_].set_data(data);
  tail_ ++;
  return kErrorCode_OK;
}

s16 Vector::insertLast(void *data) {
  if (NULL == data) {
    return kErrorCode_NullSource;
  }
  if (nullptr == storage_) {
    return kErrorCode_NullStorage;
  }
  if (isFull()) {
    return kErrorCode_FullVector;
  }
  storage_[tail_].set_data(data);
  tail_ ++;
  return kErrorCode_OK;
}

s16 Vector::insertAt(void *data, u16 position) {
  if (0 == position) {
    return insertFirst(data);
  }
  if (tail_ == position) {
    return insertLast(data);
  }
  if (NULL == data) {
    return kErrorCode_NullSource;
  }
  if (nullptr == storage_) {
    return kErrorCode_NullStorage;
  }
  if (isFull()) {
    return kErrorCode_FullVector;
  }
  if (position > tail_) {
    return kErrorCode_InvalidPos;
  }
  for (int i = tail_; i > position; --i) {
    storage_[i].set_data(storage_[i - 1].data());
  }
  storage_[position].set_data(data);
  tail_ ++;
  return kErrorCode_OK;
}

void* Vector::extractFirst() {
  if (nullptr == storage_) {
    return NULL;
  }
  if (isEmpty()) {
    return NULL;
  }
  return NULL;
}

void* Vector::extractLast() {
  if (nullptr == storage_) {
    return NULL;
  }
  if (isEmpty()) {
    return NULL;
  }
  return NULL;
}

void* Vector::extractAt(u16 position) {
  if (0 == position) {
    return extractFirst();
  }
  if (tail_ - 1 == position) {
    return extractLast();
  }
  if (nullptr == storage_) {
    return NULL;
  }
  if (isEmpty()) {
    return NULL;
  }
  if (position >= tail_) {
    return NULL;
  }
  return NULL;
}

u16 Vector::head() {
  return head_;
}

u16 Vector::tail() {
  return tail_;
}

u16 Vector::size() {
  return size_;
}

MemoryNode* Vector::storage() {
  return storage_;
}