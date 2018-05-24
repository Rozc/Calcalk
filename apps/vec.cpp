//
// Created by Rozc on 2018/5/4.
//

#include "vec.h"

vec::vec() {
    len = 0;
    v.clear();
}
vec::vec(const vector<basicNumber>& vec) {
    v = vec;
    len = vec.size();
}

vec::vec(vec& other) {
    v = other.v;
    len = other.len;
}

int vec::getLen() {
    return len;
}

istream& operator>>(istream& in, vec& item) {
    int len;
    basicNumber num;
    in >> len;
    item.len = len;
    item.v.clear();
    while(len--) {
        in >> num;
        if(num.getEp() == -1) {
            in.setstate(ios_base::failbit);
            break;
        }
        item.v.push_back(num);
    }
    return in;
}

ostream& operator<<(ostream& out, const vec& item) {
    out << "[ ";
    for(int i=0; i<item.len; i++) {
        out << item.v[i] << " ";
    }
    out << "]";
    return out;
}

vec vec::operator+(vec& r) {
    vec result;
    result.v.clear();
    if(len != r.len) {
        result.len = -1;
        return result;
    }

    for(int i=0; i<len; i++) {
        result.v.push_back(v[i]+r.v[i]);
    }
    result.len = len;

    return result;
}
vec vec::operator-(vec& r) {
    vec result;
    result.v.clear();
    if(len != r.len) {
        result.len = -1;
        return result;
    }

    for(int i=0; i<len; i++) {
        result.v.push_back(v[i]-r.v[i]);
    }
    result.len = len;

    return result;
}

vec& vec::operator=(const vec& other) {
    len = other.len;
    v = other.v;
    return *this;
}

basicNumber vec::vecAbs() {
    basicNumber result = 0;
    for(int i=0; i<len; i++) {
        result += v[i].basicPower(2);
    }
    result = result.basicRoot(2, 0.0001);
    return result;
}

basicNumber vec::vecInnerP(vec& right) {
    basicNumber result = 0;
    if(len != right.len) {
        result.setEp(-2);
        return result;
    }

    for(int i=0; i<len; i++) {
        result += v[i] * right.v[i];
    }
    return result;

}

vec vec::vecOuterP(vec& r) {
    /*叉乘仅限 2, 3 维的同维向量*/
    vec result;
    if(len > 3 || len != r.len) {
        result.len = -1;
        return result;
    }
    if(len == 2) {
        result.len = 3;
        result.v.push_back(0);
        result.v.push_back(0);
        result.v.push_back(v[0]*r.v[1] - r.v[0]*v[1]);
        return result;
    }
    if(len == 3) {
        result.len = 3;
        result.v.push_back(v[1]*r.v[2] - r.v[1]*v[2]);
        result.v.push_back(r.v[0]*v[2] - v[0]*r.v[2]);
        result.v.push_back(v[0]*r.v[1] - r.v[0]*v[1]);
        return result;
    }
}
vec vec::vecNumP(basicNumber num) {
    vec result = *this;
    for(int i=0; i<len; i++) {
        result.v[i] *= num;
    }
    return result;
}
vec vec::unitize() {
    vec result = *this;
    for(int i=0; i<len; i++) {
        result.v[i] /= this->vecAbs();
    }
    return result;
}


void vecModeInfo() {
    cout << "Now in Vector Mode" << endl;
    cout << "    How to use:" << endl;
    cout << "        We have 3 vector variables: a, b and n(ans)" << endl;
    cout << "            n(ans) is the result of last calculation." << endl;
    cout << "            if the result is not a vector, it won't be saved into n(ans)" << endl;
    cout << "            when you quit Vector Mode, all variables will be cleared." << endl;
    cout << "        There are 2 kind of operations:" << endl;
    cout << "            1. Input: set the value of variable a" << endl;
    cout << "            2. Input: set the value of variable b" << endl;
    cout << "            Calculate: calculation with the variables above and functions" << endl;
    cout << "                3. +, 4. -, 5. Inner Product, 6. Outer Product(Only for two or three dimension vector)" << endl;
    cout << "                7. Product with number" << endl;
    cout << "                8. Abs" << endl;
    cout << "                9. Unitize" << endl;
}