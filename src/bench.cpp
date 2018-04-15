//
// Created by morteza on 11-04-2018.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <array>
#include <vector>
#include <numeric>
#include <limits>
using std::string;
using std::to_string;
using std::vector;
using std::array;
using std::cerr;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::istringstream;
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;
#define IGNORE_LINE(in) \
        (in).ignore(std::numeric_limits<std::streamsize>::max(), '\n')

// Global
static const string repName = "report";

class gnuplot
{
 public:
  gnuplot () {
    gnuplotpipe = popen("gnuplot -persist", "w");
    if (!gnuplotpipe)
      cerr << "Gnuplot not found!";
  }
  ~gnuplot () {
    fprintf(gnuplotpipe, "exit\n");
    pclose(gnuplotpipe);
  }
  void operator<< (const string& cmd) {
    fprintf(gnuplotpipe, "%s\n", cmd.c_str());
    fflush(gnuplotpipe);
  }
  
 private:
  FILE* gnuplotpipe;
};


void run (const string& cmd) {
  if (std::system(cmd.c_str()) != 0)
    throw std::runtime_error("Error: failed to execute.");
}

void runGnuplot (const string& cmd) {
  string gnuplotCmd = "gnuplot -p -e ";    // -p=-persist
  gnuplotCmd += "\"" + cmd + "\"";
  if (std::system(gnuplotCmd.c_str()) != 0)
    throw std::runtime_error("Error: failed to execute.");
}

string exec (const char* cmd) {
  const u32 bufSize = 128;
  array<char, bufSize> buffer{};
  string result;
  std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
  if (!pipe)
    throw std::runtime_error("Error: popen() failed!");
  while (!feof(pipe.get())) {
    if (fgets(buffer.data(), bufSize, pipe.get()) != nullptr)
      result += buffer.data();
  }
  return result;
}

void memUsage (u8 k) {//todo

}

string combine (u8 ir, u8 k, float alpha) {
  return to_string(ir)+","+to_string(k)+","+to_string(alpha);
}

void plot () {
  ifstream ifs(repName);
  vector<u16>    vir    {};
  vector<u16>    vk     {};
  vector<float>  valpha {};
  vector<double> vent   {};
  vector<string> vtar   {};
  vector<string> vref   {};
  
  IGNORE_LINE(ifs);  // Ignore the header line
  for (string line; getline(ifs, line);) {
    u16 ir;  u16 k;  float alpha;  double ent;  string tar;  string ref;
    
    istringstream ss(line);
    ss >> tar >> ref >> ir >> k >> alpha >> ent;
    
    vir.emplace_back(ir);   vk.emplace_back(k);     valpha.emplace_back(alpha);
    vent.emplace_back(ent); vtar.emplace_back(tar); vref.emplace_back(ref);
  }
  
  string cmd = "plot '-' with lines\n";
  for(int i=0;i<3;i+=2) cmd+=to_string(vk[i])+" "+to_string(vent[i])+"\n";
  cmd+="e";
  cerr<<cmd;
//  runGnuplot(cmd);
  gnuplot p;
  p << cmd;
//  p << "plot '-' using 1:2 with lines";
//  p << "1 4";
//  p << "2 5";
//  p << "e";
  
  
//  for (auto a:vir)     cerr << a << ' ';
//  cerr << '\n';
//  for (auto a:vk)      cerr << a << ' ';
//  cerr << '\n';
//  for (auto a:valpha)  cerr << a << ' ';
//  cerr << '\n';
//  for (auto a:vent)    cerr << a << ' ';
//  cerr << '\n';
  
  
  ifs.close();
}

void writeHeader (bool append) {
  ofstream f;
  if (append)  f.open(repName, ofstream::app);
  else         f.open(repName);
  f << "tar\tref\tir\tk\talpha\tH\n";
  f.close();
}


int main (int argc, char* argv[])
{
  try {bool writeHdr=false, execute=false, plt=true;
  
//  static std::vector<std::vector<u8>> level;
    vector<u8>    vir    {0, 1};
    vector<u8>    vk     {1, 2};
    vector<float> valpha {1, 0.1};
//    vector<u8>    vir    {0, 1};
//    vector<u8>    vk;    vk.resize(14);    std::iota(vk.begin(),vk.end(),1);
//    vector<float> valpha {1, 0.1, 0.01, 0.001};
    constexpr bool bVerbose {false};
    static string verbose="";  if (bVerbose) verbose=" -v";
    constexpr bool bRep {true};
    static string report="";  if (bRep) report=" -R "+repName;
    static const vector<string> vTar    {"A"};
    static const vector<string> vRef    {"A"};
//    static const vector<string> vLevel  {"0", "1"};
//    static const string model
////      {"0,14,0.001"};
////      {"0,12,0.6:1,14,0.9:0,5,0.2:1,17,0.4,20,5"};
////    {"0,12,0.6:0,5,0.2:1,17,0.4,20,5:1,14,0.9"};

    
    if (writeHdr) {
    writeHeader(false);
    }
    if (execute) {
    for (u8 tIdx=0; tIdx!=vTar.size(); ++tIdx) {
//      for (u8 lIdx=0; lIdx!=vLevel.size(); ++lIdx)
      for (const auto& ir : vir)
        for (const auto& k : vk)
          for (const auto& a : valpha) {
            string model {combine(ir, k, a)};

//            cerr << model<<'\n';
        run("./smashpp"
            " -t " + vTar[tIdx] +
            " -r " + vRef[tIdx] +
            " -m " + model +
//            " -l " + vLevel[lIdx] +
            report +
            verbose
        );
          }
    }
    }
    if (plt) {
      plot();// Plot results
    }
  }
  catch (std::exception& e) { cerr << e.what(); }
  
  return 0;
}