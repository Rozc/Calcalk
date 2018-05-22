#include <iostream>
#include <string>
#include "apps/basicNumber.h"
#include "apps/imageNumber.h"
#include "apps/tools.h"
#include "apps/vec.h"

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
    cout << "For the user docs, see /Calcalk/docs (hmmm... no docs now~ >w<)" << endl;
    cout << "Test Version, only Mode 1, 2 and 4 is usable." << endl;
    cout << "So many bug, don't make strange input T_T" << endl;
    cout << "Press any key to continue." << endl;
    system("pause");

    int mode;
    int errorCode = 0;

    while(true) {
        system("cls");
        mainMenuInfo();

        if(errorCode == 1) {
            cout << "Bad input, please input an integer between 0 and 5" << endl;
        }

        cout << "Main Menu - Please input to choose mode: ";
        cin >> mode;


        if(!cin) {
            errorCode = 1;
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
                errorCode = 1;
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

}
void ImageCalc() {
    system("cls");
    ComplexInfo();

    int oprt;
    imageNumber var[5] = {0, 0, 0, 0, 0}; // b, c, d, g, n;

    while(true) {
        cout << "Please input the ID of operation(0 to quit): ";
        cin >> oprt;

        if(!cin) {
            cout << "Bad input, please input an integer between 0 and 2" << endl;
            cin.clear();
            while(cin.get() != '\n');
            continue;
        }
        while(cin.get() != '\n');

        switch(oprt) {
            case 0:
                goto cmplxExit;
            case 1:
                CmplxInput(var);
                break;
            case 2:
                CmplxCalc(var);
                break;
            default:
                cout << "Bad input, please input an integer between 0 and 2" << endl;
                break;
        }
    }

    cmplxExit:
    cout << "Exit Complex Mode, return to main menu." << endl << endl;

}
void MatCalc() {
    cout << "Now in Matrix Mode" << endl;
}
void VecCalc() {
    int oprt;
    vec var[3]; // a, b, n;
    basicNumber numResult;
    numResult.setEp(-1);
    int errorCode = 0;

    while(true) {
        vecHead:
        system("cls");
        vecModeInfo();

        cout << "Value of variables now: " << endl;
        cout << "    a: " << var[0] << endl;
        cout << "    b: " << var[1] << endl;
        cout << "    n: " << var[2] << endl;

        if(errorCode == 1) {
            cout << "Bad input, please input an integer between 0 and 9" << endl;
        } else if(errorCode == 2) {
            cout << "Bad Format." << endl;
        } else if(errorCode == 3) {
            cout << "Bad input, illegal expression." << endl;
        }

        if(numResult.getEp() != -1) {
            cout << endl << "Result: " << numResult << endl;
            numResult.wrongNumber();
        } else {
            cout << endl << "Result: " << var[2] << endl;
        }

        cout << "Please input the ID of operation(0 to quit): ";
        cin >> oprt;

        if(!cin) {
            errorCode = 1;
            cin.clear();
            while(cin.get() != '\n');
            continue;
        }
        while(cin.get() != '\n');

        if(oprt == 0) {
            break;
        } else if(oprt == 1 || oprt == 2) {
            cout << "Please input the value you want to set";
            cout << "    First input an integer means the length of vector." << endl;
            cout << "    And then input n integers for every value of vector" << endl;
            example:
            cout << "    For example, if you input 3 1.2 3.4 5.6, you will get a 3 dimension vector: [ 1.2, 3.4, 5.6 ]" << endl;
            cout << "    Input: ";
            cin >> var[oprt-1];
            if (!cin) {
                errorCode = 2;
                cin.clear();
                while (cin.get() != '\n');
                goto example;
            }
            while (cin.get() != '\n');

            system("cls");
            vecModeInfo();
            continue;

        } else if(3 <= oprt && oprt <= 6) {
            int v1, v2;
            dbStart:
            cout << "Please choose 2 variables(1.a, 2.b, 3.n)(single 0 to quit): ";
            cin >> v1 >> v2;

            if(!cin) {
                cout << "Bad input, please input 2 integers between 0 and 3" << endl;
                cin.clear();
                while(cin.get() != '\n');
                goto dbStart;
            }
            while(cin.get() != '\n');
            if(v1 == 0) {
                system("cls");
                vecModeInfo();
                continue;
            }
            if(v1 < 0 || v2 < 0 || v1 > 3 || v2 > 3) {
                cout << "Bad input, please input 2 integers between 0 and 3" << endl;
                goto dbStart;
            }
            v1--; v2--;

            switch(oprt) {
                case 3:
                    var[2] = var[v1] + var[v2];
                    break;
                case 4:
                    var[2] = var[v1] - var[v2];
                    break;
                case 5:
                    numResult = var[0].vecInnerP(var[2]);
                    break;
                case 6:
                    var[2] = var[v1].vecOuterP(var[v2]);
                    break;
                default: break;
            }

        } else if(6 <= oprt && oprt <= 9) {
            int v1;
            sgStart:
            cout << "Please choose the variable(1.a, 2.b, 3.n)(0 to quit): ";
            cin >> v1;

            if(!cin) {
                cout << "Bad input, please input an integer between 0 and 3" << endl;
                cin.clear();
                while(cin.get() != '\n');
                goto sgStart;
            }
            while(cin.get() != '\n');
            if(v1 == 0) {
                system("cls");
                vecModeInfo();
                continue;
            }
            if(v1 < 0 || v1 > 3) {
                cout << "Bad input, please input 2 integers between 0 and 3" << endl;
                goto sgStart;
            }
            v1--;

            switch(oprt) {
                case 7: {
                    string num;
                    cout << "Please input a real number(expression available): ";
                    cin >> num;
                    if(!cin) {
                        errorCode = 3;
                        cin.clear();
                        while(cin.get() != '\n');
                        goto vecHead;
                    }
                    while(cin.get() != '\n');
                    var[2] = var[v1].vecNumP(realCalcRP(realRePolish(num, 0)));
                } break;

                case 8:
                    numResult = var[v1].vecAbs();
                    break;
                case 9:
                    var[2] = var[v1].unitize();
                    break;
                default: break;
            }
        } else {
            errorCode = 1;
            continue;
        }

        errorCode = 0;

    }

    cout << "Exit Vector Mode, return to main menu." << endl << endl;

}


void DEBUG() {
    string a = "\7\7\7";
    cout << a << endl;
}

void Settings() {
#ifdef _winver
    system("cls");
#else
    system("printf \"\\033c\"");
#endif
    cout << "Now in Settings" << endl;
    cout << "You can change the following parameters:" << endl <<
    "    1. Maximum number of iterations of Division(/) " << endl <<
    "    2. Maximum number of iterations of Root(_)" << endl <<
    "    0 to Quit" << endl <<
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
         "    1 for Normal(Real Number) Mode" << endl <<
         "    2 for Complex Mode" << endl <<
         "    3 for Matrix Mode" << endl <<
         "    4 for Vector Mode" << endl <<
         "    5 for Settings" << endl <<
         "    0 to Quit" << endl;
}