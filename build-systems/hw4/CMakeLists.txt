cmake_minimum_required(VERSION 3.0)
project(hw4)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hw4_without_code_generation src/main.cpp src/map_without_code_generation.cpp src/map_without_code_generation.h src/Map.h src/map_image.cpp src/map_image.h)
target_link_libraries(hw4_without_code_generation ${OpenCV_LIBS})

