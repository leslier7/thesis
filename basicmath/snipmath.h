/* +++Date last modified: 05-Jul-1997 */

/*
**  SNIPMATH.H - Header file for SNIPPETS math functions and macros
*/

#ifndef SNIPMATH__H
#define SNIPMATH__H

#include <math.h>
#include "sniptype.h"
#include "round.h"

/*
**  Callable library functions begin here
*/

void    SetBCDLen(int n);                             /* Bcdl.C         */
long    BCDtoLong(char *BCDNum);                      /* Bcdl.C         */
void    LongtoBCD(long num, char BCDNum[]);           /* Bcdl.C         */
float  bcd_to_float(void *buf, size_t len,          /* Bcdd.C         */
                      int digits);
int     float_to_bcd(float arg, char *buf,          /* Bcdd.C         */
                      size_t length, size_t digits );
DWORD   ncomb1 (int n, int m);                        /* Combin.C       */
DWORD   ncomb2 (int n, int m);                        /* Combin.C       */
void    SolveCubic(float a, float b, float c,      /* Cubic.C        */
                  float d, int *solutions,
                  float *x);
DWORD   dbl2ulong(float t);                          /* Dbl2Long.C     */
long    dbl2long(float t);                           /* Dbl2Long.C     */
float  dround(float x);                             /* Dblround.C     */

/* Use #defines for Permutations and Combinations     -- Factoryl.C     */

#define log10P(n,r) (log10factorial(n)-log10factorial((n)-(r)))
#define log10C(n,r) (log10P((n),(r))-log10factorial(r))

float  log10factorial(float N);                     /* Factoryl.C     */

float  fibo(unsigned short term);                    /* Fibo.C         */
float  frandom(int n);                               /* Frand.C        */
float  ipow(float x, int n);                        /* Ipow.C         */
int     ispow2(int x);                                /* Ispow2.C       */
    float ldfloor(float a);                /* Ldfloor.C      */
int     initlogscale(long dmax, long rmax);           /* Logscale.C     */
long    logscale(long d);                             /* Logscale.C     */

float   MSBINToIEEE(float f);                         /* Msb2Ieee.C     */
float   IEEEToMSBIN(float f);                         /* Msb2Ieee.C     */
int     perm_index (char pit[], int size);            /* Perm_Idx.C     */
int     round_div(int n, int d);                      /* Rnd_Div.C      */
long    round_ldiv(long n, long d);                   /* Rnd_Div.C      */
float  rad2deg(float rad);                          /* Rad2Deg.C      */
float  deg2rad(float deg);                          /* Rad2Deg.C      */

#include "pi.h"
#ifndef PHI
 #define PHI      ((1.0+sqrt(5.0))/2.0)         /* the golden number    */
 #define INV_PHI  (1.0/PHI)                     /* the golden ratio     */
#endif

/*
**  File: ISQRT.C
*/

struct int_sqrt {
      unsigned sqrt,
               frac;
};

void usqrt(unsigned long x, struct int_sqrt *q);


#endif /* SNIPMATH__H */
