#include "../src/mpfrcpp.h"
#include <utestcpp/utest.h>

using namespace mpfr;

TEST_CASE( "Mpfr lambda" ) {
    typedef std::function <Mpfr( Mpfr )> Flambda;
    Flambda fl = [](Mpfr x) {return exp(x);};
    Mpfr x = 33;
    Mpfr tmp = fl(x);
}