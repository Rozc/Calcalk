#include <iostream>
#include <string>
#include "apps/basicNumber.h"
#include "apps/imageNumber.h"
#include "apps/tools.h"
#include "apps/vec.h"
#include "apps/matrix.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>

// TODO: 更好看的伪图形界面(利用控制台文字与背景颜色变化)-DOING

using namespace std;

void RealCalc();
void ImageCalc();
void MatCalc();
void VecCalc();
void Settings();
void DEBUG();
void mainMenuInfo();



#define co(a) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a)
#define ico(a) ;co(a); cout <<

int main() {


    // BOOT
    // TODO: Print welcome info

//    SetConsoleTextAttribute(hdl, 0x0000);
//    cout << "Test Text 0" << endl;
//    SetConsoleTextAttribute(hdl, 0x0001);
//    cout << "Test Text 1" << endl;
//    SetConsoleTextAttribute(hdl, 0x0002);
//    cout << "Test Text 2" << endl;
//    SetConsoleTextAttribute(hdl, 0x0003);
//    cout << "Test Text 3" << endl;
//    SetConsoleTextAttribute(hdl, 0x0004);
//    cout << "Test Text 4" << endl;
//    SetConsoleTextAttribute(hdl, 0x0005);
//    cout << "Test Text 5" << endl;
//    SetConsoleTextAttribute(hdl, 0x0006);
//    cout << "Test Text 6" << endl;
//    SetConsoleTextAttribute(hdl, 0x0007);
//    cout << "Test Text 7" << endl;
//    SetConsoleTextAttribute(hdl, 0x0008);
//    cout << "Test Text 8" << endl;
//    SetConsoleTextAttribute(hdl, 0x0009);
//    cout << "Test Text 9" << endl;
//    SetConsoleTextAttribute(hdl, 0x000A);
//    cout << "Test Text A" << endl;
//    SetConsoleTextAttribute(hdl, 0x000B);
//    cout << "Test Text B" << endl;
//    SetConsoleTextAttribute(hdl, 0x000C);
//    cout << "Test Text C" << endl;
//    SetConsoleTextAttribute(hdl, 0x000D);
//    cout << "Test Text D" << endl;
//    SetConsoleTextAttribute(hdl, 0x000E);
//    cout << "Test Text E" << endl;


    co(0x0e);
    cout << "Welcome to ";
    co(0x0b);
    cout << "Calcalk!" << endl;
    co(0x0e);



    cout << "red"" bule" << endl;


    cout << endl << endl;
    cout << "      ______       ___       __        ______   " ico(0x0b) "    ___       __       __  ___   " << endl; co(0x0e);
    cout << "     /      |     /   \\     |  |      /      | " ico(0x0b) "    /   \\     |  |     |  |/  /  " << endl; co(0x0e);
    cout << "    |  ,----'    /  ^  \\    |  |     |  ,----' " ico(0x0b) "   /  ^  \\    |  |     |  '  /    " << endl; co(0x0e);
    cout << "    |  |        /  /_\\  \\   |  |     |  |     " ico(0x0b) "   /  /_\\  \\   |  |     |    <    " << endl; co(0x0e);
    cout << "    |  `----.  /  _____  \\  |  `----.|  `----. " ico(0x0b) " /  _____  \\  |  `----.|  .  \\   " << endl; co(0x0e);
    cout << "     \\______| /__/     \\__\\ |_______| \\______|" ico(0x0b) " /__/     \\__\\ |_______||__|\\__\\ " << endl; co(0x07);
    cout << endl << endl;

    cout << "For the user docs, see " ico(0x0e) "/Calcalk/docs" << endl; co(0x07);
    cout << "Press any key to continue." << endl;

    co(0x07);
    system("pause");

    int mode;
    int errorCode = 0;

    while(true) {
        system("cls");
        mainMenuInfo();

        co(0x0c);
        if(errorCode == 1) {
            cout << "Bad input, please input an integer between 0 and 5" << endl;
            errorCode = 0;
        }
        co(0x07);

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
    co(0x0a);
    cout << "See you next time, press any key to quit." << endl;
    co(0x07);
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

//void ImageCalc() {
//    system("cls");
//    ComplexInfo();
//
//    int oprt;
//    imageNumber var[5] = {0, 0, 0, 0, 0}; // b, c, d, g, n;
//
//    while(true) {
//        cout << "Please input the ID of operation(0 to quit): ";
//        cin >> oprt;
//
//        if(!cin) {
//            cout << "Bad input, please input an integer between 0 and 2" << endl;
//            cin.clear();
//            while(cin.get() != '\n');
//            continue;
//        }
//        while(cin.get() != '\n');
//
//        switch(oprt) {
//            case 0:
//                goto cmplxExit;
//            case 1:
//                CmplxInput(var);
//                break;
//            case 2:
//                CmplxCalc(var);
//                break;
//            default:
//                cout << "Bad input, please input an integer between 0 and 2" << endl;
//                break;
//        }
//    }
//
//    cmplxExit:
//    cout << "Exit Complex Mode, return to main menu." << endl << endl;
//
//}

void ImageCalc() {
    int oprt;
    imageNumber var[5]; // a, b, c, d, n
    int errorCode = 0;

    while(true) {
        imgHead:
        system("cls");
        ComplexInfo();

        cout << "Value of variables now: " << endl;
        cout << "a: " << var[0] << endl;
        cout << "b: " << var[1] << endl;
        cout << "c: " << var[2] << endl;
        cout << "d: " << var[3] << endl;
        cout << "n: " << var[4] << endl;

        if(errorCode == 1) {
            cout << "Bad input, please input an integer between 0 and 12" << endl;
        }

        cout << "Result: " << var[4] << endl;

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
        } else if(1 <= oprt && oprt <= 4) {
            cout << "Please input the value you want to set" << endl;
            cout << "    Format: a,b -> a+bi (No SPACE Please) e.g. 1,3 = 1+3i, 0,123 -> 123i" << endl;
            cout << "        ',' is necessary" << endl;
            cout << "        For a and b, expression available" << endl;
            inp:
            cout << "    Input: ";
            cin >> var[oprt-1];
            if (!cin) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Wrong Input." << endl;
                goto inp;
            }
            while (cin.get() != '\n');

            continue;
        } else if(5 <= oprt && oprt <= 8) {
            char cl, cr;
            int l, r;
            dbStart:
            cout << "Please input 2 variables you want to calculate" << endl;
            cout << "    (a, b, c, d, n(ans)), separated by space(0 0 to quit): ";
            cin >> cl >> cr;

            if(!cin) {
                cin.clear();
                while(cin.get() != '\n');
                cout << "Bad input, please input 2 characters in a, b, c, d and n" << endl;
                goto dbStart;
            }
            while(cin.get() != '\n');

            if(cl == '0' && cr == '0') {
                continue;
            }

            if(cl == 'a') l = 0;
            else if(cl == 'b') l = 1;
            else if(cl == 'c') l = 2;
            else if(cl == 'd') l = 3;
            else if(cl == 'n') l = 4;
            else {
                cout << "Bad input, please input 2 characters in a, b, c, d and n" << endl;
                goto dbStart;
            }

            if(cr == 'a') r = 0;
            else if(cr == 'b') r = 1;
            else if(cr == 'c') r = 2;
            else if(cr == 'd') r = 3;
            else if(cr == 'n') r = 4;
            else {
                cout << "Bad input, please input 2 characters in a, b, c, d and n" << endl;
                goto dbStart;
            }

            var[4] = CmplxBasicCalc(l, r, oprt, var);

        } else if(9 <= oprt && oprt <= 12) {
            char cl;
            int l;
            sgStart:
            cout << "Please input a variable you want to calculate" << endl;
            cout << "    (a, b, c, d, n(ans))(0 to quit): ";
            cin >> cl;

            if(!cin) {
                cin.clear();
                while(cin.get() != '\n');
                goto sgStart;
            }
            while(cin.get() != '\n');

            if(cl == '0') {
                continue;
            }

            if(cl == 'a') l = 0;
            else if(cl == 'b') l = 1;
            else if(cl == 'c') l = 2;
            else if(cl == 'd') l = 3;
            else if(cl == 'n') l = 4;
            else {
                cout << "Bad input, please input 2 characters in a, b, c, d and n" << endl;
                goto sgStart;
            }

            if (oprt == 9) {
                string ex;
                realStart:
                cout << "Please input the exponent(real number)(expression available): ";
                cin >> ex;
                if(!cin) {
                    cout << "Bad input, illegal expression." << endl;
                    cin.clear();
                    while(cin.get() != '\n');
                    goto realStart;
                }
                while(cin.get() != '\n');

                basicNumber num = realCalcRP(realRePolish(ex, 0));
                if(num.getEp() == -1) {
                    cout << "Bad input, illegal expression." << endl;
                    cout << "Have you:" << endl;
                    cout << "    1. Divided by 0." << endl;
                    cout << "    2. A^B or A_B and B is not an integer." << endl <<
                         "        (A^B requires that B is an integer, A_B requires that B is a positive integer)." << endl;
                    cout << "    3. A%B or A$B and A or B is not integer." << endl;
                    cout << "    4. Illegal input." << endl;
                    cout << "?" << endl;
                    goto realStart;
                }

                var[4] = var[l].imagePower(num);
            } else {
                switch (oprt) {
                    case 10:
                        var[4] = imageNumber(var[l].imageAbs(), 0);
                        break;
                    case 11:
                        var[4] = imageNumber(var[l].imageAngle(), 0);
                        break;
                    case 12:
                        var[4] = var[l].imageConj();
                        break;
                    default:
                        break;
                }
            }

        } else {
            errorCode = 1;
            continue;
        }

        errorCode = 0;


    }
}

void MatCalc() {
    int oprt;
    matrix var[3]; // a, b, n
    basicNumber numResult;
    numResult.setEp(-1);
    int errorCode = 0;

    while(true) {
        matHead:
        system("cls");
        matModeInfo();

        cout << "Value of variables now: " << endl;
        cout << "a: " << endl << var[0] << endl;
        cout << "b: " << endl << var[1] << endl;

        if(errorCode == 1) {
            cout << "Bad input, please input an integer between 0 and 8" << endl;
        }

        if(numResult.getEp() != -1) {
            if(numResult.getEp() == -2) {
                cout << endl << "--- ERROR: in Matrix Mode ---" << endl;
                cout << "    You just try to get the determinant of a non-square matrix" << endl;
                cout << "--- ERROR: End of error message ---" << endl << endl;
            }
            cout << endl << "Result: " << numResult << endl;
            numResult.wrongNumber();
        } else {
            if(var[2].getRow() == -1) {
                cout << endl << "--- ERROR: in Matrix Mode ---" << endl;
                cout << "Have you:" << endl;
                cout << "    1. + - with non-Homotypic matrix." << endl;
                cout << "    2. * when column of left matrix not equal to row of right matrix." << endl;
                cout << "?" << endl;
                cout << "--- ERROR: End of error message ---" << endl << endl;
            }
            cout << endl << "Result: " << endl << var[2] << endl;
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
            cout << "Please input the value you want to set" << endl;
            cout << "    First input an integer means the row and column." << endl;
            cout << "    And then input row*column integers for every value of matrix" << endl;
            example:
            cout << "    For example, if you input 3 3 1 2 3 4 5 6 7 8 9" << endl;
            cout << "    You will get a 3x3 matrix" << endl;
            cout << "    | 1 2 3 |" << endl;
            cout << "    | 4 5 6 |" << endl;
            cout << "    | 7 8 9 |" << endl;
            cout << "    Input: ";
            cin >> var[oprt-1];
            if (!cin) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Wrong Input." << endl;
                goto example;
            }
            while (cin.get() != '\n');

            continue;
        } else if(3 <= oprt && oprt <= 5) {
            char cv1, cv2;
            int v1, v2;
            dbStart:
            cout << "Please choose 2 variables(a, b, n), separated by space(0 0 to quit): ";
            cin >> cv1 >> cv2;


            if(!cin) {
                cout << "Bad input, please input 2 characters in a, b or n" << endl;
                cin.clear();
                while(cin.get() != '\n');
                goto dbStart;
            }
            while(cin.get() != '\n');


            if(cv1 == '0' || cv2 == '0') {
                system("cls");
                matModeInfo();
                continue;
            }

            if(cv1 == 'a') v1 = 0;
            else if(cv1 == 'b') v1 = 1;
            else if(cv1 == 'c') v1 = 2;
            else {
                cout << "Bad input, please input 2 characters in a, b or n" << endl;
                goto dbStart;
            }

            if(cv2 == 'a') v2 = 0;
            else if(cv2 == 'b') v2 = 1;
            else if(cv2 == 'n') v2 = 2;
            else {
                cout << "Bad input, please input 2 characters in a, b or n" << endl;
                goto dbStart;
            }

            switch(oprt) {
                case 3:
                    var[2] = var[v1] + var[v2];
                    break;
                case 4:
                    var[2] = var[v1] - var[v2];
                    break;
                case 5:
                    var[2] = var[v1] * var[v2];
                    break;
                default: break;
            }

        } else if(6 <= oprt && oprt <= 8) {
            char cv1;
            int v1;
            sgStart:
            cout << "Please choose the variable(a, b, n)(0 to quit): ";
            cin >> cv1;

            if(!cin) {
                cout << "Bad input, please input a character in a, b or n" << endl;
                cin.clear();
                while(cin.get() != '\n');
                goto sgStart;
            }
            while(cin.get() != '\n');

            if(cv1 == '0') {
                continue;
            }

            if(cv1 == 'a') v1 = 0;
            else if(cv1 == 'b') v1 = 1;
            else if(cv1 == 'c') v1 = 2;
            else {
                cout << "Bad input, please input a character in a, b or n" << endl;
                goto dbStart;
            }

            switch(oprt) {
                case 6: {
                    string num;
                    cout << "Please input a real number(expression available): ";
                    cin >> num;
                    if(!cin) {
                        errorCode = 3;
                        cin.clear();
                        while(cin.get() != '\n');
                        goto matHead;
                    }
                    while(cin.get() != '\n');
                    var[2] = realCalcRP(realRePolish(num, 0)) * var[v1];
                } break;

                case 7:
                    numResult = var[v1].det();
                    break;
                case 8:
                    var[2] = var[v1].T();
                    break;
                default: break;
            }
        } else {
            errorCode = 1;
            continue;
        }

    }

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

        if(errorCode == 1) {
            cout << "Bad input, please input an integer between 0 and 9" << endl;
        } else if(errorCode == 3) {
            cout << "Bad input, illegal expression." << endl;
        }

        if(numResult.getEp() != -1) {
            if(numResult.getEp() == -2) {
                cout << endl << "--- ERROR: in Vector Mode ---" << endl;
                cout << "    You just try to get the Inner Product with 2 vector with different dimension" << endl;
                cout << "--- ERROR: End of error message ---" << endl << endl;
            } else {
                cout << endl << "Result: " << numResult << endl;
            }
            numResult.wrongNumber();
        } else {
            if(var[2].getLen() == -1) {
                cout << endl << "--- ERROR: in Vector Mode ---" << endl;
                cout << "Have you:" << endl;
                cout << "    1. + - with 2 vector with different dimension." << endl;
                cout << "    2. Try to get the Outer Product with 2 vector with different dimension" << endl;
                cout << "         or their dimension are higher then 3." << endl;
                cout << "?" << endl;
                cout << "--- ERROR: End of error message ---" << endl << endl;
            }
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
            cout << "Please input the value you want to set" << endl;
            cout << "    First input an integer means the length of vector." << endl;
            cout << "    And then input n integers for every value of vector" << endl;
            example:
            cout << "    For example, if you input 3 1.2 3.4 5.6, you will get a 3 dimension vector: [ 1.2, 3.4, 5.6 ]" << endl;
            cout << "    Input: ";
            cin >> var[oprt-1];
            if (!cin) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Wrong Input." << endl;
                goto example;
            }
            while (cin.get() != '\n');

            system("cls");
            vecModeInfo();
            continue;

        } else if(3 <= oprt && oprt <= 6) {
            char cv1, cv2;
            int v1, v2;
            dbStart:
            cout << "Please choose 2 variables(a, b, n), separated by space(0 0 to quit): ";
            cin >> cv1 >> cv2;

            if(!cin) {
                cout << "Bad input, please input 2 integers between 0 and 3" << endl;
                cin.clear();
                while(cin.get() != '\n');
                goto dbStart;
            }
            while(cin.get() != '\n');
            if(cv1 == '0' || cv2 == '0') {
                continue;
            }
            if(cv1 == 'a') v1 = 0;
            else if(cv1 == 'b') v1 = 1;
            else if(cv1 == 'c') v1 = 2;
            else {
                cout << "Bad input, please input 2 integers between 0 and 3" << endl;
                goto dbStart;
            }

            if(cv2 == 'a') v2 = 0;
            else if(cv2 == 'b') v2 = 1;
            else if(cv2 == 'n') v2 = 2;
            else {
                cout << "Bad input, please input 2 integers between 0 and 3" << endl;
                goto dbStart;
            }

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
    matrix a;
    cin >> a;
    a = a.inverse();
    cout << a;
    system("pause");
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

}

void mainMenuInfo() {
    // Read keyboard input, choose mode
    cout << "|"; co(0x70); cout << " Main Menu "; co(0x07); cout << "| Normal Mode | Complex Mode | Matrix Mode | Vector Mode |" << endl;
    cout << "======================================================================" << endl << endl;
    cout << "Please choose mode: " << endl;
    cout << "    " ico(0x0D) "1 " ico(0x07) "for" ico(0x0b) " Normal(Real Number) Mode" << endl; co(0x07);
    cout << "    " ico(0x0D) "2 " ico(0x07) "for" ico(0x0b) " Complex Mode" << endl; co(0x07);
    cout << "    " ico(0x0D) "3 " ico(0x07) "for" ico(0x0b) " Matrix Mode" << endl; co(0x07);
    cout << "    " ico(0x0D) "4 " ico(0x07) "for" ico(0x0b) " Vector Mode" << endl; co(0x07);
    cout << "    " ico(0x0D) "5 " ico(0x07) "for" ico(0x0b) " Settings" << endl; co(0x07);
    cout << "    " ico(0x0D) "0 " ico(0x07) " to" ico(0x0c) " Quit" << endl; co(0x07);
}