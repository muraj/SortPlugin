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

#include "bsort.h"
#include "plugin_builder.h"

BubbleSort::BubbleSort() : SortAlgorithm() {

}
BubbleSort::~BubbleSort() {

}

void BubbleSort::sort(value_type* a, size_t N) {
  for(size_t i=0;i<N;i++) {
    bool swapped = false;
    for(size_t j=i+1;j<N;j++)
      if(a[j] < a[j-1]) {
        std::swap(a[j], a[j-1]);
        swapped = true;
      }
    if(!swapped) break;
  }
}


InsertionSort::InsertionSort() : SortAlgorithm() {

}
InsertionSort::~InsertionSort() {

}

void InsertionSort::sort(value_type* a, size_t N) {
  for(size_t i=1; i<N; i++)
  {
    value_type v = a[i];
    size_t j = i;
    for(; j>0 && v < a[j-1]; j--)
      a[j] = a[j-1];
    a[j] = v;
  }
}

REGISTER_PLUGIN(SortAlgorithm, BubbleSort)
REGISTER_PLUGIN(SortAlgorithm, InsertionSort)
