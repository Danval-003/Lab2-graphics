cmake_minimum_required(VERSION 3.25)
project(Lab2-graphics)
set(EXECUTABLE_NAME "Lab2-graphics")
set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)

add_executable(${EXECUTABLE_NAME} main.cpp render.h color.h framebuffer.h)
target_link_libraries(${EXECUTABLE_NAME} SDL2)
target_sources(${EXECUTABLE_NAME} PRIVATE render.cpp color.cpp framebuffer.cpp)
