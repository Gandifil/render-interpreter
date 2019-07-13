cmake_minimum_required(VERSION 3.13)
project(console_cpu_render)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(console_cpu_render ${SOURCES} src/engine/math/OBJReader.h src/engine/Model.cpp src/engine/Model.h src/engine/Frame.cpp src/engine/Frame.h src/utils.h)
