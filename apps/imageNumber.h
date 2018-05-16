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
    imageNumber(basicNumber, basicNumber);

    imageNumber operator+(imageNumber& r);
    imageNumber operator-(imageNumber& r);
    imageNumber operator*(imageNumber& r);
    imageNumber operator/(imageNumber& r);

    imageNumber imagePower(imageNumber pow);

    basicNumber imageAbs();
    double imageAngle();

    imageNumber imageConj();


};


#endif //CALC_IMAGENUMBER_H
