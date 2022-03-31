/*
 * palindrome.cc - read in a line of text and see if it's a palindrome.
 *
 * Copyright (c) 2001, 2003, 2013 - Russell C. Bjork
 * Updated 2017, 2021 by Russ Tuck
 */

#include <stack>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;

int main(int argc, char * argv []) {
  stack<char> theStack;
  string toTest;

  cout << "Enter a string: ";
  getline(cin, toTest);

  while (cin.good() && toTest.length() > 0) {
    for (int i = 0; i < toTest.length(); i ++){
      theStack.push(toTest[i]);
    }

    bool ok = true;

    for (int i = 0; ok && i < toTest.length(); i ++) {
      if (toTest[i] == theStack.top()) {
                theStack.pop();
      } else {
        ok = false;
      }
    }

    if (ok) {
      cout << "Input was a palindrome" << endl;
    } else {
      cout << "Input was not a palindrome" << endl;
    }

    cout << "Enter another string, empty line to quit: ";
    getline(cin, toTest);
  }
}
