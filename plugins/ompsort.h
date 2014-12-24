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

#ifndef __OMPSORT_H__
#define __OMPSORT_H__

#include "sort_algo.h"

class OMPQSort : public SortAlgorithm {
public:
  OMPQSort();
  virtual ~OMPQSort();
  void sort(value_type* a, size_t N);
};

class OMPMSort : public SortAlgorithm {
public:
  OMPMSort();
  virtual ~OMPMSort();
  void sort(value_type* a, size_t N);
};

#endif // __OMPSORT_H__
