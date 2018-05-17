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
        case ''
    }
}

void realSolve(const string& expression) {
    int sz = (int)expression.size();
    stack<char> stkOprt;
    string RePolish;

    for(int i=0; i<sz; i++) {
        char exp = expression[i];
        if((48 <= exp && exp < 58) || exp == '.') {
            RePolish += exp;
        } else {

            RePolish += ',';
            if(exp == '(') {

                stkOprt.push(exp);

            } else if(exp == ')') {

                while(stkOprt.top() != '(') {
                    RePolish += stkOprt.top();
                    stkOprt.pop();
                }
                stkOprt.pop(); // Pop the '('

            } else {



            }

        }
    }

}
