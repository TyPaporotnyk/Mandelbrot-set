#include "complex.h"
#include <math.h>

complex::complex(double r, double im)
{
    this->r = r;
    this->im = im;
}

void complex::add(complex c)
{
    this->r += c.getA();
    this->im += c.getB();
}

double complex::absolute()
{
    return sqrt((r*r) + (im*im));
}

void complex::square()
{
    double temp = (r*r)-(im*im);
    this->im = (r*im) + (im*r);
    this->r = temp;
}

double complex::getA()
{
    return this->r;
}

double complex::getB()
{
    return this->im;
}
