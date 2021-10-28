cmake_minimum_required(VERSION 3.20)
project(Mandelbrot_set)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Mandelbrot_set main.cpp complex.cpp complex.h assets.hpp)

if(APPLE OR UNIX)
    include_directories(/usr/local/include)
else()
    set(SFML_DIR "SFML-mingw32/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

target_link_libraries(Mandelbrot_set sfml-graphics)