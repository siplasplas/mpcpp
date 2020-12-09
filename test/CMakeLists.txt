cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 17)

add_definitions("-Werror=return-type")

add_executable(test gout.cpp frout.cpp lambda.cpp)

target_link_libraries(test mpcpp gmp mpfr)