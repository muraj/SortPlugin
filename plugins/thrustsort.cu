//  Copyright (c) 2014 Cory Perry
//  This file is part of CXXPluginFramework.
//
//  CXXPluginFramework is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  CXXPluginFramework is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with CXXPluginFramework.  If not, see <http://www.gnu.org/licenses/>.

#include "thrustsort.h"
#include "plugin_builder.h"
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/copy.h>

ThrustSort::ThrustSort() : SortAlgorithm() {

}

ThrustSort::~ThrustSort() {

}

void ThrustSort::sort(value_type* a, size_t n) {
  thrust::device_vector<value_type> d_vec(a, a+n);
  thrust::sort(d_vec.begin(), d_vec.end());
  thrust::copy(d_vec.begin(), d_vec.end(), a);
}

REGISTER_PLUGIN(SortAlgorithm, ThrustSort)
