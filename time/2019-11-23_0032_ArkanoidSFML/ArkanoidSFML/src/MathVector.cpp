#include "MathVector.h"
#define _USE_MATH_DEFINES
#include <math.h>

float radToDeg(float radians)
{
    auto degrees = radians * (180.0 / M_PI);
    return degrees;
}

float degToRad(float degrees)
{
    auto radians = degrees / (180.0 / M_PI);
    return radians;
}

MathVector::MathVector()
{
    setSize(0);
    setAngle(0);
}

MathVector::MathVector(float angle_deg, float size)
{
    setSize(size);
    setAngle(angle_deg);
}

MathVector::MathVector(sf::Vector2f coordinates)
{
    setCoordinates(coordinates);
}

MathVector& MathVector::operator=(sf::Vector2f coordinates)
{
    setCoordinates(coordinates);
    return *this;
}

void MathVector::setSize(float size)
{
    m_size = size;
}

float MathVector::getSize()
{
    return m_size;
}

void MathVector::setAngle(float angle_deg)
{
    int int_angle_deg = static_cast<int>(angle_deg);
    float offset = angle_deg - int_angle_deg;
    m_angle_deg = int_angle_deg % 360 + offset;
}

float MathVector::getAngle()
{
    return m_angle_deg;
}

void MathVector::setCoordinates(sf::Vector2f coordinate)
{
    auto x = coordinate.x;
    auto y = coordinate.y;
    m_size = sqrt(x * x + y * y);
    auto radians = atan(y / x);
    setAngle(radToDeg(radians));
}

sf::Vector2f MathVector::getCoordinates()
{
    auto radians = degToRad(m_angle_deg);
    sf::Vector2f coord;
    coord.y = sin(radians) * m_size;
    coord.x = cos(radians) * m_size;
    return coord;
}

void MathVector::rotate(float angle_deg)
{
    setAngle(getAngle() + angle_deg);
}

void MathVector::reflectFromVertical()
{
    auto coordinate = getCoordinates();
    coordinate.x = -coordinate.x;
    setCoordinates(coordinate);
}

void MathVector::reflectFromHorizontal()
{
    auto coordinate = getCoordinates();
    coordinate.y = -coordinate.y;
    setCoordinates(coordinate);
}
