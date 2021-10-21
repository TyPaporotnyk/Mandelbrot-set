#include <SFML/Graphics.hpp>
#include <iostream>

#include "complex.h"

using std::cout;
using std::endl;


constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set");
    window.setFramerateLimit(30);

    sf::Image image;
    image.create(WIDTH, HEIGHT);
    sf::Texture texture;
    sf::Sprite sprite;

    bool draw = false;
    int iterations = 1000;
    double minReal = -2.5;
    double maxReal = 1;
    double minImagin = -1;
    double maxImagin = 1;

    while(window.isOpen())
    {

        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();

//            if(e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
//            {
//                draw = false;
//                if(e.mouseWheelScroll.delta > 0) iterations+=20;
//                else iterations-=20;
//                if(iterations<5) iterations = 1;
//            }

        }

        window.clear();

        if(!draw)
        {
            draw = true;
            for (int y = 0; y < HEIGHT; ++y)
            {
                for (int x = 0; x < WIDTH; ++x)
                {
                    double a = minReal+(maxReal-minReal)*x/WIDTH;
                    double b = minImagin+(maxImagin-minImagin)*y/HEIGHT;

                    complex c(a, b);
                    complex z(0, 0);

                    int iteration = 0;
                    do
                    {
                        iteration++;

                        z.square();
                        z.add(c);

//                        cout << iteration << " : " << z.getA() << "\t" << z.getB() << " => " << z.absolute() << endl;

                        if (z.absolute() > 2) break;
                    } while (iteration < iterations);
                    image.setPixel(x, y, iteration < iterations ? sf::Color(iteration, iteration, iteration) :
                                                                        sf::Color(255,255,255));
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