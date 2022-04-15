#include "Mandelbrot.h"
#include "complex.h"
#include "mathIn.h"

#include <iomanip>
#include <iostream>
#include <sstream>

Mandelbrot::Mandelbrot()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set");
    window->setFramerateLimit(MAX_FPS);

    // Image load
    image.create(WIDTH, HEIGHT);

    // Font load
    if(!font1.loadFromFile(FONT_PATH)) std::cout << "Font not loaded!" << std::endl;

    text.setFont(font1);
    text.setCharacterSize(TEXT_SIZE);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setFillColor(TEXT_COLOR);
    text.setPosition({20,20});

    // Coloring
    max_color = colors.size()-1;

    clock = sf::Clock();

    threads = std::vector<std::thread>(std::thread::hardware_concurrency());
}

int Mandelbrot::run()
{
    while(window->isOpen())
    {
        sf::Event e;

        control(e);

        window->clear();

        paint();
        setText();

        window->display();
    }

    return 1;
}

void Mandelbrot::control(sf::Event e)
{
    while(window->pollEvent(e))
    {
        if(e.type == sf::Event::Closed) window->close();

            //control
        else if(e.type == sf::Event::KeyPressed)
        {
            calculated = false;
            if(e.key.code == sf::Keyboard::RBracket)
            {
                iterations+=25;
            }
            else if(e.key.code == sf::Keyboard::LBracket & iterations > 25)
            {
                iterations -= 25;
            }

                // Up/Down
            else if(e.key.code == sf::Keyboard::W)
            {

                minIm-= stepIm;
                maxIm-= stepIm;
            }
            else if(e.key.code == sf::Keyboard::S)
            {
                minIm+= stepIm;
                maxIm+= stepIm;
            }

                //Left/Right
            else if(e.key.code == sf::Keyboard::A)
            {

                minRe-= stepRe;
                maxRe-= stepRe;
            }
            else if(e.key.code == sf::Keyboard::D)
            {
                minRe+= stepRe;
                maxRe+= stepRe;
            }
        }

        else if(e.type == sf::Event::MouseButtonPressed)
        {
            calculated = false;
            auto zoom_z = [&](double z)
            {
                double cx = minRe+(maxRe-minRe)*e.mouseButton.x/WIDTH;
                double cy = minIm+(maxIm-minIm)*e.mouseButton.y/HEIGHT;

                double tminr = cx-(maxRe-minRe)/2/z;
                maxRe = cx+(maxRe-minRe)/2/z;
                minRe = tminr;

                double tmini = cy-(maxIm-minIm)/2/z;
                maxIm = cy+(maxIm-minIm)/2/z;
                minIm = tmini;
            };

            // Left Click to ZoomIn
            if(e.mouseButton.button==sf::Mouse::Left)
            {
                zoom_z(2);
                zoom*=2;
            }
            // Right Click to ZoomOut
            if(e.mouseButton.button==sf::Mouse::Right)
            {
                zoom_z(1.0/2);
                zoom/=2;
            }

        }
    }
}

void Mandelbrot::paint()
{
    if(!calculated)
    {
        calculated = true;
        int sum = HEIGHT/threads.size();
        int start = 0;
        int end = sum;
        for(int i = 0; i < threads.size(); i++)
        {
            threads[i] = std::thread([this](int start, int end){
                for (int y = start; y < end; ++y)
                {
                    for (int x = 0; x < WIDTH; ++x)
                    {
                        double a = minRe + (maxRe - minRe) * x / WIDTH;
                        double b = minIm + (maxIm - minIm) * y / HEIGHT;

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

                        if (iteration == iterations) iteration = 0;

                        double mu = 1.0 * iteration / iterations * max_color;

                        size_t i_mu = static_cast<size_t>(mu);
                        sf::Color color1 = colors[i_mu];
                        sf::Color color2 = colors[std::min(i_mu + 1, max_color)];

                        image.setPixel(x, y, linearInterpolation(color1, color2, mu - i_mu));
                    }
                }
            }, start, end);

            start += sum;
            end += sum;
        }
        for(auto& thread : threads)
        {
            thread.join();
        }

        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    window->draw(sprite);
}

void Mandelbrot::setText()
{
    auto textBuilder = std::ostringstream();

    textBuilder << std::setw(4) << 1'000'000 / clock.restart().asMicroseconds() << " fps\n";
    textBuilder << std::setw(4) << iterations << " iterations\n";

    text.setString(textBuilder.str());
    window->draw(text);
}
