#include <SFML/Graphics.hpp>
#include <iostream>

bool isKeyPressed(sf::Event event, sf::Keyboard::Key key)
{
    return (event.type == sf::Event::EventType::KeyPressed
        && event.key.code == key);
}

sf::Font getDefaultFont()
{
    sf::Font font;
    std::string fontFileName = "C:\\Windows\\Fonts\\calibri.ttf";
    if(!font.loadFromFile(fontFileName))
    {
        std::string msg = "Can't open font file " + fontFileName;
        throw std::exception(msg.c_str());
    }

    return font;
}

std::ostream & operator<<(std::ostream& os, const sf::FloatRect& rect)
{
    os
        << rect.left << ", "
        << rect.top << ", "
        << rect.width << ", "
        << rect.height
        ;
    return os;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFMLCollisionTest");
    
    sf::RectangleShape r1({ 100, 100 });
    sf::RectangleShape r2({ 100, 100 });
    r1.setPosition(400, 300);
    r1.setFillColor(sf::Color::Transparent);
    r1.setOutlineColor(sf::Color::White);
    r1.setOutlineThickness(2);
    r2.setPosition(510, 300);
    r2.setFillColor(sf::Color::Transparent);
    r2.setOutlineColor(sf::Color::White);
    r2.setOutlineThickness(2);

    auto font = getDefaultFont();
    sf::Text t1("text", font);
    t1.setFillColor(sf::Color::White);
    t1.setPosition(10, 10);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if(isKeyPressed(event, sf::Keyboard::Key::Up))
            {
                r1.move({ 0, -1 });
            }
            if(isKeyPressed(event, sf::Keyboard::Key::Down))
            {
                r1.move({ 0, +1 });
            }
            if(isKeyPressed(event, sf::Keyboard::Key::Left))
            {
                r1.move({ -1, 0 });
            }
            if(isKeyPressed(event, sf::Keyboard::Key::Right))
            {
                r1.move({ +1, 0 });
            }
        }


        const auto& rect1 = r1.getGlobalBounds();
        const auto& rect2 = r2.getGlobalBounds();
        
        window.clear();

        t1.setString(std::to_string(rect1.intersects(rect2)));
        window.draw(t1);
        window.draw(r1);
        window.draw(r2);

        window.display();
    }

    return 0;
}
