#include "Object.h"
#include <cassert>

Object::Object()
{
    m_pos = { 0, 0 };
    generateShape();
}

Object::Object(const Object& other)
{
    if(&other == this)
        return;

    *this = other;
}

Object Object::getMoved(int x, int y) const
{
    Object moved(*this);
    moved.m_pos.x += x;
    moved.m_pos.y += y;
    return moved;
}

void Object::generateShape()
{
    m_shape.resize(2);
    for (auto & line : m_shape)
    {
        line.push_back(Cell{sf::Color::Red, true});
        line.push_back(Cell{ sf::Color::Red, true });
    }
}

void Object::draw(sf::RenderWindow& window) const
{
    const unsigned shiftRow = m_pos.y;
    const unsigned shiftCol = m_pos.x;
    for(unsigned row = 0; row < m_shape.size(); ++row)
    {
        const auto& line = m_shape[row];
        for(unsigned col = 0; col < line.size(); ++col)
        {
            const auto& cell = line[col];
            cell.draw(window, { shiftCol + col, shiftRow + row });
        }
    }
}

void Object::setShape(const Lines& shape)
{
    m_shape = shape;
}

const Lines& Object::getShape() const
{
    return m_shape;
}

void Object::setPos(sf::Vector2u pos)
{
    m_pos = pos;
}

sf::Vector2u Object::getPos() const
{
    return m_pos;
}

bool Object::isVisible(sf::Vector2u matrixPos) const
{
    return getCell(matrixPos).isVisible;
}

Cell Object::getCell(sf::Vector2u matrixPos) const
{
    auto shapePos = matrixPos - m_pos;
    assert(shapePos.y >= 0);
    assert(shapePos.x >= 0);

    if(shapePos.y < m_shape.size())
    {
        const auto& line = m_shape[shapePos.y];
        if(shapePos.x < line.size())
        {
            return line[shapePos.x];
        }
    }

    return Cell();
}
