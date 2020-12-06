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
#include "gmp.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "outformat.h"

#ifndef _GLIBCXX_CMATH
namespace std
{ //avoid include include <cmath> here
    long double ceil(long double __x);
    long double floor(long double __x);
}
#endif

namespace gmp {
    const long double BITS_PER_DIGIT = 3.32192809488736234787; //LOG2_10
    const long double DIGITS_PER_BIT = 0.3010299956639811952137; //LOG10_2

    const int DOUBLE_PREC = 53;


    inline long int digits2bits(long int d)
    {
        return std::ceil( d * BITS_PER_DIGIT );
    }

    inline long int bits2digits(long int b)
    {
        return int(std::floor( b * DIGITS_PER_BIT ));
    }

    class Mpz {
        friend class Mpf;
    public:
        mpz_t mp;
        Mpz() {
            mpz_init(mp);
        }

        Mpz(const Mpz &rhs) {
            mpz_init_set(mp, rhs.mp);
        }

        Mpz(const mpz_t &mpsrc) {
            mpz_init_set(mp, mpsrc);
        }

        explicit Mpz(const double d) {
            mpz_init_set_d(mp, d);
        }

        explicit Mpz(const std::string &str) { //#todo bex, oct
            mpz_init_set_str(mp, str.c_str(), 10);
        }

        ~Mpz() {
            mpz_clear(mp);
        }

        Mpz &operator=(const double d) {
            mpz_set_d(mp, d);
            return *this;
        }

        void operator+=(const long int n) {
            mpz_add_ui(mp, mp, n);
        }

        void operator*=(const long int n) {
            mpz_mul_si(mp, mp, n);
        }

        void operator+=(const Mpz &rhs) {
            mpz_add(mp, mp, rhs.mp);
        }

        void operator*=(const Mpz &rhs) {
            mpz_mul(mp, mp, rhs.mp);
        }

        explicit operator double() const {
            return mpz_get_d(mp);
        }

        explicit operator long int() const {
            return mpz_get_si(mp);
        }

        explicit operator unsigned long int() const {
            return mpz_get_ui(mp);
        }

        void divexactinplace(const Mpz &rhs) {
            mpz_divexact(mp, mp, rhs.mp);
        }

        Mpz divexact(const Mpz &rhs) {
            Mpz result;
            mpz_divexact(result.mp, mp, rhs.mp);
            return result;
        }

        void addmul(const Mpz &rhs, unsigned long int a) {
            mpz_addmul_ui(mp, rhs.mp, a);
        }


        friend std::ostream &operator<<(std::ostream &os, const Mpz &mpz);

        friend Mpz sqrt(const Mpz &v);

        size_t sizeinbase(int base);

        void neg();
    };

    inline Mpz sqrt(const Mpz &v) {
        Mpz result;
        mpz_sqrt(result.mp, v.mp);
        return result;
    }

    inline std::ostream &operator<<(std::ostream &os, const Mpz &mpz) {
        char* buffer = new char[mpz_sizeinbase(mpz.mp,10)+2];
        mpz_get_str (buffer, 10, mpz.mp);
        os << buffer;
        delete []buffer;
        return os;
    }

    class Mpf {
    public:
        static bool precWithZeros;
        mpf_t mp;
        Mpf() {
            mpf_init2(mp, mpf_get_default_prec());
        }

        Mpf(const Mpf &rhs) {
            mpf_init2(mp, mpf_get_prec(rhs.mp));
            mpf_set(mp, rhs.mp);
        }

        Mpf(const Mpz &rhs) {
            mpf_init2(mp, mpf_get_default_prec());
            mpf_set_z(mp, rhs.mp);
        }

        Mpf(const mpf_t &mpsrc) {
            mpf_init2(mp, mpf_get_prec(mpsrc));
            mpf_set(mp, mpsrc);
        }

        explicit Mpf(const double d) {
            mpf_init_set_d(mp, d);
        }

        Mpf(const double d, mp_bitcnt_t prec) {
            mpf_init2(mp, prec);
            mpf_set_d(mp, d);
        }

        explicit Mpf(const std::string &str) {
            mpf_init_set_str(mp, str.c_str(), 10);
        }

        Mpf(const std::string &str, mp_bitcnt_t prec) {
            mpf_init2(mp, prec);
            mpf_set_str(mp, str.c_str(), 10);
        }

        ~Mpf() {
            mpf_clear(mp);
        }

        Mpf &operator=(const double d) {
            mpf_set_d(mp, d);
            return *this;
        }

        Mpf &operator=(const Mpf &rhs) {
            mpf_set(mp, rhs.mp);
            return *this;
        }

        void operator*=(const Mpf &rhs) {
            mpf_mul(mp, mp, rhs.mp);
        }

        Mpf operator/(const Mpf &rhs) {
            Mpf result;
            mpf_div(result.mp, mp, rhs.mp);
            return result;
        }

        operator double() const {
            return mpf_get_d(mp);
        }

        std::string toString(const size_t precision) const {
            int sign = mp->_mp_size < 0;
            char *buf = new char[precision + 1 + sign];
            mp_exp_t exp;
            char *p = mpf_get_str(buf, &exp, 10, precision, mp);
            std::string str = Format::output(buf,libMpf, precWithZeros, precision,exp,sign);
            delete[]buf;
            return str;
        }

        friend std::ostream &operator<<(std::ostream &os, const Mpf &mpf);

        mp_bitcnt_t precision() {
            return mpf_get_prec(mp);
        }

        friend Mpf sqrt(const unsigned long int v);
    };

    inline size_t Mpz::sizeinbase(int base) {
        return mpz_sizeinbase(mp, base);
    }

    inline void Mpz::neg() {
        mpz_neg(mp, mp);
    }

    inline Mpf sqrt(const unsigned long v) {
        Mpf result;
        mpf_sqrt_ui(result.mp, v);
        return result;
    }

    inline std::ostream &operator<<(std::ostream &os, const Mpf &mpf) {
        const size_t precision = os.precision();
        std::string str = mpf.toString(precision);
        if (os.flags() & os.uppercase)
            transform(str.begin(), str.end(), str.begin(), ::toupper);
        os << str;
        return os;
    }
    inline bool Mpf::precWithZeros = false;
}

namespace std{
    inline string to_string(gmp::Mpf x) {
        return x.toString(40);
    }
};
