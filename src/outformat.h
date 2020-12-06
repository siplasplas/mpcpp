/*
Copyright 2020 Andrzej Borucki

This file is part of the mpcpp library wrapper.

The mpcpp is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The mpcpp is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MPFR Library; see the file COPYING.LESSER.  If not, see
https://www.gnu.org/licenses/ or write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA. */
#pragma once
#include <cstddef>

namespace gmp {
    enum Library {libMpf, libMpfr};

    class Format {
    public:
        //below is not used because I can't repeat case numstrings begin with zeros
        static int roundBuf(char *buf, const size_t precision) {
            if (precision == 0) {
                buf[0] = 0;
                return 0;
            }
            if (buf[precision] < '5') return 0; //also return if 0 byte
            buf[precision] = 0;
            size_t n = precision - 1;
            if (buf[n] < '9') buf[n]++;
            else {
                while (n >= 0 && buf[n] == '9') {
                    buf[n] = 0;
                    n--;
                }
                if (n >= 0) buf[n]++;
                else { //overlow
                    buf[0] = '1';
                    return 1;
                }
            }
            return 0;
        }

        static std::string addPrecZeros(std::string str, size_t precision) {
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

        static std::string removePrecZeros(std::string str) {
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

    public:
        static std::string output(char *buf, Library library, bool precWithZeros, const size_t precision, const mp_exp_t exp, const int sign) {
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
    };
 }