//
// Created by morteza on 27-02-2018.
//

#ifndef SMASHPP_CMLS_HPP
#define SMASHPP_CMLS_HPP

#include "def.hpp"
using std::vector;
using std::array;

class CMLS    // Count-min-log sketch
{
 public:
  CMLS ();
  void update (u64);          // Update sketch
  u16  query (u64) const;         // Query count of ctx
  u64  getTotal () const;               // Total count of all items in the sketch
  void printSketch () const;

 private:
  u32 w;                          // Width of sketch
  u8  d;                          // Depth of sketch
  vector<array<u64,2>> ab;        // Coefficients of hash functions
  u8  uhashShift;                 // Universal hash shift. G-M in (a*x+b)>>(G-M)
  vector<vector<u8>>  sk;        // Sketch
  u64 tot;       // Total # elements so far

  bool incDecision (u8);         // Increase decision
  void setAB ();                  // Set coeffs a, b of hash funcs (a*x+b) %P %w
  u32  hash (u8, u64) const;
  u8   minLogCount (u64) const;   // Find min log value in the sketch
};

#endif //SMASHPP_CMLS_HPP