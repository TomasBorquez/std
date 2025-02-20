#include "vector.h"

// TODO: Use Malloc, Realloc and Free
static StrVector *strVectorNew() {
  StrVector *vector = malloc(sizeof(StrVector));
  vector->data = NULL;
  vector->length = 0;
  vector->capacity = 0;
  return vector;
}

static void strVectorPush(StrVector *vector, String *value) {
  if (vector->length == 0) {
    vector->data = (String *) malloc(sizeof(String) * 2);
    vector->capacity = 2;
    vector->length = 1;
    vector->data[0] = *value;
    return;
  }

  ASSERT(vector->length <= vector->capacity, "Vector length should never be higher than length (possible memory corruption)");
  if (vector->length == vector->capacity) {
    float factor = vector->capacity > 1024 ? 1.2 : 2.0;
    vector->capacity *= factor;
    vector->data = (String *) realloc(vector->data, vector->capacity * sizeof(String));
    ASSERT(vector->data != NULL, "Vector reallocation should never equal null, out of memory");
  }

  vector->data[vector->length] = *value;
  vector->length++;
}

static String strVectorPop(StrVector *vector) {
  ASSERT(vector->length > 0, "Vector length should never be <= 0");
  String result = vector->data[vector->length - 1];
  vector->length--;
  return result;
}

static void strVectorUnshift(StrVector *vector, String *value) {
  if (vector->length == 0) {
    vector->data = (String *) malloc(sizeof(String) * 2);
    vector->capacity = 2;
    vector->length = 1;
    vector->data[0] = *value;
    return;
  }

  ASSERT(vector->length <= vector->capacity, "Vector length should never be higher than length (possible memory corruption)");
  if (vector->length == vector->capacity) {
    float factor = vector->capacity > 1024 ? 1.2 : 2.0;
    vector->capacity *= factor;
    vector->data = (String *) realloc(vector->data, vector->capacity * sizeof(String));
    ASSERT(vector->data != NULL, "Vector reallocation should never equal null, out of memory");
  }

  memmove(&vector->data[1], // destination (one position to the right)
          &vector->data[0], // source (current position)
          vector->length * sizeof(String)); // size of block to move
  vector->data[0] = *value;
  vector->length++;
}

static String strVectorShift(StrVector *vector) {
  ASSERT(vector->length > 0, "Vector length should never be <= 0");
  String result = vector->data[0];
  memmove(&vector->data[0], // destination (current position)
          &vector->data[1], // source (one position right)
          (vector->length - 1) * sizeof(String)); // size of block to move
  vector->length--;
  return result;
}

static void strVectorInsert(StrVector *vector, size index, String *value) {
  ASSERT(index <= vector->length, "Vector index should never be higher than length");
  if (vector->length == 0) {
    vector->data = (String *) malloc(sizeof(String) * 2);
    vector->capacity = 2;
    vector->length = 1;
    vector->data[0] = *value;
    return;
  }

  ASSERT(vector->length <= vector->capacity, "Vector length should never be higher than length (possible memory corruption)");
  if (vector->length == vector->capacity) {
    float factor = vector->capacity > 1024 ? 1.2 : 2.0;
    vector->capacity *= factor;
    vector->data = (String *) realloc(vector->data, vector->capacity * sizeof(String));
    ASSERT(vector->data != NULL, "Vector reallocation should never equal null, out of memory");
  }

  memmove(&vector->data[index + 1],
          &vector->data[index],
          (vector->length - index) * sizeof(String));

  vector->data[index] = *value;
  vector->length++;
}

static String *strVectorAt(StrVector *vector, size index) {
  ASSERT(index < vector->length, "Vector Index out of bounds");
  return &vector->data[index];
}

static void strVectorFree(StrVector *vector) {
  ASSERT(vector != NULL, "Vector should never be null");
  ASSERT(vector->data != NULL, "Vector data should never be null");

  free(vector->data);
  free(vector);
}

SVectorVT sVec = {
  .New = strVectorNew,
  .Push = strVectorPush,
  .Pop = strVectorPop,
  .At = strVectorAt,
  .Free = strVectorFree,
  .Unshift = strVectorUnshift,
  .Shift = strVectorShift,
  .Insert = strVectorInsert
};
