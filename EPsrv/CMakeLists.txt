cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0144 NEW)
cmake_policy(SET CMP0167 OLD)

project(EPsrv VERSION 0.1.0 LANGUAGES C CXX)

set(GOOGLETEST_VERSION 1.15.2)

#set(BOOST_INCLUDEDIR "C:/boost_1_88_0")
#set(Boost_LIBRARY_DIR "../boost_1_88_0/stage/lib")


#find_package(Boost COMPONENTS REQUIRED asio)




add_executable(EPsrv main.cpp)


#find_library(ws2_32_LIBRARY_PATH ws2_32)
#add_executable(Executive ${exec_src})
#target_link_libraries(Executive ${ws2_32_LIBRARY_PATH})

