#include "Ray.hpp"

VECTOR2 vec::UP = VECTOR2(0.f, -1.f);
VECTOR2 vec::RIGHT = VECTOR2(-1.f, 0.f);
VECTOR2 vec::BOTTOM = VECTOR2(0.f, 1.f);
VECTOR2 vec::LEFT = VECTOR2(1.f, 0.f);

float Ray::magnitude(const sf::Vertex &p0, const sf::Vertex &p1)
{
    return sqrt((p0.position.x - p1.position.x) * (p0.position.x - p1.position.x) + (p0.position.y - p1.position.y) * (p0.position.y - p1.position.y));
}

float Ray::angle(VECTOR2 v1, VECTOR2 v2)
{
    return acos((v1.dot(v2)) / (v1.mag() * v2.mag())) * 180.f / 3.1415926f;
}

void Ray::isHit(std::vector<point *> &p, const unsigned int &index)
{
    if (!(0 < p[index]->vert.position.x))
    {
        p[index]->ishit = true;
        p[index]->sideHitted = LEFT;
    }
    else if (!(p[index]->vert.position.x < area.x))
    {
        p[index]->ishit = true;
        p[index]->sideHitted = RIGHT;
    }
    else if (!(0 < p[index]->vert.position.y))
    {
        p[index]->ishit = true;
        p[index]->sideHitted = UP;
    }
    else if (!(p[index]->vert.position.y < area.y))
    {
        p[index]->ishit = true;
        p[index]->sideHitted = BOTTOM;
    }
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

        if (magnitude(points[i]->vert, points[i + 1]->vert) <= 0.f)
            points.pop_back();
    }

    for (size_t i = 0; i < points.size(); i++)
    {
        isHit(points, i);

        if (points[i]->ishit && !points[i]->added)
        {

            //std::cout << "hitted";

            if (points[i]->sideHitted == UP)
            {
                points.push_back(new point(sf::Vertex(sf::Vector2f(points[i]->vert.position.x + 2, points[i]->vert.position.y + 2), sf::Color::Red), sf::Vector2f(points[i]->dir.x, -points[i]->dir.y), false));
                points[i]->added = true;
            }
            else if (points[i]->sideHitted == BOTTOM)
            {
                points.push_back(new point(sf::Vertex(sf::Vector2f(points[i]->vert.position.x - 2, points[i]->vert.position.y - 2), sf::Color::Red), sf::Vector2f(points[i]->dir.x, -points[i]->dir.y), false));
                points[i]->added = true;
            }
            else if (points[i]->sideHitted == LEFT)
            {
                points.push_back(new point(sf::Vertex(sf::Vector2f(points[i]->vert.position.x + 2, points[i]->vert.position.y + 2), sf::Color::Red), sf::Vector2f(-points[i]->dir.x, points[i]->dir.y), false));
                points[i]->added = true;
            }
            else if (points[i]->sideHitted == RIGHT)
            {
                points.push_back(new point(sf::Vertex(sf::Vector2f(points[i]->vert.position.x - 2, points[i]->vert.position.y - 2), sf::Color::Red), sf::Vector2f(-points[i]->dir.x, points[i]->dir.y), false));
                points[i]->added = true;
            }

            std::cout << angle(VECTOR2(points[i]->dir.x, points[i]->dir.y), vec::UP) << std::endl;
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