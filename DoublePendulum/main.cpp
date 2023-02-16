#ifdef _WIN64
#define _USE_MATH_DEFINES
#endif

#include <iostream>
#include <cmath>
#include "Pendulum.h"
#include "Drawable.h"

constexpr double dt = 0.008;

int main()
{
    sf::RenderWindow window (sf::VideoMode (1920, 1200), "Double Pendulum");
    window.setVerticalSyncEnabled(true);

    auto deg2rad = [](double deg) { return deg * (M_PI / 180.0); };

    double deg1 =110.0;
    double deg2 = 110.0;

    Object::Pendulum pendulum(50, 300, 960, 540,
        deg2rad(deg1), deg2rad(deg2), sf::Color::Cyan);

    State s(deg2rad(deg1), deg2rad(deg2), 0.0, 0.0);
    Pendulum p(1.0, 1.0, 1.0, 1.0, s);

    sf::Clock clock;
    float fps, currentTime;

    int record = 0;

    while (window.isOpen ())
    {
        sf::Event event;
        while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                window.close ();
        }

        window.clear ();
        
        if (record > 1200)
        {
            p.CalculateMove(dt);
            pendulum.Move(std::get<0>(p.getTwoAngles()), std::get<1>(p.getTwoAngles()));
        }

        record++;

        pendulum.Draw (&window);

        window.display ();

        currentTime = clock.restart().asSeconds();
        fps = 1.0f / (currentTime);
        
        std::cout << fps << "\n";
    }

    return 0;
}