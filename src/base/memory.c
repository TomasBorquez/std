#include "memory.h"

static ptr_t alignForward(const ptr_t ptr) {
  ptr_t p, a, modulo;

  p = ptr;
  a = (ptr_t) DEFAULT_ALIGNMENT;
  // Same as (p % a) but faster as 'a' is a power of two
  modulo = p & (a - 1);

  if (modulo != 0) {
    // If 'p' address is not aligned, push the address to the
    // next value which is aligned
    p += a - modulo;
  }
  return p;
}

static void *arenaAlloc(Arena *a, const size size) {
  // Align 'currPtr' forward to the specified alignment
  ptr_t currPtr = (ptr_t) a->buffer + (ptr_t) a->currOffset;
  ptr_t offset = alignForward(currPtr);
  offset -= (ptr_t) a->buffer; // Change to relative offset

  ASSERT(offset + size <= a->bufferLength, "Arena ran out of space left");

  void *ptr = &a->buffer[offset];
  a->prevOffset = offset;
  a->currOffset = offset + size;

  // Zero new memory by default
  memset(ptr, 0, size);
  return ptr;
}

static void arenaFree(Arena *arena) {
  free(arena->buffer);
}

Arena ArenaInit(const size size) {
  return (Arena){
    .Alloc = arenaAlloc,
    .Free = arenaFree,
    .buffer = (u8 *) malloc(size),
    .bufferLength = size,
    .prevOffset = 0,
    .currOffset = 0,
  };
}
