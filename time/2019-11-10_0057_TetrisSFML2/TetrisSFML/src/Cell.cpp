#include "Cell.h"

Cell::Cell()
{
    m_color = sf::Color::Blue;
    m_isVisible = false;
}

Cell::Cell(sf::Color color, bool isVisible)
{
    m_color = color;
    m_isVisible = isVisible;
}

sf::Color Cell::getColor() const
{
    return m_color;
}

bool Cell::isVisible() const
{
    return m_isVisible;
}

void Cell::setVisible(bool b)
{
    m_isVisible = b;
}

void Cell::draw(sf::RenderWindow& window, sf::Vector2u cellPos) const
{
    if(isVisible())
    {
        float size_px = 20;
        float borderWidht = 4;
        float coef = size_px + borderWidht;
        sf::RectangleShape rect({ size_px, size_px });
        rect.setPosition({ cellPos.x * coef, cellPos.y * coef });
        rect.setFillColor(getColor());
        rect.setOutlineThickness(2);
        window.draw(rect);
    }
}
