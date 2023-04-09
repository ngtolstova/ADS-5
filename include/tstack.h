// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template <typename T, int size>
class TStack {
  // добавьте код стека
 private:
  T arr[size] = {0};
  int top = 0;

 public:
  TStack(): top(-1) {}
  void push(const T& value) {
     if (isFull())
       throw std::string("Full");
     else
       arr[++top] = value;
    }
    const T& pop() {
      if (isEmpty())
        throw std::string("Empty");
      else
        return arr[top--];
    }
    const T& get() const {
      if (isEmpty())
        throw std::string("Empty");
      else
        return arr[top];
    }
    bool isEmpty() const {
      return top == -1;
    }
    bool isFull() const {
      return top == size - 1;
    }
    const T& GetArr(int i) {
      return arr[i];
    }
    int GetTop() {
      return top;
    }
};

#endif  // INCLUDE_TSTACK_H_
