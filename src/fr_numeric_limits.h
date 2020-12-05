#pragma once

namespace mpfr {
    inline Mpfr nextabove(const Mpfr& x)
    {
        Mpfr a(x);
        mpfr_nextabove(a.mp);
        return a;
    }

    inline Mpfr nextbelow(const Mpfr& x)
    {
        Mpfr a(x);
        mpfr_nextbelow(a.mp);
        return a;
    }

    inline Mpfr machine_epsilon(const Mpfr& x)
    {
        /* the smallest eps such that x + eps != x */
        if( x < 0)
        {
            return nextabove(-x) + x;
        }else{
            return nextabove( x) - x;
        }
    }

    inline Mpfr machine_epsilon(mp_prec_t prec)
    {
        /* the smallest eps such that 1 + eps != 1 */
        return machine_epsilon(Mpfr(1, prec));
    }

    inline Mpfr machine_epsilon()
    {
        /* the smallest eps such that 1 + eps != 1 */
        return machine_epsilon(get_default_prec());
    }

// minval is 'safe' meaning 1 / minval does not overflow
    inline Mpfr minval(mp_prec_t prec) {
        /* min = 1/2 * 2^emin = 2^(emin - 1) */
        return Mpfr(1, prec) << Mpfr::get_emin()-1;
    }

    inline Mpfr minval() {
       return minval(get_default_prec());
    }

// maxval is 'safe' meaning 1 / maxval does not underflow
    inline Mpfr maxval(mp_prec_t prec) {
        /* max = (1 - eps) * 2^emax, eps is machine epsilon */
        return (Mpfr(1, prec) - machine_epsilon(prec)) << Mpfr::get_emax();
    }

    inline Mpfr maxval() {
        return maxval(get_default_prec());
    }

    inline bool isEqualUlps(const Mpfr& x, const Mpfr& y, int maxUlps)
    {
        return abs(x - y) <= machine_epsilon(max(abs(x), abs(y))) * maxUlps;
    }

    inline bool isEqualFuzzy(const Mpfr& x, const Mpfr& y, const Mpfr& eps)
    {
        return abs(x - y) <= eps;
    }

    inline bool isEqualFuzzy(const Mpfr& a, const Mpfr& b)
    {
        return isEqualFuzzy(a, b, machine_epsilon(max(1, min(abs(a), abs(b)))));
    }
}

namespace std {
    template<>
    struct numeric_limits<mpfr::Mpfr> {
        static const bool is_specialized = true;

        static const mpfr::Mpfr min() {
            return mpfr::minval();
        }

        static const mpfr::Mpfr max() {
            return mpfr::maxval();
        }

#if __cplusplus >= 201103L
        static const mpfr::Mpfr lowest() {
            return -mpfr::maxval();
        }
#endif
        static const bool is_signed = true;
        static const bool is_integer = false;
        static const bool is_exact = false;
        static const int radix = 2;

        static const mpfr::Mpfr epsilon() { return mpfr::machine_epsilon(); }
        static const mpfr::Mpfr round_error()  { return 0.5; }

        static const bool has_infinity = true;
        static const bool has_quiet_NaN = true;
        static const bool has_signaling_NaN = has_quiet_NaN;
        static const float_denorm_style has_denorm = denorm_absent;

        static const mpfr::Mpfr infinity() { return mpfr::const_infinity(); }

        static const mpfr::Mpfr quiet_NaN()  { return mpfr::Mpfr().setNan(); }

        static const mpfr::Mpfr signaling_NaN()  { return mpfr::Mpfr().setNan(); }

        static const mpfr::Mpfr denorm_min()  { return min(); }

        static const bool is_iec559 = true;        // = IEEE 754
        static const bool is_bounded = true;
        static const bool is_modulo = false;
        static const bool traps = true;
        static const bool tinyness_before = true;
        static const float_round_style round_style() {
            mp_rnd_t r = mpfr::get_default_round();
            switch (r)
            {
                case GMP_RNDN: return round_to_nearest;
                case GMP_RNDZ: return round_toward_zero;
                case GMP_RNDU: return round_toward_infinity;
                case GMP_RNDD: return round_toward_neg_infinity;
                default: return round_indeterminate;
            }
        }
    };
}
