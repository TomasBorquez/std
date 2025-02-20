#pragma once

#include "types.h"
#include "logger.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(condition, message) customAssert(condition, message, __FILE__, __LINE__)
void customAssert(bool condition, char *message, const char *file, int line);
