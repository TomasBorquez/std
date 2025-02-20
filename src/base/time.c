#include "time.h"

i64 Now() {
#ifdef PLATFORM_WIN
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  LARGE_INTEGER li;
  li.LowPart = ft.dwLowDateTime;
  li.HighPart = ft.dwHighDateTime;
  // Convert Windows FILETIME (100-nanosecond intervals since January 1, 1601)
  // to UNIX timestamp in milliseconds
  i64 currentTime = (li.QuadPart - 116444736000000000LL) / 10000;
#else
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  i64 currentTime = (ts.tv_sec * 1000LL) + (ts.tv_nsec / 1000000LL);
#endif
  ASSERT(currentTime != -1, "currentTime should never be -1");
  return currentTime;
}

void WaitTime(i32 ms) {
#ifdef PLATFORM_WIN
  Sleep(ms);
#else
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  nanosleep(&ts, NULL);
#endif
}
