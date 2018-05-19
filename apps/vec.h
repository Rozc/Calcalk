//
// Created by Rozc on 2018/5/4.
//

#ifndef CALC_VECTOR_H
#define CALC_VECTOR_H


#include "basicNumber.h"

class vec {
private:
    basicNumber len;
    vector<basicNumber> vect;
public:
    vec();
    vec(basicNumber* vec);
    vec(vec& other);

    vec operator+(vec& other);
    vec operator-(vec& other);

    basicNumber vecInnerP(vec& right);
    vec vecOuterP(vec& right);
    friend vec vecNumP(basicNumber& num, vec& v);
    vec unitize();
};


#endif //CALC_VECTOR_H
