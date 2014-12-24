//  Copyright (c) 2014 Cory Perry
//  This file is part of SortPlugin.
//
//  SortPlugin is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  SortPlugin is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with SortPlugin.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <stdlib.h>
#include <time.h>

#include "plugin_loader.h"
#include "plugin_builder.h"

#include "sort_algo.h"
#include "timer.h"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

INIT_PLUGIN_BUILDER

typedef std::vector<SortAlgorithm::value_type> ArrayType;

template<typename T>
class GenRandom {
public:
  typedef T value_type;
  GenRandom() { srand(time(NULL)); }
  GenRandom(size_t seed) { srand(seed); }

  value_type operator()()
    { return rand() * T(1.0 / RAND_MAX); }
};


std::vector<PluginHandle> load_plugins(const std::string& dir) {
  static bool init = false;
  if(!init) { PLUGIN_INIT(); init = true; }
  std::vector<PluginHandle> ret;
  fs::directory_iterator end, it(dir);
  for(;it!=end;++it) {
    if(it->path().extension() != PLUGIN_EXT) continue;
    PluginHandle plugin = PLUGIN_LOAD(it->path().string().c_str());
    if(!plugin)
      std::cerr << "Failed to load " << it->path().string() << ": "
                << PLUGIN_ERR() << std::endl;
    else
      ret.push_back(plugin);
  }
  return ret;
}


int main(int argc, char** argv) {

  bool validate = true;
  size_t N = 1024*1024/sizeof(SortAlgorithm::value_type);
  size_t samples = 10;
  size_t seed = time(NULL);
  std::vector<std::string> rkinds;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "help message")
    ("type,t",     po::value(&rkinds),              "test this kind")
    ("sz,n",       po::value(&N)->default_value(N), "Size of data")
    ("seed,s",     po::value(&seed),                "Random seed to initialize rng")
    ("samples,m",  po::value(&samples)->default_value(samples), "Number of runs to average over")
    ("no-validate,V", "Skip validation of results");

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  } catch(boost::program_options::error& e) {
    std::cerr << e.what() << std::endl;
    // Print help later
    vm.insert(std::make_pair("help", po::variable_value()));
    po::notify(vm);
  }
  validate = vm.count("no-validate") == 0;

  if(vm.count("help")) std::cout << desc << '\n';

  std::vector<PluginHandle> plugins = load_plugins("plugins");
  std::cout << "Registered kinds:" << std::endl;
  std::vector<std::string> kinds = SortAlgorithm::kinds();
  for(size_t i=0;i<kinds.size();i++)
    std::cout << '\t' << kinds[i] << '\n';

  if(vm.count("help")) return 1;

  std::vector<std::string> test_kinds;
  if(rkinds.empty())
    test_kinds = kinds;
  else {
    std::set_intersection(kinds.begin(), kinds.end(), rkinds.begin(), rkinds.end(),
        std::back_inserter(test_kinds));
  }

  // Build initial array and sorted array
  std::cout << "Generating initial data" << std::endl;
  ArrayType ia(N);
  std::generate(ia.begin(), ia.end(), GenRandom<SortAlgorithm::value_type>(seed));

  ArrayType sa;
  if(validate) {    // use known sort to validate against
    sa = ia;
    std::sort(sa.begin(), sa.end());
  }

  ArrayType a(ia.size());   // Preallocate a

  std::cout << "Running tests" << std::endl;
  for(size_t i=0;i<test_kinds.size();i++) {
    Timer timer;
    std::cout << "Testing kind '" << test_kinds[i] << '\'' << std::endl;
    std::auto_ptr<SortAlgorithm> algo(SortAlgorithm::create(test_kinds[i]));
    // Startup performance metrics
    // Sort already!
    for(int j=0; j<samples;j++) {
      std::copy(ia.begin(), ia.end(), a.begin()); // Overwrite a with ia
      timer.start();
      algo->sort(a.data(), a.size());
      timer.stop();
    }
    // Gather performance metrics
    std::cout << "\tAvg: " << timer.average() << " seconds";
    // Check data
    std::cout << '\t'
              // Always pass and don't check if we're not validating results
              << ((!validate || sa == a) ? "PASS" : "FAIL")
              << '\n';
  }


  for(size_t i=0;i<plugins.size();i++)
  {
    PLUGIN_CLOSE(plugins[i]);
  }
  return 0;
}
