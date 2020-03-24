#include "Ray.hpp"

float Ray::magnitude(const sf::Vertex &p0, const sf::Vertex &p1)
{
    return sqrt((p0.position.x - p1.position.x) * (p0.position.x - p1.position.x) + (p0.position.y - p1.position.y) * (p0.position.y - p1.position.y));
}

void Ray::isHit(std::vector<point *> &p, unsigned int index)
{
    if (!(0 < p[index]->vert.position.x) || !(p[index]->vert.position.x < area.x) || !(0 < p[index]->vert.position.y) || !(p[index]->vert.position.y < area.y))
        p[index]->ishit = true;
}

Ray::Ray(sf::Vector2f pos, double direction) : area(sf::Vector2f(pos.x * 2, pos.y * 2))
{
    points.push_back(new point(sf::Vertex(pos, sf::Color::Red), sf::Vector2f((float)cos(direction * (3.14159 / 180.0)), (float)sin(-direction * (3.14159 / 180.0))), false));

    points.push_back(new point(sf::Vertex(pos, sf::Color::Red), sf::Vector2f((float)cos(direction * (3.14159 / 180.0)), (float)sin(-direction * (3.14159 / 180.0))), false));
}

void Ray::update()
{
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        if (magnitude(points[i]->vert, points[i + 1]->vert) < 100.f)
        {
            points[i + 1]->vert.position.x += points[i + 1]->dir.x * speed;
            points[i + 1]->vert.position.y += points[i + 1]->dir.y * speed;
        }
        else
        {
            for (size_t i = 0; i < points.size(); i++)
            {
                if (points[i]->ishit)
                    continue;
                points[i]->vert.position.x += points[i]->dir.x * speed;
                points[i]->vert.position.y += points[i]->dir.y * speed;
            }
        }
    }

    for (size_t i = 0; i < points.size(); i++)
    {
        isHit(points, i);

        if (points[i]->ishit)
        {
            std::cout << "hitted";
            points.push_back(new point(sf::Vertex(sf::Vector2f(points[i]->vert.position.x + 2, points[i]->vert.position.y + 2), sf::Color::Red), sf::Vector2f(points[i]->dir.x, -points[i]->dir.y), false));
        }
    }
}

std::vector<sf::Vertex> Ray::getVertex() const
{
    std::vector<sf::Vertex> data;
    for (size_t i = 0; i < points.size(); i++)
        data.push_back(points[i]->vert);

    return data;
}

Ray::~Ray() {}