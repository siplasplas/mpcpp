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
#include <iostream>
#include "mpfr.h"
#include "gmpcpp.h"

namespace mpfr {
    inline mpfr_prec_t get_default_prec() {
        return mpfr_get_default_prec();
    }

    inline void set_default_prec(mpfr_prec_t prec) {
        mpfr_set_default_prec(prec);
    }

    inline mpfr_rnd_t get_default_round() {
        return mpfr_get_default_rounding_mode();
    }

    inline void set_default_round(mpfr_rnd_t r) {
        mpfr_set_default_rounding_mode(r);
    }

    inline mp_exp_t get_emin()
    {
        return mpfr_get_emin();
    }

    inline int set_global_emin(mp_exp_t exp)
    {
        return mpfr_set_emin(exp);
    }

    inline mp_exp_t get_emax()
    {
        return mpfr_get_emax();
    }

    inline int set_global_emax(mp_exp_t exp)
    {
        return mpfr_set_emax(exp);
    }

    inline mp_exp_t get_emin_min()
    {
        return mpfr_get_emin_min();
    }

    inline mp_exp_t get_emin_max()
    {
        return mpfr_get_emin_max();
    }

    inline mp_exp_t get_emax_min()
    {
        return mpfr_get_emax_min();
    }

    inline mp_exp_t get_emax_max()
    {
        return mpfr_get_emax_max();
    }

    class Mpfr {
    public:
        static bool precWithZeros;
        mpfr_t mp;
        Mpfr() {
            mpfr_init2(mp, mpfr_get_default_prec());
            mp->_mpfr_exp = __MPFR_EXP_ZERO;
        }

        Mpfr(const double d) {
            mpfr_init2(mp, mpfr_get_default_prec());
            mpfr_set_d(mp, d, mpfr_get_default_rounding_mode());
        }

        Mpfr(const double d, const mpfr_prec_t prec) {
            mpfr_init2(mp, prec);
            mpfr_set_d(mp, d, mpfr_get_default_rounding_mode());
        }

        Mpfr(const std::string str, mp_rnd_t r=mpfr_get_default_rounding_mode()) {
            mpfr_init2(mp, mpfr_get_default_prec());
            mpfr_set_str(mp, str.c_str(), 10, mpfr_get_default_rounding_mode());
        }

        ~Mpfr() {
            mpfr_clear(mp);
        }

        mpfr_prec_t getprec() const {
            return mpfr_get_prec(mp);
        }

        Mpfr(const Mpfr& rhs) {
            mpfr_init2(mp, mpfr_get_default_prec());
            mpfr_set(mp, rhs.mp, mpfr_get_default_rounding_mode());
        }

        Mpfr(Mpfr&& other)
        {
            mpfr_init2(mp, 1);  // small object, will be deleted
            mpfr_swap(mp, other.mp);
        }

        Mpfr operator<<(const unsigned long int k) {
            Mpfr r(0, getprec());
            mpfr_mul_2ui(r.mp, mp, k, get_default_round());
            return r;
        }

        Mpfr operator<<(const long int k) {
            Mpfr r(0, getprec());
            mpfr_mul_2si(r.mp, mp, k, get_default_round());
            return r;
        }

        Mpfr operator>>(const unsigned long int k) {
            Mpfr r(0, getprec());
            mpfr_div_2ui(r.mp, mp, k, get_default_round());
            return r;
        }

        Mpfr operator>>(const long int k) {
            Mpfr r(0, getprec());
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
            Mpfr rhs(d, getprec());
            return mpfr_greater_p(mp, rhs.mp)!=0;
        }

        bool operator>=(const Mpfr& rhs) const{
            return mpfr_greaterequal_p(mp, rhs.mp)!=0;
        }

        bool operator>=(const double d) const{
            Mpfr rhs(d, getprec());
            return mpfr_greaterequal_p(mp, rhs.mp)!=0;
        }

        bool operator<(const Mpfr& rhs) const{
            return mpfr_less_p(mp, rhs.mp)!=0;
        }

        bool operator<(const double d) const{
            Mpfr rhs(d, getprec());
            return mpfr_less_p(mp, rhs.mp)!=0;
        }

        bool operator<=(const Mpfr& rhs) const{
            return mpfr_lessequal_p(mp, rhs.mp)!=0;
        }

        bool operator<=(const double d) const{
            Mpfr rhs(d, getprec());
            return mpfr_lessequal_p(mp, rhs.mp)!=0;
        }

        bool operator==(const Mpfr& rhs) const{
            return mpfr_equal_p(mp, rhs.mp)!=0;
        }

        bool operator==(const double d) const{
            Mpfr rhs(d, getprec());
            return mpfr_equal_p(mp, rhs.mp)!=0;
        }

        bool operator!=(const Mpfr& rhs) const{
            return mpfr_lessgreater_p(mp, rhs.mp)!=0;
        }

        bool operator!=(const double d) const{
            Mpfr rhs(d, getprec());
            return mpfr_lessgreater_p(mp, rhs.mp)!=0;
        }

        explicit operator double() const {
            return mpfr_get_d(mp, mpfr_get_default_rounding_mode());
        }

        std::string toString(mpfr_prec_t precision) const {
            /*mpfr_exp_t exp;
            int sign = mp->_mpfr_sign<0;
            char *buf = new char[precision + 1 + sign];
            mpfr_get_str(buf, &exp, 10, precision, mp, mpfr_get_default_rounding_mode());
            if (buf[0]==0 || buf[sign]=='0') {
                delete[]buf;
                buf = new char[exp + 22 + sign];
                mpfr_get_str(buf, &exp, 10, exp+20, mp, mpfr_get_default_rounding_mode());
            }
            std::string str = Format::output(buf,precision,exp+1,sign);
            delete []buf;
            return str;*/
            int sign = mp->_mpfr_sign<0;
            char *buf = new char[precision + 1 + sign];
            mp_exp_t exp;
            char *p = mpfr_get_str(buf, &exp, 10, precision, mp, mpfr_get_default_rounding_mode());
            std::string str = gmp::Format::output(buf,gmp::libMpfr, precWithZeros, precision,exp,sign);
            delete[]buf;
            return str;
        }

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

    inline bool Mpfr::precWithZeros = true;

    inline std::ostream &operator<<(std::ostream &os, const Mpfr &mp) {
        os << mp.toString(os.precision());
        return os;
    }

    struct Randstate {
        gmp_randstate_t state;
        Randstate() {
            gmp_randinit_default(state);
        }
        ~Randstate() {
            gmp_randclear(state);
        }
    };

    inline Mpfr operator+(double d, const Mpfr& rhs) {
        Mpfr result;
        mpfr_add_d(result.mp, rhs.mp, d, mpfr_get_default_rounding_mode());
        return result;
    }

    inline Mpfr operator+(int k, const Mpfr& rhs) {
        Mpfr result;
        mpfr_add_d(result.mp, rhs.mp, double(k), mpfr_get_default_rounding_mode());
        return result;
    }

    inline Mpfr operator-(double d, const Mpfr& rhs) {
        Mpfr result(d);
        mpfr_sub(result.mp, result.mp, rhs.mp, mpfr_get_default_rounding_mode());
        return result;
    }

    inline Mpfr operator-(int k, const Mpfr& rhs) {
        Mpfr result((double)k);
        mpfr_sub(result.mp, result.mp, rhs.mp, mpfr_get_default_rounding_mode());
        return result;
    }

    inline Mpfr operator*(double d, const Mpfr& rhs) {
        Mpfr result;
        mpfr_mul_d(result.mp, rhs.mp, d, mpfr_get_default_rounding_mode());
        return result;
    }

    inline Mpfr operator*(int k, const Mpfr& rhs) {
        Mpfr result;
        mpfr_mul_d(result.mp, rhs.mp, (double)k, mpfr_get_default_rounding_mode());
        return result;
    }

    inline Mpfr operator/(double d, const Mpfr& rhs) {
        Mpfr result(d);
        mpfr_div(result.mp, result.mp, rhs.mp, mpfr_get_default_rounding_mode());
        return result;
    }

    inline Mpfr operator/(int k, const Mpfr& rhs) {
        Mpfr result((double)k);
        mpfr_div(result.mp, result.mp, rhs.mp, mpfr_get_default_rounding_mode());
        return result;
    }


#define FUNC_F_To_F(name) \
    inline Mpfr name(const Mpfr& x, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##name(result.mp, x.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_F_To_F_rename(name, mpfrname) \
    inline Mpfr name(const Mpfr& x, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##mpfrname(result.mp, x.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_FI_To_F(name) \
inline Mpfr name(const Mpfr& x, long int k, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##name(result.mp, x.mp, k, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_FU_To_F(name) \
inline Mpfr name(const Mpfr& x, unsigned long int k, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##name(result.mp, x.mp, k, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_IF_To_F_rename(name, mpfrname) \
inline Mpfr name(unsigned long int k, const Mpfr& x, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##mpfrname(result.mp, k, x.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_I_To_F(name) \
inline Mpfr name(unsigned long int k, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##name(result.mp, k, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_FF_To_F(name) \
inline Mpfr name(const Mpfr& x, const Mpfr& y, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##name(result.mp, x.mp, y.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_FF_To_F_rename(name, mpfrname) \
inline Mpfr name(const Mpfr& x, const Mpfr& y, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##mpfrname(result.mp, x.mp, y.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_FFF_To_F(name) \
inline Mpfr name(const Mpfr& x, const Mpfr& y, const Mpfr& z, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        Mpfr result; \
        mpfr_##name(result.mp, x.mp, y.mp, z.mp, mpfr_get_default_rounding_mode()); \
        return result; \
    }

#define FUNC_F_To_I(name) \
inline const int name(const Mpfr& x, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        return mpfr_##name(x.mp); \
    }

#define FUNC_FF_To_I(name) \
inline const int name(const Mpfr& x, const Mpfr& y, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
        return mpfr_##name(x.mp, y.mp); \
    }

#define FUNC_F_To_FF(name) \
inline const int name(Mpfr& a, Mpfr& b, const Mpfr& x, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
    return mpfr_##name(a.mp, b.mp, x.mp, r); \
}

#define FUNC_RANDOM(name) \
inline Mpfr name(Randstate &state, mp_rnd_t r = mpfr_get_default_rounding_mode()) { \
            Mpfr result; \
            mpfr_##name(result.mp, state.state, r); \
            return result;\
}

    FUNC_F_To_F(abs);
    FUNC_F_To_F_rename(fabs, abs)
    FUNC_F_To_F(sqr);
    FUNC_F_To_F(sqrt);
    FUNC_F_To_F(rec_sqrt);
    FUNC_F_To_F(log);
    FUNC_F_To_F(log2);
    FUNC_F_To_F(log10);
    FUNC_F_To_F(log1p);
    FUNC_F_To_F(exp);
    FUNC_F_To_F(exp2);
    FUNC_F_To_F(exp10);
    FUNC_F_To_F(expm1);
    FUNC_F_To_F(sin);
    FUNC_F_To_F(cos);
    FUNC_F_To_F(tan);
    FUNC_F_To_F(sec);
    FUNC_F_To_F(csc);
    FUNC_F_To_F(cot);
    FUNC_F_To_F(acos);
    FUNC_F_To_F(asin);
    FUNC_F_To_F(atan);
    FUNC_F_To_F(sinh);
    FUNC_F_To_F(cosh);
    FUNC_F_To_F(tanh);
    FUNC_F_To_F(sech);
    FUNC_F_To_F(csch);
    FUNC_F_To_F(coth);
    FUNC_F_To_F(acosh);
    FUNC_F_To_F(asinh);
    FUNC_F_To_F(atanh);
    FUNC_F_To_F(digamma)
    FUNC_F_To_F(ai)
    FUNC_F_To_F(frac)

    inline Mpfr trunc(const Mpfr& x)
    {
        Mpfr result(0, x.getprec());
        mpfr_trunc(result.mp,x.mp);
        return x;
    }

    inline void modf(Mpfr& n, Mpfr& f, const Mpfr& x)
    {
        // rounding is not important since we are using the same number
        mpfr_frac (f.mp,f.mp, get_default_round());
        mpfr_trunc(n.mp,x.mp);
    }

    FUNC_FI_To_F(rootn_ui);
    FUNC_FU_To_F(mul_2ui)
    FUNC_FI_To_F(mul_2si)
    FUNC_FU_To_F(div_2ui)
    FUNC_FI_To_F(div_2si)

    FUNC_FF_To_F(dim)
    FUNC_FF_To_F(atan2)
    FUNC_FF_To_F(hypot)


    FUNC_FF_To_I(cmpabs)
    FUNC_F_To_I(sgn)

    FUNC_F_To_FF(sin_cos)
    FUNC_F_To_FF(sinh_cosh)

    FUNC_I_To_F(fac_ui)

    FUNC_F_To_F(eint);
    FUNC_F_To_F(gamma);
    FUNC_F_To_F(lngamma);
    FUNC_F_To_F(zeta);
    FUNC_F_To_F(erf);
    FUNC_F_To_F(erfc);
    FUNC_F_To_F(li2);
    FUNC_F_To_F_rename(besselj0, j0);
    FUNC_F_To_F_rename(besselj1, j1);
    FUNC_IF_To_F_rename(besseljn, jn);
    FUNC_F_To_F_rename(bessely0, y0);
    FUNC_F_To_F_rename(bessely1, y1);
    FUNC_IF_To_F_rename(besselyn, yn);
    FUNC_FF_To_F(agm)
    FUNC_FF_To_F(fmod)
    FUNC_FF_To_F_rename(rem, fmod)
    FUNC_FFF_To_F(fma)
    FUNC_FFF_To_F(fms)
    FUNC_F_To_F(rint);
    FUNC_F_To_F(rint_ceil)
    FUNC_F_To_F(rint_floor)
    FUNC_F_To_F(rint_round)
    FUNC_F_To_F(rint_trunc)
    FUNC_FF_To_F(remainder)
    FUNC_RANDOM(urandom)
    FUNC_RANDOM(nrandom)
    FUNC_RANDOM(erandom)

    inline Mpfr remquo(const Mpfr& x, const Mpfr& y, int* q, mp_rnd_t r = get_default_round())
    {
        long lq;
        Mpfr a(0,(std::max)(y.getprec(), x.getprec()));
        mpfr_remquo(a.mp, &lq, x.mp, y.mp, r);
        if (q) *q = int(lq);
        return a;
    }

    inline Mpfr ceil(const Mpfr& x) {
        Mpfr result;
        mpfr_ceil(result.mp, x.mp);
        return result;
    }

    inline Mpfr floor(const Mpfr& x) {
        Mpfr result;
        mpfr_floor(result.mp, x.mp);
        return result;
    }

    inline Mpfr round(const Mpfr& x) {
        Mpfr result;
        mpfr_round(result.mp, x.mp);
        return result;
    }

    inline Mpfr nexttoward(const Mpfr& x, const Mpfr& y)
    {
        Mpfr a(0, x.getprec());
        mpfr_nexttoward(a.mp,y.mp);
        return a;
    }

    inline Mpfr urandomb(Randstate &state) {
        Mpfr result;
        mpfr_urandomb(result.mp, state.state);
        return result;
    }

    inline Mpfr logb(const Mpfr& x, mp_rnd_t r = mpfr_get_default_rounding_mode()) {
        return log2(abs(x),r);
    }

    inline mp_exp_t ilogb (const Mpfr& x) { return x.get_exp(); }

    inline bool isnan(const Mpfr& x) {
        return mpfr_nan_p(x.mp)!=0;
    }

    inline bool isinf(const Mpfr& x) {
        return mpfr_inf_p(x.mp)!=0;
    }

    inline bool isfinite(const Mpfr& x) {
        return mpfr_number_p(x.mp)!=0;
    }

    inline bool iszero(const Mpfr& x) {
        return mpfr_zero_p(x.mp)!=0;
    }

    inline bool isint(const Mpfr& x) {
        return mpfr_integer_p(x.mp)!=0;
    }

    inline bool isregular(const Mpfr& x) {
        return mpfr_regular_p(x.mp)!=0;
    }

#define CONST_FUNC(name) \
    inline Mpfr name(mpfr_prec_t prec=get_default_prec()) { \
        Mpfr result(0,prec); \
        mpfr_##name(result.mp, mpfr_get_default_rounding_mode()); \
        return result;\
    }

    CONST_FUNC(const_pi)
    CONST_FUNC(const_log2)
    CONST_FUNC(const_euler)
    CONST_FUNC(const_catalan)

    inline Mpfr const_infinity (int sign = 1, mp_prec_t prec = mpfr_get_default_prec())
    {
        Mpfr x(0, prec);
        mpfr_set_inf(x.mp, sign);
        return x;
    }

    inline Mpfr pow(const Mpfr&x, int n) {
        gmp::Mpz z(n);
        Mpfr result;
        mpfr_pow_z(result.mp, x.mp, z.mp, mpfr_get_default_rounding_mode());
        return result;
    }

    inline Mpfr min(const Mpfr& x, const Mpfr& y,  mp_rnd_t r = get_default_round())
    {
        Mpfr res;
        mpfr_min(res.mp,x.mp,y.mp, r);
        return res;
    }

    inline Mpfr max(const Mpfr& x, const Mpfr& y,  mp_rnd_t r = get_default_round())
    {
        Mpfr res;
        mpfr_max(res.mp,x.mp,y.mp, r);
        return res;
    }
}

namespace std {
    inline string to_string(mpfr::Mpfr x) {
        return x.toString(mpfr::get_default_prec());
    }
}

#include "fr_numeric_limits.h"