# Mandelbrot-set

[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](http://choosealicense.com/licenses/mit/)
![Commits](https://img.shields.io/github/last-commit/TyPaporotnyk/Mandelbrot-set)

Implementation of the Mandelbrot set with c ++ and the sfml graphics library</br>

<p float="middle">
    <img src="docs/1.png" width="300"/>
    <img src="docs/1.png" width="300"/>
</p>

# Requirements
* C++20
* CMake 3.16
* SFML 2.5.1

# Building & Running
```
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --build build --target relise
```