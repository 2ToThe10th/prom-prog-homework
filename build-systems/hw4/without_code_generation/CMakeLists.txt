cmake_minimum_required(VERSION 3.0)
project(hw4)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hw4 main.cpp)
target_link_libraries(hw4 ${OpenCV_LIBS})

