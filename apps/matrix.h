//
// Created by Rozc on 2018/5/4.
//

#ifndef CALC_MATRIX_H
#define CALC_MATRIX_H


#include "basicNumber.h"

#include <vector>

class matrix {
private:
    vector<vector<int> > mat;
public:
    matrix();
    matrix(matrix& other);
    matrix(vector<vector<int> >&);

    matrix operator+(matrix& r);
    matrix operator-(matrix& r);
    matrix operator*(matrix& r);
    friend matrix matrixNumP(basicNumber num, vector<vector<int> > vec);

    matrix matrixT();
    basicNumber matrixDeterminant();

};


#endif //CALC_MATRIX_H
