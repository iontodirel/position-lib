cmake_minimum_required (VERSION 3.8)

project (position_tests VERSION 1.0 LANGUAGES CXX)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
	cmake_policy(SET CMP0135 NEW)
endif()

# This is set for Google Test
set(CMAKE_CXX_STANDARD 23)

if(MSVC)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

include(FetchContent)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(position_tests "position_tests.cpp")
target_link_libraries(position_tests GTest::gtest_main gtest gtest_main)

set_property(TARGET position_tests PROPERTY CXX_STANDARD 23)

include(GoogleTest)

gtest_discover_tests(position_tests)

#
# Build only tests
#

add_executable (position_example_with_namespace "use_with_namespace.cpp")
add_executable (position_example_without_namespace "use_without_namespace.cpp")
add_executable (position_example_compile_in_tu "use_in_tu.h" "use_in_tu.cpp" "compile_in_tu.cpp")
