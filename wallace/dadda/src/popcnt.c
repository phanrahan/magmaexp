#line 15 "popcnt.web"

#line 22 "popcnt.web"
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define WORDSSIZE 32

#if WORDSSIZE==64
typedef uint64_t word;
#define POPC popc_mul
#elif  WORDSSIZE==32
typedef uint32_t word;
#define POPC popcTL
#endif

const word mu0 = (word)UINT64_C(0x5555555555555555);
const word nmu0= (word)UINT64_C(0xAAAAAAAAAAAAAAAA);
const word mu1 = (word)UINT64_C(0x3333333333333333);
const word mu2 = (word)UINT64_C(0x0F0F0F0F0F0F0F0F);
const word mu3 = (word)UINT64_C(0x00FF00FF00FF00FF);
const word mu4 = (word)UINT64_C(0x0000FFFF0000FFFF);

const uint_fast32_t iter = 10000ul;
#define N 255*200
word A[N];


#define POPC255 popc_255v

double runtime;


#line 15 "popcnt.web"


#line 968 "popcnt.web"
extern inline void CSA(word *h,word *l,word a, word b, word c) {
  word u = a^b; 
  *h = (a & b) | (u & c);
  *l = u ^ c;
}
          

#line 16 "popcnt.web"


#line 56 "popcnt.web"

#line 79 "popcnt.web"
uint_fast8_t popcTL(word a) {
  static const uint8_t table[256] =
    {
      0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
    };
    
  uint8_t *p = (uint8_t*)&a;
  uint_fast8_t res = table[p[0]];
  for(uint_fast8_t i=1; i<sizeof(word);i++) {
    res+=table[p[i]];
  }
  return res;
}


#line 56 "popcnt.web"


#line 113 "popcnt.web"

#line 121 "popcnt.web"
uint_fast8_t popc_unoptimized(uint32_t x) {
  x = (x & mu0) + ((x>> 1) & mu0);
  x = (x & mu1) + ((x>> 2) & mu1);
  x = (x & mu2) + ((x>> 4) & mu2);
  x = (x & mu3) + ((x>> 8) & mu3);
  x = (x & mu4) + ((x>>16) & mu4);
  return x;
}


#line 113 "popcnt.web"


#line 138 "popcnt.web"
uint_fast8_t popc(uint64_t a) {
  uint64_t x = a - ((a>>1)&mu0);
  x = (x & mu1) + ((x>>2)&mu1);
  x = (x + (x>>4)) & mu2;
  x = x + (x>>8);
  x = x + (x>>16);
  x = x + (x>>32);
  return x & 0x000000FF;
}


#line 114 "popcnt.web"


#line 153 "popcnt.web"
uint_fast8_t popc_mul(uint64_t x) {
  x = x - ((x>>1)&mu0);
  x = (x & mu1) + ((x>>2)&mu1);
  x = (x + (x>>4)) & mu2;
  const uint64_t M = UINT64_C(0x0101010101010101);
  return ((M*x) >> 56);
}


#line 115 "popcnt.web"


#line 57 "popcnt.web"
 

#line 232 "popcnt.web"
uint_fast8_t popc_sparse(word x) {
  uint_fast8_t counter =0;
  while(x != 0) {
    counter++;
    x = x & (x-1);         // delete the right most bit
  }
  return counter;
}

#line 58 "popcnt.web"


#line 164 "popcnt.web"

#line 172 "popcnt.web"
uint_fast8_t popc_HAKMEM(uint32_t x) {
  uint32_t n = (x>>1) & 033333333333; 
  x = x - n;
  n = (n>>1) & 033333333333;
  x = x - n;
  x = (x + (x>>3)) & 030707070707;
  return x%63;
}

#line 164 "popcnt.web"


#line 183 "popcnt.web"
uint_fast8_t popc_HAKMEM2(uint32_t x) {
   uint32_t n = (x >> 1) & 0x77777777;       
   x = x - n;                        
   n = (n>>1) & 0x77777777;        
   x = x - n;
   n = (n>>1) & 0x77777777;
   x = x - n;
   x = (x + (x>>4)) & 0x0F0F0F0F;  
   return ((x*0x01010101) >> 24);
}

#line 165 "popcnt.web"


#line 196 "popcnt.web"
uint_fast8_t popc_HAKMEM7bit(uint32_t x) {
   x = x * 0x02040810;
   x = x & 0x11111111;
   x = x * 0x11111111;
   return (x >> 28);
}


#line 166 "popcnt.web"


#line 206 "popcnt.web"
uint_fast8_t popc_HAKMEM8bit(uint32_t x) {
   x = x * 0x08040201;
   x = x >> 3;
   x = x & 0x11111111;
   x = x * 0x11111111;
   return (x >> 28);
}


#line 167 "popcnt.web"


#line 217 "popcnt.web"
uint_fast8_t popc_HAKMEM15bit(uint64_t x) {
   x = x * UINT64_C(0x0002000400080010);
   x = x & UINT64_C(0x1111111111111111);
   x = x * UINT64_C(0x1111111111111111);
   return (x >> 60);
}



#line 168 "popcnt.web"


#line 59 "popcnt.web"


#line 246 "popcnt.web"

#line 258 "popcnt.web"
uint_fast8_t popc_sum_sub(word x) {
  word sum=x;
  while(x != 0) {
    x = (x>>1);
    sum = sum - x;
  }
  return sum;
}


#line 246 "popcnt.web"


#line 270 "popcnt.web"
extern inline word rotate(word x) {
   return ((x << 1) | (x >> (8*sizeof(word)-1)));
} 

uint_fast8_t popc_rotate(word x) {
  word sum=x;
  for(uint_fast8_t i=1; i<8*sizeof(word); ++i) {
    x = rotate(x);
    sum += x;
  }
  return -sum;
}

#line 247 "popcnt.web"



#line 60 "popcnt.web"


#line 347 "popcnt.web"
uint_fast16_t popc_255(word a[const restrict static 255]) {
  static word b[170];
  for(uint_fast8_t i=0; i<85; ++i) {
    b[2*i] = (a[3*i]&mu0) + (a[3*i+1]&mu0) + (a[3*i+2]&mu0);
    b[2*i+1] = ((a[3*i]>>1)&mu0) + ((a[3*i+1]>>1)&mu0) + ((a[3*i+2]>>1)&mu0);
  }

  static word c[68];
  for(uint_fast8_t i=0; i<17; ++i) {
    for(uint_fast8_t x=0; x<2; ++x) {
      c[4*i+x] = b[10*i+x]&mu1;
      c[4*i+2+x] = (b[10*i+x]>>2)&mu1;
      for(uint_fast8_t j = 2;j<10;j+=2) {
        c[4*i+x] += b[10*i+j+x]&mu1;
        c[4*i+2+x] += (b[10*i+j+x]>>2)&mu1;
      }
    }    
  } 

  static word d[8];
  for(uint_fast8_t x=0; x<4; ++x) {
    d[x] = c[x]&mu2;    
    d[4+x] = (c[x]>>4) & mu2;
    for(uint_fast8_t j = 4;j<68;j+=4) {
      d[x] += c[x+j]&mu2;    
      d[4+x] += (c[x+j]>>4) & mu2;
    }
  }

  uint8_t *p = (uint8_t*)d;
  uint_fast16_t res =p[0];
  for(uint_fast8_t x=1; x<8*sizeof(word); ++x) {
    res += p[x];
  }

  return res;
} 


#line 61 "popcnt.web"
 

#line 408 "popcnt.web"
uint_fast16_t popc_255v(word a[const restrict static 255]) {
  static word b[170];
  for(uint_fast8_t i=0; i<85; ++i) {
    b[2*i] = (a[3*i] - ((a[3*i]>>1)&mu0))  + (a[3*i+2]&mu0);
    b[2*i+1] = (a[3*i+1] - ((a[3*i+1]>>1)&mu0)) + ((a[3*i+2]>>1)&mu0);
  }

  static word c[68];
  for(uint_fast8_t i=0; i<34; ++i) {
    c[2*i]   = b[5*i]&mu1;
    c[2*i+1] = (b[5*i]>>2)&mu1;
    for(uint_fast8_t j = 1;j<5;++j) {
      c[2*i] += b[5*i+j]&mu1;
      c[2*i+1] += (b[5*i+j]>>2)&mu1;
    }    
  } 

  static word d[8];
  for(uint_fast8_t x=0; x<4; ++x) {
    d[x] = c[x]&mu2;    
    d[x+4] = (c[x]>>4) & mu2;
    for(uint_fast8_t j = 4;j<68;j+=4) {
      d[x] += c[x+j]&mu2;    
      d[x+4] += (c[x+j]>>4) & mu2;
    }
  }

  uint8_t *p = (uint8_t*)d;
  uint_fast16_t res =p[0];
  for(uint_fast8_t x=1; x<8*sizeof(word); ++x) {
    res += p[x];
  }

  return res;
} 

uint_fast16_t popc_255v_oByte(word a[const restrict static 255]) {
  static word b[170];
  for(uint_fast8_t i=0; i<85; ++i) {
    b[2*i] = (a[3*i] - ((a[3*i]>>1)&mu0))  + (a[3*i+2]&mu0);
    b[2*i+1] = (a[3*i+1] - ((a[3*i+1]>>1)&mu0)) + ((a[3*i+2]>>1)&mu0);
  }

  static word c[68];
  for(uint_fast8_t i=0; i<34; ++i) {
    c[2*i]   = b[5*i]&mu1;
    c[2*i+1] = (b[5*i]>>2)&mu1;
    for(uint_fast8_t j = 1;j<5;++j) {
      c[2*i] += b[5*i+j]&mu1;
      c[2*i+1] += (b[5*i+j]>>2)&mu1;
    }    
  } 

  static word d[8];
  for(uint_fast8_t x=0; x<4; ++x) {
    d[x] = c[x]&mu2;    
    d[x+4] = (c[x]>>4) & mu2;
    for(uint_fast8_t j = 4;j<68;j+=4) {
      d[x] += c[x+j]&mu2;    
      d[x+4] += (c[x+j]>>4) & mu2;
    }
  }

uint_fast16_t res=0;
static word y;
for(uint_fast8_t x=0; x<8; ++x) {
 	y = (d[x]&mu3) + ((d[x]>>8)&mu3);
    y = y + (y>>16);
 #if WORDSSIZE==64
    y = y + (y>>32);
 #endif
    res+= y & 0x0000FFFF;
  }

  return res;
} 


#line 62 "popcnt.web"


#line 503 "popcnt.web"

extern inline uint_fast16_t popc_510(word a[const restrict static 510]) {
  static word b[170];
  word one=0;
  for(uint_fast8_t i=0; i<85; ++i) {
    word X,Y,Z;
    CSA(&X,&one,one,a[6*i  ],a[6*i+1]);
    CSA(&Y,&one,one,a[6*i+2],a[6*i+3]);
    CSA(&Z,&one,one,a[6*i+4],a[6*i+5]);
    b[2*i  ] = (X - ((X>>1)&mu0)) + (Z&mu0);
    b[2*i+1] = (Y - ((Y>>1)&mu0)) + ((Z>>1)&mu0);
  }

  static word c[68];
  for(uint_fast8_t i=0; i<17; ++i) {
    for(uint_fast8_t x=0; x<2; ++x) {
      c[4*i+x] = b[10*i+x]&mu1;
      c[4*i+2+x] = (b[10*i+x]>>2)&mu1;
      for(uint_fast8_t j = 2;j<10;j+=2) {
        c[4*i+x] += b[10*i+j+x]&mu1;
        c[4*i+2+x] += (b[10*i+j+x]>>2)&mu1;
      }
    }    
  } 

  static word d[8];
  for(uint_fast8_t x=0; x<4; ++x) {
    d[x] = c[x]&mu2;    
    d[4+x] = (c[x]>>4) & mu2;
    for(uint_fast8_t j = 4;j<68;j+=4) {
      d[x] += c[x+j]&mu2;    
      d[4+x] += (c[x+j]>>4) & mu2;
    }
  }

  uint8_t *p = (uint8_t*)d;
  uint_fast16_t res =p[0];
  for(uint_fast8_t x=1; x<8*sizeof(word); ++x) {
    res += p[x];
  }

  return 2*res+POPC(one);
} 

extern inline uint_fast16_t popc_1020(word a[const restrict static 1020]) {
  static word b[170];
  word one=0,two=0,twoA,twoB;
  for(uint_fast8_t i=0; i<85; ++i) {
    word X,Y,Z;
    CSA(&twoA,&one,one,a[12*i  ],a[12*i+1]);    
    CSA(&twoB,&one,one,a[12*i+2],a[12*i+3]);    
    CSA(&X,&two,two,twoA,twoB);    
    CSA(&twoA,&one,one,a[12*i+4],a[12*i+5]);    
    CSA(&twoB,&one,one,a[12*i+6],a[12*i+7]);    
    CSA(&Y,&two,two,twoA,twoB);    
    CSA(&twoA,&one,one,a[12*i+8],a[12*i+9]);    
    CSA(&twoB,&one,one,a[12*i+10],a[12*i+11]);    
    CSA(&Z,&two,two,twoA,twoB);    

    b[2*i  ] = (X - ((X>>1)&mu0)) + (Z&mu0);
    b[2*i+1] = (Y - ((Y>>1)&mu0)) + ((Z>>1)&mu0);
  }

  static word c[68];
  for(uint_fast8_t i=0; i<17; ++i) {
    for(uint_fast8_t x=0; x<2; ++x) {
      c[4*i+x] = b[10*i+x]&mu1;
      c[4*i+2+x] = (b[10*i+x]>>2)&mu1;
      for(uint_fast8_t j = 2;j<10;j+=2) {
        c[4*i+x] += b[10*i+j+x]&mu1;
        c[4*i+2+x] += (b[10*i+j+x]>>2)&mu1;
      }
    }    
  } 

  static word d[8];
  for(uint_fast8_t x=0; x<4; ++x) {
    d[x] = c[x]&mu2;    
    d[4+x] = (c[x]>>4) & mu2;
    for(uint_fast8_t j = 4;j<68;j+=4) {
      d[x] += c[x+j]&mu2;    
      d[4+x] += (c[x+j]>>4) & mu2;
    }
  }

  uint8_t *p = (uint8_t*)d;
  uint_fast16_t res =p[0];
  for(uint_fast8_t x=1; x<8*sizeof(word); ++x) {
    res += p[x];
  }

  return 4*res+2*POPC(two)+POPC(one);
} 

extern inline uint_fast16_t popc_2040(word a[const restrict static 2040]) {
  static word b[170];
  word one=0,two=0,forth=0,twoA,twoB,forthA,forthB;
  for(uint_fast8_t i=0; i<85; ++i) {
    word X,Y,Z;
    CSA(&twoA  ,&one,one,a[24*i  ],a[24*i+1]);    
    CSA(&twoB  ,&one,one,a[24*i+2],a[24*i+3]);    
    CSA(&forthA,&two,two,twoA,twoB);    
    CSA(&twoA  ,&one,one,a[24*i+4],a[24*i+5]);    
    CSA(&twoB  ,&one,one,a[24*i+6],a[24*i+7]);    
    CSA(&forthB,&two,two,twoA,twoB);    
    CSA(&X,&forth,forth,forthA,forthB);
    CSA(&twoA  ,&one,one,a[24*i+8],a[24*i+9]);    
    CSA(&twoB  ,&one,one,a[24*i+10],a[24*i+11]);    
    CSA(&forthA,&two,two,twoA,twoB);    
    CSA(&twoA  ,&one,one,a[24*i+12],a[24*i+13]);    
    CSA(&twoB  ,&one,one,a[24*i+14],a[24*i+15]);    
    CSA(&forthB,&two,two,twoA,twoB);    
    CSA(&Y,&forth,forth,forthA,forthB);
    CSA(&twoA  ,&one,one,a[24*i+16],a[24*i+17]);    
    CSA(&twoB  ,&one,one,a[24*i+18],a[24*i+19]);    
    CSA(&forthA,&two,two,twoA,twoB);    
    CSA(&twoA  ,&one,one,a[24*i+20],a[24*i+21]);    
    CSA(&twoB  ,&one,one,a[24*i+22],a[24*i+23]);    
    CSA(&forthB,&two,two,twoA,twoB);    
    CSA(&Z,&forth,forth,forthA,forthB);

    b[2*i  ] = (X - ((X>>1)&mu0)) + (Z&mu0);
    b[2*i+1] = (Y - ((Y>>1)&mu0)) + ((Z>>1)&mu0);
  }

  static word c[68];
  for(uint_fast8_t i=0; i<17; ++i) {
    for(uint_fast8_t x=0; x<2; ++x) {
      c[4*i+x] = b[10*i+x]&mu1;
      c[4*i+2+x] = (b[10*i+x]>>2)&mu1;
      for(uint_fast8_t j = 2;j<10;j+=2) {
        c[4*i+x] += b[10*i+j+x]&mu1;
        c[4*i+2+x] += (b[10*i+j+x]>>2)&mu1;
      }
    }    
  } 

  static word d[8];
  for(uint_fast8_t x=0; x<4; ++x) {
    d[x] = c[x]&mu2;    
    d[4+x] = (c[x]>>4) & mu2;
    for(uint_fast8_t j = 4;j<68;j+=4) {
      d[x] += c[x+j]&mu2;    
      d[4+x] += (c[x+j]>>4) & mu2;
    }
  }

  uint8_t *p = (uint8_t*)d;
  uint_fast16_t res =p[0];
  for(uint_fast8_t x=1; x<8*sizeof(word); ++x) {
    res += p[x];
  }

  return 8*res+4*POPC(forth)+2*POPC(two)+POPC(one);
} 


#line 63 "popcnt.web"



#line 675 "popcnt.web"
extern inline void popc_255r_v3_a(const word* a, word* b)
{
	b[0] = (a[0]&mu0) + (a[1]&mu0) + (a[2]&mu0);
	b[1] = ((a[0]>>1)&mu0) + ((a[1]>>1)&mu0) + ((a[2]>>1)&mu0);
}


extern inline void popc_255r_v3_b(const word* a, word* b, word* c)
{
	popc_255r_v3_a(a,c);
	c[2] = (c[0]>>2)&mu1;
	c[0] &= mu1;
	c[3] = (c[1]>>2)&mu1;
	c[1] &= mu1;
	
	for(uint8_t k=1; k<5; ++k)
	{
		popc_255r_v3_a(a+3*k,b);
		c[0] += b[0]&mu1;
		c[2] += (b[0]>>2)&mu1;
		c[1] += b[1]&mu1;
		c[3] += (b[1]>>2)&mu1;
	}
}

extern inline void popc_255r_v3(const word* a,word d[8]) 
{
	static word b[2];
	static word c[4];
	
	popc_255r_v3_b(a,b,d);
	for(uint8_t i=0; i<4; ++i) 
	{
		d[4+i] = (d[i]>>4)&mu2;
		d[i] &= mu2;    
	} 
	for(uint8_t l=1; l<17; ++l)
	{
		popc_255r_v3_b(a+15*l,b,c);
		for(uint8_t i=0; i<4; ++i) {
			d[i] += c[i]&mu2;    
			d[4+i] += (c[i]>>4)&mu2;
		} 
	}   
}

extern inline uint_fast16_t PC_255r_v3 (const word* a)
{
    static word d[8];
    popc_255r_v3(a,d);
    uint8_t *p = (uint8_t*)d;
    uint_fast16_t res =p[0];
    for(uint_fast8_t x=1; x<8*sizeof(word); ++x) {
        res += p[x];
    }
    return res;
}


#line 65 "popcnt.web"


#line 736 "popcnt.web"
extern inline void popc_255r_v3_a_neg(const word* a, word* b)
{
	b[0] = (a[0] - ((a[0]>>1)&mu0)) + (a[2]&mu0);
	b[1] = (a[1] - ((a[1]>>1)&mu0)) + ((a[2]>>1)&mu0);
}

extern inline void popc_255r_v3_b_neg(const word* a, word* b, word* c)
{
	popc_255r_v3_a_neg(a,c);
	c[2] = (c[0]>>2)&mu1;
	c[0] &= mu1;
	c[3] = (c[1]>>2)&mu1;
	c[1] &= mu1;
	
	for(uint8_t k=1; k<5; ++k)
	{
		popc_255r_v3_a_neg(a+3*k,b);
		c[0] += b[0]&mu1;
		c[2] += (b[0]>>2)&mu1;
		c[1] += b[1]&mu1;
		c[3] += (b[1]>>2)&mu1;
	}
}

extern inline void popc_255r_v3_neg(const word* a,word d[8]) 
{
	static word b[2];
	static word c[4];
	
	popc_255r_v3_b_neg(a,b,d);
	for(uint8_t i=0; i<4; ++i) 
	{
		d[4+i] = (d[i]>>4)&mu2;
		d[i] &= mu2;    
	} 
	for(uint8_t l=1; l<17; ++l)
	{
		popc_255r_v3_b_neg(a+15*l,b,c);
		for(uint8_t i=0; i<4; ++i) {
			d[i] += c[i]&mu2;    
			d[4+i] += (c[i]>>4)&mu2;
		} 
	}   
}

extern inline uint_fast16_t PC_255r_v3_neg (const word* a)
{
    static word d[8];
    popc_255r_v3_neg(a,d);
    uint8_t *p = (uint8_t*)d;
    uint_fast16_t res =p[0];
    for(uint_fast8_t x=1; x<8*sizeof(word); ++x) {
        res += p[x];
    }
    return res;
}



#line 66 "popcnt.web"



#line 17 "popcnt.web"


#line 796 "popcnt.web"

#line 813 "popcnt.web"
uint_fast32_t simple_TL(word a[const restrict]) {
  uint_fast32_t total=0;
  for(uint_fast32_t i=0; i<N;++i) 
    total += popcTL(a[i]);
  return total;
}

uint_fast32_t simple_popc(word a[const restrict]) {
  uint_fast32_t total=0;
  for(uint_fast32_t i=0; i<N;++i) 
    total += popc(a[i]);
  return total;
}

uint_fast32_t simple_mul(word a[const restrict]) {
  uint_fast32_t total=0;
  for(uint_fast32_t i=0; i<N;++i) 
    total += popc_mul(a[i]);
  return total;
}

uint_fast32_t popc_array1(word a[const restrict]) {
  uint_fast32_t total=0;
  for(uint_fast32_t i=0; i<N;++i) 
    total += POPC(a[i]);
  return total;
}

uint_fast32_t popc_array1_new(word a[const restrict]) {
  uint_fast32_t total=0;
  uint_fast32_t i=0;
  for(; i<=N-255;i+=255)  
    total += POPC255(a+i);
  for(; i<N;++i) 
    total += POPC(a[i]);
  return total;
}

uint_fast32_t popc_array1_oByte(word a[const restrict]) {
  uint_fast32_t total=0;
  uint_fast32_t i=0;
  for(; i<=N-255;i+=255)  
    total += popc_255v_oByte(a+i);
  for(; i<N;++i) 
    total += POPC(a[i]);
  return total;
}

uint_fast32_t popc_new_red(word a[const restrict]) {
  uint_fast32_t total=0;
  uint_fast32_t i=0;
  for(; i<=N-255;i+=255)  
    total += PC_255r_v3(a+i);
  for(; i<N;++i) 
    total += POPC(a[i]);
  return total;
}

uint_fast32_t popc_new_red_neg(word a[const restrict]) {
  uint_fast32_t total=0;
  uint_fast32_t i=0;
  for(; i<=N-255;i+=255)  
    total += PC_255r_v3_neg(a+i);
  for(; i<N;++i) 
    total += POPC(a[i]);
  return total;
}

uint_fast32_t popc_array_510(word a[const restrict]) {
  uint_fast32_t total=0;
  uint_fast32_t i=0;
  for(; i<=N-510;i+=510) 
    total += popc_510(a+i);
  for(; i<=N-255;i+=255)  
    total += POPC255(a+i);
  for(; i<N;++i) 
    total += POPC(a[i]);
  return total;
}

uint_fast32_t popc_array_1020(word a[const restrict]) {
  uint_fast32_t total=0;
  uint_fast32_t i=0;
  for(; i<=N-1020;i+=1020) 
    total += popc_1020(a+i);
  for(; i<=N-510;i+=510) 
    total += popc_510(a+i);
  for(; i<=N-255;i+=255)  
    total += POPC255(a+i);
  for(; i<N;++i) 
    total += POPC(a[i]);
  return total;
}

uint_fast32_t popc_array_2040(word a[const restrict]) {
  uint_fast32_t total=0;
  uint_fast32_t i=0;
  for(; i<=N-2040;i+=2040) 
    total += popc_2040(a+i);
  for(; i<=N-1020;i+=1020) 
    total += popc_1020(a+i);
  for(; i<=N-510;i+=510) 
    total += popc_510(a+i);
  for(; i<=N-255;i+=255)  
    total += POPC255(a+i);
  for(; i<N;++i) 
    total += POPC(a[i]);
  return total;
}



#line 796 "popcnt.web"


#line 933 "popcnt.web"
extern inline uint_fast32_t min(uint_fast32_t a, uint_fast32_t b) {
  return ((a<b) ? a : b);
}

uint_fast32_t popc_warren(word a[const restrict]) {
  uint_fast32_t res=0;
  for(uint_fast32_t i=0; i<N; i+=31) {
    uint_fast32_t lim = min(N,i+31);
    word sumbytes =0;
    for(uint_fast32_t j=i;j<lim; ++j) { 
      word x = a[j] - ((a[j]>>1) & mu0);
      x = (x & mu1) + ((x>>2) & mu1);
      x = (x + (x >> 4)) & mu2;
      sumbytes +=x;
    }

    uint8_t *p = (uint8_t*)(&sumbytes);
    for(uint_fast8_t x=0; x<sizeof(word); ++x) {
      res += p[x];
    }

  }
  return res;
}

#line 797 "popcnt.web"


#line 980 "popcnt.web"
uint_fast32_t popc_array2(word a[const restrict]) {
  uint_fast32_t total1=0;
  uint_fast32_t total2=0;
  word ones,twos;
  uint_fast32_t i=0;
  for(; i<=N-3;i+=3) {
    CSA(&twos,&ones,a[i],a[i+1],a[i+2]);    
    total1 += POPC(ones);
    total2 += POPC(twos);
  }
  for(; i<N;++i) {
    total1 += POPC(a[i]);
  }

  return total1+2*total2;
}



#line 798 "popcnt.web"


#line 1006 "popcnt.web"
uint_fast32_t popc_array3(word a[const restrict]) {
  uint_fast32_t total=0;
  word ones=0,twos;
  uint_fast32_t i=0;
  for(; i<=N-2;i+=2) {
    CSA(&twos,&ones,ones,a[i],a[i+1]);    
    total += POPC(twos);
  }
  total = 2*total + POPC(ones);
  for(; i<N;++i) {
    total += POPC(a[i]);
  }

  return total;
}

uint_fast32_t popc_array3_new(word a[const restrict]) {
  uint_fast32_t total=0;
  static word twos[255];
  word one = 0;
  uint_fast32_t i=0;
  for(; i<=N-510;i+=510) { // N must be multiply of 255
    for(uint_fast16_t j=0; j<255; ++j)
      CSA(twos+j,&one,one,a[i+2*j],a[i+2*j+1]);
    total += POPC255(twos);
  }
  total = 2*total + POPC(one);
  for(; i<N;i+=255) {
    total += POPC255(a+i);
  }
  return total;
}


#line 799 "popcnt.web"


#line 1041 "popcnt.web"

uint_fast32_t popc_array4(word a[const restrict]) {
  uint_fast32_t total=0;
  word ones=0,twos=0,twosA,twosB,fours;
  uint_fast32_t i=0;
  for(; i<=N-4;i+=4) {
    CSA(&twosA  ,&ones,ones,a[i  ],a[i+1]);    
    CSA(&twosB  ,&ones,ones,a[i+2],a[i+3]);    
    CSA(&fours,&twos,twos,twosA,twosB);    
    total += POPC(fours);
  }
  total = 4*total + 2*POPC(twos)+POPC(ones);
  for(; i<N;++i) {
    total += POPC(a[i]);
  }

  return total;
}

uint_fast32_t popc_array5(word a[const restrict]) {
  uint_fast32_t total=0;
  word ones=0,twos=0,fours=0,eights;
  word twosA,twosB,foursA,foursB;
  uint_fast32_t i=0;
  for(; i<=N-8;i+=8) {
    CSA(&twosA  ,&ones,ones,a[i  ],a[i+1]);    
    CSA(&twosB  ,&ones,ones,a[i+2],a[i+3]);    
    CSA(&foursA,&twos,twos,twosA,twosB);    
    CSA(&twosA  ,&ones,ones,a[i+4],a[i+5]);    
    CSA(&twosB  ,&ones,ones,a[i+6],a[i+7]);    
    CSA(&foursB,&twos,twos,twosA,twosB);    
    CSA(&eights,&fours,fours,foursA,foursB);
    total += POPC(eights);
  }
  total = 8*total + 4*POPC(fours)+2*POPC(twos)+POPC(ones);
  for(; i<N;++i) {
    total += POPC(a[i]);
  }

  return total;
}


#line 800 "popcnt.web"


#line 1143 "popcnt.web"

#line 1120 "popcnt.web"
extern  inline word rCSA(word* a,const  word b,const word c)
{
	(*a)^=b^c; //l
	return(c&b)|((c^b)&(~(*a))); //h
}



#line 1143 "popcnt.web"


#line 1130 "popcnt.web"
#define  maxl 32
word bits_a[maxl];

word rcsa(const word* const  A,  const uint_fast8_t ti)
{
    if(ti>0)
        return rCSA(&bits_a[ti],rcsa(A,ti-1),rcsa(A+(1<<ti),ti-1));
    return rCSA(&bits_a[0],A[0],A[1]);
}


#line 1144 "popcnt.web"

extern  inline uint_fast32_t PC_r_CSA(const word* lA, const uint_fast32_t sizeA) /// 
{
    if(sizeA<1)
        return 0;
    
    const uint_fast32_t einz =1;
    if(sizeA & einz)
    {
        bits_a[0]=lA[0];
        lA++;
    }
    else
        bits_a[0]=0;
        
    uint_fast8_t logb=1;
    for(uint_fast32_t lsizeA=sizeA>>1;lsizeA; logb++ , lsizeA>>=1)
    {
        if(lsizeA & einz)
        {
            bits_a[logb]= rcsa(lA,logb-1);
            lA+=(1<<logb);
        }
        else
            bits_a[logb]=0;
    }
    
    uint_fast32_t s=0;
    for(uint_fast8_t j=0;j<logb;j++)
        s+=(POPC(bits_a[j])<<j);
    return s;
}

uint_fast32_t r_CSA(word a[const restrict]) {
  return PC_r_CSA(a,N);
}


#line 801 "popcnt.web"



#line 18 "popcnt.web"


#line 1185 "popcnt.web"

#line 1192 "popcnt.web"
void testing(char* text, uint_fast8_t(* f)()) {
  static const uint64_t test[] = {0,0, 1,1, 2,1, 3,2, 4,1, 5,2, 6,2, 7,3,
    8,1, 9,2, 10,2, 11,3, 12,2, 13,3, 14,3, 15,4, 16,1, 17,2,
    0x3F,6, 0x40,1, 0x41,2, 0x7f,7, 0x80,1, 0x81,2, 0xfe,7, 0xff,8,
    0x4000,1, 0x4001,2, 0x7000,3, 0x7fff,15,
    0x55555555,16, 0xAAAAAAAA, 16, 0xFF000000,8, 0xC0C0C0C0,8,
    0x0FFFFFF0,24, 0x80000000,1, 0xFFFFFFFF,32};

  uint_fast8_t test_cases = sizeof(test)/8;

  printf("Testing %s: ",text);
  unsigned int failed =0;
  for (uint_fast8_t i = 0; i < test_cases; i += 2) 
     if ((*f)(test[i]) != test[i+1]) 
       failed++;
  if (failed == 0)
     printf("Ok!\n");
  else
     printf("%u tests failed!\n",failed);
}

#line 1185 "popcnt.web"


#line 1231 "popcnt.web"
void timing(char* text,uint_fast32_t(* f)(word*)) {
  uint_fast64_t c=0;
  clock_t begin = clock();
  for(uint_fast32_t i=0;i<iter;++i) 
    c+=(*f)(A);
  printf("Result for %s : %" PRIu64 "\n",text,c/(uint64_t)iter);
  double newtime = (double)(clock()-begin)/(double)(CLOCKS_PER_SEC);
  printf("Timing for %s : %1.2f\n",text,newtime);
  printf("%1.2f%% saving against gcc\n\n",100*(1.0-newtime/runtime)); 
}

#line 1186 "popcnt.web"


#line 1246 "popcnt.web"
int main() {
  srand(time(0));
  for(word i=0; i<N; ++i) {
    A[i] = rand();
  }

  printf("Testing word functions.\n\n");

  testing("table look up method",&popcTL);
  testing("unoptimized divide and conquer method",&popc_unoptimized);
  testing("divide and conquer method",&popc);
  testing("divide and conquer method with multiplication",&popc_mul);
  testing("space words method",&popc_sparse);
  testing("shift right and subtract method",&popc_sum_sub);
  testing("rotation method",&popc_rotate);
  testing("HAKMEM method (1. variation)",&popc_HAKMEM);
  testing("HAKMEM method (2. variation)",&popc_HAKMEM2);

  printf("Testing MAKMEM 7-bit method: ");
  unsigned int failed =0;
  for (uint32_t i = 0; i < (1<<7); ++i) 
     if (popc_HAKMEM7bit(i) != POPC(i)) 
       failed++;
  if (failed == 0)
     printf("Ok!\n");
  else
     printf("%u tests failed!\n",failed);

  printf("Testing MAKMEM 8-bit method: ");
  failed =0;
  for (uint32_t i = 0; i < (1<<8); ++i) 
     if (popc_HAKMEM8bit(i) != POPC(i)) 
       failed++;
  if (failed == 0)
     printf("Ok!\n");
  else
     printf("%u tests failed!\n",failed);

  printf("Testing MAKMEM 15-bit method: ");
  failed =0;
  for (uint64_t i = 0; i < (1<<15); ++i) 
     if (popc_HAKMEM15bit(i) != POPC(i)) 
       failed++;
  if (failed == 0)
     printf("Ok!\n");
  else
     printf("%u tests failed!\n",failed);


  printf("\nTimings for the large arrays.\n\n");

  
#line 1214 "popcnt.web"
  uint_fast64_t c=0;
  clock_t begin = clock();
  for(uint_fast32_t i=0;i<iter;++i) {
    uint_fast32_t p=0;
    for(uint_fast32_t j=0; j<N;++j) 
      p +=__builtin_popcount(A[j]);
    c += p;
  }
  printf("Result for gcc internal : %" PRIu64 "\n",c/(uint64_t)iter);
  runtime = (double)(clock()-begin)/(double)(CLOCKS_PER_SEC);
  printf("Timing for gcc internal : %1.2f\n\n",runtime);
  

#line 1297 "popcnt.web"


  timing("popc_new3     ",&popc_array3_new);
  timing("popc_new      ",&popc_array1_new);
  timing("popc_array1_oB",&popc_array1_oByte);
  timing("popc_new_red  ",&popc_new_red);
  timing("popc_new_red_neg",&popc_new_red_neg);
  timing("popc_new510   ",&popc_array_510);
  timing("popc_new1020  ",&popc_array_1020);
  timing("popc_new2040  ",&popc_array_2040);
  timing("popc_warren   ",&popc_warren);
  timing("popc_array1   ",&popc_array1);
  timing("simple_TL     ",&simple_TL);
#if WORDSSIZE==64
  timing("simple_popc   ",&simple_popc);
  timing("simple_mul    ",&simple_mul);
#endif
  timing("popc_array2   ",&popc_array2);
  timing("popc_array3   ",&popc_array3);
  timing("popc_array4   ",&popc_array4);
  timing("popc_array5   ",&popc_array5);
  timing("r_CSA ",&r_CSA);

  return EXIT_SUCCESS;
}

#line 1187 "popcnt.web"



#line 19 "popcnt.web"


