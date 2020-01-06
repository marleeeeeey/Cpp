#include "Info.h"
#include "Cell.h"

Info::Info()
{
    std::string fontFileName = "C:\\Windows\\Fonts\\calibri.ttf";
    if (!font.loadFromFile(fontFileName))
    {
        std::string msg = "Can't open font file " + fontFileName;
        throw std::runtime_error(msg);
    }
    scopes.push_front(0);
}


void Info::draw(sf::RenderWindow& window) const
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(Cell::getSize());

    auto curPos = m_pos;
    text.setPosition(curPos.x * Cell::getSize(), curPos.y * Cell::getSize());
    text.setString("Scopes:");
    window.draw(text);
    curPos.y += 2;

    for(auto it = scopes.begin(); it != scopes.end(); ++it, ++curPos.y)
    {
        if(it == scopes.begin())
        {
            text.setFillColor(sf::Color::Green);
        }
        else
        {
            text.setFillColor(sf::Color::Red);
        }

        const auto scope = *it;
        text.setPosition(curPos.x * Cell::getSize(), curPos.y * Cell::getSize());
        text.setString(std::to_string(scope));
        window.draw(text);
    }
}

void Info::setScope(unsigned scope)
{
    scopes.front() = scope * 100;
}

void Info::fixScope()
{
    scopes.push_front(0);
    if(scopes.size() > 10)
    {
        scopes.pop_back();
    }
}

void Info::setPos(sf::Vector2u pos)
{
    m_pos = pos;
}
