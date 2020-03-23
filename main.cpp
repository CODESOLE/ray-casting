#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class ray
{
private:
    std::vector<sf::Vertex> points;
    float speed = 0.05f;
    sf::Vector2f dir;
    sf::Vector2f area;

    float magnitude(const sf::Vertex &p0, const sf::Vertex &p1)
    {
        return sqrt((p0.position.x - p1.position.x) * (p0.position.x - p1.position.x) + (p0.position.y - p1.position.y) * (p0.position.y - p1.position.y));
    }

    bool isHit(sf::Vertex p)
    {
        if (!(0 < p.position.x < area.x) || !(0 < p.position.y < area.y))
            return true;
        else
            return false;
    }

public:
    ray(sf::Vector2f pos, double direction) : area(sf::Vector2f(pos.x * 2, pos.y * 2))
    {
        dir.x = (float)cos(direction * (3.14159 / 180.0));
        dir.y = (float)sin(-direction * (3.14159 / 180.0));

        points.push_back(sf::Vertex(pos, sf::Color::Red));
        points.push_back(sf::Vertex(pos, sf::Color::Red));
    }

    void update()
    {
        if (magnitude(points[0], points[1]) < 100.f)
        {
            points[1].position.x += dir.x * speed;
            points[1].position.y += dir.y * speed;
        }
        else
        {
            for (size_t i = 0; i < points.size(); i++)
            {
                points[i].position.x += dir.x * speed;
                points[i].position.y += dir.y * speed;
            }
        }

        /*  for (size_t i = 0; i < points.size(); i++)
        {
            if (isHit(points[i]))
            {
                points.push_back(sf::Vertex(points[i].position, sf::Color::Red));
            }
        } */
    }

    std::vector<sf::Vertex> getVertex() const
    {
        return points;
    }

    ~ray() {}
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    ray r1(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 45.0);

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