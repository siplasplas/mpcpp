#include <vector>
#include <cmath>
#include <cassert>
#include <cstring>
#include "../src/gmpcpp.h"

using namespace std;

#define DIGITS_PER_ITER  14.1816474627254776555

#define A   13591409
#define B   545140134
#define C   640320
#define D   12

char *prog_name;

#if CHECK_MEMUSAGE
#undef CHECK_MEMUSAGE
#define CHECK_MEMUSAGE							\
  do {									\
    char buf[100];							\
    snprintf (buf, 100,							\
	      "ps aguxw | grep '[%c]%s'", prog_name[0], prog_name+1);	\
    system (buf);							\
  } while (0)
#else
#undef CHECK_MEMUSAGE
#define CHECK_MEMUSAGE
#endif


/* Return user CPU time measured in milliseconds.  */

#if !defined (__sun) \
    && (defined (USG) || defined (__SVR4) || defined (_UNICOS) \
	|| defined (__hpux)) || defined (_MSC_VER)
int
cputime ()
{
  return (int) ((double) clock () * 1000 / CLOCKS_PER_SEC);
}
#else
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sstream>

int
cputime ()
{
    struct rusage rus;

    getrusage (0, &rus);
    return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}
#endif

/*///////////////////////////////////////////////////////////////////////////*/

#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))

#define INIT_FACS 32

typedef struct {
    long int fac;
    long int pow;
    long int nxt;
} sieve_t;

sieve_t *sieve;
long int sieve_size;

struct Fac;

struct Fac {
    unsigned long max_facs;
    unsigned long num_facs;
    unsigned long *fac;
    unsigned long *pow;

    void reset()
    {
        num_facs = 0;
    }

    void init()
    {
        init_size(INIT_FACS);
    }

    void resize(long int s)
    {
        if (max_facs < s) {
            clear();
            init_size(s);
        }
    }

    void init_size(long int s)
    {
        if (s<INIT_FACS)
            s=INIT_FACS;

        fac  = (long unsigned*)malloc(s*sizeof(unsigned long));
        pow  = (long unsigned*)malloc(s*sizeof(unsigned long));//f->fac + s;
        max_facs = s;

        reset();
    }

    Fac() {
        init_size(INIT_FACS);
    }

    Fac(const Fac &rhs) {
        deepCopy(rhs);
    }

    /* remove factors of power 0 */
    void compact()
    {
        long int i, j;
        for (i=0, j=0; i<num_facs; i++) {
            if (pow[i]>0) {
                if (j<i) {
                    fac[j] = fac[i];
                    pow[j] = pow[i];
                }
                j++;
            }
        }
        num_facs = j;
    }

    /* f = base^pow */
    void set_bp(unsigned long base, long int power)
    {
        long int i;
        assert(base<sieve_size);
        for (i=0, base/=2; base>0; i++, base = sieve[base].nxt) {
            fac[i] = sieve[base].fac;
            pow[i] = sieve[base].pow*power;
        }
        num_facs = i;
        assert(i<=f->max_facs);
    }

    /* f *= base^pow */
    void mul_bp(unsigned long base, unsigned long power)
    {
        Fac ftmp;
        ftmp.set_bp(base, power);
        *this *= ftmp;
    }

    void deepCopy(const Fac &rhs) {
        max_facs = rhs.max_facs;
        num_facs = rhs.num_facs;
        fac  = (long unsigned*)malloc(max_facs*sizeof(unsigned long));
        pow  = (long unsigned*)malloc(max_facs*sizeof(unsigned long));
        memcpy(fac, rhs.fac, num_facs*sizeof(unsigned long));
        memcpy(pow, rhs.pow, num_facs*sizeof(unsigned long));
    }

    Fac &operator=(const Fac &rhs) {
        deepCopy(rhs);
        return *this;
    }

    /* f *= g */
    void operator*=(const Fac &g)
    {
        long int i, j, k;
        Fac r;
        r.clear();
        r.init_size(num_facs + g.num_facs);
        for (i=j=k=0; i<num_facs && j<g.num_facs; k++) {
            if (fac[i] == g.fac[j]) {
                r.fac[k] = fac[i];
                r.pow[k] = pow[i] + g.pow[j];
                i++; j++;
            } else if (fac[i] < g.fac[j]) {
                r.fac[k] = fac[i];
                r.pow[k] = pow[i];
                i++;
            } else {
                r.fac[k] = g.fac[j];
                r.pow[k] = g.pow[j];
                j++;
            }
        }
        for (; i<num_facs; i++, k++) {
            r.fac[k] = fac[i];
            r.pow[k] = pow[i];
        }
        for (; j<g.num_facs; j++, k++) {
            r.fac[k] = g.fac[j];
            r.pow[k] = g.pow[j];
        }
        r.num_facs = k;
        assert(k<=r->max_facs);
        swap(r);
    }

    void swap(Fac &rhs) {
        ::swap(max_facs,rhs.max_facs);
        ::swap(num_facs,rhs.num_facs);
        ::swap(fac,rhs.fac);
        ::swap(pow,rhs.pow);
    }

    void clear() {
        free(fac);
        fac = nullptr;
        free(pow);
        pow = nullptr;
    }


    ~Fac() {
        clear();
    }
};

/* convert factorized form to number */
void bs_mul(gmp::Mpz &r, long int a, long int b, const Fac &fmul_1)
{
    long int i, j;
    if (b-a<=32) {
        r = 1;
        for (i=a; i<b; i++)
            for (j = 0; j < fmul_1.pow[i]; j++)
                r *= fmul_1.fac[i];
    } else {
        /*gmp::Mpz r2;
        r2 = a * (a+b)/2;
        r =  (a+b)/2 * b;
        r *= r2;*/
        gmp::Mpz r2;
        bs_mul(r2, a, (a + b) / 2, fmul_1);
        bs_mul(r, (a + b) / 2, b, fmul_1);
        r *= r2;
    }
}

//mpz_t    gcd, mgcd;
gmp::Mpz gcd;

#if HAVE_DIVEXACT_PREINV
void mpz_invert_mod_2exp (mpz_ptr, mpz_srcptr);
void mpz_divexact_pre (mpz_ptr, mpz_srcptr, mpz_srcptr, mpz_srcptr);

#endif

/* f /= gcd(f,g), g /= gcd(f,g) */
void fac_remove_gcd(gmp::Mpz &p, Fac *fp, gmp::Mpz &g, Fac *fg)
{
    long int i, j, k, c;
    Fac  fmul_1;
    fmul_1.resize(min(fp->num_facs, fg->num_facs));
    for (i=j=k=0; i<fp->num_facs && j<fg->num_facs; ) {
        if (fp->fac[i] == fg->fac[j]) {
            c = min(fp->pow[i], fg->pow[j]);
            fp->pow[i] -= c;
            fg->pow[j] -= c;
            fmul_1.fac[k] = fp->fac[i];
            fmul_1.pow[k] = c;
            i++; j++; k++;
        } else if (fp->fac[i] < fg->fac[j]) {
            i++;
        } else {
            j++;
        }
    }
    fmul_1.num_facs = k;
    assert(k <= fmul_1.max_facs);

    if (fmul_1.num_facs) {
        bs_mul(gcd, 0, fmul_1.num_facs, fmul_1);
#if HAVE_DIVEXACT_PREINV
        mpz_invert_mod_2exp (mgcd, gcd);
    mpz_divexact_pre (p, p, gcd, mgcd);
    mpz_divexact_pre (g, g, gcd, mgcd);
#else
#define SIZ(x) x->_mp_size
        p.divexactinplace(gcd);
        g.divexactinplace(gcd);
#endif
        fp->compact();
        fg->compact();
    }
}


/*///////////////////////////////////////////////////////////////////////////*/
std::vector<gmp::Mpz> pstack,qstack,gstack;
std::vector<Fac> fpstack,fgstack;

int      out=1;
long int      top = 0;
double   progress=0, percent;

#define p1 (pstack[top])
#define q1 (qstack[top])
#define g1 (gstack[top])
#define fp1 (fpstack[top])
#define fg1 (fgstack[top])

#define p2 (pstack[top+1])
#define q2 (qstack[top+1])
#define g2 (gstack[top+1])
#define fp2 (fpstack[top+1])
#define fg2 (fgstack[top+1])

int depth=1;
long gcd_time = 0;

/* binary splitting */
void bs(unsigned long a, unsigned long b, unsigned gflag, long int level)
{
    unsigned long i, mid;
    int ccc;
    if (b-a==1) {
        /*
          g(b-1,b) = (6b-5)(2b-1)(6b-1)
          p(b-1,b) = b^3 * C^3 / 24
          q(b-1,b) = (-1)^b*g(b-1,b)*(A+Bb).
        */
        p1 = b;
        p1 *= b;
        p1 *= b;
        p1 *= (C/24)*(C/24);
        p1 *= C*24;

        g1 = 2*b-1;
        g1 *= 6*b-1;
        g1 *= 6*b-5;

        q1 = b;
        q1 *= B;
        q1 += A;
        q1 *= g1;
        if (b%2) {
            q1.neg();
        }

        i=b;
        while ((i&1)==0) i>>=1;
        fp1.set_bp(i, 3);	/*  b^3 */
        fp1.mul_bp(3 * 5 * 23 * 29, 3);
        fp1.pow[0]--;

        fg1.set_bp(2 * b - 1, 1);	/* 2b-1 */
        fg1.mul_bp(6 * b - 1, 1);	/* 6b-1 */
        fg1.mul_bp(6 * b - 5, 1);	/* 6b-5 */

        if (b>(int)(progress)) {
            //printf("."); fflush(stdout);
            progress += percent*2;
        }

    } else {
        /*
          p(a,b) = p(a,m) * p(m,b)
          g(a,b) = g(a,m) * g(m,b)
          q(a,b) = q(a,m) * p(m,b) + q(m,b) * g(a,m)
        */
        mid = a+(b-a)*0.5224;     /* tuning parameter */
        bs(a, mid, 1, level + 1);

        top++;
        bs(mid, b, gflag, level + 1);
        top--;

        if (level == 0)
            puts ("");

        ccc = level == 0;

        if (ccc) CHECK_MEMUSAGE;

        if (level>=4) {           /* tuning parameter */
#if 0
            long t = cputime();
#endif
            fac_remove_gcd(p2, &fp2, g1, &fg1);
#if 0
            gcd_time += cputime()-t;
#endif
        }

        if (ccc) CHECK_MEMUSAGE;
        p1 *= p2;

        if (ccc) CHECK_MEMUSAGE;
        q1 *= p2;

        if (ccc) CHECK_MEMUSAGE;
        q2 *= g1;

        if (ccc) CHECK_MEMUSAGE;
        q1 += q2;

        if (ccc) CHECK_MEMUSAGE;
        fp1 *= fp2;

        if (gflag) {
            g1 *= g2;
            fg1 *= fg2;
        }
    }
}

void build_sieve(long int n, sieve_t *s)
{
    long int m, i, j, k;

    sieve_size = n;
    m = (long int)sqrt(n);
    memset(s, 0, sizeof(sieve_t)*n/2);

    s[1/2].fac = 1;
    s[1/2].pow = 1;

    for (i=3; i<=n; i+=2) {
        if (s[i/2].fac == 0) {
            s[i/2].fac = i;
            s[i/2].pow = 1;
            if (i<=m) {
                for (j=i*i, k=i/2; j<=n; j+=i+i, k++) {
                    if (s[j/2].fac==0) {
                        s[j/2].fac = i;
                        if (s[k].fac == i) {
                            s[j/2].pow = s[k].pow + 1;
                            s[j/2].nxt = s[k].nxt;
                        } else {
                            s[j/2].pow = 1;
                            s[j/2].nxt = k;
                        }
                    }
                }
            }
        }
    }
}

gmp::Mpf compute(long int d)
{
    //mpf_t  pi, qi;
    long int i, terms;
    unsigned long psize, qsize;
    long begin, mid0, mid1, mid2, mid3, mid4, end;

    terms = d/DIGITS_PER_ITER;
    while ((1L<<depth)<terms)
        depth++;
    depth++;
    percent = terms/100.0;
    printf("#terms=%ld, depth=%d\n", terms, depth);

    begin = cputime();
    printf("sieve   "); fflush(stdout);

    sieve_size = max(3*5*23*29+1, terms*6);
    sieve = (sieve_t *)malloc(sizeof(sieve_t)*sieve_size/2);
    build_sieve(sieve_size, sieve);

    mid0 = cputime();
    printf("time = %6.3f\n", (double)(mid0-begin)/1000);

    pstack.resize(depth),qstack.resize(depth),gstack.resize(depth);
    fpstack.resize(depth),fgstack.resize(depth);
#if HAVE_DIVEXACT_PREINV
    mpz_init(mgcd);
#endif
    /* begin binary splitting process */
    if (terms<=0) {
        p2 = 1;
        q2 = 0;
        g2 = 1;
    } else
        bs(0, terms, 0, 0);


    mid1 = cputime();
    printf("\nbs      time = %6.3f\n", (double)(mid1-mid0)/1000);
    printf("   gcd  time = %6.3f\n", (double)(gcd_time)/1000);

    /* free some resources */
    free(sieve);

#if HAVE_DIVEXACT_PREINV
    mpz_clear(mgcd);
#endif

    pstack.resize(1);
    qstack.resize(1);
    gstack.clear();
    fpstack.clear();
    fgstack.clear();

    /* prepare to convert integers to floats */
    mpf_set_default_prec(gmp::digits2bits(d)+16);

    /*
        p*(C/D)*sqrt(C)
      pi = -----------------
           (q+A*p)
    */
    q1.addmul(p1,A);
    p1 *= C/D;
    gmp::Mpf pi(p1);
    gmp::Mpf qi(q1);
    pstack.clear();
    qstack.clear();

    mid2 = cputime();
    /* initialize temp float variables for sqrt & div */
    gmp::Mpf t1,t2;
    /* final step */
    qi = pi / qi;
    mid3 = cputime();
    printf("time = %6.3f\n", (double)(mid3-mid2)/1000);

    printf("sqrt    ");  fflush(stdout);
    pi = gmp::sqrt(C);
    mid4 = cputime();
    printf("time = %6.3f\n", (double)(mid4-mid3)/1000);

    qi *= pi;
    end = cputime();
    printf("time = %6.3f\n", (double)(end-mid4)/1000);

    printf("total   time = %6.3f\n", (double)(end-begin)/1000);
    fflush(stdout);

    psize = p1.sizeinbase(10);
    qsize = q1.sizeinbase(10);

    printf("   P size=%ld digits (%f)\n"
           "   Q size=%ld digits (%f)\n",
           psize, (double)psize/d, qsize, (double)qsize/d);

    return qi;
}

string getSub10(long int d) {
    gmp::Mpf pi = compute(d+2);
    string str = pi.toString(d+2);
    string substr = str.substr(d-8,10);
    return substr;
}

void testLast() {
    string lastdig[5] = {
            "3421170679",
            "2164201989",
            "5256375678",
            "5493624646",
            "5779458151"};

    long int d = 100;
    for (int i=0; i<5 ; i++) {
        string str = getSub10(d);
        if (str!=lastdig[i]) throw exception();
        cout << "pass for " << d << endl << flush;
        d *=10;
    }
}

int main(int argc, char *argv[]) {
    testLast();
    return 0;
}