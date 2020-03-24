// Smash++
// Morteza Hosseini    seyedmorteza@ua.pt
// Copyright (C) 2018-2020, IEETA, University of Aveiro, Portugal.

#ifndef SMASHPP_APPLICATION_HPP
#define SMASHPP_APPLICATION_HPP

#include <chrono>
#include <iomanip>  // setw, setprecision
#include <iostream>
#include <memory>
#include <thread>

#include "container.hpp"
#include "fcm.hpp"
#include "file.hpp"
#include "filter.hpp"
#include "naming.hpp"
#include "output.hpp"
#include "par.hpp"
#include "segment.hpp"
#include "string.hpp"
#include "time.hpp"
#include "vizpaint.hpp"

namespace smashpp {
class application {
 private:
  std::unique_ptr<Param> par;
  std::unique_ptr<VizParam> vizpar;
  uint8_t round;
  std::vector<PosRow> pos_out;
  std::vector<uint64_t> num_seg_round;

 public:
  application() : round(1) { num_seg_round.resize(3); }
  void exe(int, char**);

 private:
  void process();
  void process_round1();
  void process_round2(std::string const&, std::string const&, uint64_t&);
  void process_round3(std::string const&, std::string const&, uint64_t&);
  auto process_round_impl(uint64_t&) -> uint64_t;
  void compress_ref_free(std::unique_ptr<FCM>&, std::unique_ptr<Filter>&);
  void write_pos_file() const;

  void prepare_data() const;
  void convert_to_seq(std::string, std::string, FileType const&) const;
  void make_ir_consistent(std::unique_ptr<FCM>&) const;
  void remove_temp_seg(std::unique_ptr<Param>&, uint64_t) const;
  void remove_temp_seq(std::unique_ptr<Param>&) const;
};

class info {
 private:
  uint8_t lblWidth = 20;
  uint8_t colWidth = 8;
  uint8_t tblWidth = 52;

 public:
  info() = default;
  void show(std::unique_ptr<Param>&);

 private:
  void show_ref_FCM(std::unique_ptr<Param>&) const;
  void show_ref_STMM(std::unique_ptr<Param>&) const;
  void show_tar_FCM(std::unique_ptr<Param>&) const;
  void show_tar_STMM(std::unique_ptr<Param>&) const;
  void show_filter(std::unique_ptr<Param>&) const;
  void show_file(std::unique_ptr<Param>&) const;

  void rule(uint8_t, std::string&&) const;
  void toprule() const;
  void midrule() const;
  void botrule() const;
  void label(std::string) const;
  void header(std::string) const;
  void info_FCM(std::vector<MMPar> const&, char) const;
  void info_STMM(std::vector<MMPar> const&, char) const;
  void info_filter(std::unique_ptr<Param>&, char) const;
  void info_file(std::unique_ptr<Param>&, char) const;
};

void application::exe(int argc, char* argv[]) {
  if (contains(argv, argv + argc, std::string("-viz"))) {
    vizpar = std::make_unique<VizParam>();
    vizpar->parse(argc, argv);
    std::make_unique<VizPaint>()->plot(vizpar);
  } else {
    par = std::make_unique<Param>();
    par->parse(argc, argv);
    process();
  }
}

void application::process() {
  prepare_data();    // FASTA/FASTQ to seq, if applicable
  process_round1();  // Runs implicitly process_round2 and process_round3
  remove_temp_seq(par);
  write_pos_file();
}

void application::prepare_data() const {
  if (par->refType == FileType::seq && par->tarType == FileType::seq) return;

  std::cerr << bold("====[ PREPARE DATA ]==================================\n");
  const std::string ref_seq = file_name_no_ext(par->refName) + ".seq";
  const std::string tar_seq = file_name_no_ext(par->tarName) + ".seq";
  if (par->refType == FileType::fasta) {
    convert_to_seq(par->refName, ref_seq, FileType::fasta);
  } else if (par->refType == FileType::fastq) {
    convert_to_seq(par->refName, ref_seq, FileType::fastq);
  } else if (par->refType != FileType::seq) {
    error("\"" + par->refName + "\" has unknown format.");
  }
  if (par->tarType == FileType::fasta) {
    convert_to_seq(par->tarName, tar_seq, FileType::fasta);
  } else if (par->tarType == FileType::fastq) {
    convert_to_seq(par->tarName, tar_seq, FileType::fastq);
  } else if (par->tarType != FileType::seq) {
    error("\"" + par->tarName + "\" has unknown format.");
  }
  std::cerr << '\n';
}

void application::convert_to_seq(std::string in, std::string out,
                                 FileType const& type) const {
  std::string msg = "[+] " + italic(in) + " (FAST";
  if (type == FileType::fasta) {
    msg += "A";
  } else if (type == FileType::fastq) {
    msg += "Q";
  }
  msg += ") -> " + italic(out) + " (seq) ";
  std::cerr << msg << "...";
  rename(in.c_str(), (in + LBL_BAK).c_str());
  to_seq(in + LBL_BAK, in, type);
  std::cerr << "\r" << msg << "finished.\n";
}

void application::process_round1() {
  std::string ref_round1 = par->ref;
  std::string tar_round1 = par->tar;
  uint64_t current_pos_row = 0;
  // #pragma omp parallel for ordered schedule(static, 1) //todo
  for (par->ID = 0; par->ID <= 1; ++par->ID) {
    round = 1;
    if (par->verbose && par->showInfo) {
      info{}.show(par);
      par->showInfo = false;
    }
    if (par->ID == 0) {
      std::cerr << bold(
          "====[ REGULAR MODE ]==================================\n");
    } else if (par->ID == 1) {
      std::cerr << bold(
          "====[ INVERTED MODE ]=================================\n");
    }
    num_seg_round[0] = process_round_impl(current_pos_row);
    process_round2(ref_round1, tar_round1, current_pos_row);
    par->ref = ref_round1;
    par->tar = tar_round1;
    remove_temp_seg(par, num_seg_round[0]);
    // remove_temp_seq(par);
  }
}

auto application::process_round_impl(uint64_t& current_pos_row) -> uint64_t {
  par->refName = file_name(par->ref);
  par->tarName = file_name(par->tar);
  auto models = std::make_unique<FCM>(par);
  make_ir_consistent(models);

  models->store(par, round);
  models->compress(par, round);

  auto filter = std::make_unique<Filter>(par);
  // if (!par->manThresh)
  //   par->thresh = static_cast<float>(round_to_prec(models->aveEnt, 0.5));
  //   // par->thresh = static_cast<float>(models->aveEnt);
  filter->smooth_seg(pos_out, par, round, current_pos_row);
  if (filter->nSegs == 0) {
    // if (round == 2) {
    //   pos_out.push_back(
    //       PosRow(0, 0, 0.0, 0.0, run_num, par->ref, par->tar, 0, round));
    // }
    if (round == 1) std::cerr << '\n';
    return 0;  // continue;
  }
  filter->extract_seg(pos_out, round, par->ID, par->ref);

  compress_ref_free(models, filter);

  current_pos_row += filter->nSegs;
  return filter->nSegs;
}

void application::make_ir_consistent(std::unique_ptr<FCM>& models) const {
  for (auto& ref_model : models->rMs) {
    ref_model.ir = par->ID;
    if (ref_model.child) ref_model.child->ir = par->ID;
  }
  for (auto& tar_model : models->tMs) {
    tar_model.ir = par->ID;
    if (tar_model.child) tar_model.child->ir = par->ID;
  }
}

void application::compress_ref_free(std::unique_ptr<FCM>& models,
                                    std::unique_ptr<Filter>& filter) {
  if (par->noRedun) return;

  if (par->verbose) {
    if (round == 3) std::cerr << "    ";
    std::cerr << "[+] Reference-free compression of the segment"
              << (filter->nSegs == 1 ? "" : "s") << '\n';
  } else {
    if (round == 1) par->message = "[+] Ref-free compression of ";
  }
  const auto seg{gen_name(par->ID, par->ref, par->tar, Format::segment)};
  models->selfEnt.reserve(filter->nSegs);
#pragma omp parallel for ordered schedule(static, 1)
  for (uint64_t i = 0; i < filter->nSegs; ++i) {
#pragma omp ordered
    {
      if (!par->verbose && round == 1)
        std::cerr << "\r" << par->message << "segment " << i + 1 << " ...";
      par->seq = seg + std::to_string(i);
    }
    models->self_compress(par, i, round);
  }
  models->aggregate_slf_ent(pos_out, round, par->ID, par->ref, par->noRedun);
  if (!par->verbose && round == 1)
    std::cerr << "\r" << par->message
              << (filter->nSegs == 1 ? "the segment " : "all segments ")
              << "done.         " << '\n';
}

void application::process_round2(std::string const& ref, std::string const& tar,
                                 uint64_t& current_pos_row) {
  if (num_seg_round[0] == 0) return;

  if (par->verbose) {
    par->message = italic("Repeat above process for each segment");
    std::cerr << '\n' << par->message << '\n';
  } else {
    par->message = "[+] Repeating above process for ";
  }
  const auto name_seg_round1{gen_name(par->ID, ref, tar, Format::segment)};
  std::string tar_round2 = par->tar = par->ref;
#pragma omp parallel for ordered schedule(static, 1)
  for (uint64_t i = 0; i < num_seg_round[0]; ++i) {
    round = 2;
#pragma omp ordered
    if (!par->verbose)
      std::cerr << "\r" << par->message << "segment " << i + 1 << " ... ";
    std::string ref_round2 = par->ref = name_seg_round1 + std::to_string(i);
    num_seg_round[1] = process_round_impl(current_pos_row);
#pragma omp ordered
    if (par->verbose) std::cerr << '\n';
    process_round3(ref_round2, tar_round2, current_pos_row);
  }
  if (!par->verbose)
    std::cerr << "\r" << par->message << "all segments done.\n\n";
}

void application::process_round3(std::string const& ref, std::string const& tar,
                                 uint64_t& current_pos_row) {
  if (num_seg_round[1] == 0) return;

  if (par->deep) {
#pragma omp ordered
    if (par->verbose) std::cerr << "    " << italic("Deep compression") << '\n';
    const auto name_seg_round2{gen_name(par->ID, ref, tar, Format::segment)};
    par->tar = ref;
#pragma omp parallel for ordered schedule(static, 1)
    for (uint64_t j = 0; j < num_seg_round[1]; ++j) {
      round = 3;
      par->ref = name_seg_round2 + std::to_string(j);
      num_seg_round[2] = process_round_impl(current_pos_row);
#pragma omp ordered
      if (par->verbose) std::cerr << "\n";
      remove_temp_seg(par, num_seg_round[2]);
    }
  }
  par->ref = ref;
  par->tar = tar;
  remove_temp_seg(par, num_seg_round[1]);
}

void application::remove_temp_seg(std::unique_ptr<Param>& par,
                                  uint64_t seg_num) const {
  const auto seg{gen_name(par->ID, par->ref, par->tar, Format::segment)};

  for (uint64_t i = 0; i != seg_num; ++i)
    if (!par->saveAll && !par->saveSegment)
      remove((seg + std::to_string(i)).c_str());
}

void application::remove_temp_seq(std::unique_ptr<Param>& par) const {
  if (par->refType == FileType::fasta || par->refType == FileType::fastq) {
    if (!par->saveSeq) {
      remove(par->ref.c_str());
    } else {
      const std::string seq_name = file_name_no_ext(par->ref) + ".seq";
      rename(par->ref.c_str(), seq_name.c_str());
    }
    rename((par->ref + LBL_BAK).c_str(), par->ref.c_str());
  }
  if (par->tarType == FileType::fasta || par->tarType == FileType::fastq) {
    if (!par->saveSeq) {
      remove(par->tar.c_str());
    } else {
      const std::string seq_name = file_name_no_ext(par->tar) + ".seq";
      rename(par->tar.c_str(), seq_name.c_str());
    }
    rename((par->tar + LBL_BAK).c_str(), par->tar.c_str());
  }
}

void application::write_pos_file() const {
  if (pos_out.empty()) return;

  auto pos_file = std::make_unique<PositionFile>();
  pos_file->param_list = par->param_list;
  pos_file->info->ref = file_name(par->ref);
  pos_file->info->ref_size = file_size(par->ref);
  pos_file->info->tar = file_name(par->tar);
  pos_file->info->tar_size = file_size(par->tar);
  pos_file->name =
      gen_name(pos_file->info->ref, pos_file->info->tar, Format::position);
  pos_file->write(pos_out, par->asym_region);
}

void info::show(std::unique_ptr<Param>& par) {
  show_ref_FCM(par);
  show_ref_STMM(par);
  show_tar_FCM(par);
  show_tar_STMM(par);
  show_filter(par);
  show_file(par);
}

void info::show_ref_FCM(std::unique_ptr<Param>& par) const {
  auto ref_FCM_row = [&](std::string lbl, char c) {
    label(lbl);
    info_FCM(par->refMs, c);
    std::cerr << '\n';
  };

  toprule();
  ref_FCM_row(bold("Ref Model           "), 'm');
  midrule();
  ref_FCM_row("Context size (k)", 'k');
  bool hasSketch{false};
  for (const auto& e : par->refMs) {
    if (e.cont == Container::sketch_8) {
      hasSketch = true;
      break;
    }
  }
  if (hasSketch) {
    ref_FCM_row("Sketch width (w)", 'w');
    ref_FCM_row("Sketch depth (d)", 'd');
  }
  ref_FCM_row("Inv. repeat  (ir)", 'i');
  ref_FCM_row("Alpha        (a)", 'a');
  ref_FCM_row("Gamma        (g)", 'g');
  botrule();  // cerr << '\n';
}

void info::show_ref_STMM(std::unique_ptr<Param>& par) const {
  bool show_rstmm = false;
  for (const auto& model : par->refMs) {
    if (model.child) {
      show_rstmm = true;
      break;
    }
  }
  if (!show_rstmm) return;

  auto ref_STMM_row = [&](std::string lbl, char c) {
    label(lbl);
    if (c != 'h') info_STMM(par->refMs, c);
    std::cerr << '\n';
  };

  toprule();
  ref_STMM_row(bold("Ref Substituttional Model           "), 'h');
  midrule();
  ref_STMM_row("No. Subst.   (t)", 't');
  ref_STMM_row("Inv. repeat  (ir)", 'i');
  ref_STMM_row("Alpha        (a)", 'a');
  ref_STMM_row("Gamma        (g)", 'g');
  botrule();  // cerr << '\n';
}

void info::show_tar_FCM(std::unique_ptr<Param>& par) const {
  auto tar_FCM_row = [&](std::string lbl, char c) {
    label(lbl);
    info_FCM(par->tarMs, c);
    std::cerr << '\n';
  };

  toprule();
  tar_FCM_row(bold("Tar Model           "), 'm');
  midrule();
  tar_FCM_row("Context size (k)", 'k');
  bool hasSketch = false;
  for (const auto& e : par->tarMs)
    if (e.cont == Container::sketch_8) {
      hasSketch = true;
      break;
    }
  if (hasSketch) {
    tar_FCM_row("Sketch width (w)", 'w');
    tar_FCM_row("Sketch depth (d)", 'd');
  }
  tar_FCM_row("Inv. repeat  (ir)", 'i');
  tar_FCM_row("Alpha        (a)", 'a');
  tar_FCM_row("Gamma        (g)", 'g');
  botrule();  // cerr << '\n';
}

void info::show_tar_STMM(std::unique_ptr<Param>& par) const {
  bool show_tstmm = false;
  for (const auto& model : par->tarMs) {
    if (model.child) {
      show_tstmm = true;
      break;
    }
  }
  if (!show_tstmm) return;

  auto tar_STMM_row = [&](std::string lbl, char c) {
    label(lbl);
    if (c != 'h') info_STMM(par->tarMs, c);
    std::cerr << '\n';
  };

  toprule();
  tar_STMM_row(bold("Tar Substituttional Model           "), 'h');
  midrule();
  tar_STMM_row("No. Subst.   (t)", 't');
  tar_STMM_row("Inv. repeat  (ir)", 'i');
  tar_STMM_row("Alpha        (a)", 'a');
  tar_STMM_row("Gamma        (g)", 'g');
  botrule();  // cerr << '\n';
}

void info::show_filter(std::unique_ptr<Param>& par) const {
  if (par->compress) return;

  auto filter_row = [&](std::string lbl, char c) {
    label(lbl);
    if (c != 'h') info_filter(par, c);
    std::cerr << '\n';
  };

  toprule();
  filter_row(bold("Filter & Segment"), 'h');
  midrule();
  filter_row("Window function", 'f');
  if (par->manFilterScale) filter_row("Filter scale", 's');
  if (!par->manFilterScale) filter_row("Window size", 'w');
  if (par->manThresh) filter_row("Threshold", 't');
  botrule();  // cerr << '\n';
}

void info::show_file(std::unique_ptr<Param>& par) const {
  auto file_row = [&](std::string lbl, std::string s1, std::string s2) {
    label(lbl);
    if (s1.size() == 1) {
      info_file(par, s1.front());
      info_file(par, s2.front());
    } else {
      header(s1);
      header(s2);
    }
    std::cerr << '\n';
  };

  toprule();
  file_row(bold("File                "), bold("Name            "),
           bold("Size (B)"));
  midrule();
  file_row("Reference", "r", "1");
  file_row("Target", "t", "2");
  botrule();
}

void info::rule(uint8_t n, std::string&& s) const {
  for (auto i = n / s.size(); i--;) std::cerr << s;
  std::cerr << '\n';
}

void info::toprule() const {}
// void toprule () { rule(tblWidth, "~"); }

void info::midrule() const { rule(tblWidth, "="); }
// void midrule () { rule(tblWidth, "~"); }

void info::botrule() const { rule(tblWidth, " "); }

void info::label(std::string s) const {
  std::cerr << std::setw(lblWidth) << std::left << s;
}

void info::header(std::string s) const {
  std::cerr << std::setw(2 * colWidth) << std::left << s;
}

void info::info_FCM(const std::vector<MMPar>& Ms, char c) const {
  int i = 0;
  for (const auto& e : Ms) {
    std::cerr << std::setw(colWidth) << std::left;
    switch (c) {
      case 'm':
        std::cerr << ++i;
        break;
      case 'k':
        std::cerr << static_cast<int>(e.k);
        break;
      case 'w':
        std::cerr << (e.w == 0 ? "0"
                               : "2^" + std::to_string(
                                            static_cast<int>(std::log2(e.w))));
        break;
      case 'd':
        std::cerr << static_cast<int>(e.d);
        break;
      case 'i':
        std::cerr << (e.ir == 0 ? "reg" : e.ir == 1 ? "inv" : "reg+inv");
        break;
      case 'a':
        std::cerr << e.alpha;
        break;
      case 'g':
        std::cerr << e.gamma;
        break;
    }
  }
}

void info::info_STMM(std::vector<MMPar> const& Ms, char c) const {
  for (const auto& e : Ms) {
    std::cerr << std::setw(colWidth) << std::left;
    if (e.child) {
      switch (c) {
        case 't':
          std::cerr << static_cast<int>(e.child->thresh);
          break;
        case 'i':
          std::cerr << (e.child->ir == 0
                            ? "reg"
                            : e.child->ir == 1 ? "inv" : "reg+inv");
          break;
        case 'a':
          std::cerr << e.child->alpha;
          break;
        case 'g':
          std::cerr << e.child->gamma;
          break;
        default:
          break;
      }
    } else {
      std::cerr << '-';
    }
  }
}

void info::info_filter(std::unique_ptr<Param>& par, char c) const {
  std::cerr << std::setw(colWidth) << std::left;
  switch (c) {
    case 'f':
      std::cerr << par->print_win_type();
      break;
    case 's':
      std::cerr << par->print_filter_scale();
      break;
    case 'w':
      std::cerr << par->filt_size;
      break;
    case 't':
      std::cerr << par->thresh;
      break;
    default:
      break;
  }
}

void info::info_file(std::unique_ptr<Param>& par, char c) const {
  std::cerr << std::setw(2 * colWidth) << std::left;
  // const auto lacale = "en_US.UTF8";
  // std::setlocale(LC_ALL, "en_US.UTF-8");
  switch (c) {
    case '1':
      // std::cerr.imbue(std::locale(lacale));
      std::cerr << file_size(par->ref);
      break;
    // case 'r':  cerr<<par->ref;  break;
    case 'r':
      std::cerr << par->refName;
      break;
    case '2':
      // std::cerr.imbue(std::locale(lacale));
      std::cerr << file_size(par->tar);
      break;
    // case 't':  cerr<<par->tar;  break;
    case 't':
      std::cerr << par->tarName;
      break;
    default:
      break;
  }
}
}  // namespace smashpp

#endif  // SMASHPP_APPLICATION_HPP