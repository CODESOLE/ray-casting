#pragma once

#include <SFML/Graphics.hpp>
#include "vec.hpp"
#include <iostream>
#include <cmath>

struct vec
{
    static VECTOR2 UP;
    static VECTOR2 RIGHT;
    static VECTOR2 BOTTOM;
    static VECTOR2 LEFT;
};

struct point
{
    sf::Vertex vert;
    sf::Vector2f dir;
    bool ishit, added;
    point(sf::Vertex v, sf::Vector2f vec, bool ish, bool add = false) : vert(v), dir(vec), ishit(ish), added(add) {}
};

class Ray
{
private:
    std::vector<point *> points;
    float speed = 0.05f;
    sf::Vector2f area;

    float magnitude(const sf::Vertex &p0, const sf::Vertex &p1);

    float angle(VECTOR2, VECTOR2);

    void isHit(std::vector<point *> &p, unsigned int index);

public:
    Ray(sf::Vector2f pos, double direction);

    void update();

    std::vector<sf::Vertex> getVertex() const;

    ~Ray();
};