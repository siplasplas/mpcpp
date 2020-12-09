cmake_minimum_required(VERSION 3.5)
project(mpcpp)

set(CMAKE_CXX_STANDARD 14)

add_library(mpcpp fr_numeric_limits.cpp mpfrcpp.cpp gmpcpp.cpp outformat.cpp)