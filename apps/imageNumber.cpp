//
// Created by Rozc on 2018/5/4.
//

#include <sstream>
#include "imageNumber.h"
#include "basicNumber.h"

using namespace std;

imageNumber::imageNumber() {
    realPart = 0;
    imagePart = 0;
}
imageNumber::imageNumber(const basicNumber& real, const basicNumber& image) {
    realPart = real;
    imagePart = image;
}
imageNumber::imageNumber(const long long real) {
    realPart = real;
}
imageNumber::imageNumber(const imageNumber& other) {
    realPart = other.realPart;
    imagePart = other.imagePart;
}

ostream& operator<<(ostream& out, const imageNumber& item) {

    // Output Real Part
    if(item.realPart != 0) {
        out << item.realPart;
    }

    // Output Image Part
    if(item.imagePart != 0) {

        if(item.imagePart > 0 && item.realPart != 0) {
            out << '+';
        }

        if(item.imagePart == -1) {
            out << '-';
        } else if(item.imagePart != 1) {
            out << item.imagePart;
        }
        out << 'i';
    }

    if(item.realPart == 0 && item.imagePart == 0) {
        out << '0';
    }


    return out;
}
istream& operator>>(istream& in, imageNumber& item) {
    item.realPart = item.imagePart = 0;

    string buf;
    in >> buf;

    item.realPart = realCalcRP(realRePolish(buf.substr(0, buf.find(',')), 0));
    item.imagePart = realCalcRP(realRePolish(buf.substr(buf.find(',')+1), 0));

    if(item.realPart.getEp() == -1 || item.imagePart.getEp() == -1) {
        in.setstate(ios_base::failbit);
    }

    return in;
}

imageNumber imageNumber::operator+(imageNumber &r){
    imageNumber result;
    result.realPart = realPart + r.realPart;
    result.imagePart = imagePart + r.imagePart;
    return result;
}
imageNumber& imageNumber::operator+=(imageNumber &r) {
    *this = *this + r;
    return *this;
}

imageNumber imageNumber::operator-(imageNumber &r) {
    imageNumber result;
    result.realPart = realPart - r.realPart;
    result.imagePart = imagePart - r.imagePart;
    return result;
}
imageNumber& imageNumber::operator-=(imageNumber& r) {
    *this = *this - r;
    return *this;
}

imageNumber imageNumber::operator*(imageNumber &r) {
    imageNumber result;
    result.realPart = realPart*r.realPart - imagePart*r.imagePart;
    result.imagePart = realPart*r.imagePart + imagePart*r.realPart;
    return result;
}
imageNumber& imageNumber::operator*=(imageNumber &r) {
    *this = *this * r;
    return *this;
}

imageNumber imageNumber::operator/(imageNumber &r) {
    imageNumber result;
    result.realPart = (realPart*r.imagePart + imagePart*r.realPart)/r.imageAbs();
    result.imagePart = (imagePart*r.realPart + realPart*r.imagePart)/r.imageAbs();
    return result;
}
imageNumber& imageNumber::operator/=(imageNumber &r) {
    *this = *this / r;
    return *this;
}

imageNumber& imageNumber::operator=(imageNumber r) {
    realPart = r.realPart;
    imagePart = r.imagePart;
    return *this;
}

bool imageNumber::operator==(imageNumber& r) {
    return realPart == r.realPart && imagePart == r.imagePart;
}
bool imageNumber::operator==(long long r) {
    return realPart == r && imagePart == 0;
}

imageNumber imageNumber::imagePower(basicNumber pow) {
    imageNumber result = 1;

    for(basicNumber i=0; i<pow; i++) {
        result *= *this;
    }
    return result;
}

basicNumber imageNumber::imageAbs() {
    return (realPart.basicPower(2) + imagePart.basicPower(2)).basicRoot(2, 0.0001);
}

basicNumber imageNumber::imageAngle() {
    return basicATan(imagePart/realPart);
}

imageNumber imageNumber::imageConj() {
    imageNumber result = *this;
    result.imagePart = -result.imagePart;
    return result;
}



// Process Function

void CmplxInput(imageNumber* var) {
    int vari;
    int errorCode = 0;

    while (true) {
        system("cls");
        CmplxInputInfo();
        cout << "Value of variables now: " << endl;
        cout << "    a: " << var[0] << endl;
        cout << "    b: " << var[1] << endl;
        cout << "    c: " << var[2] << endl;
        cout << "    d: " << var[3] << endl;

        if(errorCode == 1) {
            cout << "Bad input, please input positive integer between 0 to 4)" << endl;
        } else if(errorCode == 2) {
            cout << "Bad format: Format: (+/-)a(+/-)bi e.g. 1.2+3.4i, -1.2+3.4i, 1.2, -3.4i, i, -i" << endl;
        }

        cout << "Please choose the variable you want to set(1. a, 2. b, 3. c, 4. d, 0 to quit): ";
        cin >> vari;
        if (!cin) {
            errorCode = 1;
            cin.clear();
            while (cin.get() != '\n');
            continue;
        }
        while (cin.get() != '\n');

        if(vari == 0) {
            goto CmplxInputExit;
        } else if(vari <= 4) {

            cout << "Please input the value you want to set: ";
            cin >> var[vari-1];
            if (!cin) {
                errorCode = 2;
                cin.clear();
                while (cin.get() != '\n');
                continue;
            }
            while (cin.get() != '\n');
            errorCode = 0;
            continue;

        } else {
            errorCode = 1;
        }
    }

    CmplxInputExit:
    system("cls");
    ComplexInfo();
}

void CmplxCalc(imageNumber* var) {
    int oprt;
    int errorCode = 0;

    while(true) {
        system("cls");
        CmplxCalcInfo();
        cout << "Value of variables now: " << endl;
        cout << "    a: " << var[0] << endl;
        cout << "    b: " << var[1] << endl;
        cout << "    c: " << var[2] << endl;
        cout << "    d: " << var[3] << endl;
        cout << "    n: " << var[4] << endl;

        cout << "Functions and Operations List: " << endl;
        cout << "    1. +, 2. -, 3. *, 4. /" << endl;
        cout << "    5. Power (Complex ^ Real)" << endl;
        cout << "    6. Abs" << endl;
        cout << "    7. Angle" << endl;
        cout << "    8. Conjugate" << endl;
        cout << "    You can input 9 to get the variables list." << endl;

        if(errorCode == 1) {
            cout << "Bad input, please input an integer between 0 and 9" << endl;
        } else if(errorCode == 2) {
            cout << "Bad input, please input an integer between 1 and 5" << endl;
        } else if(errorCode == 3) {
            cout << "Bad input, please input positive integer between 1 to 4)" << endl;
        } else if(errorCode == 4) {
            cout << endl << "--- ERROR: in Complex Mode ---" << endl;
            cout << "Math Error: Divided by 0" << endl;
            cout << "--- ERROR: End of error message ---" << endl;
        }

        cout << endl << "Result: " << var[4] << endl;

        cout << "Please input the ID of function or operator(0 to quit): ";
        cin >> oprt;

        if(!cin) {
            errorCode = 1;
            cin.clear();
            while(cin.get() != '\n');
            continue;
        }
        while(cin.get() != '\n');

        if(oprt == 0) {
            goto CmplxCalcExit;
        } else if(1 <= oprt && oprt <= 4) {
            int l, r;
            cout << "Please input 2 variables you want to calculate" << endl;
            cout << "    (1.a, 2.b, 3.c, 4.d, 5.n(ans)): ";
            cin >> l >> r;

            if(!cin) {
                errorCode = 2;
                cin.clear();
                while(cin.get() != '\n');
                continue;
            }
            while(cin.get() != '\n');

            if(l<1 || r<1 || l>5 || r>5) {
                errorCode = 3;
                continue;
            }
            if(oprt == 4 && var[r-1] == 0) {
                errorCode = 4;
                continue;
            }
            var[4] = CmplxBasicCalc(l, r, oprt, var);
        } else if(5 <= oprt && oprt <= 8) {
            int l;
            cout << "Please input the variable you want to calculate" << endl;
            cout << "    (1.a, 2.b, 3.c, 4.d, 5.n(ans)): ";
            cin >> l;
            if(!cin) {
                errorCode = 2;
                cin.clear();
                while(cin.get() != '\n');
                continue;
            }
            while(cin.get() != '\n');

            if(l<1 || l>5) {
                errorCode = 3;
                continue;
            }
            if (oprt == 5) {
                string ex;
                cout << "Please input the exponent(real number)(expression available): ";
                cin >> ex;
                if(!cin) {
                    cout << "Bad input, illegal expression." << endl;
                    cin.clear();
                    while(cin.get() != '\n');
                    continue;
                }
                while(cin.get() != '\n');

                var[4] = var[l - 1].imagePower(realCalcRP(realRePolish(ex, 0)));
            }
            switch (oprt) {
                case 6:
                    var[4] = imageNumber(var[l - 1].imageAbs(), 0);
                    break;
                case 7:
                    var[4] = imageNumber(var[l - 1].imageAngle(), 0);
                    break;
                case 8:
                    var[4] = var[l - 1].imageConj();
                    break;
                default:
                    break;
            }
//        } else if(oprt == 9) {
//            cout << "Value of variables now: " << endl;
//            cout << "    b: " << var[0] << endl;
//            cout << "    c: " << var[1] << endl;
//            cout << "    d: " << var[2] << endl;
//            cout << "    g: " << var[3] << endl;
//            cout << "    n: " << var[4] << endl;
        } else {
            cout << "Bad input, please input an integer between 0 and 9" << endl;
        }

//        if(oprt != 9) {
//            cout << endl << "Result: " << var[4] << endl;
//        }

    }
    CmplxCalcExit:
    system("cls");
    ComplexInfo();
}

imageNumber CmplxBasicCalc(int l, int r, int oprt, imageNumber* var) {
    switch(oprt) {
        case 1: return var[l-1] + var[r-1];
        case 2: return var[l-1] - var[r-1];
        case 3: return var[l-1] * var[r-1];
        default: return 0;
    }
}


void CmplxCalcInfo() {
    cout << "Now in Complex Mode - Calculate" << endl;
    cout << "    How to use:" << endl;
    cout << "        1. Choose an operator or function" << endl;
    cout << "        2. Choose 1 or 2 variable(s)" << endl;
    cout << "        Then the result will print to screen and save to variable n" << endl;
}

void CmplxInputInfo() {
    cout << "Now in Complex Mode - Input" << endl;
    cout << "    Format: a,b -> a+bi (No SPACE Please) e.g. 1,3 = 1+3i, 0,123 -> 123i" << endl;
    cout << "        For a and b, expression available" << endl;
}

// Message Function

void ComplexInfo() {
    cout << "Now in Complex Mode" << endl;
    cout << "    How to use:" << endl;
    cout << "        We have 4 complex variable: a, b, c, d and n(ans)" << endl;
    cout << "            n(ans) is the result of last calculation." << endl;
    cout << "            when you quit Complex Mode, all variable will be set to 0." << endl;
    cout << "        There are 2 kind of operations:" << endl;
    cout << "            1. Input: set the value of variable a, b, c or d" << endl;
    cout << "            2. Calculate: calculation with the variables above and functions" << endl;
}
