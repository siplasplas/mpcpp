#include "gmpcpp.h"
#include "outformat.h"
#include <cmath>
#include <iostream>
#include <algorithm>

namespace gmp {
    long int digits2bits(long int d) {
        return std::ceil(d * BITS_PER_DIGIT);
    }

    long int bits2digits(long int b) {
        return int(std::floor(b * DIGITS_PER_BIT));
    }

    Mpz sqrt(const Mpz &v) {
        Mpz result;
        mpz_sqrt(result.mp, v.mp);
        return result;
    }

    size_t Mpz::sizeinbase(int base) {
        return mpz_sizeinbase(mp, base);
    }

    void Mpz::neg() {
        mpz_neg(mp, mp);
    }

    Mpf sqrt(const unsigned long v) {
        Mpf result;
        mpf_sqrt_ui(result.mp, v);
        return result;
    }

    Mpz::Mpz(const std::string &str) { //#todo hex, oct
        mpz_init_set_str(mp, str.c_str(), 10);
    }

    Mpf::Mpf(const std::string &str) {
        mpf_init_set_str(mp, str.c_str(), 10);
    }

    Mpf::Mpf(const std::string &str, mp_bitcnt_t prec) {
        mpf_init2(mp, prec);
        mpf_set_str(mp, str.c_str(), 10);
    }

    Mpf::~Mpf() {
        mpf_clear(mp);
    }

    std::string Mpf::toString(const size_t precision) const {
        int sign = mp->_mp_size < 0;
        char *buf = new char[precision + 1 + sign];
        mp_exp_t exp;
        char *p = mpf_get_str(buf, &exp, 10, precision, mp);
        std::string str = Format::output(buf,libMpf, precWithZeros, precision,exp,sign);
        delete[]buf;
        return str;
    }


    std::ostream &operator<<(std::ostream &os, const Mpf &mpf) {
        const size_t precision = os.precision();
        std::string str = mpf.toString(precision);
        if (os.flags() & os.uppercase)
            transform(str.begin(), str.end(), str.begin(), ::toupper);
        os << str;
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const Mpz &mpz) {
        char* buffer = new char[mpz_sizeinbase(mpz.mp,10)+2];
        mpz_get_str (buffer, 10, mpz.mp);
        os << buffer;
        delete []buffer;
        return os;
    }

    bool Mpf::precWithZeros = false;
}

namespace std{
    string to_string(gmp::Mpf x) {
        return x.toString(40); //todo bits to digits default precision
    }
};
