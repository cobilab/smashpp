// Smash++
// Morteza Hosseini    seyedmorteza@ua.pt
// Copyright (C) 2018-2020, IEETA, University of Aveiro, Portugal.

#include "logtbl8.hpp"

#include <algorithm>
#include <fstream>

#include "exception.hpp"
using namespace smashpp;

LogTable8::LogTable8(uint8_t k_) : k(k_), tot(0) {
  try {
    tbl.resize(1ull << (2 * (k + 1)));
  } catch (std::bad_alloc& b) {
    error("failed memory allocation.");
  }
}

auto LogTable8::must_update(uint8_t count) const -> bool {
  if (count == 0) return true;
  for (uint8_t i = 0; i != count; ++i)
    if ((tot >> i) & 1) return false;
  return true;

  // return (tot & POW2minus1[count]) == 0;  // x % 2^n = x & (2^n-1)
}

void LogTable8::update(LogTable8::ctx_t context_and_base) {
  auto count_address = &tbl[context_and_base];
  if (must_update(*count_address)) {
    ++(*count_address);
    ++tot;
  }

  // if ((tot++ & POW2minus1[tbl[ctx]]) == 0)  // x % 2^n = x & (2^n-1)
  //   ++tbl[ctx];
}

// void LogTable8::update(LogTable8::ctx_t context, uint8_t encoded_base) {
//   auto row_iter = std::next(std::begin(tbl), context);
//   switch (encoded_base) {
//     case 0:
//       if (must_update(*row_iter & 0xFF)) {
//         ++(*row_iter);  // Rightmost 8 bits
//         ++tot;
//       }
//       break;
//     case 1:
//       if (must_update((*row_iter >> 8) & 0xFF)) {
//         *row_iter += (1ul << 8);
//         ++tot;
//       }
//       break;
//     case 2:
//       if (must_update((*row_iter >> 16) & 0xFF)) {
//         *row_iter += (1ul << 16);
//         ++tot;
//       }
//       break;
//     case 3:
//       if (must_update(*row_iter >> 24)) {
//         *row_iter += (1ul << 24);
//         ++tot;
//       }
//       break;
//     default:
//       break;
//   }

//   // auto const row_index = context >> 2;
//   // auto const col_index = context % 4;
//   // auto row_iter = std::next(std::begin(tbl), row_index);
//   // auto shift = (3 - col_index) * 16;
//   // switch (encoded_base) {
//   //   case 0:
//   //     break;
//   //   case 1:
//   //     shift += 4;
//   //     break;
//   //   case 2:
//   //     shift += 8;
//   //     break;
//   //   case 3:
//   //     shift += 12;
//   //     break;
//   //   default:
//   //     break;
//   // }
//   // if (must_update((*row_iter >> shift) & 0xF)) {
//   //   *row_iter += (1ull << shift);
//   //   ++tot;
//   // }
// }

auto LogTable8::query(LogTable8::ctx_t context_and_base) const
    -> LogTable8::val_t {
  return (1u << tbl[context_and_base]) - 1;  // 2 ^ tbl[.] - 1

  // return POW2minus1[tbl[context_and_base]];

  // auto const row_index = context >> 2;
  // auto const col_index = context % 4;
  // auto row_iter = std::next(std::begin(tbl), row_index);
  // auto shift = (3 - col_index) * 16;
  // auto count = (*row_iter >> (shift + base * 4)) & 0xF;
  // return (1ul << count) - 1;
}

auto LogTable8::query_counters(LogTable8::ctx_t context_and_base)
    -> std::vector<LogTable8::val_t> {
  auto row_address = &tbl[context_and_base];
  return {static_cast<LogTable8::val_t>((1ul << *row_address) - 1ul),
          static_cast<LogTable8::val_t>((1ul << *(row_address + 1)) - 1ul),
          static_cast<LogTable8::val_t>((1ul << *(row_address + 2)) - 1ul),
          static_cast<LogTable8::val_t>((1ul << *(row_address + 3)) - 1ul)};
}

#ifdef DEBUG
void LogTable8::dump(std::ofstream& ofs) const {
  ofs.write((const char*)&tbl[0], tbl.size());
  //  ofs.close();
}

void LogTable8::load(std::ifstream& ifs) const {
  ifs.read((char*)&tbl[0], tbl.size());
}

uint64_t LogTable8::get_total() const { return tot; }

uint64_t LogTable8::count_empty() const {
  return static_cast<uint64_t>(std::count(std::begin(tbl), std::end(tbl), 0));
}

uint32_t LogTable8::max_tbl_val() const {
  return *std::max_element(std::begin(tbl), std::end(tbl));
}

void LogTable8::print() const {
  constexpr uint8_t context_width{12};
  std::cerr.width(context_width);
  std::cerr << std::left << "Context";
  std::cerr << "Count\n";
  std::cerr << "-------------------\n";
  uint32_t i{0};
  for (const auto& c : tbl) {
    std::cerr.width(context_width);
    std::cerr << std::left << i++;
    std::cerr << static_cast<uint16_t>(c) << '\n';
  }
}
#endif