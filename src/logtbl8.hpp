// Smash++
// Morteza Hosseini    seyedmorteza@ua.pt
// Copyright (C) 2018-2020, IEETA, University of Aveiro, Portugal.

#ifndef SMASHPP_LOGTABLE8_HPP
#define SMASHPP_LOGTABLE8_HPP

#include <vector>

#include "def.hpp"

// #define DEBUG

namespace smashpp {
class LogTable8 {
  using ctx_t = uint32_t;
  using val_t = uint32_t;

 private:
  std::vector<uint8_t> tbl;  // Table of 8 bit logarithmic counters
  uint8_t k;                 // Ctx size
  uint64_t tot;              // Total # elements so far

 public:
  LogTable8() : k(0), tot(0) {}
  explicit LogTable8(uint8_t);
  void update(ctx_t);                                // Update table
  void update(ctx_t, uint8_t);                       // Update table
  auto query(ctx_t) const -> val_t;                  // Query count of ctx
  auto query(ctx_t, uint8_t) const -> val_t;         // Query count of ctx
  auto query_counters(ctx_t) -> std::vector<val_t>;  // todo

#ifdef DEBUG
  void dump(std::ofstream&) const;
  void load(std::ifstream&) const;
  auto get_total() const -> uint64_t;  // Total count of all items in the table
  auto count_empty() const -> uint64_t;  // Number of empty cells in the table
  auto max_tbl_val() const -> uint32_t;
  void print() const;
  ~LogTable8() {
    std::cerr << "count_empty=" << count_empty() << "\ntotal=" << get_total()
              << "\nmax_tbl_val=" << max_tbl_val() << '\n';
  }
#endif

 private:
  bool must_update(uint8_t) const;
};
}  // namespace smashpp

#endif  // SMASHPP_LOGTABLE8_HPP