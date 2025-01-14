cmake_minimum_required(VERSION 3.17)
project(SEP_MT)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory("festo/test")
add_subdirectory("festo" "festo/make_festo_output")