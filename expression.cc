/*
 * expression.cc - Implementation of a class representing simple arithmetic
 *                 expressions, as declared in expression.h.  Part of CPS222
 *                 Project 2.
 *
 * Skeleton copyright (c) 2001, 2013 - Russell C. Bjork
 *
 */

#include "expression.h"
#include <stack>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::cerr;

/* The following methods are to be written by students, and constitute
 * CPS222 Project 2.
 */

string Expression::convertToPostfix(string infix) {
  std::stack<char> theStack;
  string postfix = "";
  bool expectOperand = true;
  int infixLength = infix.length();
  int tail = infixLength - 1;
  for (int i = 0; i < infixLength; i++) {
    if (isdigit(infix[i])) {
      if (!expectOperand) {
        throw SyntaxError(i, "Operator expected");
      } else {
        postfix += infix[i];
        expectOperand = false;
      }
    } else if (infix[i] == '+' || infix[i] == '-') {
      if (expectOperand && infix[i] == '-') {
        infix[i] = '#';
        theStack.push(infix[i]);
      } else if (expectOperand) {
        throw SyntaxError(i, "Operand expected");
      } else {
        while (!theStack.empty() && theStack.top() != '(') {
          postfix += theStack.top();
          theStack.pop();
        }
        theStack.push(infix[i]);
        expectOperand = true;
      }
    } else if (infix[i] == ')') {
      if (expectOperand) {
        throw SyntaxError(i, "Operand expected");
      } else {
        while (!theStack.empty() && theStack.top() != '(') {
          postfix += theStack.top();
          theStack.pop();
        }
        if (theStack.empty()) {
          throw SyntaxError(i, "Unbalanced parentheses");
        } else {
          theStack.pop();
        }
      }
    } else if (infix[i] == '*' || infix[i] == '/') {
      if (expectOperand) {
        throw SyntaxError(i, "Operand expected");
      } else {
        while (!theStack.empty() && (theStack.top() == '*' || 
                theStack.top() == '/' || theStack.top() == '#')) {
          postfix += theStack.top();
          theStack.pop();
        }
        theStack.push(infix[i]);
        expectOperand = true;
      }
    } else if (infix[i] == '(') {
      if (!expectOperand) {
        throw SyntaxError(i, "Operator expected");
      } else {
        theStack.push(infix[i]);
      }
    } else {
      throw SyntaxError(i, "Invalid character");
    }
  }
  if (infix[tail] == '+' || infix[tail] == '-' || infix[tail] == '*' || 
      infix[tail] == '/' || infix[tail] == '(') {
    throw SyntaxError(tail, "Operand expected");
  } else if (infixLength == 0) {
    throw SyntaxError(0, "Operand expected");
  }
  while (!theStack.empty()) {
    if (theStack.top() == '(') {
      throw SyntaxError(tail, "Unbalanced parentheses");
    }
    postfix += theStack.top();
    theStack.pop();
  }
  return string(postfix);
}

int Expression::evaluate(string postfix) {
  std::stack<int> theStack;
  int postfixLength = postfix.length();
  for (int i = 0; i < postfixLength; i++) {
    if (isdigit(postfix[i])) {
      theStack.push(postfix[i] - 48);
    } else if (postfix[i] == '#') {
      int x = theStack.top();
      theStack.pop();
      theStack.push(-x);
    } else {
      int x = theStack.top();
      theStack.pop();
      int y = theStack.top();
      theStack.pop();
      if (postfix[i] == '+') {
        theStack.push(y + x);
      } else if (postfix[i] == '-') {
        theStack.push(y - x);
      } else if (postfix[i] == '*') {
        theStack.push(y * x);
      } else if (postfix[i] == '/') {
        if (x == 0) {
          throw DivideByZeroError(i);
        } else {
          theStack.push(y / x);
        }
      }
    }
  }
  return theStack.top();
}

string Expression::convertToPrefix(string postfix) {
  stack<string> theStack;
  int postfixLength = postfix.length();
  for (int i = 0; i < postfixLength; i++) {
    if (isdigit(postfix[i])) {
      theStack.push(postfix.substr(i, 1));
    } else if (postfix[i] == '#') {
      string op1 = theStack.top();
      theStack.pop();
      string negation = postfix[i] + op1;
      theStack.push(negation);
    } else {
      string op1 = theStack.top();
      theStack.pop();
      string op2 = theStack.top();
      theStack.pop();
      string convert = postfix[i] + op2 + op1;
      theStack.push(convert);
    }
  }
  return theStack.top();
}
