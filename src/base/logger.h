#pragma once

#include "types.h"
#include <stdio.h>
#include <Windows.h>
#include <stdarg.h>

#define RESET "\x1b[0m"
#define GRAY "\x1b[0;37m"
#define RED "\x1b[0;31m"
#define GREEN "\x1b[0;32m"
#define ORANGE "\x1b[0;33m"

#ifdef __clang__
#define FORMAT_CHECK(fmt_pos, args_pos) __attribute__((format(printf, fmt_pos, args_pos)))
#else
#define FORMAT_CHECK(fmt_pos, args_pos)
#endif

typedef struct {
		void (*Info)(const char *format, ...) FORMAT_CHECK(1, 2);

		void (*Warn)(const char *format, ...) FORMAT_CHECK(1, 2);

		void (*Error)(const char *format, ...) FORMAT_CHECK(1, 2);

		void (*Success)(const char *format, ...)FORMAT_CHECK(1, 2);
} LoggerVT;

LoggerVT logger;

void LogInit();
