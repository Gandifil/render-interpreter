cmake_minimum_required(VERSION 3.13)
project(console_cpu_render)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(console_cpu_render ${SOURCES} src/engine/Frame.cpp src/engine/Frame.h src/utils.h src/interpreter/ContainerVariable.h src/interpreter/ConstantCommand.h src/interpreter/ConstructCommand.h src/interpreter/FunctionCommand.h)
