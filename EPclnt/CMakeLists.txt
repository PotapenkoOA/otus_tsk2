cmake_minimum_required(VERSION 3.12)

set(GOOGLETEST_VERSION 1.15.2)

project(EPsrv VERSION 0.1.0 LANGUAGES C CXX)

link_libraries(ws2_32 wsock32)

add_executable(EPsrv main.cpp)

