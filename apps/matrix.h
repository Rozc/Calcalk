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

    friend istream& operator>>(istream& in, matrix& item);
    friend ostream& operator<<(ostream& out, const matrix& item);

    matrix operator+(matrix& r);
    matrix operator-(matrix& r);
    matrix operator*(matrix& r);
    friend matrix operator*(basicNumber, matrix&);

    matrix inverse();


    matrix T();
    basicNumber det();

};

void matModeInfo();


#endif //CALC_MATRIX_H
