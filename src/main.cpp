// Smash++
// Morteza Hosseini    seyedmorteza@ua.pt
// Copyright (C) 2018-2020, IEETA, University of Aveiro, Portugal.
//    ____                      _
//   / ___| _ __ ___   __ _ ___| |__    _     _
//   \___ \| '_ ` _ \ / _` / __| '_ \ _| |_ _| |_
//    ___) | | | | | | (_| \__ \ | | |_   _|_   _|
//   |____/|_| |_| |_|\__,_|___/_| |_| |_|   |_|

//                 ```.```
//           `-/oydmmmmmmmmdho:`
//          `smNNMMMMMMMMMNNMMNd+`
//          :hNNNmmdhhmmddddmmNNNh`
//         sNNmy+/::--:::--::/ohNN/
//        .NMNs/:----.-..-----:/hNy
//        :NMm+::---........--:/sNd`
//        -NNd/://+oo+/-:/+o+///sNh
//        `dNh/+yyhdddy:/dmmhhyooNo
//        `sds:+syydhho.-yddhys++h-
//        `+y+:---:::::.-:///:::/s-
//         :+/:--...-:-.--:-..-:/+-
//         .//::----:+oooo/:---:/:`
//          .//:::://+yyys//::///`
//           .++//+sssyyyssyo+++-
//            /+++//:/osso//+++/
//            :ooo+/::://///+oo.
//          `:/ossssoo+oooosssoso.
//         `sm++ossyyyyyyyyyso+smh`
//      ``.smdo++ossssyyyysoo++hNNh/.`
//  `.-:/+odmNmysoooooossoooshmNNNmsso/.`
// /+++++++odNNNNmdhhyssyhdmNNNNNdyooo+++/:
// ++++++++++ymNNNNNNmddmmmNNNNmhssooo+++++
// +++++++++++ohmmmmmmmNmddmmmdyysoooo+++++
// +++++++++++oossyyyhmmhhhhhhyysoooo++++++
// o+++++++++++++oosyhddyhhhyyssooo++++++++

// MMMMNMMNNMNNNNNNNNNMNNNNmmmmmNNNNNNNMNNN
// MMMMMMMNNMNNNNNNmmdddmmNNNmmmNNNMNNNNNNN
// MMMMMMMNNMMNmhso+////++shdNNNNNNMNmNNNNN
// MMMMMMMMNMMds+:-..``..-:/sdNNNNNNmNNMNNN
// MMMMMMMMMMmy+:.```  ``.-:+sdNMNMMMNMMMMN
// MMMMMMMMMMh+/:-.``````.-:/oymMMMMMNMMMMN
// MMMMMMMMMNsohhyo:``` `/yhhdddMMMMMMMMMMN
// MMMMMMMMMNyy/...`.```````.:sdNMMMMMMMMMM
// MMMMMMMMMNo/ooso/::://::+ssysmMMMMMMMMMM
// MMMMMMMMmdo+/.``.:/:+o+-..:osddMMMMMMMMM
// MMMMMMMMNyo/.```-/:-:oo:---:odhMMMMMMMMM
// MMMMMMMMM+y:.```.-:..//-```-+dyMMMMMMMMM
// MMMMMMMMMmm+-.`.://--+syo:-:oNMMMMMMMMMM
// MMMMMMMMMMNs/::+o:.```-o+//+yNMMMMMMMMMM
// MMMMMMMMMMMh//:://-..-/o//+sdMMMMMMMMMMM
// MMMMMMMMMMMNs+//-..``..-+sshmMMMMMMMMMMM
// MMMMMMMMMMMMsooo-```.`.-shhydMMMMMMMMMMM
// MMMMMMMMMMMMy::oo:---::+hs+odmddmMMMMMMN
// MMMMMMMMms+-o:..-/+//+//:::+yy:-::/sdmNN
// MMMMNhs:````.:.````````...-/o-...-.-:-:s

// +++/+:-://+/:---.---:-.-:::hyyyyyyyy..-/
// oo+/:::-:-/+:/++ooooo+++/:/ysosyhsss/:-.
// so+oo+o/:-:oyhhhhhyyyhhysyyys+/+oso//:o+
// sso///+sosyyyhhhhhyyyyyssssssss+::::/:/o
// /+/////oyssyhhhhdmmNNNNNmmmmmmdhs+/-----
// ossooooyhydNmdhhdddddhddddmmdddmds/:::-/
// /++/oohddmNdo+///++++++++++//::oddyooo+/
// ++o+/shdmmh/::-::///////::::----:ddsoo++
// o++//syhdho/:://++++++/////:::---ody+//+
// sooo/shhys+///+++++++++////////::/ho:/os
// ys/-/yhhs/////////++///////::::://s+so+o
// oo+o:sys+://///++oooooo/+++//::-:/o:oooo
// ++//s+++::/+osyhmmmmmhyo+ydddho////-/+++
// osso+sy/::/+sssyhhdddhs//ydmdhyy+/os::``
// ssso:++//::///+ossssso/:-/oyyo+//+osoo/-
// ++/://o+////++///+os+/-::-://////--::++:
// yssyy+++//++++++osyy+//+/:/+///////+oooo
// ssyyyso///+ooosyhyyyhdyhyo+os+++/+sssoo+
// ooooooo/++osssyhhhhyhhhhysossssoooos+ooo
// o+oooso++ossyyhhdddddhdhhhhhyssoooo+//+o
// ::+shyds+osyhhhhyyyyyyysoooyyyddhy+:.-:-
// ::+ydNm+osyyhhhhyyyyhdhysssyhmdmmmmmh+//
// hhyhNNd+osyhhhddhhyyyyyssyyodmmmmmNNmNmd
// hsymNNmsosyhhhyhhddddddhyssyNNdNmmmNNNNN
// yydmmmmhssyhddhhhdddhhyyssyNNNmdNNNNNNNN
// hhdmmmmmhhyyhhhhhdddhhyyyhNNNNNmmNNNNNNN
// hddmmNNmmddhhhhhhddhhhhhmNNNNNMNNNNNNNNN

// #define __STDC_FORMAT_MACROS
// #if defined(_MSC_VER)
// #include <io.h>
// #else
// #include <unistd.h>
// #endif

#include <chrono>
#include <iomanip>  // setw, setprecision
#include <iostream>
#include <thread>

#include "clean.hpp"
#include "container.hpp"
#include "fcm.hpp"
#include "filter.hpp"
#include "naming.hpp"
#include "output.hpp"
#include "par.hpp"
#include "segment.hpp"
#include "string.hpp"
#include "time.hpp"
#include "vizpaint.hpp"
using namespace smashpp;

class application {
 private:
  std::unique_ptr<Param> par;
  std::unique_ptr<VizParam> vizpar;
  uint8_t round;
  std::vector<PosRow> pos_out;
  std::vector<uint64_t> num_seg_round;

 public:
  application() : round(1) { num_seg_round.resize(3); }

 private:
  void show_info(std::unique_ptr<Param>& par) {
    constexpr uint8_t lblWidth = 20;
    constexpr uint8_t colWidth = 8;
    constexpr uint8_t tblWidth =
        52;  // static_cast<uint8_t>(lblWidth + Ms.size()*colWidth);

    const auto rule = [](uint8_t n, std::string&& s) {
      for (auto i = n / s.size(); i--;) std::cerr << s;
      std::cerr << '\n';
    };
    const auto toprule = [=]() {};
    // const auto toprule = [=]() { rule(tblWidth, "~"); };
    const auto midrule = [=]() { rule(tblWidth, "="); };
    // const auto midrule = [=]() { rule(tblWidth, "~"); };
    const auto botrule = [=]() { rule(tblWidth, " "); };
    const auto label = [=](std::string s) {
      std::cerr << std::setw(lblWidth) << std::left << s;
    };
    const auto header = [=](std::string s) {
      std::cerr << std::setw(2 * colWidth) << std::left << s;
    };
    const auto info_MM = [&](const std::vector<MMPar>& Ms, char c) {
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
                                   : "2^" + std::to_string(static_cast<int>(
                                                std::log2(e.w))));
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
          default:
            break;
        }
      }
    };
    const auto info_STMM = [&](const std::vector<MMPar>& Ms, char c) {
      for (const auto& e : Ms) {
        std::cerr << std::setw(colWidth) << std::left;
        if (e.child) switch (c) {
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
        else
          std::cerr << '-';
      }
    };
    const auto info_filter = [&](char c) {
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
    };
    const auto info_file = [&](char c) {
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
    };
    auto rMs = par->refMs;
    auto tMs = par->tarMs;
    const auto rmm_row = [=](std::string&& lbl, char c) {
      label(lbl);
      info_MM(rMs, c);
      std::cerr << '\n';
    };
    const auto rstmm_row = [=](std::string&& lbl, char c) {
      label(lbl);
      if (c != 'h') info_STMM(rMs, c);
      std::cerr << '\n';
    };
    const auto tmm_row = [=](std::string&& lbl, char c) {
      label(lbl);
      info_MM(tMs, c);
      std::cerr << '\n';
    };
    const auto tstmm_row = [=](std::string&& lbl, char c) {
      label(lbl);
      if (c != 'h') info_STMM(tMs, c);
      std::cerr << '\n';
    };
    const auto filter_row = [=](std::string&& lbl, char c) {
      label(lbl);
      if (c != 'h') info_filter(c);
      std::cerr << '\n';
    };
    const auto file_row = [=](std::string&& lbl, std::string&& s1,
                              std::string&& s2) {
      label(lbl);
      if (s1.size() == 1) {
        char c1 = s1[0];
        char c2 = s2[0];
        info_file(c1);
        info_file(c2);
      } else {
        header(s1);
        header(s2);
      }
      std::cerr << '\n';
    };

    toprule();
    rmm_row(bold("Ref Model           "), 'm');
    midrule();
    rmm_row("Context size (k)", 'k');
    bool hasSketch{false};
    for (const auto& e : rMs)
      if (e.cont == Container::sketch_8) {
        hasSketch = true;
        break;
      }
    if (hasSketch) {
      rmm_row("Sketch width (w)", 'w');
      rmm_row("Sketch depth (d)", 'd');
    }
    rmm_row("Inv. repeat  (ir)", 'i');
    rmm_row("Alpha        (a)", 'a');
    rmm_row("Gamma        (g)", 'g');
    botrule();  // cerr << '\n';

    {
      bool show_rstmm = false;
      for (const auto& model : rMs)
        if (model.child) {
          show_rstmm = true;
          break;
        }
      if (show_rstmm) {
        toprule();
        rstmm_row(bold("Ref Substituttional Model           "), 'h');
        midrule();
        rstmm_row("No. Subst.   (t)", 't');
        rstmm_row("Inv. repeat  (ir)", 'i');
        rmm_row("Alpha        (a)", 'a');
        rmm_row("Gamma        (g)", 'g');
        botrule();  // cerr << '\n';
      }
    }

    toprule();
    tmm_row(bold("Tar Model           "), 'm');
    midrule();
    rmm_row("Context size (k)", 'k');
    hasSketch = false;
    for (const auto& e : tMs)
      if (e.cont == Container::sketch_8) {
        hasSketch = true;
        break;
      }
    if (hasSketch) {
      rmm_row("Sketch width (w)", 'w');
      rmm_row("Sketch depth (d)", 'd');
    }
    tmm_row("Inv. repeat  (ir)", 'i');
    rmm_row("Alpha        (a)", 'a');
    rmm_row("Gamma        (g)", 'g');
    botrule();  // cerr << '\n';

    {
      bool show_tstmm = false;
      for (const auto& model : tMs)
        if (model.child) {
          show_tstmm = true;
          break;
        }
      if (show_tstmm) {
        toprule();
        tstmm_row(bold("Tar Substituttional Model           "), 'h');
        midrule();
        rstmm_row("No. Subst.   (t)", 't');
        tstmm_row("Inv. repeat  (ir)", 'i');
        rmm_row("Alpha        (a)", 'a');
        rmm_row("Gamma        (g)", 'g');
        botrule();  // cerr << '\n';
      }
    }

    if (!par->compress) {
      toprule();
      filter_row(bold("Filter & Segment"), 'h');
      midrule();
      filter_row("Window function", 'f');
      if (par->manFilterScale) filter_row("Filter scale", 's');
      if (!par->manFilterScale) filter_row("Window size", 'w');
      if (par->manThresh) filter_row("Threshold", 't');
      botrule();  // cerr << '\n';
    }

    toprule();
    file_row(bold("File                "), bold("Name            "),
             bold("Size (B)"));
    midrule();
    file_row("Reference", "r", "1");
    file_row("Target", "t", "2");
    botrule();
  }

  void convert_to_seq(std::string in, std::string out, FileType const& type) {
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

  void prepare_data() {
    if (par->refType == FileType::seq && par->tarType == FileType::seq) return;

    std::cerr << bold(
        "====[ PREPARE DATA ]==================================\n");
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

  void make_ir_consistent(std::unique_ptr<FCM>& models) {
    for (auto& ref_model : models->rMs) {
      ref_model.ir = par->ID;
      if (ref_model.child) ref_model.child->ir = par->ID;
    }
    for (auto& tar_model : models->tMs) {
      tar_model.ir = par->ID;
      if (tar_model.child) tar_model.child->ir = par->ID;
    }
  }

  void compress_ref_free(std::unique_ptr<FCM>& models,
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

  auto process_round_impl(uint64_t& current_pos_row) -> uint64_t {
    par->refName = file_name(par->ref);
    par->tarName = file_name(par->tar);
    auto models = std::make_unique<FCM>(par);
    make_ir_consistent(models);

    // Build models and Compress
    models->store(par, round);
    models->compress(par, round);

    // Filter and segment
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

    // Reference-free compression, if applicable
    compress_ref_free(models, filter);

    current_pos_row += filter->nSegs;
    return filter->nSegs;
  }

  void process_round3(std::string const& ref, std::string const& tar,
                      uint64_t& current_pos_row) {
    if (num_seg_round[1] == 0) return;

    if (par->deep) {
#pragma omp ordered
      if (par->verbose)
        std::cerr << "    " << italic("Deep compression") << '\n';
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

  void process_round2(std::string const& ref, std::string const& tar,
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

  void process_round1() {
    std::string ref_round1 = par->ref;
    std::string tar_round1 = par->tar;
    uint64_t current_pos_row = 0;
    // #pragma omp parallel for ordered schedule(static, 1) //todo
    for (par->ID = 0; par->ID <= 1; ++par->ID) {
      round = 1;
      if (par->verbose && par->showInfo) {
        show_info(par);
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

  void write_pos_file() {
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

  void process() {
    prepare_data();    // FASTA/FASTQ to seq, if applicable
    process_round1();  // Runs implicitly process_round2 and process_round3
    remove_temp_seq(par);
    write_pos_file();
  }

 public:
  void exe(int argc, char* argv[]) {
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
};

int main(int argc, char* argv[]) {
  activate_fast_io();

  try {
    const auto t0{now()};
    application{}.exe(argc, argv);
    const auto t1{now()};
    std::cerr << "Total time: " << hms(t1 - t0);
  } catch (std::exception& e) {
    std::cerr << e.what();
  } catch (...) {
    return EXIT_FAILURE;
  }

  return 0;
}