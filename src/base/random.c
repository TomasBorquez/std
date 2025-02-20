#include "random.h"

static u64 seed = 0;

void RandomInit() {
  seed = Now();
  srand(seed);
}

static u64 randomGetSeed() {
  return seed;
}

static void randomSetSeed(u64 newSeed) {
  seed = newSeed;
}

static i32 randomInteger(i32 min, i32 max) {
  ASSERT(min <= max, "min should always be less than or equal to max");
  ASSERT(max - min <= INT32_MAX - 1, "range too large");

  i32 range = max - min + 1;

  // Calculate scaling factor to avoid modulo bias
  uint32_t buckets = RAND_MAX / range;
  uint32_t limit = buckets * range;

  // Reject numbers that would create bias
  uint32_t r;
  do {
    r = rand();
  } while (r >= limit);

  return min + (r / buckets);
}

static float randomFloat(float min, float max) {
  ASSERT(min <= max, "min must be less than or equal to max");
  float normalized = (float) rand() / RAND_MAX;
  return min + normalized * (max - min);
}

RandomVT random = {
  .GetSeed = randomGetSeed,
  .SetSeed = randomSetSeed,
  .Integer = randomInteger,
  .Float = randomFloat,
};
