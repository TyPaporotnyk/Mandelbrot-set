#ifndef MANDELBROT_SET_MANDELBROT_H
#define MANDELBROT_SET_MANDELBROT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <string>
#include <thread>

class Mandelbrot
{
private:
    const int MAX_FPS = 60;

    static const int WIDTH = 960;
    static const int HEIGHT = 640;

    const int TEXT_SIZE = 24;
    const sf::Color TEXT_COLOR = sf::Color::White;

    bool calculated = false;
    int iterations = 100;

    sf::Clock clock;

    std::unique_ptr<std::array<std::array<sf::Color, WIDTH>, HEIGHT>> pixels;

    double minRe = -2, maxRe = 1;
    double minIm = -1, maxIm = 1;
    double zoom = 1;
    unsigned long max_color;

    double stepIm = (abs(minIm) + abs(maxIm)) * (1.0/3);
    double stepRe = (abs(minRe) + abs(maxRe)) * (1.0/4);

    std::vector<sf::Color> colors{
            {  0,   2, 0},
            {   32, 107, 203},
            { 237, 255, 255},
            {255, 170,   0},
            { 0,   7, 100}
    };
    sf::RenderWindow*  window;

    sf::Font font1;
    sf::Text text;

    sf::Image image;
    sf::Sprite sprite;
    sf::Texture texture;

    std::vector<std::thread> threads;

    void control(sf::Event &e);
    void paint();
    void processText();

public:
    Mandelbrot();

    int run();
};


#endif //MANDELBROT_SET_MANDELBROT_H
