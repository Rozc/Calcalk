//
// Created by Rozc on 2018/5/4.
//
#include <iostream>
#include "basicNumber.h"
#include <string>
#include <cmath>
#include "tools.h"
#include <sstream>

using namespace std;

int basicNumber::DIVISION_ITERATIONS = 10;
int basicNumber::ROOT_ITERATIONS = 50;

basicNumber::basicNumber() {
    /*basicNumber 缺省构造函数*/
    AcNe = true;
    intPart = vector<int>(1);
    ep = 0;
}
basicNumber::basicNumber(const string& num) {
    /* basicNumber 构造函数
     * Args:
     *  string& num: 字符串形式传入的数, e.g. 1234.5678, -1234.8765
     * */
    AcNe = num[0] != '-';
    ep = 0;
    int idx;
    for(idx=AcNe?0:1; idx<num.size(); idx++) {
        if(num[idx] == '.') {
            ep = num.size()-idx-1;
            continue;
        }
        if(num[idx] < 48 || num[idx] >= 58) { // 不是数字, 异常, 返回 ep=-1 的对象
            intPart.clear();
            ep = -1;
            return;
        }
        intPart.push_back(num[idx]-48);
    }
    this->clearZero();

}
basicNumber::basicNumber(const int num) {
    *this = basicNumber(intToString(num));
}
basicNumber::basicNumber(const long long num) {
    *this = basicNumber(intToString(num));
}
basicNumber::basicNumber(const double num) {
    *this = basicNumber(doubleToString(num));
}
basicNumber::basicNumber(const basicNumber& other) {
    /*basicNumber 拷贝构造函数*/
    AcNe = other.AcNe;
    intPart = other.intPart;
    ep = other.ep;
}

basicNumber& basicNumber::operator=(basicNumber r) {
    /* basicNumber operator= 赋值运算符
     * Args:
     *  basicNumber 右值
     * */
    AcNe = r.AcNe;
    intPart = r.intPart;
    ep = r.ep;
    return *this;
}
basicNumber& basicNumber::operator=(int r) {
    * this = intToString(r);
    return *this;
}
basicNumber& basicNumber::operator=(long long r) {
    *this = intToString(r);
    return *this;
}
basicNumber& basicNumber::operator=(double r) {
    *this = doubleToString(r);
    return *this;
}

ostream& operator<<(ostream& out, const basicNumber& item) {
    int idx=0, cnt=0;
    if(!item.AcNe) {
        out << '-';
    }
    for(; idx<item.intPart.size()-item.ep; idx++) {
        out << item.intPart[idx];
        cnt++;
    }
    if(cnt == 0) { // 整数部分为 0
        out << 0;
    }
    if(item.ep != 0) {
        out << ".";
        for(; idx<item.intPart.size(); idx++) {
            out << item.intPart[idx];
        }
    }

    return out;
}
istream& operator>>(istream& in, basicNumber& item) {
    string buf;
    in >> buf;
    item = buf;
    return in;
}

basicNumber basicNumber::operator+(basicNumber r) {
    /* basicNumber operator+ 加号运算符
     * Args:
     *  basicNumber r: 右值
     * Return:
     *  basicNumber result: 结果
     * */
    basicNumber result;

    if((AcNe&&r.AcNe) || (!AcNe&&!(r.AcNe))) {
        int intLen = (intPart.size()-ep>r.intPart.size()-r.ep?intPart.size()-ep:r.intPart.size()-r.ep)
                + (ep>r.ep?ep:r.ep);
        result.intPart = vector<int>(intLen);

        // 对齐
        int chgCnt = 0; // 记录 this 的 ep 修改次数, 以便复原
        while(ep < r.ep) {
            ep++;
            chgCnt++;
            intPart.push_back(0);
        }
        while(r.ep < ep) {
            r.ep++;
            r.intPart.push_back(0);
        }
        result.ep = ep;

        for(int i=intLen-1, j=intPart.size()-1, k=r.intPart.size()-1; i>=0; i--, j--, k--) {
            result.intPart[i] += (j>=0?intPart[j]:0) + (k>=0?r.intPart[k]:0);
            if(result.intPart[i] >= 10) {
                if(i!=0) {
                    result.intPart[i-1] += 1;
                    result.intPart[i] -= 10;
                } else {
                    result.intPart.insert(result.intPart.begin(), 1);
                    result.intPart[i+1] -= 10; // 插入后下标变化
                }
            }
        }
        while(chgCnt--) { // 复原 ep
            ep--;
            intPart.pop_back();
        }

        result.AcNe = !AcNe&&!(r.AcNe) ? 0 : 1;
    } else {
        if(AcNe && !(r.AcNe)) {
            r.AcNe = 1;
            result = *this - r;
        } else {
            AcNe = 1;
            result = r - *this;
            AcNe = 0;
        }
    }
    result.clearZero();
    return result;
}
basicNumber basicNumber::operator+=(basicNumber r) {
    *this = *this + r;
    return *this;
}
basicNumber basicNumber::operator+(double r) {
    return *this + doubleToString(r);
}
basicNumber basicNumber::operator+=(double r) {
    *this = *this + r;
    return *this;
}

basicNumber basicNumber::operator-(basicNumber r) {
    /* basicNumber operator- 减号运算符
     * Args:
     *  basicNumber r: 右值
     * Return:
     *  basicNumber result: 结果
     * */
    basicNumber result;
    if((AcNe&&r.AcNe) || (!AcNe&&!(r.AcNe))) {
        int intLen = (intPart.size()-ep>r.intPart.size()-r.ep?intPart.size()-ep:r.intPart.size()-r.ep)
                                    + (ep>r.ep?ep:r.ep);
        result.intPart = vector<int>(intLen);

        // 对齐
        int chgCnt = 0; // 记录 this 的 ep 修改次数, 以便复原
        while(ep < r.ep) {
            ep++;
            chgCnt++;
            intPart.push_back(0);
        }
        while(r.ep < ep) {
            r.ep++;
            r.intPart.push_back(0);
        }
        result.ep = ep;

        for(int i=intLen-1, j=intPart.size()-1, k=r.intPart.size()-1; i>=0; i--, j--, k--) {
            result.intPart[i] += (j>=0?intPart[j]:0) - (k>=0?r.intPart[k]:0);
            if(result.intPart[i] < 0) {
                if(i!=0) {
                    result.intPart[i] = 10 + result.intPart[i];
                    result.intPart[i-1] -= 1;
                } else { // 首位为负, 修正
                    result.intPart[i] = 10 + result.intPart[i];
                    result.AcNe = !(AcNe&&r.AcNe);
                    for(int idx=0; idx<intLen-1; idx++) {
                        result.intPart[idx] = 9 - result.intPart[idx];
                    }

                    result.intPart[intLen-1] = 10 - result.intPart[intLen-1];
                    if(result.intPart[intLen-1] == 10) {
                        result.intPart[intLen-1] = 0;
                        if(intLen == 1) {
                            result.intPart.insert(result.intPart.begin(), 1);
                        } else {
                            result.intPart[intLen-2] += 1;
                            for(int idx=intLen-2; idx>0; idx--) { // 首位无论如何不会溢出
                                if(result.intPart[idx] >= 10) {
                                    result.intPart[idx] -= 10;
                                    result.intPart[idx-1] += 1;
                                }
                            }
                        }
                    }
                }

            }
        }
        while(chgCnt--) { // 复原 ep
            ep--;
            intPart.pop_back();
        }
    } else {
        if(AcNe && !(r.AcNe)) {
            r.AcNe = true;
            result = *this + r;
        } else {
            this->AcNe = true;
            result = *this + r;
            result.AcNe = false;
            this->AcNe = false;
        }
    }
    result.clearZero();
    return result;

}
basicNumber basicNumber::operator-=(basicNumber r) {
    *this = *this - r;
    return *this;
}
basicNumber basicNumber::operator-(double r) {
    return *this - doubleToString(r);
}
basicNumber basicNumber::operator-=(double r) {
    *this = *this - r;
    return *this;
}

basicNumber basicNumber::operator*(basicNumber r) {
    /* basicNumber operator* 乘号运算符
     * Args:
     *  basicNumber r: 右值
     * Return:
     *  basicNumber result: 结果
     * */
    basicNumber result;
    result.AcNe = !(AcNe^r.AcNe);
    result.ep = ep + r.ep;
    int intLen = intPart.size()+r.intPart.size();
    result.intPart = vector<int>(intLen);


    for(int i=r.intPart.size()-1; i>=0; i--) {
        for(int k=intPart.size()-1; k>=0; k--) {
            result.intPart[i+k+1] += r.intPart[i] * intPart[k];
            if(result.intPart[i+k+1] >= 10) {
                result.intPart[i+k] += result.intPart[i+k+1]/10; // 最高位不会超过 10, 不用考虑下标前溢
                result.intPart[i+k+1] %= 10;
            }
        }
    }

    result.clearZero();

    return result;
}
basicNumber basicNumber::operator*=(basicNumber r) {
    *this = *this * r;
    return *this;
}
basicNumber basicNumber::operator*(double r) {
    return *this * doubleToString(r);
}
basicNumber basicNumber::operator*=(double r) {
    *this = *this * r;
    return *this;
}

basicNumber basicNumber::operator++() {
    *this += string("1");
    return *this;
}
const basicNumber basicNumber::operator++(int) {
    basicNumber tmp = *this;
    ++(*this);
    return tmp;
}
basicNumber basicNumber::operator--() {
    *this -= string("1");
    return *this;
}
const basicNumber basicNumber::operator--(int) {
    basicNumber tmp = *this;
    --(*this);
    return tmp;
}

basicNumber basicNumber::operator-() {
    AcNe = !AcNe;
    return *this;
}

basicNumber basicNumber::basicAbs() {
    if(*this >= string("0")) {
        return *this;
    } else {
        return -(*this);
    }
}

basicNumber basicNumber::operator/(basicNumber r) {
    basicNumber result, div=*this, offset = string("1"), rem;

    if(r == string("0")) { // 除数为 0, 不合法, 返回 ep=-1 的对象
        result.ep = -1;
        return result;
    }

    while(div.ep!=0 || r.ep!=0) { // 将小数转化为整数
        div *= string("10");
        r *= string("10");
    }

    result += (div.intDivision(r)).basicAbs();
    rem = (div%r).basicAbs();
    int cnt=0;
    while(cnt++ < DIVISION_ITERATIONS && rem!=0) {
        offset *= string("0.1");
        rem *= string("10");
        result += rem.intDivision(r) * offset;
        rem = (rem%r).basicAbs();
    }
    result.AcNe = !(AcNe^r.AcNe);
    return result;
}
basicNumber basicNumber::operator/=(basicNumber r) {
    *this = *this / r;
    return *this;
}
basicNumber basicNumber::operator/(double r) {
    return *this / doubleToString(r);
}
basicNumber basicNumber::operator/=(double r) {
    *this = *this / r;
    return *this;
}

basicNumber basicNumber::operator%(basicNumber r) {
    /* basicNumber 求余运算符(仅限整数)
     * 求余规则遵循 C++ int 型规则
     * Args:
     *  左操作数与右操作数均要求 eq == 0
     *  */
    basicNumber result;
    if(ep!=0 || r.ep!=0) { // 存在小数部分, 不允许取余, 返回 eq=-1 的对象
        result.ep = -1;
        return result;
    }

    result = *this - this->intDivision(r) * r.basicAbs();

    result.AcNe = AcNe;
    return result;
}
basicNumber basicNumber::operator%=(basicNumber r) {
    *this = *this % r;
    return *this;
}
basicNumber basicNumber::operator%(double r) {
    return *this % doubleToString(r);
}
basicNumber basicNumber::operator%=(double r) {
    *this = *this % r;
    return *this;
}

basicNumber basicNumber::helpIntDivi(basicNumber r) {
    /* basicNumber 整数除法辅助函数(低效率整数除法)
     * 规则遵循 C++ int 型规则
     * Args:
     *  左操作数与右操作数均要求 eq == 0
     * */
    basicNumber result = 0;
    if(ep!=0 || r.ep!=0 || r==0) { // 存在小数部分或除数为 0, 返回 eq=-1 的对象
        result.ep = -1;
        return result;
    }
    while(result * r.basicAbs() <= this->basicAbs()) {
        result++;
    }

    result--;
    result.AcNe = !(AcNe^r.AcNe);

    return result;
}
basicNumber basicNumber::intDivision(basicNumber r) {
    /* basicNumber 整数除法(仅限整数)
     * 规则遵循 C++ int 型规则
     * Args:
     *  左操作数与右操作数均要求 eq == 0
     * */
    basicNumber result=0, div=this->intPart[0], hlpV=0;
    if(ep!=0 || r.ep!=0 || r==0) { // 存在小数部分或除数为 0, 返回 eq=-1 的对象
        result.ep = -1;
        return result;
    }
//    while(result * r.basicAbs() <= this->basicAbs()) {
//        result++;
//    }
//    result--;

    int cntDiv=0;

    while(true) {
        if(div >= r) {
            result *= 10;
            hlpV =  div.helpIntDivi(r);
            result += hlpV;
            div = div - hlpV*r;
        } else {
            if(cntDiv == intPart.size()-1) {
                break;
            }
            div = div*10 + intPart[++cntDiv];
            if(div < r) {
                result *= 10;
            }
            // result *= 10;
        }

    }

    result.AcNe = !(AcNe^r.AcNe);

    return result;
}
basicNumber basicNumber::intDivision(long long r) {
    return this->intDivision(intToString(r));
}

basicNumber operator+(const string num, basicNumber r) {
    return basicNumber(num) + r;
}
basicNumber operator-(const string num, basicNumber r) {
    return basicNumber(num) - r;
}
basicNumber operator*(const string num, basicNumber r) {
    return basicNumber(num) * r;
}
basicNumber operator/(const string num, basicNumber r) {
    return basicNumber(num) / r;
}
basicNumber operator%(const string num, basicNumber r) {
    return basicNumber(num) % r;
}

basicNumber operator+(long long num, basicNumber r) {
    return intToString(num) + r;
}
basicNumber operator-(long long num, basicNumber r) {
    return intToString(num) - r;
}
basicNumber operator*(long long num, basicNumber r) {
    return intToString(num) * r;
}
basicNumber operator/(long long num, basicNumber r) {
    return intToString(num) / r;
}
basicNumber operator%(long long num, basicNumber r) {
    return intToString(num) % r;
}

basicNumber operator+(int num, basicNumber r) {
    return intToString(num) + r;
}
basicNumber operator-(int num, basicNumber r) {
    return intToString(num) - r;
}
basicNumber operator*(int num, basicNumber r) {
    return intToString(num) * r;
}
basicNumber operator/(int num, basicNumber r) {
    return intToString(num) / r;
}
basicNumber operator%(int num, basicNumber r) {
    return intToString(num) % r;
}

basicNumber operator+(double num, basicNumber r) {
    return doubleToString(num) + r;
}
basicNumber operator-(double num, basicNumber r) {
    return doubleToString(num) - r;
}
basicNumber operator*(double num, basicNumber r) {
    return doubleToString(num) * r;
}
basicNumber operator/(double num, basicNumber r) {
    return doubleToString(num) / r;
}
basicNumber operator%(double num, basicNumber r) {
    return doubleToString(num) % r;
}

int basicNumber::comp(basicNumber r) {
    /* basicNumber 比较运算符 辅助函数
     * Return:
     *  -1: 小于 <
     *  0 : 等于 ==
     *  1 : 大于 >
     * */
    bool bothNegFlag=false; // 记录两个操作数是否都为负
    if(AcNe && !(r.AcNe)) {
        return 1;
    } else if(!AcNe && r.AcNe) {
        return -1;
    } else if(!AcNe && !(r.AcNe)) {
        bothNegFlag = true;
    }

    if(intPart.size()-ep > r.intPart.size()-r.ep) {
        return bothNegFlag ? -1 : 1;
    } else if(intPart.size()-ep < r.intPart.size()-r.ep) {
        return bothNegFlag ? 1 : -1;
    } else {
        for(int i=0; i<intPart.size(); i++) {
            if(intPart[i] > r.intPart[i]) {
                return bothNegFlag ? -1 : 1;
            } else if(intPart[i] < r.intPart[i]) {
                return bothNegFlag ? 1 : -1;
            } else if(i==intPart.size()-1 || i==r.intPart.size()-1) {
                if(intPart.size() == r.intPart.size()) {
                    return 0;
                }
                return intPart.size() > r.intPart.size() ? (bothNegFlag ? -1 : 1) : ( bothNegFlag ? 1 :-1);
            }
        }
    }
}
bool basicNumber::operator>(basicNumber r) {
    return this->comp(r) == 1;
}
bool basicNumber::operator<(basicNumber r) {
    return this->comp(r) == -1;
}
bool basicNumber::operator>=(basicNumber r) {
    int cond = this->comp(r);
    return cond==1 || cond==0;
}
bool basicNumber::operator<=(basicNumber r) {
    int cond = this->comp(r);
    return cond==-1 || cond==0;
}
bool basicNumber::operator==(basicNumber r) {
    return this->comp(r) == 0;
}
bool basicNumber::operator!=(basicNumber r) {
    int cond = this->comp(r);
    return cond==1 || cond==-1;
}

void basicNumber::clearZero() {
    while(intPart[0] == 0 && intPart.size()-ep!=1) { // 不删除小数部分的前导 0 和 0. 的 0
        intPart.erase(intPart.begin());
    }

    int cnt = ep; // 只能删除小数部分的后导 0
    while(cnt && *(intPart.end()-1) == 0) {
        intPart.pop_back();
        cnt--;
        ep--;
    }
}


basicNumber basicNumber::basicPower(basicNumber pow) {
    basicNumber result("1");

    if(pow.ep != 0) { // 指数非整数, 返回 ep=-1 的对象
        result.ep = -1;
        return result;
    }
    if(*this == 0) {
        result = 0;
        return result;
    }

    if(pow == 0) {
        result = 1;
        return result;
    }

    if(pow < 0) {
        pow = -pow;
        return 1 / basicPower(pow);
    }

    for(basicNumber i=0; i<pow; i++) {
        result *= *this;
    }
    return result;
}
basicNumber basicNumber::basicRoot(basicNumber rot, basicNumber diff) {
    basicNumber result = *this/2;
    if(rot.ep!=0 || rot<=0 || (*this<0 && rot%2 == 0)) { // 参数非整数或 底数为负且参数为偶数, 返回 ep=-1 的对象
        result.ep = -1;
        return result;
    }
    if(*this == 0) {
        result = 0;
        return result;
    }

    int cnt=0; // 迭代次数

    while(!( (result.basicPower(rot)-*this).basicAbs() <= diff ) && cnt<ROOT_ITERATIONS) {
        result = ((rot-1)*result + *this/result.basicPower(rot-1)) / rot;
    }
    return result;
}

basicNumber basicNumber::basicLn() {
    /* basicNumber 自然对数
     * 由于精度问题只取到 4 位小数, 基本可以保证精确到 3 位小数
     * */
    basicNumber result=0, cae=*this; // cae: 不修改 this 的值;
    if(*this <= 0) { // 不合法, 返回 ep=-1 的对象
        result.ep = -1;
        return result;
    }
    if(*this == 1) { // ln1 = 0
        return result;
    }

    basicNumber k;
    for(k=0; cae>=10; k++) {
        cae/=10;
    }
    result += k*string("2.3025850929940456840179914546844"); // ln10
    // result += cae.helpBasicLn();
    stringstream buf;
    double caeD;
    buf << cae;
    buf >> caeD;

    result += log(caeD);

    result.basicCut(4);

    return result;
}
basicNumber basicNumber::basicLog(basicNumber base) { // 换底公式
    if(base == 1) {
        return -1;
    }
    return this->basicLn()/base.basicLn();
}

basicNumber basicNumber::basicCut(int dec) {
    /*basicNumber 截断函数
     * 取小数点后 dec 位
     * */
    if(dec < 0) {
        return *this;
    }

    while(ep > dec) {
        intPart.pop_back();
        ep--;
    }
    return *this;

}


basicNumber basicGCD(basicNumber a, basicNumber b) {
    basicNumber r = a % b;
    while(r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}
basicNumber basicLCM(basicNumber a, basicNumber b) {
    return a*b/basicGCD(a, b);
}


//basicNumber basicNumber::basicRound() {}
//basicNumber basicNumber::basicFloor() {}
//basicNumber basicNumber::basicCeil() {}
//
//basicNumber basicNumber::basicSin() {}
//basicNumber basicNumber::basicCos() {}
//basicNumber basicNumber::basicTan() {}
//
//basicNumber basicNumber::basicASin() {}
//basicNumber basicNumber::basicACos() {}
//basicNumber basicNumber::basicATan() {}