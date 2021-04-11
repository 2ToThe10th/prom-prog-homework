cmake_minimum_required(VERSION 3.0.2)

project(CMakeHomework)

execute_process(
    COMMAND python3 preparing.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/A/
)

include_directories(.)
add_subdirectory(B)

add_executable(C C/main.cpp C/C.cpp A/index.cpp)
target_link_libraries(C lib)

find_package(GTest REQUIRED)
add_executable(CTest C/main_test.cpp C/test.cpp C/C.cpp A/index.cpp)

target_link_libraries(CTest lib ${GTEST_BOTH_LIBRARIES} pthread)

set_target_properties(
    C CTest
    PROPERTIES
    INSTALL_RPATH "$ORIGIN/../lib"
)

install(
	TARGETS C CTest lib
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
