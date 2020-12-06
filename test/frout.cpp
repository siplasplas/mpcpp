#include "../src/mpfrcpp.h"
#include <iomanip>
#include <string>
#include <utestcpp/utest.h>

using namespace std;
using namespace mpfr;

bool FuzzyCompare(const string &test, const string &check) {
    if (test==check) return true;
    if (test.length()!=check.length()) return false;
    if (test.substr(0,test.length()-1)!=check.substr(0,check.length()-1)) return false;
    return test.back()==check.back()+1;
};

void testMpfrDouble(const Mpfr &mpfr, double d, int precision) {
    stringstream ssDouble;
    stringstream ssTest;
    ssDouble << setprecision(precision) << d;
    ssTest << setprecision(precision) << mpfr;
    string test = ssTest.str();
    string check = ssDouble.str();
    if (Mpfr::precWithZeros) check = gmp::Format::addPrecZeros(check,precision);
    int dl = 16; //rounding last digits of double
    if (precision>=16)
        ASSERT_BOOL( test , check, FuzzyCompare(test, check), "only last digits");
    else
        ASSERT_EQ(test,check);
}

void testMpfrDouble(double d) {
    Mpfr mpfr(d);
    for (int precision=1; precision<22;  precision++) {
        Mpfr::precWithZeros = false;
        testMpfrDouble(mpfr, d, precision);
        Mpfr::precWithZeros = true;
        testMpfrDouble(mpfr, d, precision);
    }
}

struct ZeroCase {
    string first;
    int prec;
    string second;
};

TEST_CASE( "Mpfr output" ) {
    double samples[6] = {3.1415, 1.234567890123456, 1.23, 0.45999999, 1, 9.99999999};
    for (int i=0; i<sizeof(samples)/sizeof(double); i++) {
        double d = samples[i];
        for (int decPow=0; decPow<20; decPow++) {
            testMpfrDouble(d);
            testMpfrDouble(-d);
            d *= 10;
        }
        d = samples[i];
        for (int decPow=0; decPow>-20; decPow--) {
            testMpfrDouble(d);
            testMpfrDouble(-d);
            d /= 10;
        }
    }
}

TEST_CASE( "Mpfr zero fill" ) {
    ZeroCase cases[10] = {
            {"0.012", 4, "0.01200"},
            {"-3.12e-05",5,"-3.1200e-05"},
            {"3",5,"3.0000"},
            {"30",5,"30.000"},
            {"123.45",3,"123.45"},
            {"123.45",5,"123.45"},
            {"123.45",6,"123.450"},
            {"0.012",4,"0.01200"},
            {"3.12e+05",5,"3.1200e+05"},
            {"-3e-05",3,"-3.00e-05"}};
    for (int i=0; i<9; i++) {
        string first = cases[i].first;
        string second = cases[i].second;
        string test = gmp::Format::addPrecZeros(first, cases[i].prec);
        ASSERT_EQ(test, second);
        string testRev = gmp::Format::removePrecZeros(second);
        ASSERT_EQ(testRev, first);
    }
}

DEFAULT_MAIN