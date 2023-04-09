// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#include <map>
#include "tstack.h"

int Priority(char c);
int Execute(char oper, int first, int second);
std::string infx2pstfx(std::string inpt);
int eval(std::string post);
const int size = 100;
TStack <unsigned char, size> ts;
TStack <int, size> val;
std::string Func1(unsigned char c, std::string output);
std::string infx2pstfx(std::string inpt) {
  std::size_t len = inpt.length();
  std::string output, buf;
  unsigned char c , tp = '\0';
  for (int i = 0; i < len; i++) {
    c = inpt[i];
    try {
      switch (c) {
        case '(':
          ts.push(c);
          break;
        case ')':
          tp = '\0';
          while (tp != '(') {
            tp = ts.pop();
            if (tp != '(') {
              output += tp;
              output += " ";
              std::cout << tp << " ";
            } else {
              break;
            }
          }
          break;
        case '+':
          buf = "";
          output += Func1(c, buf);
          break;
        case '-':
          buf = "";
          output += Func1(c, buf);
          break;
        case '*':
          buf = "";
          output += Func1(c, buf);
          break;
        case '/':
          buf = "";
          output += Func1(c, buf);
          break;
        default:
          if (c >= '0' && c <= '9') {
            output += c;
            output += " ";
            std::cout << c << " ";
          }
      }
    }
    catch (std::string e) {
      std::cout << e << std::endl;
    }
  }
  tp = '\0';
  while (!ts.isEmpty()) {
    tp = ts.pop();
    if (tp != '(') {
      output += tp;
      if (!ts.isEmpty())
        output += " ";
      std::cout << tp << " ";
    }
  }
  return output;
}
std::string Func1(unsigned char c, std::string outp) {
  char temp;
  if (!ts.isEmpty()) {
    temp = ts.get();
    while (!ts.isEmpty() && (Priority(temp) >= Priority(c))) {
      outp += ts.pop();
      outp += " ";
      std::cout << outp;
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
  char c;
  for (int i = 0; i < len; i++) {
    c = post[i];
    if (c == ' ') continue;
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
