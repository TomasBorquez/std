#pragma once

#include "types.h"
#include "logger.h"
#include <stdbool.h>

static int total_tests = 0;
static int passed_tests = 0;
static bool current_test_failed = false;
static const char *current_test_name = NULL;
static int current_test_assertions = 0;

#define RUN_TEST(test_func) do { \
    current_test_name = #test_func; \
    current_test_failed = false; \
    current_test_assertions = 0; \
    logger.Info("Running %s:", current_test_name); \
    test_func(); \
    if (!current_test_failed) { \
        passed_tests++; \
        logger.Success("  PASSED: %s (%d assertions)\n", current_test_name, current_test_assertions); \
    } \
    total_tests++; \
} while(0)

#define UNITY_BEGIN() do { \
    total_tests = 0; \
    passed_tests = 0; \
    LogInit(); \
    logger.Info("Test Suite Started\n"); \
} while(0)

#define UNITY_END() do { \
    logger.Info("Test Summary:"); \
    logger.Info("  Total tests: %d", total_tests); \
    logger.Success("  Passed: %d", passed_tests); \
    if (total_tests - passed_tests > 0) { \
        logger.Error("  Failed: %d", total_tests - passed_tests); \
    } \
    if (passed_tests == total_tests) { \
        return 0; \
    } else { \
        return 1; \
    } \
} while(0)

#define ASSERT_EQUAL(expected, actual) do { \
    current_test_assertions++; \
    if (((expected)) != ((actual))) { \
        logger.Error("  FAILED: %s, expected %d actual %d\n", current_test_name, ((expected)), ((actual))); \
        current_test_failed = true; \
        return; \
    } \
} while(0)
