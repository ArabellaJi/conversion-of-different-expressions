/*
 * reverse.cc - read in a line of text and print it out in reverse order:
 *
 * Copyright (c) 2001, 2003, 2021 - Russell C. Bjork, Russ Tuck
 */

#include <stack>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::stack;

int main(int argc, char * argv []) {
  stack<char> theStack;
  char c;

  while ((c = cin.get()) != '\n') {
    theStack.push(c);
  }

  while (! theStack.empty()) {
    cout << theStack.top();
    theStack.pop();
  }

  cout << endl;
}
