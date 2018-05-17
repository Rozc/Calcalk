//
// Created by Rozc on 2018/5/9.
//

#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include "basicNumber.h"

using namespace std;

string doubleToString(double num) {
    char str[256];
    sprintf(str, "%lf", num);
    string result = str;
    return result;
}

string intToString(long long num) {
    char str[256];
    sprintf(str, "%lld", num);
    string result = str;
    return result;
}

int oprtPriority(char op) {
    switch(op) {
        case '(':
        case ')':
            return 1;
        case '#':
            return 2;
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
            return 4;
        case '+':
        case '-':
            return 5;
        default:
            return -1;
    }
}

void realPre(string& expression) {
    int sz = expression.size();
    for(int i=0; i<sz; i++) {
        if(expression[i] == '-' && 
            (i==0 || 
            (expression[i-1] != ')' && 
            !(48 <= expression[i-1] && expression[i-1] < 58 )))) {
                
                expression[i] = '#';
            }
    }
}

void realRePolish(string expression) {
    realPre(expression);
    
    int sz = expression.size();
    stack<char> stkOprt;
    string RePolish;

    for(int i=0; i<sz; i++) {
        char expr = expression[i];
        if((48 <= expr && expr < 58) || expr == '.') {
            RePolish += expr;
        } else {

            RePolish += ',';
            if(expr == '(') {

                stkOprt.push(expr);

            } else if(expr == ')') {

                while(stkOprt.top() != '(') {
                    RePolish += stkOprt.top();
                    stkOprt.pop();
                }
                stkOprt.pop(); // Pop the '('

            } else  {
                
                if(stkOprt.empty() || stkOprt.top() == '(' ||
                    oprtPriority(expr)<oprtPriority(stkOprt.top())) {
                    stkOprt.push(expr);
                } else {
                    while(!stkOprt.empty() && stkOprt.top() != '(') {
                         RePolish += stkOprt.top();
                         stkOprt.pop();
                    }
                    stkOprt.push(expr);
                }

            }

        }
    }
    while(!stkOprt.empty()) {
        RePolish += stkOprt.top();
        stkOprt.pop();
    }

}
