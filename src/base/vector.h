#pragma once

#include "types.h"
#include "assert.h"

typedef struct SVectorVT {
  StrVector *(*New)();
  void (*Push)(StrVector *vector, String *value);
  String (*Pop)(StrVector *vector);
  void (*Unshift)(StrVector *vector, String *value);
  String (*Shift)(StrVector *vector);
  void (*Insert)(StrVector *vector, size index, String *value);
  String *(*At)(StrVector *vector, size index);
  void (*Free)(StrVector *vector);
} SVectorVT;

extern SVectorVT sVec;
