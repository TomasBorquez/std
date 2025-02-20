#include "assert.h"

void customAssert(bool condition, char *message, const char *file, i32 line) {
	if (condition) {
		return;
	}

	logger.Error("Assert error: %s", message);
	logger.Error("File: %s, Line: %d", file, line);
	abort();
}