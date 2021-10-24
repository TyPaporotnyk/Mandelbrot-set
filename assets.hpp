#ifndef MANDELBROT_SET_ASSETS_H
#define MANDELBROT_SET_ASSETS_H

#define MAX_FPS 30

// Window size
#define WIDTH 1920
#define HEIGHT 1280

// Text
#define FONT_PATH "../font/poppins.ttf"
#define TEXT_SIZE 21
#define TEXT_COLOR sf::Color::White

// Set color
std::vector<sf::Color> colors{
        {  0,   2, 0},
        {   32, 107, 203},
        { 237, 255, 255},
        {255, 170,   0},
        { 0,   7, 100}
};

#endif //MANDELBROT_SET_ASSETS_H