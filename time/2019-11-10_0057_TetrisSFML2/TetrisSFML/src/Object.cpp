#include "Object.h"
#include <cassert>
#include <iostream>

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
    int shapeNumber = rand() % 5;
    m_shape.clear();

    switch (shapeNumber)
    {
    case 0:
        m_shape.resize(2);
        m_shape[0].push_back({ true });
        m_shape[0].push_back({ true });
        m_shape[1].push_back({ false });
        m_shape[1].push_back({ true });
        m_shape[1].push_back({ true });
        break;
    case 1:
        m_shape.resize(2);
        m_shape[0].push_back({ true });
        m_shape[0].push_back({ true });
        m_shape[0].push_back({ true });
        m_shape[1].push_back({ false });
        m_shape[1].push_back({ true });
        break;
    case 2:
        m_shape.resize(4);
        m_shape[0].push_back({ true });
        m_shape[1].push_back({ true });
        m_shape[2].push_back({ true });
        m_shape[3].push_back({ true });
        break;
    case 3:
        m_shape.resize(2);
        m_shape[0].push_back({ true });
        m_shape[0].push_back({ true });
        m_shape[1].push_back({ true });
        m_shape[1].push_back({ true });
        break;
    case 4:
        m_shape.resize(2);
        m_shape[0].push_back({ true });
        m_shape[0].push_back({ true });
        m_shape[0].push_back({ true });
        m_shape[1].push_back({ true });
        break;
    }

    unsigned rotationNumber = rand() % 3;
    for (unsigned i = 0; i < rotationNumber; ++i)
    {
        *this = getRotateObject();
    }

    bool hasFlip = rand() % 2;
    for(unsigned i = 0; i < rotationNumber; ++i)
    {
        *this = getFlipObject();
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
    return getCell(matrixPos).isVisible();
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

Object Object::getRotateObject() const
{
    Lines rotatedShape;
    Lines fullShape = m_shape;

    auto boundSize = getBoundSize();
    for(auto & line : fullShape)
    {
        line.resize(boundSize.x);
    }

    rotatedShape.resize(boundSize.x);
    for (auto & line : rotatedShape)
    {
        line.resize(boundSize.y);
    }

    for (unsigned row = 0; row < boundSize.y; ++row)
    {        
        for(unsigned col = 0; col < boundSize.x; ++col)
        {
            rotatedShape[boundSize.x-col-1][row] = fullShape[row][col];
        }
    }

    Object object(*this);
    object.setShape(rotatedShape);
    return object;
}

Object Object::getFlipObject() const
{
    Lines flipShape = m_shape;
    for(auto & line : flipShape)
    {
        std::reverse(line.begin(), line.end());
    }

    Object object(*this);
    object.setShape(flipShape);
    return object;
}

sf::Vector2u Object::getBoundSize() const
{
    sf::Vector2u size {0, 0};
    
    if(m_shape.empty())
        return size;

    size.y = m_shape.size();
    size.x = m_shape[0].size();

    for(const auto & line : m_shape)
    {
        if(line.size() > size.x)
            size.x = line.size();
    }

    return size;
}
