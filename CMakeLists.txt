cmake_minimum_required(VERSION 3.12)

set(GOOGLETEST_VERSION 1.15.2)

project(starship VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost COMPONENTS json)

find_package(OpenSSL REQUIRED)

find_package(jwt-cpp CONFIG REQUIRED)

#enable_testing() #to  discover tests in test explorer 

#append_coverage_compiler_flags()

#include(FetchContent)
#FetchContent_Declare(
#  googletest
#  GIT_REPOSITORY https://github.com/google/googletest.git
#  GIT_TAG        v1.14.0
#)
#FetchContent_MakeAvailable(googletest)

#add_subdirectory(googletest) #add googletest subdirectory

# Настраиваем флаги для покрытия
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

include_directories(googlemock/include) # this is so we can #include <gtest/gtest.h>

add_executable(starship main.cpp)

#target_link_libraries(game PRIVATE ${Boost_LIBRARIES} ${OpenSSL_LIBRARIES} jwt-cpp::jwt-cpp)

target_link_libraries(starship PRIVATE ${OpenSSL_LIBRARIES} jwt-cpp::jwt-cpp)

target_link_libraries(starship PRIVATE ${Boost_LIBRARIES})
target_link_libraries(starship PRIVATE gtest) # link google test to this executable
target_link_libraries(starship PRIVATE gmock) # link google mock to this executable

include_directories(${Boost_INCLUDE_DIRS})


include(GoogleTest)

gtest_discover_tests(starship) # discovers tests by asking the compiled test executable to enumerate its tests

