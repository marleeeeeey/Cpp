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
    if (!font.loadFromFile(fontFileName))
    {
        std::string msg = "Can't open font file " + fontFileName;
        throw std::exception(msg.c_str());
    }

    return font;
}

sf::Text createDefaultTextObject(const std::string& msg = "")
{
    static sf::Font defaultFont = getDefaultFont();

    sf::Text text("text", defaultFont);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    text.setString(msg);
    return text;
}

std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect)
{
    os
        << rect.left << ", "
        << rect.top << ", "
        << rect.width << ", "
        << rect.height;
    return os;
}

sf::RectangleShape createRectangleShape(sf::Vector2f size, sf::Vector2f pos)
{
    sf::RectangleShape rect(size);
    rect.setPosition(pos);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(2);
    return rect;
}

void doMove(sf::Shape& moveObject, sf::Event event)
{
    if (isKeyPressed(event, sf::Keyboard::Key::Up))
    {
        moveObject.move({0, -1});
    }
    if (isKeyPressed(event, sf::Keyboard::Key::Down))
    {
        moveObject.move({0, +1});
    }
    if (isKeyPressed(event, sf::Keyboard::Key::Left))
    {
        moveObject.move({-1, 0});
    }
    if (isKeyPressed(event, sf::Keyboard::Key::Right))
    {
        moveObject.move({+1, 0});
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFMLCollisionTest");
    auto text1 = createDefaultTextObject();
    auto rectangleShape1 = createRectangleShape({100, 100}, {400, 300});
    auto rectangleShape2 = createRectangleShape({100, 100}, {510, 300});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                isKeyPressed(event, sf::Keyboard::Key::Escape))
            {
                window.close();
            }

            doMove(rectangleShape1, event);
        }

        const auto& rect1 = rectangleShape1.getGlobalBounds();
        const auto& rect2 = rectangleShape2.getGlobalBounds();

        window.clear();

        text1.setString(std::to_string(rect1.intersects(rect2)));
        window.draw(text1);
        window.draw(rectangleShape1);
        window.draw(rectangleShape2);

        window.display();
    }

    return 0;
}
