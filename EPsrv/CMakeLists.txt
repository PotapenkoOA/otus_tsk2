cmake_minimum_required(VERSION 3.10.0)
project(game VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost COMPONENTS json)

find_package(OpenSSL REQUIRED)

find_package(jwt-cpp CONFIG REQUIRED)


include_directories(${Boost_INCLUDE_DIRS})

add_executable(game main.cpp)

target_link_libraries(game PRIVATE ${Boost_LIBRARIES} ${OpenSSL_LIBRARIES} jwt-cpp::jwt-cpp)

