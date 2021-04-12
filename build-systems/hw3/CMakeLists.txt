cmake_minimum_required(VERSION 3.0)
project(SimpleLibrary)

include_directories(include)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SimpleLibrary_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SimpleLibrary_SOURCE_DIR}/lib)
add_subdirectory(src)
add_executable(Main main.cpp)
add_executable(MainLib main_lib.cpp)

target_link_libraries(MainLib buffer)

set_target_properties(
    Main MainLib
    PROPERTIES
    INSTALL_RPATH "$ORIGIN/../lib"
)

set_target_properties(
    buffer
    PROPERTIES
    PUBLIC_HEADER include/buffer.h
)


install(
	TARGETS Main MainLib buffer
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include
)
