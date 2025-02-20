#pragma once

#include "types.h"
#include "time.h"
#include <stdlib.h>

typedef struct {
  u64 (*GetSeed)(void);
  void (*SetSeed)(u64 newSeed);
  i32 (*Integer)(i32 min, i32 max); // ! Limited randomness
  float (*Float)(float min, float max); // ! Limited randomness
} RandomVT;

RandomVT random;

void RandomInit();
