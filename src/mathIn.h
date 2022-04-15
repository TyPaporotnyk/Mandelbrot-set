//
// Created by Даниил on 09.01.2022.
//

#ifndef MANDELBROT_SET_MATHIN_H
#define MANDELBROT_SET_MATHIN_H

#include <SFML/Graphics.hpp>

sf::Color linearInterpolation(sf::Color v, sf::Color u, double a)
{
    double b = 1-a;
    return sf::Color(b * v.r + a * u.r,
                     b * v.g + a * u.g,
                     b * v.b + a * u.b);
}

#endif //MANDELBROT_SET_MATHIN_H
