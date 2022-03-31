#include "gtest/gtest.h"
#include "expression.h"

TEST(postfix, two) {
  Expression e("2");
  EXPECT_EQ("2", e.getPostfix());
}

TEST(postfix, addition) {
  Expression e("2+3+4");
  EXPECT_EQ("23+4+", e.getPostfix());
}

TEST(postfix, multiplication) {
  Expression e("2+3+4+3*4");
  EXPECT_EQ("23+4+34*+", e.getPostfix());
}

TEST(postfix, division) {
  Expression e("2+3*4+5*6/2");
  EXPECT_EQ("234*+56*2/+", e.getPostfix());
}

TEST(postfix, parentheses) {
  Expression e("(2)");
  EXPECT_EQ("2", e.getPostfix());
}

TEST(postfix, parenthesesMultiplication) {
  Expression e("(1+3)*(2+4)");
  EXPECT_EQ("13+24+*", e.getPostfix());
}

TEST(postfix, parenthesesDivision) {
  Expression e("3*((2+4)*(1+1)+7)/(2*5+9)");
  EXPECT_EQ("324+11+*7+*25*9+/", e.getPostfix());
}

TEST(postfix, parenthesesAddition) {
  Expression e("7+4*(2+4*(7-2)*(5*(4-2))/(5*4*5))");
  EXPECT_EQ("742472-*542-**54*5*/+*+", e.getPostfix());
}

TEST(postfix, someParentheses) {
  Expression e("(((2)))");
  EXPECT_EQ("2", e.getPostfix());
}

TEST(evaluate, two) {
  Expression e("2");
  EXPECT_EQ(2, e.getValue());
}

TEST(evaluate, addition) {
  Expression e("2+3+4");
  EXPECT_EQ(9, e.getValue());
}

TEST(evaluate, multiplication) {
  Expression e("2+3+4+3*4");
  EXPECT_EQ(21, e.getValue());
}

TEST(evaluate, division) {
  Expression e("2+3*4+5*6/2");
  EXPECT_EQ(29, e.getValue());
}

TEST(evaluate, parentheses) {
  Expression e("(2)");
  EXPECT_EQ(2, e.getValue());
}

TEST(evaluate, parenthesesMultiplication) {
  Expression e("(1+3)*(2+4)");
  EXPECT_EQ(24, e.getValue());
}

TEST(evaluate, parenthesesDivision) {
  Expression e("3*((2+4)*(1+1)+7)/(2*5+9)");
  EXPECT_EQ(3, e.getValue());
}

TEST(evaluate, parenthesesAddition) {
  Expression e("7+4*(2+4*(7-2)*(5*(4-2))/(5*4*5))");
  EXPECT_EQ(23, e.getValue());
}

TEST(evaluate, someParentheses) {
  Expression e("(((2)))");
  EXPECT_EQ(2, e.getValue());
}

TEST(prefix, two) {
  Expression e("2");
  EXPECT_EQ("2", e.getPrefix());
}

TEST(prefix, addition) {
  Expression e("2+3+4");
  EXPECT_EQ("++234", e.getPrefix());
}

TEST(prefix, multiplication) {
  Expression e("2+3+4+3*4");
  EXPECT_EQ("+++234*34", e.getPrefix());
}

TEST(prefix, division) {
  Expression e("2+3*4+5*6/2");
  EXPECT_EQ("++2*34/*562", e.getPrefix());
}

TEST(prefix, parentheses) {
  Expression e("(2)");
  EXPECT_EQ("2", e.getPrefix());
}

TEST(prefix, parenthesesMultiplication) {
  Expression e("(1+3)*(2+4)");
  EXPECT_EQ("*+13+24", e.getPrefix());
}

TEST(prefix, parenthesesDivision) {
  Expression e("3*((2+4)*(1+1)+7)/(2*5+9)");
  EXPECT_EQ("/*3+*+24+117+*259", e.getPrefix());
}

TEST(prefix, parenthesesAddition) {
  Expression e("7+4*(2+4*(7-2)*(5*(4-2))/(5*4*5))");
  EXPECT_EQ("+7*4+2/**4-72*5-42**545", e.getPrefix());
}

TEST(prefix, someParentheses) {
  Expression e("(((2)))");
  EXPECT_EQ("2", e.getPrefix());
}

// The tests below illustrate the error messages

TEST(postfixError, empty) {
  // test that invalid empty expression causes syntax error
  try {
    Expression e("");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(0, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, plus) {
  try {
    Expression e("+");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(0, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingOp1) {
  try {
    Expression e("1+23");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
  }
}

TEST(postfixError, missingOp2) {
  try {
    Expression e("0+12*3");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
  }
}

TEST(postfixError, missingOp3) {
  try {
    Expression e("1+2(3+4)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
  }
}

TEST(postfixError, missingOp4) {
  try {
    Expression e("(1+2)3+4");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(5, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
  }
}

TEST(postfixError, missingNum1) {
  try {
    Expression e("0+*1+2");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(2, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingNum2) {
  try {
    Expression e("(*4)+(2*4)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(1, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingNum3) {
  try {
    Expression e("(2*)+(2*4)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingNum4) {
  try {
    Expression e("((1*3)+)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(7, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingParen) {
  try {
    Expression e("1)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(1, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen2) {
  try {
    Expression e("(1*3)+(2*4");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(9, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen3) {
  try {
    Expression e("((((2)))");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(7, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen4) {
  try {
    Expression e("1+2)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen5) {
  try {
    Expression e("(1*3))");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(5, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen6) {
  try {
    Expression e("(1*3))(");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(5, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen7) {
  try {
    Expression e("(1*3))+(2");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(5, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, invaildCharacter1) {
  try {
    Expression e("a+2");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(0, e.getPosition());
    EXPECT_EQ("Invalid character", e.getDescription());
  }
}

TEST(postfixError, invaildCharacter2) {
  try {
    Expression e("1a2");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(1, e.getPosition());
    EXPECT_EQ("Invalid character", e.getDescription());
  }
}

TEST(postfixError, divideByZeroError1) {
  try {
    Expression e("3/0");
    e.getValue();
    FAIL() << "Didn't throw the expected exception.";
  } catch(DivideByZeroError &e) {
    EXPECT_EQ(2, e.getPosition());
  }
}

TEST(postfixError, divideByZeroError2) {
  try {
    Expression e("3/(1-1)");
    e.getValue();
    FAIL() << "Didn't throw the expected exception.";
  } catch(DivideByZeroError &e) {
    EXPECT_EQ(4, e.getPosition());
  }
}

// The tests below are for negations

TEST(postfix, negation1) {
  Expression e("-3");
  EXPECT_EQ("3#", e.getPostfix());
}

TEST(postfix, negation2) {
  Expression e("2*-3");
  EXPECT_EQ("23#*", e.getPostfix());
}

TEST(postfix, negation3) {
  Expression e("2*(-3)");
  EXPECT_EQ("23#*", e.getPostfix());
}

TEST(postfix, negation4) {
  Expression e("-2*3");
  EXPECT_EQ("2#3*", e.getPostfix());
}

TEST(postfix, negation5) {
  Expression e("--3");
  EXPECT_EQ("3##", e.getPostfix());
}

TEST(postfix, negation6) {
  Expression e("---3");
  EXPECT_EQ("3###", e.getPostfix());
}

TEST(postfix, negation7) {
  Expression e("2*---3");
  EXPECT_EQ("23###*", e.getPostfix());
}

TEST(postfix, negation8) {
  Expression e("2*(---3)");
  EXPECT_EQ("23###*", e.getPostfix());
}

TEST(postfix, negation9) {
  Expression e("---2*2+--3");
  EXPECT_EQ("2###2*3##+", e.getPostfix());
}

TEST(evaluate, negation1) {
  Expression e("-3");
  EXPECT_EQ(-3, e.getValue());
}

TEST(evaluate, negation2) {
  Expression e("2*-3");
  EXPECT_EQ(-6, e.getValue());
}

TEST(evaluate, negation3) {
  Expression e("2*(-3)");
  EXPECT_EQ(-6, e.getValue());
}

TEST(evaluate, negation4) {
  Expression e("-2*3");
  EXPECT_EQ(-6, e.getValue());
}

TEST(evaluate, negation5) {
  Expression e("--3");
  EXPECT_EQ(3, e.getValue());
}

TEST(evaluate, negation6) {
  Expression e("---3");
  EXPECT_EQ(-3, e.getValue());
}

TEST(evaluate, negation7) {
  Expression e("2*---3");
  EXPECT_EQ(-6, e.getValue());
}

TEST(evaluate, negation8) {
  Expression e("2*(---3)");
  EXPECT_EQ(-6, e.getValue());
}

TEST(evaluate, negation9) {
  Expression e("---2*2+--3");
  EXPECT_EQ(-1, e.getValue());
}