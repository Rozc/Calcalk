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


    // 辅助函数
    basicNumber helpIntDivi(basicNumber r);
    int comp(const basicNumber& r) const; // 比较运算符的辅助函数

public:
    static int DIVISION_ITERATIONS; // 除法迭代次数, 相当于精度
    static int ROOT_ITERATIONS; // 开根号最大迭代次数

    basicNumber();
    basicNumber(const string&);
    basicNumber(const int);
    basicNumber(const long long);
    basicNumber(const double);
    basicNumber(const basicNumber& other);

    bool getAcNe();
    int getEp();

    void wrongNumber();

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

    bool operator>(const basicNumber& r) const;
    bool operator<(const basicNumber& r) const;
    bool operator>=(const basicNumber& r) const;
    bool operator<=(const basicNumber& r) const;
    bool operator==(const basicNumber& r) const;
    bool operator!=(const basicNumber& r) const;

    void clearZero(); // 清除非必要 0

    basicNumber basicPower(basicNumber pow); // 要求指数为整数
    basicNumber basicRoot(basicNumber rot, basicNumber diff); // 牛顿迭代法

    basicNumber basicLn();
    basicNumber basicLog(basicNumber base);

    basicNumber basicCut(int); // 截断

    friend basicNumber basicRound(const basicNumber&, int d=0);
    friend basicNumber basicFloor(const basicNumber&, int d=0);
    friend basicNumber basicCeil(const basicNumber&, int d=0);

    friend basicNumber basicTriFHelp(const basicNumber&, int);
    friend basicNumber basicSin(const basicNumber&);
    friend basicNumber basicCos(const basicNumber&);
    friend basicNumber basicTan(const basicNumber&);

    friend basicNumber basicATriFHelp(const basicNumber& num, int typ);
    friend basicNumber basicASin(const basicNumber&);
    friend basicNumber basicACos(const basicNumber&);
    friend basicNumber basicATan(const basicNumber&);


};

basicNumber basicGCD(basicNumber a, basicNumber b);
basicNumber basicLCM(basicNumber a, basicNumber b);




// main Function
int oprtPriority(char op);
void realPre(string& expression);
string realRePolish(string expression);
basicNumber realCalcRP(string reP);
basicNumber realCalcWithOprt(basicNumber a, basicNumber b, char op);

basicNumber real2Calc(int, basicNumber&);

void realMode1(basicNumber&);
void realMode2(basicNumber&);

void realModeInfo();
void realMode1Info();
void realMode2Info();

void realMode1ERRORInfo();
void realMode2ERRORInfo();
#endif //CALC_BASICNUMBER_H
