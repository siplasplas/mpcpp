cmake_minimum_required(VERSION 3.17)
project(examples)

set(CMAKE_CXX_STANDARD 14)

add_definitions("-Werror=return-type")

add_executable(pi pi.cpp)

target_link_libraries(pi gmp)