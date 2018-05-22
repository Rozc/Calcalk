//
// Created by Rozc on 2018/5/4.
//

#ifndef CALC_MATRIX_H
#define CALC_MATRIX_H


#include "basicNumber.h"

#include <vector>

class matrix {
private:
    vector<vector<basicNumber> > mat;
    int row;
    int col;

    friend bool isHomotypic(const matrix& a, const matrix& b);
public:
    matrix();
    matrix(const matrix& other);
    matrix(vector<vector<basicNumber> >&);

    int getRow() const;
    int getCol() const;

    // TODO: operator stream

    matrix operator+(matrix& r) const;
    matrix operator-(matrix& r) const;
    matrix operator*(matrix& r) const;
    friend matrix operator*(const basicNumber&, const matrix&) const;

    // matrix inverseMatrix() const;


    matrix matrixT();
    basicNumber matrixDet();

};


#endif //CALC_MATRIX_H
