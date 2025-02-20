#pragma once

#include "types.h"
#include "assert.h"
#include "vector.h"
#include "memory.h"
#include <string.h>

typedef struct StrVT {
		void (*SetMaxSize)(size size);
		String (*New)(struct Arena *arena, char *str);
		String (*NewSize)(struct Arena *arena, char *str, size len); // Without null terminator
		void (*Copy)(String *destination, String *source);
		StrVector *(*Split)(struct Arena *arena, String *string, String *delimiter);
		bool (*Equal)(String *string1, String *string2);
		String (*Concat)(struct Arena *arena, String *string1, String *string2);
		void (*ToUpper)(String *string1);
		void (*ToLower)(String *string1);
		bool (*IsNull)(String *string);
		void (*Trim)(String *string);
		void (*Slice)(String *str, i32 start, i32 end);
} StrVT;

extern StrVT str;
