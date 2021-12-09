#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "complex.h"
#include "assets.hpp"

sf::Color linearInterpolation(sf::Color v, sf::Color u, double a)
{
    double b = 1-a;
    return sf::Color(b * v.r + a * u.r,
                     b * v.g + a * u.g,
                     b * v.b + a * u.b);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set");
    window.setFramerateLimit(MAX_FPS);

    sf::Image image;
    image.create(WIDTH, HEIGHT);
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Font font1;
    if(!font1.loadFromFile(FONT_PATH)) std::cout << "Font not loaded!" << std::endl;
    sf::Text text;
    text.setFont(font1);
    text.setCharacterSize(TEXT_SIZE);
    text.setFillColor(TEXT_COLOR);

    bool painted = false;
    int iterations = 100;

    // Complex plane size
    double minRe = -2, maxRe = 1;
    double minIm = -1, maxIm = 1;
    double zoom = 1;
    unsigned long max_color = colors.size()-1;

    while(window.isOpen())
    {

        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();

            //control
            else if(e.type==sf::Event::KeyPressed)
            {

                if(e.key.code == sf::Keyboard::Up)
                {
                    iterations+=10;
                    painted = false;
                }
                else if(e.key.code == sf::Keyboard::Down & iterations > 10)
                {
                    iterations -= 10;
                    painted = false;
                }
            }

            else if(e.type == sf::Event::MouseButtonPressed)
            {
                painted = false;
                auto zoom_z = [&](double z)
                {
                    double cx = minRe+(maxRe-minRe)*e.mouseButton.x/WIDTH;
                    double cy = minIm+(maxIm-minIm)*e.mouseButton.y/HEIGHT;

                    double tminr = cx-(maxRe-minRe)/2/z;
                    maxRe=cx+(maxRe-minRe)/2/z;
                    minRe=tminr;

                    double tmini = cy-(maxIm-minIm)/2/z;
                    maxIm=cy+(maxIm-minIm)/2/z;
                    minIm=tmini;
                };

                // Left Click to ZoomIn
                if(e.mouseButton.button==sf::Mouse::Left)
                {
                    zoom_z(2);
                    zoom*=5;
                }
                // Right Click to ZoomOut
                if(e.mouseButton.button==sf::Mouse::Right)
                {
                    zoom_z(1.0/2);
                    zoom/=5;
                }

            }
        }

        window.clear();

        //logic and paint
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
                    while (iteration < iterations)
                    {
                        iteration++;

                        z.square();
                        z.add(c);

                        if (z.absolute() > 2) break;
                    }

                    if(iteration == iterations) iteration = 0;

                    double mu = 1.0 * iteration / iterations * max_color;

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

        //Text
        char str[100];
        sprintf(str, "iterations : %d\nzoom : x%3.2f\nmaxRe : %f minRe : %f\nmaxIm : %f minIm : %f",
                iterations, zoom, maxRe, minRe, maxIm, minIm);
        text.setString(str);
        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}
