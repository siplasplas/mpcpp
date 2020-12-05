#include "../src/mpfrcpp.h"
#include <utestcpp/utest.h>

using namespace mpfr;


TEST_CASE( "Mpfr functions" ) {
    Mpfr epsilon = mpfr::machine_epsilon(53);
    Mpfr maxVal = mpfr::maxval(53);
    Mpfr x,y;
    y = 2.3;
    y = sqr(x);
    y = sqrt(x);
    y = rootn_ui(x, 3);
    y = pow(x, 3);
    y = fabs(x);
    y = abs(x);
    y = dim(x, 3);
    y = mul_2ui(x, 3);
    y = mul_2si(x, -3);
    y = div_2ui(x, 3);
    y = div_2si(x, -3);
    int k = cmpabs(x,y);
    y = log(x);
    y = log2(x);
    y = logb(x);
    mp_exp_t e = ilogb(x);
    y = log10(x);
    y = exp(x);
    y = exp2(x);
    y = exp10(x);
    y = log1p(x);
    y = expm1(x);
    y = cos(x);
    y = sin(x);
    y = tan(x);
    y = sec(x);
    y = csc(x);
    y = cot(x);

    Mpfr a, b;
    k = sin_cos(a, b, x);
    y = acos(x);
    y = asin(x);
    y = atan(x);
    y = atan2(x, 2.1*x);

    y = cosh(x);
    y = sinh(x);
    y = tanh(x);
    y = sech(x);
    y = csch(x);
    y = coth(x);
    y = acosh(x);
    y = asinh(x);
    y = atanh(x);
    y = hypot(2,3);
    y = hypot(Mpfr(2),Mpfr(3));
    y = fac_ui(10);
    y = eint(x);

    y = gamma(x);
    y = lngamma(x);
    y = zeta(x);
    y = erf(x);
    y = erfc(x);
    y = besselj0(x);
    y = besselj1(x);
    y = besseljn(3, x);
    y = bessely0(x);
    y = bessely1(x);
    y = besselyn(3, x);
    y = fma(Mpfr(2),Mpfr(3),Mpfr(4));
    y = fms(Mpfr(2),Mpfr(3),Mpfr(4));
    y = agm(Mpfr(2),Mpfr(3));
    int s = sgn(x);

    k = sinh_cosh(y, x, 2*x);
    y = li2(x);
    y = fmod(x,2.1 *x);
    y = rec_sqrt(x);

    y = rem(x, y/3);

    y = digamma(x);
    y = ai(x);

    Randstate state;
    y = urandom (state);
    y = nrandom(state);
    y = erandom(state);
    y = urandomb(state);
    modf(x, y, x/3);

    y = const_log2(20);
    y = const_pi(20);
    y = const_euler(20);
    y = const_catalan(20);

    y = const_infinity(1);

    y = rint (x);
    y = ceil(x);
    y = floor(x);
    y = round(x);
    y = trunc(x);

    y = rint_ceil(x);
    y = rint_floor(x);
    y = rint_round(x);
    y = rint_trunc(x);
    y = frac(x);
    y = remainder(x,x/2);
    y = remquo(x, y/2, &k);

    y = nexttoward(x,x/2);
    y = nextabove(x);
    y = nextbelow(x);

    y = urandomb (state);

    b = isnan(x);
    b = isinf(x);
    b = isfinite(x);
    b = iszero(x);
    b = isint(x);
    b = isregular(x);

    mp_prec_t prec = x.getprec();

    y.setInf(1);
    y.setNan();
    y.setZero(1);
    y.setSign(1);

    e = y.get_exp();
    y.set_exp(e);
    y.check_range(10);
    y.subnormalize(10);

    set_default_prec(100);
    e = get_emin();
    e = get_emax();
    e = get_emin_min();
    e = get_emin_max();
    e = get_emax_min();
    e = get_emax_max();
    //e = set_global_emin(100);
    //e = set_global_emax(200);

    x.swap(y);
    Mpfr mn = min(x,y);
    Mpfr mx = max(x,y);
}
