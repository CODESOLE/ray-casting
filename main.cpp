#include "Ray.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    Ray r1(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 45.0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        r1.update();

        window.clear();
        window.draw(&r1.getVertex()[0], r1.getVertex().size(), sf::Lines);
        window.display();
    }

    return 0;
}