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

#include "qsort.h"
#include "plugin_builder.h"


QSort::QSort() : SortAlgorithm() {

}

QSort::~QSort() {

}

void QSort::sort(value_type* a, size_t n) {
  if(n < 2) return;
  value_type p = a[n/2];  // TODO: change to rand...
  value_type* lo = a;
  value_type* hi = a + n - 1;
  while(lo <= hi) {
    while(*lo < p && lo <= hi) lo++;
    while(*hi > p && lo <= hi) hi--;
    if(lo <= hi) {
      std::swap(*hi, *lo);
      hi--; lo++;
    }
  }
  this->sort(a,  (hi - a) + 1);
  this->sort(lo, (a - lo) + n);
}

REGISTER_PLUGIN(SortAlgorithm, QSort)
