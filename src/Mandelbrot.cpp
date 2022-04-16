#include "Mandelbrot.h"
#include "mathIn.h"

#include <iomanip>
#include <complex>

Mandelbrot::Mandelbrot()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set");
    window->setFramerateLimit(MAX_FPS);

    // Image load
    image.create(WIDTH, HEIGHT);

    // Font load
    font1.loadFromFile(FONT_PATH);

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

    pixels = std::make_unique<std::array<std::array<sf::Color, WIDTH>, HEIGHT>>();
}

int Mandelbrot::run()
{
    while(window->isOpen())
    {
        sf::Event e;

        control(e);
        processText();

        window->clear();

        paint();

        window->display();
    }

    return 1;
}

void Mandelbrot::control(sf::Event& e)
{
    while(window->pollEvent(e))
    {
        switch (e.type)
        {
            default:
                break;

            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                calculated = false;

                switch (e.key.code)
                {
                    case sf::Keyboard::RBracket:
                        iterations+=25;
                        break;
                    case sf::Keyboard::LBracket:
                        iterations-=25;
                        break;
                        
                    case sf::Keyboard::W:
                        minIm-= stepIm;
                        maxIm-= stepIm;
                        break;
                    case sf::Keyboard::S:
                        minIm+= stepIm;
                        maxIm+= stepIm;
                        break;
                    case sf::Keyboard::A:
                        minRe-= stepRe;
                        maxRe-= stepRe;
                        break;
                    case sf::Keyboard::D:
                        minRe+= stepRe;
                        maxRe+= stepRe;
                        break;
                    default:
                        break;
                }
                break;

            case sf::Event::MouseButtonPressed:
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

                switch (e.mouseButton.button)
                {
                    case sf::Mouse::Left:
                        zoom_z(2);
                        zoom*=2;
                        break;

                    case sf::Mouse::Right:
                        zoom_z(1.0/2);
                        zoom/=2;
                        break;

                    default:
                        break;
                }
                break;
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
        for(unsigned int i = 0; i < threads.size(); i++)
        {
            threads[i] = std::thread([this](int start, int end) noexcept{
                for (int y = start; y < end; ++y)
                {
                    for (int x = 0; x < WIDTH; ++x)
                    {
                        double a = minRe + (maxRe - minRe) * x / WIDTH;
                        double b = minIm + (maxIm - minIm) * y / HEIGHT;

                        std::complex<double> c(a, b);

                        int iteration = 0;
                        for (std::complex<double> z = {0,0}; std::norm(z) <= 4.0 && iteration < iterations; ++iteration)
                            z = z * z + c;

                        if (iteration == iterations) iteration = 0;

                        double mu = 1.0 * iteration / iterations * max_color;

                        size_t i_mu = static_cast<size_t>(mu);
                        sf::Color color1 = colors[i_mu];
                        sf::Color color2 = colors[std::min(i_mu + 1, max_color)];

                        (*pixels)[y][x] = linearInterpolation(color1, color2, mu - i_mu);
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

        image.create(WIDTH, HEIGHT, (sf::Uint8*)pixels->data());

        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    window->draw(sprite);
    window->draw(text);
}

void Mandelbrot::processText()
{
    auto textBuilder = std::ostringstream();

    textBuilder << 1'000'000 / clock.restart().asMicroseconds() << " fps\n";
    textBuilder << iterations << " iterations\n";

    text.setString(textBuilder.str());
}
