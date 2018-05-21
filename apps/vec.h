//
// Created by Rozc on 2018/5/4.
//

#ifndef CALC_VECTOR_H
#define CALC_VECTOR_H


#include "basicNumber.h"

class vec {
private:
    vector<basicNumber> v;
    int len;
public:
    vec(); // 没有直接构造需求, 故不编写一般的构造函数
    vec(const vector<basicNumber>& vec);
    vec(vec& other);

    bool isEmpty();

    vec operator+(vec& other);
    vec operator-(vec& other);
    vec& operator=(const vec& other);

    friend istream& operator>>(istream& in, vec& item);
    friend ostream& operator<<(ostream& out, const vec& item);

    basicNumber vecAbs();

    basicNumber vecInnerP(vec& right);
    vec vecOuterP(vec& right);
    vec vecNumP(basicNumber num);
    vec unitize();
};


void vecModeInfo();


#endif //CALC_VECTOR_H
