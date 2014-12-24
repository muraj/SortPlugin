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

#ifndef __SORT_ALGO_H__
#define __SORT_ALGO_H__

#include <vector>
#include <string>
#include "plugin_builder.h"


class SortAlgorithm {
public:
  typedef double value_type;
  SortAlgorithm() {}
  virtual ~SortAlgorithm() {}
  virtual void sort(value_type* a, size_t N) = 0;
  static std::vector<std::string> kinds() {
    std::vector<std::string> ret;
    PluginBuilder<SortAlgorithm>::FactoryMap& f = PluginBuilder<SortAlgorithm>::factoryMap();
    for(PluginBuilder<SortAlgorithm>::FactoryMap::const_iterator it = f.begin(); it != f.end(); ++it)
      ret.push_back(it->first);   // Get all the keys
    return ret;
  }
  static SortAlgorithm* create(const std::string& kind) {
    return PluginBuilder<SortAlgorithm>::build(kind);
  }
};

#endif // __SORT_ALGO_H__

