cmake_minimum_required(VERSION 3.13)
project(console_cpu_render)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(console_cpu_render ${SOURCES})
