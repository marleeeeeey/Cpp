#include "Cell.h"

Cell::Cell()
{
    m_color = sf::Color::Blue;
    m_isVisible = false;
}

Cell::Cell(bool isVisible, sf::Color color)
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

const unsigned Cell::getSize()
{
    return s_size;
}

void Cell::draw(sf::RenderWindow& window, sf::Vector2u cellPos) const
{
    if(isVisible())
    {
        sf::RectangleShape rect({ s_bodySize_px, s_bodySize_px });
        rect.setPosition({static_cast<float>(cellPos.x * s_size), 
            static_cast<float>(cellPos.y * s_size)});
        rect.setFillColor(getColor());
        rect.setOutlineThickness(static_cast<float>(s_borderSize_px) / 2);
        window.draw(rect);
    }
}
