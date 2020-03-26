// Smash++
// Morteza Hosseini    seyedmorteza@ua.pt
// Copyright (C) 2018-2020, IEETA, University of Aveiro, Portugal.

#ifndef SMASHPP_TABLE64_HPP
#define SMASHPP_TABLE64_HPP

// #define DEBUG //todo

#include <vector>

#include "def.hpp"

namespace smashpp {
class Table64 {
  using ctx_t = uint32_t;
  using val_t = uint64_t;

 private:
  std::vector<val_t> tbl;  // Table of 64 bit counters
  uint8_t k;               // Ctx size

 public:
  Table64(uint8_t = 0);
  void update(ctx_t);                // Update table
  auto query(ctx_t) const -> val_t;  // Query count of ctx
  auto query_counters(ctx_t) -> std::vector<val_t>;

#ifdef DEBUG
  void dump(std::ofstream&) const;
  void load(std::ifstream&) const;
  auto count_empty() const -> uint64_t;  // Number of empty cells in the table
  auto max_tbl_val() const -> uint64_t;
  void print() const;
  void print(std::string) const;
#endif
};
}  // namespace smashpp

#endif  // SMASHPP_TABLE64_HPP