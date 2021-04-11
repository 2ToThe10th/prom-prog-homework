cmake_minimum_required(VERSION 2.8)

project(lib)
set(SOURCE_LIB lib.h lib.cpp)

add_library(lib SHARED ${SOURCE_LIB})
