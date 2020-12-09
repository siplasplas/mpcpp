#include "mpfrcpp.h"
#include "outformat.h"
#include <iostream>

namespace mpfr {
    Mpfr::Mpfr(const std::string str, mpfr_prec_t prec) {
        mpfr_init2(mp, prec);
        mpfr_set_str(mp, str.c_str(), 10, mpfr_get_default_rounding_mode());
    }

    std::string Mpfr::toString(mpfr_prec_t precision) const {
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


    mpfr_prec_t get_default_prec() {
        return mpfr_get_default_prec();
    }

    mpfr_prec_t get_default_digits() {
        return gmp::bits2digits(mpfr_get_default_prec());
    }

    void set_default_prec(mpfr_prec_t prec) {
        mpfr_set_default_prec(prec);
    }

    mpfr_rnd_t get_default_round() {
        return mpfr_get_default_rounding_mode();
    }

    void set_default_round(mpfr_rnd_t r) {
        mpfr_set_default_rounding_mode(r);
    }

    mp_exp_t get_emin() {
        return mpfr_get_emin();
    }

    int set_global_emin(mp_exp_t exp) {
        return mpfr_set_emin(exp);
    }

    mp_exp_t get_emax() {
        return mpfr_get_emax();
    }

    int set_global_emax(mp_exp_t exp) {
        return mpfr_set_emax(exp);
    }

    mp_exp_t get_emin_min() {
        return mpfr_get_emin_min();
    }

    mp_exp_t get_emin_max() {
        return mpfr_get_emin_max();
    }

    mp_exp_t get_emax_min() {
        return mpfr_get_emax_min();
    }

    mp_exp_t get_emax_max() {
        return mpfr_get_emax_max();
    }

    bool Mpfr::precWithZeros = true;

    std::ostream &operator<<(std::ostream &os, const Mpfr &mp) {
        os << mp.toString(os.precision());
        return os;
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

    Mpfr trunc(const Mpfr& x) {
        Mpfr result(x.getprec());
        mpfr_trunc(result.mp,x.mp);
        return x;
    }

    void modf(Mpfr& n, Mpfr& f, const Mpfr& x) {
        // rounding is not important since we are using the same number
        mpfr_frac (f.mp,f.mp, get_default_round());
        mpfr_trunc(n.mp,x.mp);
    }

    Mpfr remquo(const Mpfr& x, const Mpfr& y, int* q, mp_rnd_t r) {
        long lq;
        Mpfr a((std::max)(y.getprec(), x.getprec()));
        mpfr_remquo(a.mp, &lq, x.mp, y.mp, r);
        if (q) *q = int(lq);
        return a;
    }

    Mpfr ceil(const Mpfr& x) {
        Mpfr result;
        mpfr_ceil(result.mp, x.mp);
        return result;
    }

    Mpfr floor(const Mpfr& x) {
        Mpfr result;
        mpfr_floor(result.mp, x.mp);
        return result;
    }

    Mpfr round(const Mpfr& x) {
        Mpfr result;
        mpfr_round(result.mp, x.mp);
        return result;
    }

    Mpfr nexttoward(const Mpfr& x, const Mpfr& y)
    {
        Mpfr a(x.getprec());
        mpfr_nexttoward(a.mp,y.mp);
        return a;
    }

    Mpfr urandomb(Randstate &state) {
        Mpfr result;
        mpfr_urandomb(result.mp, state.state);
        return result;
    }

    Mpfr logb(const Mpfr& x) {
        mpfr_prec_t prec = x.getprec();
        return log2(abs(x),prec);
    }

    Mpfr logb(const Mpfr& x, mpfr_prec_t prec) {
        return log2(abs(x),prec);
    }

    mp_exp_t ilogb (const Mpfr& x) { return x.get_exp(); }

    bool isnan(const Mpfr& x) {
        return mpfr_nan_p(x.mp)!=0;
    }

    bool isinf(const Mpfr& x) {
        return mpfr_inf_p(x.mp)!=0;
    }

    bool isfinite(const Mpfr& x) {
        return mpfr_number_p(x.mp)!=0;
    }

    bool iszero(const Mpfr& x) {
        return mpfr_zero_p(x.mp)!=0;
    }

    bool isint(const Mpfr& x) {
        return mpfr_integer_p(x.mp)!=0;
    }

    bool isregular(const Mpfr& x) {
        return mpfr_regular_p(x.mp)!=0;
    }

    Mpfr const_infinity (int sign, mp_prec_t prec)
    {
        Mpfr x(0,prec);
        mpfr_set_inf(x.mp, sign);
        return x;
    }

    Mpfr pow(const Mpfr&x, int n) {
        gmp::Mpz z(n);
        Mpfr result;
        mpfr_pow_z(result.mp, x.mp, z.mp, mpfr_get_default_rounding_mode());
        return result;
    }

    Mpfr min(const Mpfr& x, const Mpfr& y,  mp_rnd_t r)
    {
        Mpfr res;
        mpfr_min(res.mp,x.mp,y.mp, r);
        return res;
    }

    Mpfr max(const Mpfr& x, const Mpfr& y,  mp_rnd_t r)
    {
        Mpfr res;
        mpfr_max(res.mp,x.mp,y.mp, r);
        return res;
    }

    CONST_FUNC(const_pi)
    CONST_FUNC(const_log2)
    CONST_FUNC(const_euler)
    CONST_FUNC(const_catalan)
}

namespace std {
    string to_string(mpfr::Mpfr x) {
        return x.toString(mpfr::get_default_prec());
    }
}
