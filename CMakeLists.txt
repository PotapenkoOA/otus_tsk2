cmake_minimum_required(VERSION 3.12)

set(GOOGLETEST_VERSION 1.15.2)

project(starship VERSION 0.1.0 LANGUAGES C CXX)

enable_testing() #to  discover tests in test explorer 

add_subdirectory(googletest) # add googletest subdirectory

#include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

#include_directories(googlemock/include) # this is so we can #include <gtest/gtest.h>

add_executable(starship test_move.cpp)

target_link_libraries(starship PRIVATE gtest) # link google test to this executable
target_link_libraries(starship PRIVATE gmock) # link google mock to this executable

include(GoogleTest)

gtest_discover_tests(starship) # discovers tests by asking the compiled test executable to enumerate its tests

