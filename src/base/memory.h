#pragma once

#include "types.h"
#include "assert.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct Arena Arena;

struct Arena {
		u8 *buffer;
		size bufferLength;
		size prevOffset;
		size currOffset;
		void *(*Alloc)(struct Arena *a, size size);
		void (*Free)(struct Arena *arena);
};

Arena ArenaInit(size size);

#ifndef DEFAULT_ALIGNMENT // This makes sure right alignment on 86/64 bits
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

char *IterateString(const char *str);