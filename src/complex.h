#ifndef MANDELBROT_SET_COMPLEX_H
#define MANDELBROT_SET_COMPLEX_H


class complex
{
private:
    double r; // real
    double im; // imaginary
public:
    explicit complex(double r, double im);
    void add(complex c);
    double absolute();
    void square();
    double getA();
    double getB();
};


#endif //MANDELBROT_SET_COMPLEX_H
