#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

struct point
{
    std::vector<sf::Vertex> vert;
    std::vector<sf::Vector2f> dir;
};

class Ray
{
private:
    point points;
    float speed = 0.05f;
    sf::Vector2f area;

    float magnitude(const sf::Vertex &p0, const sf::Vertex &p1);

    bool isHit(sf::Vertex &p);

public:
    Ray(sf::Vector2f pos, double direction);

    void update();

    std::vector<sf::Vertex> getVertex() const;

    ~Ray();
};