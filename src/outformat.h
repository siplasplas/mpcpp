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
