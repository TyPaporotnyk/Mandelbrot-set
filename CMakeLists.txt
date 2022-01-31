cmake_minimum_required(VERSION 3.20)
project(Mandelbrot_set)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Mandelbrot_set main.cpp complex.cpp complex.h Mandelbrot.cpp Mandelbrot.h mathIn.h)

target_link_libraries(Mandelbrot_set sfml-graphics)