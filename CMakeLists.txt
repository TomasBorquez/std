cmake_minimum_required(VERSION 3.30)
project(std C)
set(CMAKE_C_STANDARD 23)

option(RUN_TESTS "Build and run tests instead of main program" OFF)

file(GLOB SOURCE_FILES
        "src/base/*.c"
        "src/base/*.h"
)

if (RUN_TESTS)
    list(REMOVE_ITEM SOURCE_FILES "src/main.c")
    add_executable(std ${SOURCE_FILES} "src/tests/test-runner.c")
else ()
    list(REMOVE_ITEM SOURCE_FILES "src/tests/test-runner.c")
    add_executable(std ${SOURCE_FILES} "src/main.c")
endif ()

