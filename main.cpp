#include <iostream>
#include <string>
#include "apps/basicNumber.h"
#include "apps/tools.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

void RealCalc();
void ImageCalc();
void MatCalc();
void VecCalc();

int main() {


    // BOOT
    // TODO: Print welcome info
    cout << "Welcome to Calcalk!" << endl;
    cout << "For the user docs, see /Calcalk/docs" << endl;
    cout << endl;

    // Read keyboard input, choose mode
    cout << "Please choose mode: " << endl;
    cout << "   1 for Normal(Real Number) Mode" << endl;
    cout << "   2 for Complex Mode" << endl;
    cout << "   3 for Matrix Mode" << endl;
    cout << "   4 for Vector Mode" << endl;
    cout << "   0 for Exit" << endl;
    int mode;
    while(true) {
        cout << "Please input: ";
        cin >> mode; // 1: Real, 2: Image, 3: Matrix, 4: Vector, 0: Exit
        switch(mode) {
            case 0: goto mainEXIT;
            case 1: RealCalc(); break;
            case 2: ImageCalc(); break;
            case 3: MatCalc(); break;
            case 4: VecCalc(); break;
            default:
                cout << "Bad input, please input an integer between 0 and 4" << endl;
                break;
        }
    }

    mainEXIT:
    cout << "See you next time." << endl;

    return 0;
}

void RealCalc() {
    cout << "Now in Normal Mode" << endl;
    cout << "In this mode, you can choose 2 sub mode: " <<
            "   1 for expression only contains +, -, *, /, ^(power), _(root) and %%(mod)" <<
            "   2 for function (sin, cos, gcd, lcm, round, and so on)" << 
            "   0 for Exit." << endl;
            
    int submode;
    while(true) {
        cin >> submode;
        switch(submode) {
            case 1: realMode1(); break;
            case 2: realMode2(); break;
            case 0: goto realEXIT;
        }
    }
    
    realEXIT:
    cout << "Exit Normal Mode, return to main menu." << endl << endl;
}
void ImageCalc() {
    cout << "Now in Complex Mode" << endl;
}
void MatCalc() {
    cout << "Now in Matrix Mode" << endl;
}
void VecCalc() {
    cout << "Now in Vector Mode" << endl;
}