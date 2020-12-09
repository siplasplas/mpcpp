#include "mpfrcpp.h"

namespace mpfr {
    Mpfr nextabove(const Mpfr& x) {
        Mpfr a(x);
        mpfr_nextabove(a.mp);
        return a;
    }

    Mpfr nextbelow(const Mpfr& x) {
        Mpfr a(x);
        mpfr_nextbelow(a.mp);
        return a;
    }

    Mpfr machine_epsilon(const Mpfr& x) {
        /* the smallest eps such that x + eps != x */
        if( x < 0)
        {
            return nextabove(-x) + x;
        }else{
            return nextabove( x) - x;
        }
    }

    Mpfr machine_epsilon(mp_prec_t prec) {
        /* the smallest eps such that 1 + eps != 1 */
        Mpfr one(prec);
        one = 1;
        return machine_epsilon(one);
    }

    Mpfr machine_epsilon() {
        /* the smallest eps such that 1 + eps != 1 */
        return machine_epsilon(get_default_prec());
    }

// minval is 'safe' meaning 1 / minval does not overflow
    Mpfr minval(mp_prec_t prec) {
        /* min = 1/2 * 2^emin = 2^(emin - 1) */
        Mpfr one(prec);
        one = 1;
        return one << get_emin()-1;
    }

    Mpfr minval() {
        return minval(get_default_prec());
    }

// maxval is 'safe' meaning 1 / maxval does not underflow
    Mpfr maxval(mp_prec_t prec) {
        /* max = (1 - eps) * 2^emax, eps is machine epsilon */
        Mpfr one(prec);
        one = 1;
        return (one - machine_epsilon(prec)) << get_emax();
    }

    Mpfr maxval() {
        return maxval(get_default_prec());
    }

    bool isEqualUlps(const Mpfr& x, const Mpfr& y, int maxUlps) {
        return abs(x - y) <= machine_epsilon(max(abs(x), abs(y))) * maxUlps;
    }

    bool isEqualFuzzy(const Mpfr& x, const Mpfr& y, const Mpfr& eps) {
        return abs(x - y) <= eps;
    }

    bool isEqualFuzzy(const Mpfr& a, const Mpfr& b) {
        return isEqualFuzzy(a, b, machine_epsilon(max(1.0, min(abs(a), abs(b)))));
    }

    Mpfr operator+(double d, const Mpfr& rhs) {
        Mpfr result;
        mpfr_add_d(result.mp, rhs.mp, d, mpfr_get_default_rounding_mode());
        return result;
    }

    Mpfr operator+(int k, const Mpfr& rhs) {
        Mpfr result;
        mpfr_add_d(result.mp, rhs.mp, double(k), mpfr_get_default_rounding_mode());
        return result;
    }

    Mpfr operator-(double d, const Mpfr& rhs) {
        Mpfr result(d);
        mpfr_sub(result.mp, result.mp, rhs.mp, mpfr_get_default_rounding_mode());
        return result;
    }

    Mpfr operator-(int k, const Mpfr& rhs) {
        Mpfr result((double)k);
        mpfr_sub(result.mp, result.mp, rhs.mp, mpfr_get_default_rounding_mode());
        return result;
    }

    Mpfr operator*(double d, const Mpfr& rhs) {
        Mpfr result;
        mpfr_mul_d(result.mp, rhs.mp, d, mpfr_get_default_rounding_mode());
        return result;
    }

    Mpfr operator*(int k, const Mpfr& rhs) {
        Mpfr result;
        mpfr_mul_d(result.mp, rhs.mp, (double)k, mpfr_get_default_rounding_mode());
        return result;
    }

    Mpfr operator/(double d, const Mpfr& rhs) {
        Mpfr result(d);
        mpfr_div(result.mp, result.mp, rhs.mp, mpfr_get_default_rounding_mode());
        return result;
    }

    Mpfr operator/(int k, const Mpfr& rhs) {
        Mpfr result((double)k);
        mpfr_div(result.mp, result.mp, rhs.mp, mpfr_get_default_rounding_mode());
        return result;
    }
}

namespace std {
    mpfr::Mpfr nextafter ( mpfr::Mpfr from, mpfr::Mpfr to ) {
        if (from==to) return to;
        else if (to>from) return mpfr::nextabove(from);
        else return mpfr::nextbelow(from);
    }
}


