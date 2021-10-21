//
// Created by Даниил on 21.10.2021.
//

#ifndef MANDELBROT_SET_COMPLEX_H
#define MANDELBROT_SET_COMPLEX_H


class complex
{
private:
    double a;
    double b;
public:
    explicit complex(double a, double b);
    void add(complex c);
    double absolute();
    void square();
    double getA();
    double getB();
};


#endif //MANDELBROT_SET_COMPLEX_H
