#include "std.h"
#include "logger.h"
#include "random.h"

static void stdBegin() {
  LogInit();
  RandomInit();
}

static void stdEnd() { }

STDVT std = {
  .Begin = stdBegin,
  .End = stdEnd
};
