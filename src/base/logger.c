#include "logger.h"

static void logInfo(const char *format, ...) {
  printf("%s", GRAY);
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("%s\n", RESET);
}

static void logWarn(const char *format, ...) {
  printf("%s", ORANGE);
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("%s\n", RESET);
}

static void logError(const char *format, ...) {
  printf("%s", RED);
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("%s\n", RESET);
}

static void logSuccess(const char *format, ...) {
  printf("%s", GREEN);
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("%s\n", RESET);
}

void LogInit() {
#ifdef COMPILER_MSVC
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);
#endif
}

LoggerVT logger = {
  .Info = logInfo,
  .Warn = logWarn,
  .Error = logError,
  .Success = logSuccess,
};
