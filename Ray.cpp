#include "Ray.hpp"

float Ray::magnitude(const sf::Vertex &p0, const sf::Vertex &p1)
{
    return sqrt((p0.position.x - p1.position.x) * (p0.position.x - p1.position.x) + (p0.position.y - p1.position.y) * (p0.position.y - p1.position.y));
}

bool Ray::isHit(sf::Vertex &p)
{
    if (!(0 < p.position.x) || !(p.position.x < area.x) || !(0 < p.position.y) || !(p.position.y < area.y))
        return true;
    else
        return false;
}

Ray::Ray(sf::Vector2f pos, double direction) : area(sf::Vector2f(pos.x * 2, pos.y * 2))
{
    points.vert.push_back(sf::Vertex(pos, sf::Color::Red));
    points.dir.push_back(sf::Vector2f((float)cos(direction * (3.14159 / 180.0)), (float)sin(-direction * (3.14159 / 180.0))));
    points.vert.push_back(sf::Vertex(pos, sf::Color::Red));
    points.dir.push_back(sf::Vector2f((float)cos(direction * (3.14159 / 180.0)), (float)sin(-direction * (3.14159 / 180.0))));
}

void Ray::update()
{
    for (size_t i = 0; i < points.vert.size() - 1; i++)
    {
        if (magnitude(points.vert[i], points.vert[i + 1]) < 100.f)
        {
            points.vert[i + 1].position.x += points.dir[i + 1].x * speed;
            points.vert[i + 1].position.y += points.dir[i + 1].y * speed;
        }
        else
        {
            for (size_t i = 0; i < points.vert.size(); i++)
            {
                points.vert[i].position.x += points.dir[i].x * speed;
                points.vert[i].position.y += points.dir[i].y * speed;
            }
        }
    }

    for (size_t i = 0; i < points.vert.size(); i++)
    {
        if (isHit(points.vert[i]))
        {
            std::cout << "hitted";
            points.vert.push_back(sf::Vertex(points.vert[i].position, sf::Color::Red));
            points.dir.push_back(sf::Vector2f(points.dir[i].x, -points.dir[i].y));
        }
    }
}

std::vector<sf::Vertex> Ray::getVertex() const
{
    return points.vert;
}

Ray::~Ray() {}