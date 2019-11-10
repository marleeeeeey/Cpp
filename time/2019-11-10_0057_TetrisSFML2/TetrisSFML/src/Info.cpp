#include  "Info.h"
#include "Cell.h"

Info::Info()
{
    if(!font.loadFromFile("arial.ttf"))
    {
        throw std::exception("Can't open font file");
    }
    scopes.push_back(0);
}

void Info::draw(sf::RenderWindow& window) const
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(Cell::getSize());
    text.setFillColor(sf::Color::Red);

    auto curPos = m_pos;
    for(auto & scope : scopes)
    {
        text.setPosition(curPos.x * Cell::getSize(), curPos.y * Cell::getSize());
        text.setString(std::to_string(scope));
        window.draw(text);
        curPos.y += 1;
    }
}

void Info::setScope(unsigned scope)
{
    scopes.back() = scope * 100;
}

void Info::fixScope()
{
    scopes.push_back(0);
}

void Info::setPos(sf::Vector2u pos)
{
    m_pos = pos;
}
