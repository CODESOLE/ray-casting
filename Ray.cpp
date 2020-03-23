#include "Ray.hpp"

float Ray::magnitude(const sf::Vertex &p0, const sf::Vertex &p1)
{
    return sqrt((p0.position.x - p1.position.x) * (p0.position.x - p1.position.x) + (p0.position.y - p1.position.y) * (p0.position.y - p1.position.y));
}

bool Ray::isHit(sf::Vertex p)
{
    if (!(0 < p.position.x < area.x) || !(0 < p.position.y < area.y))
        return true;
    else
        return false;
}

Ray::Ray(sf::Vector2f pos, double direction) : area(sf::Vector2f(pos.x * 2, pos.y * 2))
{
    dir.x = (float)cos(direction * (3.14159 / 180.0));
    dir.y = (float)sin(-direction * (3.14159 / 180.0));

    points.push_back(sf::Vertex(pos, sf::Color::Red));
    points.push_back(sf::Vertex(pos, sf::Color::Red));
}

void Ray::update()
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

std::vector<sf::Vertex> Ray::getVertex() const
{
    return points;
}

Ray::~Ray() {}