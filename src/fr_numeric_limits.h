#pragma once
#include <limits>
#include <type_traits>

namespace mpfr {
    Mpfr nextabove(const Mpfr& x);
    Mpfr nextbelow(const Mpfr& x);
    Mpfr machine_epsilon(const Mpfr& x);
    Mpfr machine_epsilon(mp_prec_t prec);
    Mpfr machine_epsilon();
    Mpfr minval(mp_prec_t prec);
    Mpfr minval();
    Mpfr maxval(mp_prec_t prec);
    Mpfr maxval();
    bool isEqualUlps(const Mpfr& x, const Mpfr& y, int maxUlps);
    bool isEqualFuzzy(const Mpfr& x, const Mpfr& y, const Mpfr& eps);
    bool isEqualFuzzy(const Mpfr& a, const Mpfr& b);

    Mpfr operator+(double d, const Mpfr& rhs);
    Mpfr operator+(int k, const Mpfr& rhs);
    Mpfr operator-(double d, const Mpfr& rhs);
    Mpfr operator-(int k, const Mpfr& rhs);
    Mpfr operator*(double d, const Mpfr& rhs);
    Mpfr operator*(int k, const Mpfr& rhs);
    Mpfr operator/(double d, const Mpfr& rhs);
    Mpfr operator/(int k, const Mpfr& rhs);
}

namespace std {
    template<>
    struct __is_floating_point_helper<mpfr::Mpfr>
            : public true_type { };

    mpfr::Mpfr nextafter ( mpfr::Mpfr from, mpfr::Mpfr to );

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
        static const int digits = 53;
        static const int digits10 = 15;

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
