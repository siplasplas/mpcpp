#include "outformat.h"

namespace gmp {
    std::string Format::addPrecZeros(std::string str, size_t precision) {
        size_t digCnt = 0;
        int start;
        if (str[0]=='-') start=1;else start=0;
        while (str[start]=='0'|| str[start]=='.') start++;
        int pos = str.length();
        for (int i = start; i < str.length(); i++) {
            if (!isdigit(str[i]) && str[i] != '.') {
                pos = i;
                break;
            }
            if (isdigit(str[i])) digCnt++;
        }
        if (digCnt>=precision) return str;

        auto n = str.find('.');
        if (n==std::string::npos) {
            str.insert(pos, ".");
            pos++;
        }

        std::string zeros;
        for (int i=digCnt; i<precision; i++)
            zeros+= '0';
        str.insert(pos, zeros);
        return str;
    }

    std::string Format::removePrecZeros(std::string str) {
        auto n = str.find('.');
        if (n==std::string::npos) return str;
        int start;
        if (str[0]=='-') start=1;else start=0;
        int pos = str.length();
        for (int i = start; i < str.length(); i++) {
            if (!isdigit(str[i]) && str[i] != '.') {
                pos = i;
                break;
            }
        }
        n = pos-1;
        while (n>=0 && str[n]=='0') n--;
        if (n>=0 && str[n]!='.') n++;
        str.erase(n, pos-n);
        return str;
    }

    std::string Format::output(char *buf, Library library, bool precWithZeros, const size_t precision, const mp_exp_t exp, const int sign) {
        std::string str = buf;
        if (exp >= 1) {
            if (exp < str.length() - sign)
                str.insert(str.begin() + exp + sign, '.');
            else if (exp > str.length() - sign) {
                if (exp <= precision) {
                    for (int i = str.length() - sign; i < exp; i++)
                        str += '0';
                } else {
                    if (str.length() - sign > 1)
                        str.insert(str.begin() + 1 + sign, '.');
                    std::string expStr = std::to_string(exp - 1);
                    if (expStr.length() == 1) expStr = '0' + expStr;
                    str += "e+" + expStr;
                }
            }
        } else {
            if (exp >= -3) {
                if (str.empty())
                    str = "0";
                else {
                    std::string zeros = "0.";
                    for (int i = 0; i < -exp; i++) zeros += '0';
                    str.insert(sign, zeros);
                }
            } else {
                if (str.length() - sign > 1)
                    str.insert(str.begin() + 1 + sign, '.');
                std::string expStr = std::to_string(-exp + 1);
                if (expStr.length() == 1) expStr = '0' + expStr;
                str += "e-" + expStr;
            }
        }
        if (library==libMpfr && !precWithZeros)
            str = removePrecZeros(str);
        else if (library==libMpf && precWithZeros)
            str = addPrecZeros(str, precision);
        return str;
    }
}

