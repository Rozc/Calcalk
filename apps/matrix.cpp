//
// Created by Rozc on 2018/5/4.
//

#include "matrix.h"
#include "basicNumber.h"
#include <vector>


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

matrix matrix::operator+(matrix& r) {
    matrix result;
    if(!isHomotypic(*this, r)) {
        result.row = -1;
        return result;
    }

    result.row = row;
    result.col = col;
    result.mat = mat;

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            result.mat[i][j] += r.mat[i][j];

    return result;
}
matrix matrix::operator-(matrix& r) {
    matrix result;
    if(!isHomotypic(*this, r)) {
        result.row = -1;
        return result;
    }

    result.row = row;
    result.col = col;
    result.mat = mat;

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            result.mat[i][j] -= r.mat[i][j];

    return result;
}
matrix matrix::operator*(matrix& r) {
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
matrix operator*(basicNumber num, matrix& r) {
    matrix result = r;
    for(int i=0; i<r.row; i++)
        for(int j=0; j<r.col; j++)
            result.mat[i][j] *= num;

    return result;
}

istream& operator>>(istream& in, matrix& item) {
    int row, col;
    in >> row >> col;
    if(!in) {
        in.setstate(ios_base::failbit);
        return in;
    }
    item.row = row;
    item.col = col;
    item.mat = vector<vector<basicNumber> >(row, vector<basicNumber>(col, 0));

    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            in >> item.mat[i][j];
            if(!in) {
                in.setstate(ios_base::failbit);
                return in;
            }
        }
    }

    return in;

}
ostream& operator<<(ostream& out, const matrix& item) {

    if(item.col == 0 && item.row == 0) {
        cout << "[ ]";
    } else {
        for(int i=0; i<item.row; i++) {
            out << "| ";
            for(int j=0; j<item.col; j++) {
                cout << item.mat[i][j] << " ";
            }
            out << "|" << endl;
        }
    }
    return out;

}

//basicNumber matrix::det() {
//    basicNumber value=0;
//    if(row == col) {
//        basicNumber sum=0;
//        int num=row;
//
//        if(num == 1) {
//            value = mat[0][0];
//            return value;
//        } else if(num == 2) {
//            value = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
//            return value;
//
//        } else {
//            matrix temp[num];
//            for(int i=0;i<num;i++) {
//                temp[i].mat = vector<vector<basicNumber> >(num-1, vector<basicNumber>(num-1, 0));
//                temp[i].row = temp[i].col = num-1;
//            }
//
//            basicNumber val[num];
//
//            for(int i=0;i<num;i++) {
//                for(int j=0;j<num;j++) {
//                    for(int k=1;k<num;k++) {
//                        if(j<i) {
//                            temp[i].mat[k-1][j]=mat[k][j];
//                        } else if(j>i) {
//                            temp[i].mat[k-1][j-1]=mat[k][j];
//                        } else
//                            break;
//                    }
//                }
//                val[i]=basicNumber(-1).basicPower(2+i)*temp[i].det()*mat[0][i];
//            }
//            for(int i=0;i<num;i++) {
//                sum=sum+val[i];
//            }
//            return sum;
//        }
//
//
//    } else {
//        value.setEp(-2);
//        return value;
//    }
//}

basicNumber matrix::det() {
    basicNumber result = 1;
    if(row != col) {
        result.setEp(-2);
        return result;
    }

    int cnt = 0;
    matrix upTriMat = *this;
    int n = row;
    basicNumber coe;
    bool allZeroFlag = false;

    for(int i=0; i<n; i++) {

        if(upTriMat.mat[i][i] == 0) {
            allZeroFlag = true;
            for(int j=i+1; j<n; j++) {
                if(upTriMat.mat[j][i] != 0) {
                    swap(upTriMat.mat[i], upTriMat.mat[j]);
                    cnt++;
                    allZeroFlag = false;
                    break;
                }
            }
        }
        if(allZeroFlag) {
            allZeroFlag = false;
            continue;
        }

        for(int j=i+1; j<n; j++) {
            coe = -1 * upTriMat.mat[j][i] / upTriMat.mat[i][i];
            for(int k=0; k<n; k++) {
                upTriMat.mat[j][k] += upTriMat.mat[i][k] * coe;
                upTriMat.mat[j][k] = basicRound(upTriMat.mat[i][k], 3);
            }
        }

    }

    for(int i=0; i<n; i++) {
        result *= upTriMat.mat[i][i];
    }
    result *= basicNumber(-1).basicPower(cnt);
    result = basicRound(result, 3);
    return result;

}

matrix matrix::inverse() {
    matrix cop = *this, result;

    if(row != col || this->det() == 0) {
        result.row = -1;
        return result;
    }

    result.row = row;
    result.col = col;
    result.mat = vector<vector<basicNumber> >(row, vector<basicNumber>(col, 0));

    for(int i=0; i<row; i++)
        result.mat[i][i] = 1;

    int n = row;
    basicNumber coe;
    for(int i=0; i<n; i++) {

        if(cop.mat[i][i] == 0) {
            for(int j=i+1; j<n; j++) {
                if(cop.mat[j][i] != 0) {
                    swap(cop.mat[i], cop.mat[j]);
                    swap(result.mat[i], result.mat[j]);
                    break;
                }
            }
        }

        for(int j=0; j<n; j++) {
            if(j == i) {
                continue;
            }
            coe = -1 * cop.mat[j][i] / cop.mat[i][i];
            for(int k=0; k<n; k++) {
                cop.mat[j][k] += cop.mat[i][k] * coe;
                cop.mat[j][k] = basicRound(cop.mat[j][k], 3);
                result.mat[j][k] += result.mat[i][k] * coe;
                result.mat[j][k] = basicRound(result.mat[j][k], 3);
            }
        }
    }

    for(int i=0; i<n; i++) {
        if(cop.mat[i][i] != 1) {
            for(int j=0; j<n; j++) {
                result.mat[i][j] /= cop.mat[i][i];
                result.mat[i][j] = basicRound(result.mat[i][j], 3);
            }

        }
    }

    return result;

}

matrix matrix::T() {
    matrix result;
    result.row = col;
    result.col = row;
    result.mat = vector<vector<basicNumber> >(col, vector<basicNumber>(row, 0));

    for(int i=0; i<col; i++)
        for(int j=0; j<row; j++)
            result.mat[i][j] = mat[j][i];

    return result;
}

void matModeInfo() {
    cout << "Now in Vector Mode" << endl;
    cout << "    How to use:" << endl;
    cout << "        We have 3 matrix variables: a, b and n(ans)" << endl;
    cout << "            n(ans) is the result of last calculation." << endl;
    cout << "            if the result is not a vector, it won't be saved into n(ans)" << endl;
    cout << "            when you quit Matrix Mode, all variables will be cleared." << endl;
    cout << "        There are 2 kind of operations:" << endl;
    cout << "            1. Input: set the value of variable a" << endl;
    cout << "            2. Input: set the value of variable b" << endl;
    cout << "            Calculate: calculation with the variables above and functions" << endl;
    cout << "                3. +, 4. -, 5. *" << endl;
    cout << "                6. Product with number" << endl;
    cout << "                7. Determinant of a square matrix" << endl;
    cout << "                8. Transpose" << endl;
}