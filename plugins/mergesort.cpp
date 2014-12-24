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
#include <iostream>

MergeSort::MergeSort() : SortAlgorithm() {

}

MergeSort::~MergeSort() {

}

static int bsearch(const SortAlgorithm::value_type& v, SortAlgorithm::value_type* a, size_t s, size_t e, bool before_equals) {
  if(s>e) return s;
  size_t m = s + (e-s)/2;
  if(a[m] < v || (a[m] == v && before_equals))
    return bsearch(v, a, m+1, e, before_equals);
  else if(m > 0)
    return bsearch(v, a, s, m-1, before_equals);
  else
    return 0;
}

// Out of place merge...
static void merge(SortAlgorithm::value_type* a, SortAlgorithm::value_type* aux, size_t m, size_t n) {
  // Copy to aux array
  for(size_t i=0;i<n;i++) aux[i] = a[i];
#if 0
  for(size_t i=0;i<m;i++) {
    size_t off = bsearch(aux[i], aux+m, 0, n-m-1, true);
    a[i+off] = aux[i];
  }
  for(size_t i=m;i<n;i++) {
    size_t off = bsearch(aux[i], aux, 0, m-1, false);
    a[(i-m)+off] = aux[i];
  }
#else
  size_t x=0,y=m, i=0;
  for(; i<n && x<m && y<n; i++)
    a[i] = (aux[x] < aux[y] ? aux[x++] : aux[y++]);
  for(; i<n && x<m; i++)
    a[i] = aux[x++];
  for(; i<n && y<n; i++)
    a[i] = aux[y++];
#endif
}

static void mergesort(SortAlgorithm::value_type* a, SortAlgorithm::value_type* aux, size_t n) {
  if(n<2) return;
  size_t mid = n/2;
  ::mergesort(a, aux, mid);
  ::mergesort(a+mid, aux+mid, n-mid);
  ::merge(a, aux, mid, n);
}

void MergeSort::sort(value_type* a, size_t n) {
  std::vector<value_type> aux(n);
  ::mergesort(a, aux.data(), n);
}

REGISTER_PLUGIN(SortAlgorithm, MergeSort)
