#include <SFML/Graphics.hpp>
#include <sstream>
#include <optional>

void setOriginPointInCenter(sf::Shape& shape)
{
    auto localBound = shape.getLocalBounds();
    shape.setOrigin({ localBound.width / 2, localBound.height / 2 });
}

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
    sf::RectangleShape shape(size);
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    setOriginPointInCenter(shape);
    return shape;
}

sf::CircleShape createCircleShape(const float radius, const sf::Vector2f pos)
{
    sf::CircleShape shape(radius);
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    setOriginPointInCenter(shape);
    return shape;
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

sf::RectangleShape extractInsideRectShape(const sf::CircleShape & circleShape)
{
    float insideRectSize = cos(45) * circleShape.getRadius() * 2;
    sf::RectangleShape rectShape = createRectangleShape(
        {insideRectSize, insideRectSize}, circleShape.getPosition());
    setOriginPointInCenter(rectShape);
    return rectShape;
}

bool isIntersect(const sf::Shape & movedShape, const sf::Shape & statShape)
{
    const auto& insideRect = movedShape.getGlobalBounds();
    const auto& rect = statShape.getGlobalBounds();
    return insideRect.intersects(rect);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFMLCollisionTest");
    auto text = createDefaultTextObject();
    auto rectangleShape = createRectangleShape({100, 100}, {510, 300});
    auto circleShape = createCircleShape(20, {510, 300});
    sf::RectangleShape insideRectShape = extractInsideRectShape(circleShape);

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

            doMove(circleShape, event);
            doMove(insideRectShape, event);
        }


        std::ostringstream ss;
        ss << "intersect=" << isIntersect(insideRectShape, rectangleShape) << std::endl;

        window.clear();

        text.setString(ss.str());
        window.draw(text);
        window.draw(insideRectShape);
        window.draw(rectangleShape);
        window.draw(circleShape);

        window.display();
    }

    return 0;
}
