#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

struct point
{
    sf::Vertex vert;
    sf::Vector2f dir;
    bool ishit;
    point(sf::Vertex v, sf::Vector2f vec, bool ish) : vert(v), dir(vec), ishit(ish) {}
};

class Ray
{
private:
    std::vector<point *> points;
    float speed = 0.05f;
    sf::Vector2f area;

    float magnitude(const sf::Vertex &p0, const sf::Vertex &p1);

    void isHit(std::vector<point *> &p, unsigned int index);

public:
    Ray(sf::Vector2f pos, double direction);

    void update();

    std::vector<sf::Vertex> getVertex() const;

    ~Ray();
};