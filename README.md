# Mandelbrot-set

[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](http://choosealicense.com/licenses/mit/)
![Commits](https://img.shields.io/github/last-commit/TyPaporotnyk/Mandelbrot-set)

Implementation of the Mandelbrot set with c++ and the sfml graphics library</br>

<p float="middle">
    <img src="docs/1.png" width="49%"/>
    <img src="docs/2.png" width="49%"/>
</p>

# Requirements
* C++ 17
* CMake 3.20
* SFML 2.5

# Building & Running
```
cmake -B cmake-build -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build
cmake --build cmake-build --target release
```