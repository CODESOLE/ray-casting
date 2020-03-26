#pragma once

#include <SFML/Graphics.hpp>
#include "vec.hpp"
#include <iostream>
#include <cmath>

enum side
{
    UP = 0,
    RIGHT,
    BOTTOM,
    LEFT,
    NONE
};

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
    side sideHitted;
    point(sf::Vertex v, sf::Vector2f vec, bool ish, bool IsAdded = false, side SIDE = NONE) : vert(v), dir(vec), ishit(ish), added(IsAdded), sideHitted(SIDE) {}
};

class Ray
{
private:
    std::vector<point *> points;
    float speed = 0.09f;
    sf::Vector2f area;

    float magnitude(const sf::Vertex &p0, const sf::Vertex &p1);
    float angle(VECTOR2, VECTOR2);
    void isHit(std::vector<point *> &p, const unsigned int &index);

public:
    Ray(sf::Vector2f pos, double direction);
    void update();
    std::vector<sf::Vertex> getVertex() const;
    ~Ray();
};