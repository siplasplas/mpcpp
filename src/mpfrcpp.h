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
#include "mpfr.h"
#include "gmpcpp.h"

namespace mpfr {
    mpfr_prec_t get_default_prec();
    mpfr_prec_t get_default_digits();
    void set_default_prec(mpfr_prec_t prec);
    mpfr_rnd_t get_default_round();
    void set_default_round(mpfr_rnd_t r);
    mp_exp_t get_emin();
    int set_global_emin(mp_exp_t exp);
    mp_exp_t get_emax();
    int set_global_emax(mp_exp_t exp);
    mp_exp_t get_emin_min();
    mp_exp_t get_emin_max();
    mp_exp_t get_emax_min();
    mp_exp_t get_emax_max();
    class Mpfr {
    public:
        static bool precWithZeros;
        mpfr_t mp;
        Mpfr() {
            mpfr_init2(mp, mpfr_get_default_prec());
            mp->_mpfr_exp = __MPFR_EXP_ZERO;
        }

        Mpfr(const double d, mpfr_prec_t prec = mpfr_get_default_prec()) {
            mpfr_init2(mp, prec);
            mpfr_set_d(mp, d, mpfr_get_default_rounding_mode());
        }

        Mpfr(const std::string str, mpfr_prec_t prec = mpfr_get_default_prec());

        ~Mpfr() {
            mpfr_clear(mp);
        }

        mpfr_prec_t getprec() const {
            return mpfr_get_prec(mp);
        }

        Mpfr(const Mpfr& rhs) {
            mpfr_init2(mp, rhs.getprec());
            mpfr_set(mp, rhs.mp, mpfr_get_default_rounding_mode());
        }

        Mpfr(Mpfr&& other)
        {
            mpfr_init2(mp, 1);  // small object, will be deleted
            mpfr_swap(mp, other.mp);
        }

        Mpfr operator<<(const unsigned long int k) {
            Mpfr r(getprec());
            mpfr_mul_2ui(r.mp, mp, k, get_default_round());
            return r;
        }

        Mpfr operator<<(const long int k) {
            Mpfr r(getprec());
            mpfr_mul_2si(r.mp, mp, k, get_default_round());
            return r;
        }

        Mpfr operator>>(const unsigned long int k) {
            Mpfr r(getprec());
            mpfr_div_2ui(r.mp, mp, k, get_default_round());
            return r;
        }

        Mpfr operator>>(const long int k) {
            Mpfr r(getprec());
            mpfr_div_2si(r.mp, mp, k, get_default_round());
            return r;
        }

        Mpfr& operator<<=(const unsigned long int k) {
            mpfr_mul_2ui(mp, mp, k, get_default_round());
            return *this;
        }

        Mpfr& operator<<=(const long int k) {
            mpfr_mul_2si(mp, mp, k, get_default_round());
            return *this;
        }

        Mpfr& operator>>=(const unsigned long int k) {
            mpfr_div_2ui(mp, mp, k, get_default_round());
            return *this;
        }

        Mpfr& operator>>=(const long int k) {
            mpfr_div_2si(mp, mp, k, get_default_round());
            return *this;
        }


        Mpfr& operator=(Mpfr&& other)
        {
            if (this != &other)
            {
                mpfr_swap(mp, other.mp); // destructor for "other" will be called just afterwards
            }
            return *this;
        }

        Mpfr& setInf(int sign)
        {
            mpfr_set_inf(mp, sign);
            return *this;
        }

        Mpfr& setNan()
        {
            mpfr_set_nan(mp);
            return *this;
        }

        Mpfr& setZero(int sign)
        {
            mpfr_set_zero(mp, sign);
            return *this;
        }

        Mpfr& setSign(int sign, mp_rnd_t r=mpfr_get_default_rounding_mode())
        {
            mpfr_setsign(mp, mp, sign < 0, r);
            return *this;
        }

        Mpfr &operator=(const Mpfr &x) {
            mpfr_set(mp, x.mp, mpfr_get_default_rounding_mode());
            return *this;
        }

        Mpfr &operator=(double d) {
            mpfr_set_d(mp, d, mpfr_get_default_rounding_mode());
            return *this;
        }

        Mpfr operator+(const Mpfr& rhs) const{
            Mpfr result(*this);
            mpfr_add(result.mp, mp, rhs.mp, mpfr_get_default_rounding_mode());
            return result;
        }

        void operator+=(const Mpfr& rhs) {
            mpfr_add(mp, mp, rhs.mp, mpfr_get_default_rounding_mode());
        }

        Mpfr operator+(double d) const{
            Mpfr result(*this);
            mpfr_add_d(result.mp, mp, d, mpfr_get_default_rounding_mode());
            return result;
        }

        Mpfr operator-(const Mpfr& rhs) const{
            Mpfr result(*this);
            mpfr_sub(result.mp, mp, rhs.mp, mpfr_get_default_rounding_mode());
            return result;
        }

        void operator-=(const Mpfr& rhs) {
            mpfr_sub(mp, mp, rhs.mp, mpfr_get_default_rounding_mode());
        }

        Mpfr operator-(double d) const{
            Mpfr result(*this);
            mpfr_sub_d(result.mp, mp, d, mpfr_get_default_rounding_mode());
            return result;
        }

        Mpfr operator*(const Mpfr& rhs) const {
            Mpfr result(*this);
            mpfr_mul(result.mp, mp, rhs.mp, mpfr_get_default_rounding_mode());
            return result;
        }

        Mpfr operator*(double d) const{
            Mpfr result(*this);
            mpfr_mul_d(result.mp, mp, d, mpfr_get_default_rounding_mode());
            return result;
        }

        void operator*=(const Mpfr& rhs) {
            mpfr_mul(mp, mp, rhs.mp, mpfr_get_default_rounding_mode());
        }

        Mpfr operator/(const Mpfr& rhs) const {
            Mpfr result(*this);
            mpfr_div(result.mp, mp, rhs.mp, mpfr_get_default_rounding_mode());
            return result;
        }

        void operator/=(const Mpfr& rhs) {
            mpfr_div(mp, mp, rhs.mp, mpfr_get_default_rounding_mode());
        }

        Mpfr operator-() const {
            Mpfr result;
            mpfr_neg(result.mp, mp, mpfr_get_default_rounding_mode());
            return result;
        }

        bool operator>(const Mpfr& rhs) const{
            return mpfr_greater_p(mp, rhs.mp)!=0;
        }

        bool operator>(const double d) const{
            Mpfr rhs(getprec());
            rhs = d;
            return mpfr_greater_p(mp, rhs.mp)!=0;
        }

        bool operator>=(const Mpfr& rhs) const{
            return mpfr_greaterequal_p(mp, rhs.mp)!=0;
        }

        bool operator>=(const double d) const{
            Mpfr rhs(getprec());
            rhs = d;
            return mpfr_greaterequal_p(mp, rhs.mp)!=0;
        }

        bool operator<(const Mpfr& rhs) const{
            return mpfr_less_p(mp, rhs.mp)!=0;
        }

        bool operator<(const double d) const{
            Mpfr rhs(getprec());
            rhs = d;
            return mpfr_less_p(mp, rhs.mp)!=0;
        }

        bool operator<=(const Mpfr& rhs) const{
            return mpfr_lessequal_p(mp, rhs.mp)!=0;
        }

        bool operator<=(const double d) const{
            Mpfr rhs(getprec());
            rhs = d;
            return mpfr_lessequal_p(mp, rhs.mp)!=0;
        }

        bool operator==(const Mpfr& rhs) const{
            return mpfr_equal_p(mp, rhs.mp)!=0;
        }

        bool operator==(const double d) const{
            Mpfr rhs(getprec());
            rhs = d;
            return mpfr_equal_p(mp, rhs.mp)!=0;
        }

        bool operator!=(const Mpfr& rhs) const{
            return mpfr_lessgreater_p(mp, rhs.mp)!=0;
        }

        bool operator!=(const double d) const{
            Mpfr rhs(getprec());
            rhs = d;
            return mpfr_lessgreater_p(mp, rhs.mp)!=0;
        }

        explicit operator double() const {
            return mpfr_get_d(mp, mpfr_get_default_rounding_mode());
        }

        std::string toString(mpfr_prec_t precision) const;

        mp_exp_t get_exp() const
        {
            return mpfr_get_exp(mp);
        }

        int set_exp (mp_exp_t e)
        {
            int x = mpfr_set_exp(mp, e);
            return x;
        }

        int check_range (int t, mp_rnd_t r = mpfr_get_default_rounding_mode())
        {
            return mpfr_check_range(mp,t, r);
        }

        int subnormalize (int t, mp_rnd_t r = mpfr_get_default_rounding_mode())
        {
            int sr = mpfr_subnormalize(mp,t, r);
            return sr;
        }

        Mpfr& swap(Mpfr& x)
        {
            if (this != &x)
            {
                mpfr_swap(mp, x.mp);
            }
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const Mpfr &mp);
    };

    std::ostream &operator<<(std::ostream &os, const Mpfr &mp);

    struct Randstate {
        gmp_randstate_t state;
        Randstate() {
            gmp_randinit_default(state);
        }
        ~Randstate() {
            gmp_randclear(state);
        }
    };

    Mpfr operator+(double d, const Mpfr& rhs);
    Mpfr operator+(int k, const Mpfr& rhs);
    Mpfr operator-(double d, const Mpfr& rhs);
    Mpfr operator-(int k, const Mpfr& rhs);
    Mpfr operator*(double d, const Mpfr& rhs);
    Mpfr operator*(int k, const Mpfr& rhs);
    Mpfr operator/(double d, const Mpfr& rhs);
    Mpfr operator/(int k, const Mpfr& rhs);

#define FUNC_F_To_F_rename_h(name, mpfrname) \
    Mpfr name(const Mpfr& x, mpfr_prec_t prec); \
    Mpfr name(const Mpfr& x);

#define FUNC_F_To_F_rename(name, mpfrname) \
    Mpfr name(const Mpfr& x, mpfr_prec_t prec) { \
        Mpfr result(0,prec);                 \
        mpfr_##mpfrname(result.mp, x.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    } \
    Mpfr name(const Mpfr& x) { \
        return name(x, mpfr_get_prec(x.mp)); \
    }

#define FUNC_F_To_F_h(name) \
        FUNC_F_To_F_rename_h(name, name)

#define FUNC_F_To_F(name) \
        FUNC_F_To_F_rename(name, name)

#define FUNC_FI_To_F_h(name) \
Mpfr name(const Mpfr& x, long int k, mpfr_prec_t prec); \
    Mpfr name(const Mpfr& x, long int k);

#define FUNC_FI_To_F(name) \
Mpfr name(const Mpfr& x, long int k, mpfr_prec_t prec) { \
        Mpfr result(0,prec); \
        mpfr_##name(result.mp, x.mp, k, mpfr_get_default_rounding_mode()); \
        return result; \
    }                      \
    Mpfr name(const Mpfr& x, long int k) { \
        return name(x, k, mpfr_get_prec(x.mp)); \
    }


#define FUNC_FU_To_F_h(name) \
Mpfr name(const Mpfr& x, unsigned long int k, mpfr_prec_t prec); \
Mpfr name(const Mpfr& x, unsigned long int k);

#define FUNC_FU_To_F(name) \
Mpfr name(const Mpfr& x, unsigned long int k, mpfr_prec_t prec) { \
        Mpfr result(0,prec); \
        mpfr_##name(result.mp, x.mp, k, mpfr_get_default_rounding_mode()); \
        return result; \
    }                      \
    Mpfr name(const Mpfr& x, unsigned long int k) { \
        return name(x, k, mpfr_get_prec(x.mp)); \
    }


#define FUNC_IF_To_F_rename_h(name, mpfrname) \
    Mpfr name(unsigned long int k, const Mpfr& x, mpfr_prec_t prec); \
    Mpfr name(unsigned long int k, const Mpfr& x);

#define FUNC_IF_To_F_rename(name, mpfrname) \
    Mpfr name(unsigned long int k, const Mpfr& x, mpfr_prec_t prec) { \
        Mpfr result(0,prec); \
        mpfr_##mpfrname(result.mp, k, x.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    } \
    Mpfr name(unsigned long int k, const Mpfr& x) { \
        return name(k, x, mpfr_get_prec(x.mp)); \
    }

#define FUNC_I_To_F_h(name) \
Mpfr name(unsigned long int k, mpfr_prec_t prec); \
Mpfr name(unsigned long int k);

#define FUNC_I_To_F(name) \
Mpfr name(unsigned long int k, mpfr_prec_t prec) { \
        Mpfr result(0,prec); \
        mpfr_##name(result.mp, k, mpfr_get_default_rounding_mode()); \
        return result; \
    }                     \
    Mpfr name(unsigned long int k) {      \
        return name(k, mpfr_get_default_prec());  \
    }

#define FUNC_FF_To_F_rename_h(name, mpfrname) \
    Mpfr name(const Mpfr& x, const Mpfr& y, mpfr_prec_t prec); \
    Mpfr name(const Mpfr& x, const Mpfr& y);

#define FUNC_FF_To_F_rename(name, mpfrname) \
    Mpfr name(const Mpfr& x, const Mpfr& y, mpfr_prec_t prec) { \
        Mpfr result(0,prec); \
        mpfr_##mpfrname(result.mp, x.mp, y.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    } \
    Mpfr name(const Mpfr& x, const Mpfr& y) { \
        return name(x, mpfr_get_prec(x.mp)); \
    }

#define FUNC_FF_To_F_h(name) \
        FUNC_FF_To_F_rename_h(name, name)

#define FUNC_FF_To_F(name) \
        FUNC_FF_To_F_rename_h(name, name)

#define FUNC_FFF_To_F_h(name) \
Mpfr name(const Mpfr& x, const Mpfr& y, const Mpfr& z, mpfr_prec_t prec); \
Mpfr name(const Mpfr& x, const Mpfr& y, const Mpfr& z);

#define FUNC_FFF_To_F(name) \
Mpfr name(const Mpfr& x, const Mpfr& y, const Mpfr& z, mpfr_prec_t prec) { \
        Mpfr result(0,prec); \
        mpfr_##name(result.mp, x.mp, y.mp, z.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    }                       \
    Mpfr name(const Mpfr& x, const Mpfr& y, const Mpfr& z) { \
        mpfr_prec_t precx = mpfr_get_prec(x.mp); \
        mpfr_prec_t precy = mpfr_get_prec(y.mp); \
        mpfr_prec_t precz = mpfr_get_prec(z.mp); \
        return name(x,y,z, std::max(precx, std::max(precy,precz))); \
    }


#define FUNC_F_To_I_h(name) \
const int name(const Mpfr& x);

#define FUNC_F_To_I(name) \
const int name(const Mpfr& x) { \
        return mpfr_##name(x.mp); \
    }

#define FUNC_FF_To_I_h(name) \
const int name(const Mpfr& x, const Mpfr& y);

#define FUNC_FF_To_I(name) \
const int name(const Mpfr& x, const Mpfr& y) { \
        return mpfr_##name(x.mp, y.mp); \
    }

#define FUNC_F_To_FF_h(name) \
const int name(Mpfr& a, Mpfr& b, const Mpfr& x);

#define FUNC_F_To_FF(name) \
const int name(Mpfr& a, Mpfr& b, const Mpfr& x) { \
    return mpfr_##name(a.mp, b.mp, x.mp, mpfr_get_default_rounding_mode()); \
}

#define FUNC_RANDOM_h(name) \
Mpfr name(Randstate &state, mpfr_prec_t prec); \
   Mpfr name(Randstate &state);

#define FUNC_RANDOM(name) \
Mpfr name(Randstate &state, mpfr_prec_t prec) { \
            Mpfr result(0,prec); \
            mpfr_##name(result.mp, state.state, mpfr_get_default_rounding_mode()); \
            return result;\
}\
   Mpfr name(Randstate &state) { \
            return name(state, mpfr_get_default_prec());\
}


    Mpfr trunc(const Mpfr& x);
    void modf(Mpfr& n, Mpfr& f, const Mpfr& x);
    Mpfr remquo(const Mpfr& x, const Mpfr& y, int* q, mp_rnd_t r = get_default_round());
    Mpfr ceil(const Mpfr& x);
    Mpfr floor(const Mpfr& x);
    Mpfr round(const Mpfr& x);
    Mpfr nexttoward(const Mpfr& x, const Mpfr& y);
    Mpfr urandomb(Randstate &state);
    Mpfr logb(const Mpfr& x);
    Mpfr logb(const Mpfr& x, mpfr_prec_t prec);
    mp_exp_t ilogb (const Mpfr& x);
    bool isnan(const Mpfr& x);
    bool isinf(const Mpfr& x);
    bool isfinite(const Mpfr& x);
    bool iszero(const Mpfr& x);
    bool isint(const Mpfr& x);
    bool isregular(const Mpfr& x);

#define CONST_FUNC_h(name) \
    Mpfr name(mpfr_prec_t prec=get_default_prec());

#define CONST_FUNC(name) \
    Mpfr name(mpfr_prec_t prec) { \
        Mpfr result(0,prec); \
        mpfr_##name(result.mp, mpfr_get_default_rounding_mode()); \
        return result;\
    }

    Mpfr const_infinity (int sign = 1, mp_prec_t prec = mpfr_get_default_prec());
    Mpfr pow(const Mpfr&x, int n);
    Mpfr min(const Mpfr& x, const Mpfr& y,  mp_rnd_t r = get_default_round());
    Mpfr max(const Mpfr& x, const Mpfr& y,  mp_rnd_t r = get_default_round());

    FUNC_F_To_F_h(abs);
    FUNC_F_To_F_rename_h(fabs, abs)
    FUNC_F_To_F_h(sqr);
    FUNC_F_To_F_h(sqrt);
    FUNC_F_To_F_h(rec_sqrt);
    FUNC_F_To_F_h(log);
    FUNC_F_To_F_h(log2);
    FUNC_F_To_F_h(log10);
    FUNC_F_To_F_h(log1p);
    FUNC_F_To_F_h(exp);
    FUNC_F_To_F_h(exp2);
    FUNC_F_To_F_h(exp10);
    FUNC_F_To_F_h(expm1);
    FUNC_F_To_F_h(sin);
    FUNC_F_To_F_h(cos);
    FUNC_F_To_F_h(tan);
    FUNC_F_To_F_h(sec);
    FUNC_F_To_F_h(csc);
    FUNC_F_To_F_h(cot);
    FUNC_F_To_F_h(acos);
    FUNC_F_To_F_h(asin);
    FUNC_F_To_F_h(atan);
    FUNC_F_To_F_h(sinh);
    FUNC_F_To_F_h(cosh);
    FUNC_F_To_F_h(tanh);
    FUNC_F_To_F_h(sech);
    FUNC_F_To_F_h(csch);
    FUNC_F_To_F_h(coth);
    FUNC_F_To_F_h(acosh);
    FUNC_F_To_F_h(asinh);
    FUNC_F_To_F_h(atanh);
    FUNC_F_To_F_h(digamma)
    FUNC_F_To_F_h(ai)
    FUNC_F_To_F_h(frac)

    FUNC_FI_To_F_h(rootn_ui);
    FUNC_FU_To_F_h(mul_2ui)
    FUNC_FI_To_F_h(mul_2si)
    FUNC_FU_To_F_h(div_2ui)
    FUNC_FI_To_F_h(div_2si)

    FUNC_FF_To_F_h(dim)
    FUNC_FF_To_F_h(atan2)
    FUNC_FF_To_F_h(hypot)


    FUNC_FF_To_I_h(cmpabs)
    FUNC_F_To_I_h(sgn)

    FUNC_F_To_FF_h(sin_cos)
    FUNC_F_To_FF_h(sinh_cosh)

    FUNC_I_To_F_h(fac_ui)

    FUNC_F_To_F_h(eint);
    FUNC_F_To_F_h(gamma);
    FUNC_F_To_F_h(lngamma);
    FUNC_F_To_F_h(zeta);
    FUNC_F_To_F_h(erf);
    FUNC_F_To_F_h(erfc);
    FUNC_F_To_F_h(li2);
    FUNC_F_To_F_rename_h(besselj0, j0);
    FUNC_F_To_F_rename_h(besselj1, j1);
    FUNC_IF_To_F_rename_h(besseljn, jn);
    FUNC_F_To_F_rename_h(bessely0, y0);
    FUNC_F_To_F_rename_h(bessely1, y1);
    FUNC_IF_To_F_rename_h(besselyn, yn);
    FUNC_FF_To_F_h(agm)
    FUNC_FF_To_F_h(fmod)
    FUNC_FF_To_F_rename_h(rem, fmod)
    FUNC_FFF_To_F_h(fma)
    FUNC_FFF_To_F_h(fms)
    FUNC_F_To_F_h(rint);
    FUNC_F_To_F_h(rint_ceil)
    FUNC_F_To_F_h(rint_floor)
    FUNC_F_To_F_h(rint_round)
    FUNC_F_To_F_h(rint_trunc)
    FUNC_FF_To_F_h(remainder)
    FUNC_RANDOM_h(urandom)
    FUNC_RANDOM_h(nrandom)
    FUNC_RANDOM_h(erandom)

    CONST_FUNC_h(const_pi)
    CONST_FUNC_h(const_log2)
    CONST_FUNC_h(const_euler)
    CONST_FUNC_h(const_catalan)
}

namespace std {
    string to_string(mpfr::Mpfr x);
}

#include "fr_numeric_limits.h"