cmake_minimum_required(VERSION 3.12)

set(GOOGLETEST_VERSION 1.15.2)

project(EPsrv VERSION 0.1.0 LANGUAGES C CXX)

if(WIN32)
    link_libraries(ws2_32 wsock32)
endif()

add_executable(EPsrv main.cpp)


#find_library(ws2_32_LIBRARY_PATH ws2_32)
#add_executable(Executive ${exec_src})
#target_link_libraries(Executive ${ws2_32_LIBRARY_PATH})

