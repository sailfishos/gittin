
project(libgit)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

configure_file(libgit.pc.in libgit.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libgit.pc DESTINATION lib/pkgconfig)

# Find the QtWidgets library
find_package(Qt5Core)

set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11")

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(examples)
