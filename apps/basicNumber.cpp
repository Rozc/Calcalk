//
// Created by Rozc on 2018/5/4.
//
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <stack>
#include "basicNumber.h"
#include "tools.h"

using namespace std;

const basicNumber PI = string("3.1415926535897932384626"); // 1.22
const basicNumber EX = string("2.7182818284590452353602"); // 1.22

// Class Function Start

int basicNumber::DIVISION_ITERATIONS = 10;
int basicNumber::ROOT_ITERATIONS = 50;

bool basicNumber::getAcNe() {
    return this->AcNe;
}
int basicNumber::getEp() {
    return this->ep;
}

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
void basicNumber::wrongNumber() {
    // 使 this 变为一个 ep = -1 的数, 用于错误处理
    ep = -1;
}

basicNumber& basicNumber::operator=(basicNumber r) {
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
    if(item.ep == -1) {
        return out;
    }
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
    basicNumber result = *this;
    result.AcNe = !AcNe;
    return result;
}

basicNumber basicNumber::basicAbs() {
    if(*this >= 0) {
        return *this;
    } else {
        return -(*this);
    }
}

basicNumber basicNumber::operator/(basicNumber r) {
    basicNumber result, dividend=this->basicAbs(), divisor = r.basicAbs(), offset = string("1"), rem;

    if(divisor == 0) { // 除数为 0, 不合法, 返回 ep=-1 的对象
        result.ep = -1;
        return result;
    }

    while(dividend.ep!=0 || divisor.ep!=0) { // 将小数转化为整数
        dividend *= string("10");
        divisor *= string("10");
    }

    result += (dividend.intDivision(divisor)).basicAbs();
    rem = (dividend%divisor).basicAbs();

    int cnt=0;
    while(cnt++ < DIVISION_ITERATIONS && rem!=0) { // 模拟竖式除法, 迭代

        offset *= string("0.1");
        rem *= string("10");
        result += rem.intDivision(divisor) * offset;
        rem = (rem%divisor).basicAbs();
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
    /* basicNumber 整数除法(仅限整数) 进行了效率优化
     * 规则遵循 C++ int 型规则
     * Args:
     *  左操作数与右操作数均要求 eq == 0
     * */
    basicNumber result=0, div=this->intPart[0], hlpV=0;
    if(ep!=0 || r.ep!=0 || r==0) { // 存在小数部分或除数为 0, 返回 eq=-1 的对象
        result.ep = -1;
        return result;
    }

    int cntDiv=0;

    while(true) {
        if(div >= r) { // 除一次, 余数与被除数后一部分继续扩增
            result *= 10;
            hlpV =  div.helpIntDivi(r);
            result += hlpV;
            div = div - hlpV*r;
        } else { // 被除数从首位开始逐渐增加向后扩增, 直到大于除数
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

int basicNumber::comp(const basicNumber& r) const {
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
bool basicNumber::operator>(const basicNumber& r) const {
    return this->comp(r) == 1;
}
bool basicNumber::operator<(const basicNumber& r) const {
    return this->comp(r) == -1;
}
bool basicNumber::operator>=(const basicNumber& r) const {
    int cond = this->comp(r);
    return cond==1 || cond==0;
}
bool basicNumber::operator<=(const basicNumber& r) const {
    int cond = this->comp(r);
    return cond==-1 || cond==0;
}
bool basicNumber::operator==(const basicNumber& r) const {
    return this->comp(r) == 0;
}
bool basicNumber::operator!=(const basicNumber& r) const {
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
    result.basicCut(diff.ep-1);
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


basicNumber basicRound(const basicNumber& num, int d) { // default d = 0;
    basicNumber result = num;
    int idx = result.intPart.size();

    if(d < 0) {
        result.ep = -1;
        return result;
    }

    while(result.ep > d) {
        if(result.intPart[idx-1] >= 5) {
            result.intPart[idx-2] += 1;
        }

        result.intPart.pop_back();
        result.ep--;
        idx--;
    }

    while(result.intPart[idx-1] >= 10) {
        if(idx == 1) {
            result.intPart.insert(result.intPart.begin(), 1);
        } else {
            result.intPart[idx-2] += 1;
        }
        result.intPart[idx-1] -= 10;
        idx--;
    }

    return result;
}
basicNumber basicFloor(const basicNumber& num, int d) {
    basicNumber result = num;
    int idx = result.intPart.size();

    if(d < 0) {
        result.ep = -1;
        return result;
    }

    while(result.ep > d) {
        result.intPart.pop_back();
        result.ep--;
        idx--;
    }

}
basicNumber basicCeil(const basicNumber& num, int d) {
    basicNumber result = num;
    int idx = result.intPart.size();

    if(d < 0) {
        result.ep = -1;
        return result;
    }

    while(result.ep > d) {
        result.intPart[idx-2] += 1;
        result.intPart.pop_back();
        result.ep--;
        idx--;
    }

    while(result.intPart[idx-1] >= 10) {
        if(idx == 1) {
            result.intPart.insert(result.intPart.begin(), 1);
        } else {
            result.intPart[idx-2] += 1;
        }
        result.intPart[idx-1] -= 10;
        idx--;
    }

    return result;
}

basicNumber basicTriFHelp(const basicNumber& num, int typ) {
    /* 三角函数 辅助函数, 增强代码复用性
     * 调用 cmath 库的三角函数
     * typ:
     *  1: sin
     *  2: cos
     *  3: tan
     * */

    basicNumber pi = PI, result = num;
    stringstream buf;
    double dbRes;

    int cnt=21;

    pi *= basicNumber(10).basicPower(21); // 转化为整数以进行整数除法操作
    result *= basicNumber(10).basicPower(21); // 因为 PI 精确到小数点后 21 位, 故这 21 次是必须执行的

    while(pi.ep!=0 && result.ep!=0) {
        pi *= 10;
        result *= 10;
        cnt++;
    }
    cout << result << endl;
    result.intDivision(pi);
    result /= basicNumber(10).basicPower(cnt);
    buf << result;
    buf >> dbRes;
    switch(typ) {
        case 1:
            result = sin(dbRes);
            break;
        case 2:
            result = cos(dbRes);
            break;
        case 3:
            result = tan(dbRes);
            break;
        default:
            result.wrongNumber();
    }

    return result;

}
basicNumber basicSin(const basicNumber& num) {
    return basicTriFHelp(num, 1);
}
basicNumber basicCos(const basicNumber& num) {
    return basicTriFHelp(num, 2);
}
basicNumber basicTan(const basicNumber& num) {
    return basicTriFHelp(num, 3);
}

basicNumber basicATriFHelp(const basicNumber& num, int typ) {
    /* 反三角函数 辅助函数, 增强代码复用性
 * 调用 cmath 库的三角函数
 * typ:
 *  1: asin
 *  2: acos
 * */
    basicNumber result;
    stringstream buf;
    double dbRes;

    if(num <= -1 || num >= 1) { // 超出 asin 和 acos 的定义域
        result.wrongNumber();
        return result;
    }

    buf << num;
    buf >> dbRes;
    switch(typ) {
        case 1:
            return asin(dbRes);
        case 2:
            return acos(dbRes);
        default:
            result.wrongNumber();
            return result;
    }
}
basicNumber basicASin(const basicNumber& num) {
    return basicATriFHelp(num, 1);
}
basicNumber basicACos(const basicNumber& num) {
    return basicATriFHelp(num, 2);
}
basicNumber basicATan(const basicNumber& num) {
    /* 因为 atan 在参数较大时趋近于 pi/2, 故直接调用 cmath 库的 atan 函数 */
    stringstream buf;
    double dbRes;
    buf << num;
    buf >> dbRes;
    return atan(dbRes);

}


// Class Function End

// Main Function Start

int oprtPriority(char op) {
    switch(op) {
        case '(':
        case ')':
            return 1;
        case '#':
            return 2;
        case '^':
        case '_':
            return 3;
        case '*':
        case '/':
        case '%':
        case '$':
            return 4;
        case '+':
        case '-':
            return 5;
        default:
            return -1;
    }
}

void realPre(string& expression) {
//  负号转换为 # 以与减号区分
    int sz = expression.size();
    for(int i=0; i<sz; i++) {
        if(expression[i] == '-' &&
           (i==0 ||
            (expression[i-1] != ')' &&
             !(48 <= expression[i-1] && expression[i-1] < 58 ) &&
             expression[i-1] != 'a'))) {

            expression[i] = '#';
        }
    }
}

string realRePolish(string expression, basicNumber ansLast) {
    realPre(expression);

    int sz = expression.size();
    stack<char> stkOprt;
    string RePolish;

    for(int i=0; i<sz; i++) {
        char expr = expression[i];
        if((48 <= expr && expr < 58) || expr == '.') {
            RePolish += expr;
        } else {

            RePolish += ',';

            if(expr == 'a') {
                stringstream buf;
                string tmp;

                buf << ansLast;
                buf >> tmp;
                RePolish += tmp;
            } else if(expr == '(') {

                stkOprt.push(expr);

            } else if(expr == ')') {

                while(stkOprt.top() != '(') {
                    RePolish += stkOprt.top();
                    stkOprt.pop();
                }
                stkOprt.pop(); // Pop the '('

            } else  {

                if(stkOprt.empty() || stkOprt.top() == '(' ||
                   oprtPriority(expr)<oprtPriority(stkOprt.top())) {
                    stkOprt.push(expr);
                } else {
                    while(!stkOprt.empty() && stkOprt.top() != '(') {
                        RePolish += stkOprt.top();
                        stkOprt.pop();
                    }
                    stkOprt.push(expr);
                }

            }

        }
    }
    RePolish += ',';
    while(!stkOprt.empty()) {
        RePolish += stkOprt.top();
        stkOprt.pop();
    }
    return RePolish;
}

basicNumber realCalcRP(string reP) {
    stack<basicNumber> stkNum;
    int sz = reP.size();

    basicNumber tmpNum, tmpLeft, tmpRight, tmpResult;

    for(int i=0; i<sz; i++) {
        if(reP[i] == ',') {
            continue;
        } else if(48 <= reP[i] && reP[i] < 58) {
            stringstream buf;

            buf << reP.substr(i, reP.find(',', i+1)-i);
            buf >> tmpNum;

            if(tmpNum.getEp() == -1) { // ERROR
                return tmpNum;
            }

            stkNum.push(tmpNum);
            i = reP.find(',', i+1);
        } else {

            if(reP[i] == '#') {
                if(stkNum.empty()) { // ERROR
                    tmpResult.wrongNumber();
                    return tmpResult;
                }
                tmpLeft = stkNum.top();
                stkNum.pop();
                tmpLeft = -tmpLeft;
                stkNum.push(tmpLeft);
            } else {

                if(stkNum.empty()) { // ERROR
                    tmpResult.wrongNumber();
                    return tmpResult;
                }
                tmpRight = stkNum.top();
                stkNum.pop();

                if(stkNum.empty()) { // ERROR
                    tmpResult.wrongNumber();
                    return tmpResult;
                }
                tmpLeft = stkNum.top();
                stkNum.pop();

                tmpResult = realCalcWithOprt(tmpLeft, tmpRight, reP[i]);
                if(tmpResult.getEp() == -1) { // ERROR
                    return tmpResult;
                }
                stkNum.push(tmpResult);
            }


        }
    }
    return stkNum.top();
}

basicNumber realCalcWithOprt(basicNumber a, basicNumber b, char op) {
    basicNumber result;
    switch(op) {
        case '+':
            result = a + b; break;
        case '-':
            result = a - b; break;
        case '*':
            result = a * b; break;
        case '/':
            result = a / b; break;
        case '%':
            result = a % b; break;
        case '$':
            result = a.intDivision(b); break;
        case '^':
            result = a.basicPower(b); break;
        case '_':
            result = a.basicRoot(b, 0.0001); break;
        default:
            result.wrongNumber();
            break;
    }
    return result;
}

basicNumber real2Calc(int func, basicNumber& ansLast) {
    string exprA;
    basicNumber valA, result;
    while(true) {
        cout << "Please input expression A: ";
        cin >> exprA;
        while(cin.get() != '\n');
        valA = realCalcRP(realRePolish(exprA, ansLast));
        if(valA.getEp() != -1) {
            break;
        } else {
            realMode1ERRORInfo();
        }
    }


    if(1 <= func && func <= 8) { // single argument;
        switch(func) {
            case 1: result = valA.basicAbs(); break;
            case 2: result = valA.basicLn(); break;
            case 3: result = basicSin(valA); break;
            case 4: result = basicCos(valA); break;
            case 5: result = basicTan(valA); break;
            case 6: result = basicASin(valA); break;
            case 7: result = basicACos(valA); break;
            case 8: result = basicATan(valA); break;
            default:
                result.wrongNumber();
                break;
        }
    } else { // 2 arguments
        string exprB;
        basicNumber valB;
        while(true) {
            cout << "Please input expression A: ";
            cin >> exprB;
            while(cin.get() != '\n');
            valB = realCalcRP(realRePolish(exprB, ansLast));
            if(valB.getEp() != -1) {
                break;
            } else {
                realMode1ERRORInfo();
            }
        }

        switch(func) {
            case 9:  result = valA.basicLog(valB); break;
            case 10: result = basicGCD(valA, valB); break;
            case 11: result = basicLCM(valA, valB); break;
            default:
                result.wrongNumber();
                break;
        }
    }

    return result;

}

void realMode1(basicNumber& ansLast) {
    system("cls");
    realMode1Info();

    string expr;
    basicNumber result;
    while(true) {
        cout << "Please input the expression('EXIT' to quit): ";
        cin >> expr;
        while(cin.get() != '\n');
        if(expr == "EXIT" || expr == "exit") {
            system("cls");
            realModeInfo();
            break;
        }
        result = realCalcRP(realRePolish(expr, ansLast));
        if(result.getEp() == -1) {
            realMode1ERRORInfo();
        } else {
            ansLast = result;
            cout << "Answer: " << result << endl << endl;
        }

    }

}

void realMode2(basicNumber& ansLast) {
    system("cls");
    realMode2Info();

    int func;

    basicNumber result;

    while(true) {
        cout << "Please input function ID(0 to quit): ";
        cin >> func;

        if(!cin) {
            cout << "Bad input, please input an integer between 0 and 11" << endl;
            cin.clear();
            while(cin.get() != '\n');
            continue;
        }
        while(cin.get() != '\n');

        if(func == 0) {
            goto real2EXIT;
        } else if(1 <= func && func <= 11) {
            result = real2Calc(func, ansLast);
        } else  {
            cout << "Bad input, please input an integer between 0 and 11" << endl;
        }

        if(result.getEp() == -1) {
            realMode2ERRORInfo();
        } else {
            ansLast = result;
            cout << "Answer: " << result << endl << endl;
        }

    }

    real2EXIT:
    system("cls");
    realModeInfo();
}

// Message Function

void realModeInfo() {
    cout << endl << "Now in Normal Mode" << endl;
    cout << "In this mode, you can choose 2 sub mode: " << endl <<
         "   1 for expression only contains +, -, *, /, ^, _, %, $ and '()'" << endl <<
         "   2 for function (sin, cos, gcd, lcm, round, and so on)(also can contains expression)" << endl <<
         "   0 to Quit." << endl <<
         "   You can use 'a' in expression for result of last calculation" << endl <<
         "       (default value: 0)(It will be set to 0 when you leave Normal Mode)." << endl;
}

void realMode1Info() {
    cout << endl << "Now in Normal Mode - Mode 1" << endl;
    cout << "Operator Priority Order:" << endl <<
         "   1. (, )" << endl <<
         "   2. - | Negative Symbol" << endl <<
         "   3. ^, _ | ^ = Power, _ = Root(A_B = B_root(A))" << endl <<
         "   4. *, /, %, $ | $ = integer division " << endl <<
         "   5. +, -" << endl << endl;
}

void realMode2Info() {
    cout << endl << "Now in Normal Mode - Mode 2" << endl;
    cout << "Functions List:" << endl <<
        "   1. abs(A)" << endl <<
        "   2. ln(A) (A>0) (Precision: .3)" << endl <<
        "   3. sin(A), 4. cos(A), 5. tan(A), 6. asin(A) (-1<A<1), 7. acos(A) (-1<A<1), 8. atan(A)" << endl <<
        "   9. logA(B) (A>0, A!=0, B>0) (Precision: .3)" << endl <<
        "   10. GCD(A, B), 11. LCM(A, B), require that A and B is a positive integer" << endl << endl;
}

void realMode1ERRORInfo() {
    cout << endl << "--- ERROR: in real Number Mode ---" << endl;
    cout << "Have you:" << endl;
    cout << "   1. Divided by 0." << endl;
    cout << "   2. A^B or A_B and B is not an integer." << endl <<
         "      (A^B requires that B is an integer, A_B requires that B is a positive integer)." << endl;
    cout << "   3. A%B or A$B and A or B is not integer." << endl;
    cout << "   4. Illegal input." << endl;
    cout << "?" << endl;
    cout << "--- ERROR: End of error message ---" << endl << endl;
}

void realMode2ERRORInfo() {
    cout << endl << "--- ERROR: in real Number Mode ---" << endl;
    cout << "Have you given some wrong arguments to the function ?" << endl;
    cout << "--- ERROR: End of error message ---" << endl << endl;
}