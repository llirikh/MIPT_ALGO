#pragma once

#include "Node/Node.h"
#include <cstdio>
#include <iostream>

template <typename T>
class Stack {
 public:
  T pop();
  void push(T& val);

  void test() {
    Node* cur = tail_;
    for (int i = 0; i < size_; ++i) {
      std::cout << cur->val_ << ' ';
      cur = cur->prev_;
    }
    std::cout << '\n';
  }

  Stack() = default;

 private:
  struct Node;

  Node* tail_{nullptr};
  size_t size_{0};
};

template <typename T>
struct Stack<T>::Node {
  T val_;
  Node* prev_{nullptr};

  Node() = default;
  Node(T& val, Node* prev): val_{val}, prev_{prev} {}
  ~Node() = default;
};

template <typename T>
void Stack<T>::push(T& val) {
  Node new_tail(val, tail_);
  tail_ = &new_tail;
  size_ += 1;
}

template <typename T>
T Stack<T>::pop() {
  T ret_val(tail_->val_);
  Node* new_tail = tail_->prev_;
  tail_->~Node();
  tail_ = new_tail;
  --size_;
  return ret_val;
}