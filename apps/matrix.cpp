//
// Created by Rozc on 2018/5/4.
//

#include "matrix.h"


matrix::matrix() {
    mat = vector<vector<basicNumber> >(1,vector<basicNumber>(1));
    row = 0;
    col = 0;
}

matrix::matrix(vector<vector<basicNumber> >& arr) {
    row = arr.size();
    col = arr[0].size();
    mat = arr;
}

matrix::matrix(const matrix& other) {
    mat = other.mat;
    row = other.row;
    col = other.col;
}

int matrix::getRow() const {
    return row;
}
int matrix::getCol() const {
    return col;
}

bool isHomotypic(const matrix& a, const matrix& b) {
    return (a.row == b.row) && (a.col == b.col);
}

matrix matrix::operator+(matrix& r) const {
    matrix result;
    if(!isHomotypic(*this, r)) {
        result.row = -1;
        return result;
    }

    result.mat = mat;

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            result.mat[i][j] += r.mat[i][j];

    return result;
}
matrix matrix::operator-(matrix& r) const {
    matrix result;
    if(!isHomotypic(*this, r)) {
        result.row = -1;
        return result;
    }

    result.mat = mat;

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            result.mat[i][j] -= r.mat[i][j];

    return result;
}
matrix matrix::operator*(matrix& r) const {
    matrix result;
    if(this->col != r.row) {
        result.row = -1;
        return result;
    }
    result.mat = vector<vector<basicNumber> >(row, vector<basicNumber>(r.col, 0));
    result.row = row;
    result.col = r.col;

    for(int i=0; i<row; i++)
        for(int j=0; j<r.col; j++)
            for(int k=0; k<col; k++)
                result.mat[i][j] += mat[i][k] * r.mat[k][j];

    return result;
}
matrix operator*(const basicNumber& num, const matrix& r) const {
    matrix result = r;
    for(int i=0; i<r.row; i++)
        for(int j=0; j<r.col; j++)
            result.mat[i][j] *= num;

    return result;
}

basicNumber matrix::matrixDet() {
    basicNumber value=0;
    if(row == col) {
        basicNumber sum=0;
        int num=row;

        if(num == 1) {
            value = mat[0][0];
            return value;
        } else if(num == 2) {
            value = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
            return value;

        } else {
            matrix temp[num];
            for(int i=0;i<num;i++) {
                temp[i].mat = vector<vector<basicNumber> >(num-1, vector<basicNumber>(num-1, 0));
                temp[i].row = temp[i].col = num-1;
            }

            basicNumber val[num];

            for(int i=0;i<num;i++) {
                for(int j=0;j<num;j++) {
                    for(int k=1;k<num;k++) {
                        if(j<i) {
                            temp[i].mat[k-1][j]=mat[k][j];
                        } else if(j>i) {
                            temp[i].mat[k-1][j-1]=mat[k][j];
                        } else
                            break;
                    }
                }
                val[i]=basicNumber(-1).basicPower(2+i)*temp[i].matrixDet()*mat[0][i];
            }
            for(int i=0;i<num;i++) {
                sum=sum+val[i];
            }
            return sum;
        }


    } else {
        value.wrongNumber();
        return value;
    }
}