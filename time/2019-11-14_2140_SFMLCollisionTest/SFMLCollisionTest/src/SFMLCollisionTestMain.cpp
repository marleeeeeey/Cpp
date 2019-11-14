#include <SFML/Graphics.hpp>
#include <sstream>
#include <optional>

void setOriginPointInCenter(sf::Shape& shape)
{
    auto localBound = shape.getLocalBounds();
    auto thickness = shape.getOutlineThickness();
    shape.setOrigin({
        localBound.width / 2 - thickness,
        localBound.height / 2 - thickness
    });
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
        << "pos:(" << rect.left << ", " << rect.top << "), "
        << "size:(" << rect.width << ", " << rect.height << ")";
    return os;
}

sf::RectangleShape createRectangleShape(sf::Vector2f size, sf::Vector2f pos, bool isCenter = true)
{
    sf::RectangleShape shape(size);
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    if (!isCenter)
    {
        shape.move({size.x / 2, size.y / 2});
    }
    setOriginPointInCenter(shape);
    return shape;
}

sf::RectangleShape createRectangleShape(const sf::FloatRect& rect)
{
    return createRectangleShape({rect.width, rect.height}, {rect.left, rect.top}, false);
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

sf::RectangleShape extractInsideRectShape(const sf::CircleShape& circleShape)
{
    float insideRectSize = cos(45) * circleShape.getRadius() * 2;
    sf::RectangleShape rectShape = createRectangleShape(
        {insideRectSize, insideRectSize}, circleShape.getPosition());
    setOriginPointInCenter(rectShape);
    return rectShape;
}

std::optional<sf::FloatRect> getIntersectRect(const sf::Shape& shape1, const sf::Shape& shape2)
{
    const auto& insideRect = shape1.getGlobalBounds();
    const auto& rect = shape2.getGlobalBounds();
    sf::FloatRect outFloatRect;
    auto isIntersect = insideRect.intersects(rect, outFloatRect);
    if (isIntersect)
        return outFloatRect;

    return {};
}

std::optional<sf::RectangleShape> getIntersectRectShape(const sf::Shape& shape1, const sf::Shape& shape2)
{
    auto instersectRect = getIntersectRect(shape1, shape2);

    if (instersectRect)
    {
        auto rectShape = createRectangleShape(instersectRect.value());
        rectShape.setOutlineThickness(0);
        rectShape.setFillColor(sf::Color(100, 100, 100, 200));
        return rectShape;
    }

    return {};
}

bool isIntersect(const sf::Shape& shape1, const sf::Shape& shape2)
{
    return getIntersectRect(shape1, shape2).has_value();
}

std::ostream& operator<<(std::ostream& os, const sf::RectangleShape& shape)
{
    os
        << "pos:(" << shape.getPosition().x << ", " << shape.getPosition().y << "), "
        << "size:(" << shape.getSize().x << ", " << shape.getSize().y << ")";
    return os;
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

        auto intersectRectShape = getIntersectRectShape(insideRectShape, rectangleShape);
        std::ostringstream ss;
        ss << "intersect=" << intersectRectShape.has_value() << std::endl;

        window.clear();

        window.draw(insideRectShape);
        window.draw(rectangleShape);
        window.draw(circleShape);
        if (intersectRectShape)
        {
            ss << intersectRectShape.value() << std::endl;
            window.draw(intersectRectShape.value());
        }
        text.setString(ss.str());
        window.draw(text);

        window.display();
    }

    return 0;
}
