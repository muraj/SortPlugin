#ifndef __TIMER_H__
#define __TIMER_H__

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


#ifdef _WIN32

#include <windows.h>
#include <assert.h>

class Timer {
  double PCFreq;
  __int64 stime, etime, diff, avg;
  size_t samples;
public:
  Timer() : samples(0), avg(0) {
    LARGE_INTEGER li
    bool rc = QueryPerformanceFrequency(&li);
    assert(rc && "Failed to query performance freqency");
    PCFreq = li.QuadPart;
  }
  void start() {
    LARGE_INTEGER li
    bool rc = QueryPerformanceCounter(&li);
    assert(rc && "Failed to query performance counter");
    stime = li.QuadPart;
  }
  void stop() {
    LARGE_INTEGER li
    bool rc = QueryPerformanceCounter(&li);
    assert(rc && "Failed to query performance counter");
    etime = li.QuadPart;

    diff = etime - stime;
    avg += (diff - avg) / (++samples);
  }
  double elapsed() const {
    return diff / PCFreq;
  }
  double average() const {
    return avg / PCFreq;
  }
};

#else // _WIN32

#include <time.h>

class Timer {
  struct timespec stime, etime, diff;
  double avg;
  size_t samples;
public:
  Timer() : avg(0.0), samples(0) {}
  void start() {
    clock_gettime(CLOCK_REALTIME, &stime);
  }
  void stop() {
    clock_gettime(CLOCK_REALTIME, &etime);
    timespec_sub(etime, stime, diff);
    avg += (elapsed() - avg) / (++samples);
  }
  double elapsed() const {
    return diff.tv_sec + diff.tv_nsec * 1.0e-9;
  }
  double average() const {
    return avg;
  }
private:
  bool timespec_sub(const struct timespec& x, const struct timespec& y, struct timespec& res) const {
    if(x.tv_nsec < y.tv_nsec) {
      res.tv_nsec = 1000000000 - (y.tv_nsec - x.tv_nsec); // Prevent overflow
      res.tv_sec = (x.tv_sec - 1) - y.tv_sec;
      return (x.tv_sec-1) < y.tv_sec;
    }
    else {
      res.tv_nsec = x.tv_nsec - y.tv_nsec;
      res.tv_sec = x.tv_sec - y.tv_sec;
      return x.tv_sec < y.tv_sec;
    }
  }
};

#endif  // _WIN32

#endif // __TIMER_H__
