//
// Created by Rozc on 2018/5/9.
//

#include <string>
#include <vector>
#include <cstdio>
#include <stack>

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

void realSolve(string expression) {
    stack<char> stkOperator;


}
