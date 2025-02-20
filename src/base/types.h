#pragma once

#include <stdint.h>

typedef size_t size;

typedef struct {
  size length; // Does not include null terminator
  char *data;
} String;

typedef struct {
  String *data;
  size length;
  size capacity;
} StrVector;

// Unsigned int types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Signed int types
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

// Regular int types
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uintptr_t ptr_t;

// Floating point types
typedef float f32;
typedef double f64;

// Boolean defines
#define null NULL  // Changed to proper null pointer definition
#define bool  _Bool
#define false 0
#define true  1

// Maximum values for integer types
#define U8_MAX  UINT8_MAX
#define U16_MAX UINT16_MAX
#define U32_MAX UINT32_MAX
#define U64_MAX UINT64_MAX

#define S8_MAX  INT8_MAX
#define S8_MIN  INT8_MIN
#define S16_MAX INT16_MAX
#define S16_MIN INT16_MIN
#define S32_MAX INT32_MAX
#define S32_MIN INT32_MIN
#define S64_MAX INT64_MAX
#define S64_MIN INT64_MIN

#define I8_MAX  INT8_MAX
#define I8_MIN  INT8_MIN
#define I16_MAX INT16_MAX
#define I16_MIN INT16_MIN
#define I32_MAX INT32_MAX
#define I32_MIN INT32_MIN
#define I64_MAX INT64_MAX
#define I64_MIN INT64_MIN

#if defined(__clang__)
#  define COMPILER_CLANG
#elif defined(_MSC_VER)
#  define COMPILER_MSVC
#elif defined(__GNUC__)
#  define COMPILER_GCC
#endif

#if defined(COMPILER_CLANG)
#  define FILE_NAME __FILE_NAME__
#else
#  define FILE_NAME __FILE__
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#  define PLATFORM_WIN
#elif defined(__linux__) || defined(__gnu_linux__)
#  define PLATFORM_LINUX
#else
#  error "The codebase only supports windows and linux"
#endif
#define PATH_MAX 4096

#ifdef PLATFORM_WIN
#  include <direct.h>
#  define GetCwd _getcwd
#elif defined(PLATFORM_LINUX)
#  include <unistd.h>
#  define GetCwd getcwd
#endif

// TODO: Add time variables in ms
