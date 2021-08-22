cmake_minimum_required(VERSION 3.0)
project (BlocksGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(external)
add_subdirectory(source)
