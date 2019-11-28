#pragma once
#include <SFML/Graphics.hpp>

class MathVector
{
    float m_size;
    float m_angle_deg;

public:
    explicit MathVector();
    explicit MathVector(float angle_deg, float size);
    explicit MathVector(sf::Vector2f coordinates);
    MathVector& operator=(sf::Vector2f coordinates);
    void setSize(float size);
    float getSize();
    void setAngle(float angle_deg);
    float getAngle();
    void setCoordinates(sf::Vector2f coordinate);
    sf::Vector2f getCoordinates();
    void rotate(float angle_deg);
    void reflectFromVertical();
    void reflectFromHorizontal();
};
