//
// Created by Rozc on 2018/5/4.
//
// 基础实数类, 实现实数及其运算, 通过科学记数法 A*10e-B 实现, 利用 STL vector 储存


#ifndef CALC_BASICNUMBER_H
#define CALC_BASICNUMBER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class basicNumber {
private:
    bool AcNe; // 符号位, False 负 True 正
    vector<int> intPart; // 整数部分
    int ep; // 指数 10-ep, 应始终为正
    static int DIVISION_ITERATIONS; // 除法迭代次数, 相当于精度
    static int ROOT_ITERATIONS; // 开根号最大迭代次数

    // 辅助函数
    basicNumber helpIntDivi(basicNumber r);
    int comp(basicNumber r); // 比较运算符的辅助函数

public:
    basicNumber();
    basicNumber(const string&);
    basicNumber(const int);
    basicNumber(const long long);
    basicNumber(const double);
    basicNumber(const basicNumber& other);

    basicNumber& operator=(basicNumber r);
    basicNumber& operator=(int r);
    basicNumber& operator=(long long r);
    basicNumber& operator=(double r);

    friend ostream& operator<<(ostream& out, const basicNumber& item);
    friend istream& operator>>(istream& in, basicNumber& item);

    basicNumber operator+(basicNumber r);
    basicNumber operator+=(basicNumber r);
    basicNumber operator-(basicNumber r);
    basicNumber operator-=(basicNumber r);
    basicNumber operator*(basicNumber r);
    basicNumber operator*=(basicNumber r);
    basicNumber operator/(basicNumber r);
    basicNumber operator/=(basicNumber r);
    basicNumber operator%(basicNumber r);
    basicNumber operator%=(basicNumber r);
    basicNumber intDivision(basicNumber r); // 整数除法

    basicNumber operator+(double r);
    basicNumber operator+=(double r);
    basicNumber operator-(double r);
    basicNumber operator-=(double r);
    basicNumber operator*(double r);
    basicNumber operator*=(double r);
    basicNumber operator/(double r);
    basicNumber operator/=(double r);
    basicNumber operator%(double r);
    basicNumber operator%=(double r);
    basicNumber intDivision(long long r);

    friend basicNumber operator+(string num, basicNumber r);
    friend basicNumber operator-(string num, basicNumber r);
    friend basicNumber operator*(string num, basicNumber r);
    friend basicNumber operator/(string num, basicNumber r);
    friend basicNumber operator%(string num, basicNumber r);

    friend basicNumber operator+(long long num, basicNumber r);
    friend basicNumber operator-(long long num, basicNumber r);
    friend basicNumber operator*(long long num, basicNumber r);
    friend basicNumber operator/(long long num, basicNumber r);
    friend basicNumber operator%(long long num, basicNumber r);

    friend basicNumber operator+(int num, basicNumber r);
    friend basicNumber operator-(int num, basicNumber r);
    friend basicNumber operator*(int num, basicNumber r);
    friend basicNumber operator/(int num, basicNumber r);
    friend basicNumber operator%(int num, basicNumber r);

    friend basicNumber operator+(double num, basicNumber r);
    friend basicNumber operator-(double num, basicNumber r);
    friend basicNumber operator*(double num, basicNumber r);
    friend basicNumber operator/(double num, basicNumber r);
    friend basicNumber operator%(double num, basicNumber r);

    basicNumber operator-();
    basicNumber basicAbs();

    basicNumber operator++();
    const basicNumber operator++(int);
    basicNumber operator--();
    const basicNumber operator--(int);

    bool operator>(basicNumber r);
    bool operator<(basicNumber r);
    bool operator>=(basicNumber r);
    bool operator<=(basicNumber r);
    bool operator==(basicNumber r);
    bool operator!=(basicNumber r);

    void clearZero(); // 清除非必要 0

    basicNumber basicPower(basicNumber pow); // 要求指数为整数
    basicNumber basicRoot(basicNumber rot, basicNumber diff); // 牛顿迭代法

    basicNumber basicLn();
    basicNumber basicLog(basicNumber base);

    basicNumber basicCut(int); // 截断

//
//    basicNumber basicNumber::basicRound();
//    basicNumber basicNumber::basicFloor();
//    basicNumber basicNumber::basicCeil();
//
//    basicNumber basicNumber::basicSin();
//    basicNumber basicNumber::basicCos();
//    basicNumber basicNumber::basicTan();
//
//    basicNumber basicNumber::basicASin();
//    basicNumber basicNumber::basicACos();
//    basicNumber basicNumber::basicATan();


};

basicNumber basicGCD(basicNumber a, basicNumber b);
basicNumber basicLCM(basicNumber a, basicNumber b);


#endif //CALC_BASICNUMBER_H
