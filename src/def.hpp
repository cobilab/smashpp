//
// Created by morteza on 02-02-2018.
//

#ifndef SMASHPP_DEF_HPP
#define SMASHPP_DEF_HPP

#include <iostream>
#include <unordered_map>
#include <chrono>

// Version
const std::string VERSION   = "18.03";
const std::string DEV_YEARS = "2018";

// Typedef
typedef signed char         i8;
typedef unsigned char       u8;
typedef signed short        i16;
typedef unsigned short      u16;
typedef signed int          i32;
typedef unsigned int        u32;
typedef signed long long    i64;
typedef unsigned long long  u64;
typedef std::chrono::duration<double>  dur_t;

// Metaprogram
// Power a^n
constexpr u64 sqr (u64 a) { return a * a; }
constexpr u64 power (u64 a, u64 n) {
  return n==0 ? 1 : sqr(power(a, n>>1)) * (n&1 ? a : 1);
}

// Constant
constexpr u8  DEF_THR      = 1;    // Default # threads
constexpr u8  DEF_LVL      = 0;    // Default level
constexpr u8  ALPH_SZ      = 4;    // Alphabet size
constexpr u8  IRMAGIC      = 3;    // Calc ir syms based on syms
constexpr u8  K_MAX_TBL64  = 11;   // Max ctx depth for table 64 (128 MB mem)
constexpr u8  K_MAX_TBL32  = 13;   // Max ...           table 32 (1   GB mem)
constexpr u8  K_MAX_LGTBL8 = 14;   // Max ...       log table 8  (1   GB mem)
constexpr u32 BLK_SZ       = 8192; // 8K
constexpr u64 DEF_W        = power(2,20); // Default width of CML sketch (2^...)
constexpr u8  DEF_D        = 4;    // Default depth of CML sketch
constexpr u32 G            = 64;   // Machine word size - for universal hash fn
constexpr u8  LOG_BASE     = 2;    // Logarithmic counting
constexpr float DEF_GAMMA  = 0.99; // Default gamma for multiple models

typedef std::unordered_map<u64, std::array<u64,ALPH_SZ>>  htbl_t; //faster t a[]

// Enums
enum MODE {TABLE_64, TABLE_32, LOG_TABLE_8, SKETCH_8};  // Data structures
// Inv. repeats, 1 & 2 & 3 & 4 models. D: direct(bit 0), I: inv.(bit 1)
//enum IR0 {   D,    I};
//enum IR1 {  DD,   DI,   ID,   II};
//enum IR2 { DDD,  DDI,  DID,  DII,  IDD,  IDI,  IID,  III};
//enum IR3 {DDDD, DDDI, DDID, DDII, DIDD, DIDI, DIID, DIII,
//          IDDD, IDDI, IDID, IDII, IIDD, IIDI, IIID, IIII};
enum IR {DDDD, DDDI, DDID, DDII, DIDD, DIDI, DIID, DIII,
         IDDD, IDDI, IDID, IDII, IIDD, IIDI, IIID, IIII};

// Macro
//#define LOOP16(n)  n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n
//#define SEQ16      0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
//#define LOOP(i,S)     for(const char& (i) : (S))
//#define LOOP2(i,j,S)  LOOP(i,S) LOOP(j,S)

// Lookup table
constexpr u64 POW2[36] {
           1,          2,           4,           8,
          16,         32,          64,         128,
         256,        512,        1024,        2048,
        4096,       8192,       16384,       32768,
       65536,     131072,      262144,      524288,
     1048576,    2097152,     4194304,     8388608,
    16777216,   33554432,    67108864,   134217728,
   268435456,  536870912,  1073741824,  2147483648,
  4294967296, 8589934592, 17179869184, 34359738368
};
constexpr u32 POW3[17] {
         1,     3,     9,     27,     81,     243,     729,     2187,      // #8
      6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907,
  43046721
};
constexpr u64 POW4[32] {    // Max 4^31 contained in u64
                    1,                   4,                 16,
                   64,                 256,               1024,
                 4096,               16384,              65536,
               262144,             1048576,            4194304,
             16777216,            67108864,          268435456,
           1073741824,          4294967296,        17179869184,
          68719476736,        274877906944,      1099511627776,
        4398046511104,      17592186044416,     70368744177664,
      281474976710656,    1125899906842624,   4503599627370496,
    18014398509481984,   72057594037927936, 288230376151711744,
  1152921504606846976, 4611686018427387904
};
constexpr u64 POW5[23] {
               1,               5,               25,            125,
             625,            3125,            15625,          78125,
          390625,         1953125,          9765625,       48828125,
       244140625,      1220703125,       6103515625,    30517578125,
    152587890625,    762939453125,    3814697265625, 19073486328125,
  95367431640625, 476837158203125, 2384185791015625
};
constexpr u8 CTR[2][256] {
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
   3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
   4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
   5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
   6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
   7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
   9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
  14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15},
{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15}
};
constexpr u8 INC_CTR[2][256] {
{ 16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,255},
{  1,   2,   3,   3,   5,   6,   7,   7,   9,  10,  11,  11,  13,  14,  15,  15,
  17,  18,  19,  19,  21,  22,  23,  23,  25,  26,  27,  27,  29,  30,  31,  31,
  33,  34,  35,  35,  37,  38,  39,  39,  41,  42,  43,  43,  45,  46,  47,  47,
  49,  50,  51,  51,  53,  54,  55,  55,  57,  58,  59,  59,  61,  62,  63,  63,
  65,  66,  67,  67,  69,  70,  71,  71,  73,  74,  75,  75,  77,  78,  79,  79,
  81,  82,  83,  83,  85,  86,  87,  87,  89,  90,  91,  91,  93,  94,  95,  95,
  97,  98,  99,  99, 101, 102, 103, 103, 105, 106, 107, 107, 109, 110, 111, 111,
 113, 114, 115, 115, 117, 118, 119, 119, 121, 122, 123, 123, 125, 126, 127, 127,
 129, 130, 131, 131, 133, 134, 135, 135, 137, 138, 139, 139, 141, 142, 143, 143,
 145, 146, 147, 147, 149, 150, 151, 151, 153, 154, 155, 155, 157, 158, 159, 159,
 161, 162, 163, 163, 165, 166, 167, 167, 169, 170, 171, 171, 173, 174, 175, 175,
 177, 178, 179, 179, 181, 182, 183, 183, 185, 186, 187, 187, 189, 190, 191, 191,
 193, 194, 195, 195, 197, 198, 199, 199, 201, 202, 203, 203, 205, 206, 207, 207,
 209, 210, 211, 211, 213, 214, 215, 215, 217, 218, 219, 219, 221, 222, 223, 223,
 225, 226, 227, 227, 229, 230, 231, 231, 233, 234, 235, 235, 237, 238, 239, 239,
 241, 242, 243, 243, 245, 246, 247, 247, 249, 250, 251, 251, 253, 254, 255, 255}
};
constexpr u8 NUM[123] {    // a,A=0  c,C=1  g,G=2  t,T=3
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,             // #20
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0,
  0, 0, 0
};
constexpr u8 REVNUM[123] {    // a,A->3  c,C->2  g,G->1  t,T->0
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,             // #20
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 3, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2,
  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0
};
constexpr u8 REV[123] {    // a,A->84(T)  c,C->71(G)  g,G->67(C)  t,T->65(A)
  0, 0, 0,  0,  0,  0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 0,  0,  0, 0,  0,     // #20
  0, 0, 0,  0,  0,  0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 0,  0,  0, 0,  0,
  0, 0, 0,  0,  0,  0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 0,  0,  0, 0,  0,
  0, 0, 0,  0,  0, 84, 0, 71, 0, 0, 0, 67, 0, 0, 0, 0,  0,  0, 0,  0,
  0, 0, 0,  0, 65,  0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 84, 0, 71,
  0, 0, 0, 67,  0,  0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 0, 65,  0, 0,  0,
  0, 0, 0
};
//constexpr u8 NUM[123] {    // a,A=0  c,C=1  n,N=2  g,G=3  t,T=4
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,             // #20
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2, 0,
//  0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
//  0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 4, 0, 0, 0,
//  0, 0, 0
//};
//constexpr u8 REV[123] {    // a,A->T  c,C->G  n,N->N  g,G->C  t,T->A
//  0, 0, 0,  0,  0,  0, 0,  0, 0, 0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,   // #20
//  0, 0, 0,  0,  0,  0, 0,  0, 0, 0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,
//  0, 0, 0,  0,  0,  0, 0,  0, 0, 0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,
//  0, 0, 0,  0,  0,'T', 0,'G', 0, 0,  0,'C', 0, 0, 0, 0,  0,  0,'N',  0,
//  0, 0, 0,  0,'A',  0, 0,  0, 0, 0,  0,  0, 0, 0, 0, 0,  0,'T',  0,'G',
//  0, 0, 0,'C',  0,  0, 0,  0, 0, 0,'N',  0, 0, 0, 0, 0,'A',  0,  0,  0,
//  0, 0, 0
//};
constexpr u8 LEVEL[2][11] {    // Multiple models MUST be in sorted 'k' manner
// #mdl, ir, k, 100*alpha, log2 w,  d
  {1,     1,  11,    99,       0,      0},    // Level 0
  {2,     0, 11,    99,       0,      0,     // Level 1
          1, 20,    99,      30,  DEF_D},
};


//template<u32 N>    // Up to 262144=2^18 elements
//struct LogInt      // 0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,...
//{
//  constexpr LogInt() : lg() {
//    for (u32 i=0; i!=LOG_BASE; ++i)
//      lg[i] = 0;
//    for (u32 i=LOG_BASE; i!=N; ++i)
//      lg[i] = static_cast<u8>(1 + lg[i/LOG_BASE]);
//  }
//  u8 lg[N];
//};
// Inside function definition
//constexpr auto a = LogInt<256>();
//cerr << (int) a.lg[3];

class DS{
public:
  virtual void print(){};
  virtual ~DS (){};
};
#endif //SMASHPP_DEF_HPP