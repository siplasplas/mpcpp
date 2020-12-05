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

class Format {
public:
    static int roundBuf(char *buf,const size_t precision) {
        if (precision==0) {
            buf[0]=0;
            return 0;
        }
        if (buf[precision]<'5') return 0; //also return if 0 byte
        buf[precision] = 0;
        size_t n = precision-1;
        if (buf[n]<'9') buf[n]++;
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
public:
    static std::string output(char *buf) {
        std::string str = buf;
        return str;
    }
};
