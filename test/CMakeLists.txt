# The .cpp files for this executable
add_executable(tests
        tests-main.cpp ../src/puzzle_board.cc ../src/puzzle_board.h ../src/spf.cpp ../src/spf.h spf_tests.cpp puzzle_board_tests.cpp)

# Directories to search for header files
target_include_directories(tests PRIVATE
        ../src ../src/puzzle_board.h ../src/spf.h)

set_target_properties(tests PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

# Cross-platform compiler lints
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(tests PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(tests PRIVATE
            /W3)
endif ()