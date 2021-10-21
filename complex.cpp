//
// Created by Даниил on 21.10.2021.
//

#include "complex.h"
#include <math.h>

complex::complex(double a, double b)
{
    this->a = a;
    this->b = b;
}

void complex::add(complex c)
{
    this->a += c.getA();
    this->b += c.getB();
}

double complex::absolute()
{
    return sqrt((a*a) + (b*b));
}

void complex::square()
{
    double temp = (a*a)-(b*b);
    b = (a*b) + (b*a);
    a = temp;
}

double complex::getA()
{
    return this->a;
}

double complex::getB()
{
    return this->b;
}