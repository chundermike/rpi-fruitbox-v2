/*
http://www.cse.yorku.ca/~oz/marsaglia-rng.html

Then any one of those in-line functions, inserted in a C expression, will provide a random 32-bit integer,
or a random float if UNI or VNI is used. For example, KISS&255; would provide a random byte, while 5.+2.*UNI;
would provide a random real (float) from 5 to 7. Or 1+MWC%10; would provide the proverbial "take a number from
1 to 10", (but with not quite, but virtually, equal probabilities). More generally, something such as 1+KISS%n;
would provide a practical uniform random choice from 1 to n, if n is not too big. 
*/

#include "fast_random.hpp"

namespace fast_random
{
  #define znew (z=36969*(z&65535)+(z>>16))
  #define wnew (w=18000*(w&65535)+(w>>16))
  #define MWC ((znew<<16)+wnew )
  #define SHR3 (jsr^=(jsr<<17), jsr^=(jsr>>13), jsr^=(jsr<<5))
  #define CONG (jcong=69069*jcong+1234567)
  #define FIB ((b=a+b),(a=b-a))
  #define KISS ((MWC^CONG)+SHR3)
  #define LFIB4 (c++,t[c]=t[c]+t[UC(c+58)]+t[UC(c+119)]+t[UC(c+178)])
  #define SWB (c++,bro=(x<y),t[c]=(x=t[UC(c+34)])-(y=t[UC(c+19)]+bro))
  #define UNI (KISS*2.328306e-10)
  #define VNI ((long) KISS)*4.656613e-10
  #define UC (unsigned char) /*a cast operation*/

  /* Global static variables: */
  static uint32_t z=362436069, w=521288629, jsr=123456789, jcong=380116160;
  static uint32_t a=224466889, b=7584631, t[256];
  /* Use random seeds to reset z,w,jsr,jcong,a,b, and the table
  t[256]*/
  static uint32_t x=0,y=0,bro; static unsigned char c=0;
  /* Example procedure to set the table, using KISS: */

  void settable(uint32_t i1,uint32_t i2,uint32_t i3,uint32_t i4,uint32_t i5, uint32_t i6)
  { int i; z=i1;w=i2,jsr=i3; jcong=i4; a=i5; b=i6;
    for(i=0;i<256;i=i+1) t[i]=KISS;
  }
  /* This is a test main program. It should compile and print 7
  0's. */
  // int main(void){
  // int i; uint32_t k;

  // for(i=1;i<1000001;i++){k=LFIB4;} printf("%u\n", k-1064612766U);
  // for(i=1;i<1000001;i++){k=SWB ;} printf("%u\n", k- 627749721U);
  // for(i=1;i<1000001;i++){k=KISS ;} printf("%u\n", k-1372460312U);
  // for(i=1;i<1000001;i++){k=CONG ;} printf("%u\n", k-1529210297U);
  // for(i=1;i<1000001;i++){k=SHR3 ;} printf("%u\n", k-2642725982U);
  // for(i=1;i<1000001;i++){k=MWC ;} printf("%u\n", k- 904977562U);
  // for(i=1;i<1000001;i++){k=FIB ;} printf("%u\n", k-3519793928U);
  // }
  // Speed comparisons : FIB 49;LFIB4 77;SWB 80;CONG 80;SHR3 84;MWC 93;KISS 157; VNI 417;UNI 450;

  void init(uint32_t seed)
  {
    settable(seed, seed + 1, seed + 6031769, seed - 100, 0xffffffff - seed, seed >> 2);
  }
  
  uint32_t rand(void)
  {
    return KISS;
  }

}