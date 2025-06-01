cmake_minimum_required(VERSION 3.10.0)

set(GOOGLETEST_VERSION 1.15.2)

project(autorization VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost COMPONENTS json)

find_package(OpenSSL REQUIRED)

find_package(jwt-cpp CONFIG REQUIRED)

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>
include_directories(googlemock/include) # this is so we can #include <gtest/gtest.h>


include_directories(${Boost_INCLUDE_DIRS})

add_executable(autorization main.cpp)

target_link_libraries(autorization PRIVATE ${Boost_LIBRARIES} ${OpenSSL_LIBRARIES} jwt-cpp::jwt-cpp)
target_link_libraries(autorization PRIVATE gtest) # link google test to this executable
target_link_libraries(autorization PRIVATE gmock) # link google mock to this executable

include(GoogleTest)

gtest_discover_tests(autorization) # discovers tests by asking the compiled test executable to enumerate its tests

