cmake_minimum_required(VERSION 3.20)
project(Mandelbrot_set)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Mandelbrot_set main.cpp complex.cpp complex.h)

target_link_libraries(Mandelbrot_set sfml-graphics)