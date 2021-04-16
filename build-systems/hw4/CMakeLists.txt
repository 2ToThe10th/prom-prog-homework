cmake_minimum_required(VERSION 3.0)
project(hw4)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hw4_without_code_generation src/main_without_code_generation.cpp src/map_without_code_generation.cpp src/map_without_code_generation.h src/Map.h src/map_image.cpp src/map_image.h)
target_link_libraries(hw4_without_code_generation ${OpenCV_LIBS})

add_custom_command(
        OUTPUT src/map_with_code_generation.h
        COMMAND python3 src/map_generator.py src/map_with_code_generation.template map.png src/map_with_code_generation.h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS src/map_with_code_generation.template map.png
        COMMENT "Generating map files from map.png"
)

add_executable(hw4_with_code_generation src/main_with_code_generation.cpp src/map_with_code_generation.cpp src/map_with_code_generation.h src/Map.h src/map_image.cpp src/map_image.h)
target_link_libraries(hw4_with_code_generation ${OpenCV_LIBS})
