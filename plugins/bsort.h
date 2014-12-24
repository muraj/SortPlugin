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

#ifndef __BSORT_H__
#define __BSORT_H__

#include "sort_algo.h"

class BubbleSort : public SortAlgorithm {
public:
  BubbleSort();
  virtual ~BubbleSort();
  void sort(value_type* a, size_t N);
};

class InsertionSort : public SortAlgorithm {
public:
  InsertionSort();
  virtual ~InsertionSort();
  void sort(value_type* a, size_t N);
};

#endif // __BSORT_H__
