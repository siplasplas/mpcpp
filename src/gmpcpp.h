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

namespace gmp {
    const long double BITS_PER_DIGIT = 3.32192809488736234787; //LOG2_10
    const long double DIGITS_PER_BIT = 0.3010299956639811952137; //LOG10_2

    const int DOUBLE_PREC = 53;

    long int digits2bits(long int d);
    long int bits2digits(long int b);

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

        explicit Mpz(const std::string &str);

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

    Mpz sqrt(const Mpz &v);
    std::ostream &operator<<(std::ostream &os, const Mpz &mpz);

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

        explicit Mpf(const std::string &str);
        Mpf(const std::string &str, mp_bitcnt_t prec);
        ~Mpf();
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

        std::string toString(const size_t precision) const;

        friend std::ostream &operator<<(std::ostream &os, const Mpf &mpf);

        mp_bitcnt_t precision() {
            return mpf_get_prec(mp);
        }

        friend Mpf sqrt(const unsigned long int v);
    };

    Mpf sqrt(const unsigned long v);

    std::ostream &operator<<(std::ostream &os, const Mpf &mpf);
}

namespace std{
    string to_string(gmp::Mpf x);
};
