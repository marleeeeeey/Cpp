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
    labelFont = font;
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


    std::vector<std::string> labelLines = 
    {
        "TetrisSFML",
        "v1.0",
        "by Sergey Tyulenev",
        "marleeeeeey@gmail.com"
    };

    text.setScale(0.7, 1);
    text.setCharacterSize(text.getCharacterSize() / 1.6);
    text.setFillColor(sf::Color::Yellow);
    auto labelPos = m_pos;
    labelPos.y += m_linesNumber - labelLines.size() + 1;
    for(auto& line : labelLines)
    {
        text.setPosition((labelPos.x - 0.7) * Cell::getSize(), labelPos.y * Cell::getSize());
        text.setString(line);
        window.draw(text);
        labelPos.y += 1;
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

void Info::setLinesNumber(unsigned linesNumber)
{
    m_linesNumber = linesNumber;
}
