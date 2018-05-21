//
// Created by Rozc on 2018/5/4.
//

#ifndef CALC_IMAGENUMBER_H
#define CALC_IMAGENUMBER_H


#include "basicNumber.h"

class imageNumber {
private:
    basicNumber realPart;
    basicNumber imagePart;
public:
    imageNumber();
    imageNumber(const basicNumber&, const basicNumber&);
    imageNumber(const long long);
    imageNumber(const imageNumber& other);

    friend istream& operator>>(istream& in, imageNumber& item);
    friend ostream& operator<<(ostream& out, const imageNumber& item);

    imageNumber operator+(imageNumber& r);
    imageNumber operator-(imageNumber& r);
    imageNumber operator*(imageNumber& r);
    imageNumber operator/(imageNumber& r);
    imageNumber& operator=(imageNumber r);

    imageNumber& operator+=(imageNumber& r);
    imageNumber& operator-=(imageNumber& r);
    imageNumber& operator*=(imageNumber& r);
    imageNumber& operator/=(imageNumber& r);

    bool operator==(imageNumber& r);
    bool operator==(long long r);


    imageNumber imagePower(basicNumber pow);

    basicNumber imageAbs();
    basicNumber imageAngle();

    imageNumber imageConj();


};

void CmplxInput(imageNumber*);
void CmplxCalc(imageNumber*);

imageNumber CmplxBasicCalc(int, int, int, imageNumber*);

void CmplxCalcInfo();
void CmplxInputInfo();
void ComplexInfo();


#endif //CALC_IMAGENUMBER_H
