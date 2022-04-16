cmake_minimum_required(VERSION 3.20)
project(mandelbrot CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Wswitch)
    add_link_options("$<$<CONFIG:DEBUG>:-fsanitize=address,undefined>")
endif()

add_executable(mandelbrot src/main.cpp src/Mandelbrot.cpp src/Mandelbrot.h src/mathIn.h)

target_link_libraries(mandelbrot PRIVATE sfml-graphics)
target_compile_definitions(mandelbrot PRIVATE FONT_PATH="${CMAKE_SOURCE_DIR}/data/font.ttf")
target_compile_features(mandelbrot PRIVATE cxx_std_20)

add_custom_target(format
        COMMAND clang-format -i `git ls-files *.cpp *.h`
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy
        COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} `git ls-files *.cpp`
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(release COMMAND mandelbrot)