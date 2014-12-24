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

#ifndef __QSORT_H__
#define __QSORT_H__

#include "sort_algo.h"

class QSort : public SortAlgorithm {
public:
  QSort();
  virtual ~QSort();
  void sort(value_type* a, size_t N);
};

class MergeSort : public SortAlgorithm {
public:
  MergeSort();
  virtual ~MergeSort();
  void sort(value_type* a, size_t N);
};

#endif // __QSORT_H__
