#include <SFML/Graphics.hpp>
#include <iostream>

#include "complex.h"

using std::cout;
using std::endl;

#define WIDTH 1920
#define HEIGHT 1280

std::vector<sf::Color> colors{
        {  0,   2, 0},
        {   32, 107, 203},
        { 237, 255, 255},
        {255, 170,   0},
        { 0,   7, 100}
};

sf::Color linearInterpolation(sf::Color v, sf::Color u, double a)
{
    double const b = 1-a;
    return sf::Color(b * v.r + a * u.r, 
                     b * v.g + a * u.g, 
                     b * v.b + a * u.b);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set");
    window.setFramerateLimit(30);

    sf::Image image;
    image.create(WIDTH, HEIGHT);
    sf::Texture texture;
    sf::Sprite sprite;

    bool painted = false;
    int iterations = 100;

    // Complex plane size
    double minRe = -2, maxRe = 1;
    double minIm = -1, maxIm = 1;

    unsigned long max_color = colors.size()-1;

    while(window.isOpen())
    {

        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();

            if(e.type==sf::Event::KeyPressed)
            {

                if(e.key.code == sf::Keyboard::Up)
                {
                    iterations+=10;
                    painted = false;
                    cout << "Iterations: " << iterations << endl;
                }
                else if(e.key.code == sf::Keyboard::Down & iterations > 10)
                {
                    iterations -= 10;
                    painted = false;
                    cout << "Iterations: " << iterations << endl;
                }
            }

        }

        window.clear();

        if(!painted)
        {
            painted = true;
            for (int y = 0; y < HEIGHT; ++y)
            {
                for (int x = 0; x < WIDTH; ++x)
                {
                    double a = minRe+(maxRe-minRe)*x/WIDTH;
                    double b = minIm+(maxIm-minIm)*y/HEIGHT;

                    complex c(a, b);
                    complex z(0, 0);

                    int iteration = 0;
                    do
                    {
                        iteration++;

                        z.square();
                        z.add(c);

                        if (z.absolute() > 2) break;
                    } while (iteration < iterations);


                    if(iteration == iterations) iteration=0;

                    double mu = 1.0 * iteration / iterations;
                    mu *= max_color;
                    size_t i_mu = static_cast<size_t>(mu);
                    sf::Color color1 = colors[i_mu];
                    sf::Color color2 = colors[std::min(i_mu+1, max_color)];

                    image.setPixel(x, y, linearInterpolation(color1, color2, mu-i_mu));

                }
            }
            texture.loadFromImage(image);
            sprite.setTexture(texture);
        }
        window.draw(sprite);

        window.display();
    }

    return 0;
}
