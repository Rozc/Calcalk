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
void Settings();
void DEBUG();
void mainMenuInfo();

int main() {


    // BOOT
    // TODO: Print welcome info
    cout << "Welcome to Calcalk!" << endl;
    cout << "For the user docs, see /Calcalk/docs" << endl;
    cout << "Test Version, only Mode 1 is usable." << endl;
    cout << "Press any key to continue." << endl;
    system("pause");



    int mode;

    while(true) {
        system("cls");
        mainMenuInfo();

        cout << "Main Menu - Please input to choose mode: ";
        cin >> mode;


        if(!cin) {
            cout << "Bad input, please input an integer between 0 and 5" << endl;
            cin.clear();
            while(cin.get() != '\n');
            continue;
        }
        while(cin.get() != '\n');

        switch(mode) {
            case 0: goto mainEXIT;
            case 1: RealCalc(); break;
            case 2: ImageCalc(); break;
            case 3: MatCalc(); break;
            case 4: VecCalc(); break;
            case 5: Settings(); break;
            case 6: DEBUG(); break;
            default:
                cout << "Bad input, please input an integer between 0 and 5" << endl;
                break;
        }
    }

    mainEXIT:
    cout << "See you next time, press any key to quit." << endl;
    system("pause");

    return 0;
}

void RealCalc() {
    system("cls");
    realModeInfo();
            
    int subMode;
    basicNumber ansLast = 0;
    while(true) {
        cout << "Normal Mode - Please input to choose sub mode: ";
        cin >> subMode;


        if(!cin) {
            cout << "Bad input, please input an integer between 0 and 3" << endl;
            cin.clear();
            while(cin.get() != '\n');
            continue;
        }
        while(cin.get() != '\n');

        switch(subMode) {
            case 1: realMode1(ansLast); break;
            case 2: realMode2(ansLast); break;
            case 0: goto realEXIT;
            default:
                cout << "Bad input, please input an integer between 0 and 3" << endl;
                break;
        }
    }
    
    realEXIT:
    cout << "Exit Normal Mode, return to main menu." << endl << endl;
    mainMenuInfo();
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

void DEBUG() {
    basicNumber a;
    a = string("99999999999999999999999999999999999.9");
    a = basicATan(a);
    cout << a << endl;
    cout << atan(999999999999999999999999999999999999.9) << endl;
}

void Settings() {
    system("cls");
    cout << "Now in Settings" << endl;
    cout << "You can change the following parameters:" << endl <<
    "   1. Maximum number of iterations of Division(/) " << endl <<
    "   2. Maximum number of iterations of Root(_)" << endl <<
    "   0 to Quit"
    "Note: Large parameters will make the calculating process slow!" << endl;

    int para, val;

    while(true) {

        cout << "Please input the ID of parameter you want to change: ";
        cin >> para;
        if(!cin) {
            cout << "Bad input, please input an integer between 0 and 2" << endl;
            cin.clear();
            while(cin.get() != '\n');
            continue;
        }
        while(cin.get() != '\n');

        if(para < 0 || para > 2) {
            cout << "Bad input, please input an integer between 0 and 2" << endl;
            continue;
        }

        if(para == 0) {
            return;
        }

        cout << "Please input the value you want to set: ";
        cin >> val;
        if(!cin) {
            cout << "Bad input, please input a positive integer" << endl;
            cin.clear();
            while(cin.get() != '\n');
            continue;
        }
        while(cin.get() != '\n');

        if(val <= 0) {
            cout << "Bad input, please input a positive integer" << endl;
            continue;
        }

        switch(para) {
            case 1:
                basicNumber::DIVISION_ITERATIONS = val;
                cout << "Maximum number of iterations of Division(/) changed" << endl << endl;
                break;
            case 2:
                basicNumber::ROOT_ITERATIONS = val;
                cout << "Maximum number of iterations of Root(_) changed" << endl << endl;
                break;
            default:
                break;
        }
    }
    setEXIT:
    return;

}

void mainMenuInfo() {
    // Read keyboard input, choose mode
    cout << "Now in Main Menu" << endl;
    cout << "Please choose mode: " << endl <<
         "   1 for Normal(Real Number) Mode" << endl <<
         "   2 for Complex Mode" << endl <<
         "   3 for Matrix Mode" << endl <<
         "   4 for Vector Mode" << endl <<
         "   5 for Settings" << endl <<
         "   0 to Quit" << endl;
}