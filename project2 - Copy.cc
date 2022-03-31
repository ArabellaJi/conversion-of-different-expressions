/*
 * project2.cc - Main program for CPS222 project 2
 *
 * Repeatedly read infix expressions from standard input (one per line)
 * and echo each and print out various information.
 *
 * Copyright (c) 2001, 2003, 2013 - Russell C. Bjork
 *
 */

#include <iostream>
using namespace std;
#include "expression.h"

// Write out an expression with an extra space between characters
static void writeExpression(string expression) {
    for (size_t i = 0; i < expression.length(); i ++) {
        if (i != 0) cout << " ";
        cout << expression[i];
    }
}

// Write out an error marker carat (^) at specified place
static void writeErrorMarker(int position) {
    for (int i = 0; i < position; i ++) {
        cout << "  ";
    }
    cout << "^";
}

int main() {
    string infix, postfix, prefix;
    getline(cin, infix);
    while (! cin.eof()) {
        try {
            Expression theExpression(infix);

            cout << "Infix:   ";
            writeExpression(theExpression.getInfix());
            cout << endl;

            postfix = theExpression.getPostfix();
            if (postfix.length() > 0) {
                cout << "Postfix: ";
                writeExpression(postfix);
                cout << endl;

                int value = theExpression.getValue();
                cout << "Value:   " << value << endl;

                prefix = theExpression.getPrefix();
                if (prefix.length() > 0) {
                    cout << "Prefix:  ";
                    writeExpression(prefix);
                    cout << endl;
                }
            }
        }
        catch(SyntaxError e) {
            cout << "         ";
            writeErrorMarker(e.getPosition());
            cout << e.getDescription() << endl;
        }
        catch(DivideByZeroError e) {
            cout << "         ";
            writeErrorMarker(e.getPosition());
            cout << "Division by Zero" << endl;
        }

        cout << endl;

        getline(cin, infix);
    }
}
