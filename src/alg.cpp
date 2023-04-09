// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int Priority(char c);
int Execute(char oper, int second, int first);
std::string infx2pstfx(std::string input);
int eval(std::string post);
const int size = 100;
TStack <unsigned char, size> ts;
TStack <int, size> val;
std::string Func1(unsigned char c, int* j, std::string output);
std::string infx2pstfx(std::string inpt) {std::size_t len = inpt.length();
  static std::string output(len, '\0');
  unsigned char c, tp = '\0';
  int j = 0;
  for (int i = 0; i < len; i++) {
    c = inpt[i];
    switch (c) {
      case '(':
        ts.push(c);
        break;
      case ')':
        tp = '\0';
        while (tp != '(') {
          tp = ts.pop();
          if (tp!= '(') {
            output[j] = tp;
            j++;
          } else
            break;
        }
        break;
      case '+':
        output = Func1(c, &j, output);
        break;
      case '-':
        output = Func1(c, &j, output);
        break;
      case '*':
        output = Func1(c, &j, output);
        break;
      case '/':
        output = Func1(c, &j, output);
        break;
      default:
        if (c >= '0' && c <= '9') {
          output[j] = c;
          j++;
        }
    }
  }
  tp = '\0';
  while (ts.GetTop() >= 0) {
    tp = ts.pop();
    if (tp != '(') {
      output[j] = tp;
      j++;
    }
  }
  return output;
}
std::string Func1(unsigned char c, int* j, std::string outp) {
  char temp;
  if (ts.GetTop() >= 0) {
    temp = ts.get();
    while (ts.GetTop() >= 0 && (Priority(temp) >= Priority(c))) {
      outp[*j] = ts.pop();
      (*j)++;
    }
  }
  ts.push(c);
  return outp;
}
int Priority(char c) {
  int pr = 0;
  switch (c) {
    case '-':
      pr = 1;
      break;
    case '+':
      pr = 1;
      break;
    case '*':
      pr = 2;
      break;
    case '/':
      pr = 2;
      break;
    case '(':
      pr = 0;
      break;
  }
  return pr;
}
int eval(std::string post) {
  std::size_t len = post.length();
  int count = 0, z;
  std::string N;
  char c;
  for (int i = 0; i < len; i++) {
    c = post[i];
    if (c == '\0') {
      break;
    }
    if (c >= '0' && c <= '9') {
      z = atoi(&c);
      val.push(z);
    } else {
      int second = val.pop();
      int first = val.pop();
      z = Execute(c, first, second);
      val.push(z);
    }
  }
  return val.pop();
}
int Execute(char oper, int first, int second) {
  switch (oper) {
    case'+':
      return first + second;
    case'-':
      return first - second;
    case'*':
      return first * second;
    case'/':
      return first / second;
  }
  return 0;
}
