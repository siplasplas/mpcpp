#include "../src/gmpcpp.h"
#include "../src/outformat.h"
#include <iomanip>
#include <string>
#include <utestcpp/utest.h>

using namespace std;
using namespace gmp;

static bool FuzzyCompare(const string &test, const string &check) {
    if (test==check) return true;
    if (test.length()!=check.length()) return false;
    if (test.substr(0,test.length()-1)!=check.substr(0,check.length()-1)) return false;
    return test.back()==check.back()+1;
};

static void testMpfDouble(const Mpf &mpf, double d, int precision) {
    stringstream ssDouble;
    stringstream ssTest;
    ssDouble << setprecision(precision) << d;
    ssTest << setprecision(precision) << mpf;
    string test = ssTest.str();
    string check = ssDouble.str();
    if (Mpf::precWithZeros) check = gmp::Format::addPrecZeros(check,precision);
    int dl = 16; //rounding last digits of double
    if (precision>=16)
        ASSERT_BOOL( test , check, FuzzyCompare(test, check), "only last digits","");
    else
        ASSERT_EQ(test,check);
}

static void testMpfDouble(double d) {
    Mpf mpf(d);
    for (int precision=1; precision<22;  precision++) {
        Mpf::precWithZeros = false;
        testMpfDouble(mpf, d, precision);
        Mpf::precWithZeros = true;
        testMpfDouble(mpf, d, precision);
    }
}

TEST_CASE( "Mpf output" ) {
    double samples[6] = {3.1415, 1.234567890123456, 1.23, 0.45999999, 1, 9.99999999};
//    testMpfDouble(0);
    for (int i=0; i<sizeof(samples)/sizeof(double); i++){
        double d = samples[i];
        for (int decPow=0; decPow<20; decPow++) {
            testMpfDouble(d);
            testMpfDouble(-d);
            d *= 10;
        }
        d = samples[i];
        for (int decPow=0; decPow>-20; decPow--) {
            testMpfDouble(d);
            testMpfDouble(-d);
            d /= 10;
        }
    }
}
