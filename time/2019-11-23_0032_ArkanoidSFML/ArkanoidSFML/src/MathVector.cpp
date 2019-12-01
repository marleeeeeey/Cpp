#include "MathVector.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "HelperFunctions.h"

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
    setSize(sqrt(x * x + y * y));

    if (hf::isEqual(x, 0.0f))
    {
        if (hf::isEqual(y, 0.0f))
            setAngle(0);
        else if (y > 0)
            setAngle(90);
        else
            setAngle(-90);
    }
    else if (hf::isEqual(y, 0.0f))
    {
        if (hf::isEqual(x, 0.0f))
            setAngle(0);
        if (x > 0)
            setAngle(0);
        else
            setAngle(180);
    }
    else
    {
        auto radians = atan(abs(y) / abs(x));
        auto deg = radToDeg(radians);
        if (x > 0 && y > 0)
            setAngle(deg);
        else if (x > 0 && y < 0)
            setAngle(-deg);
        else if (x < 0 && y > 0)
            setAngle(180 - deg);
        else if (x < 0 && y < 0)
            setAngle(180 + deg);
        else
            throw std::exception("MathVector::setCoordinates angle error");
    }
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
