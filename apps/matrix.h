//
// Created by Rozc on 2018/5/4.
//

#ifndef CALC_MATRIX_H
#define CALC_MATRIX_H


#include "basicNumber.h"

class matrix {
private:
    basicNumber row;
    basicNumber col;
    basicNumber** mat;
public:
    matrix();
    matrix(matrix& other);
    explicit matrix(basicNumber**);

    matrix operator+(matrix& r);
    matrix operator-(matrix& r);
    matrix operator*(matrix& r);
    friend matrix matrixNumP(basicNumber num);

    matrix matrixT();
    basicNumber matrixDeterminant();

};


#endif //CALC_MATRIX_H
