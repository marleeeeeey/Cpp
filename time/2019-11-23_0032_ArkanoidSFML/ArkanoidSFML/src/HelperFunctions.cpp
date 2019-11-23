#include "HelperFunctions.h"

using namespace HelperFunctions;

void setOriginPointInCenter(sf::Shape& shape)
{
    auto localBound = shape.getLocalBounds();
    auto thickness = shape.getOutlineThickness();
    shape.setOrigin({
        localBound.width / 2 - thickness,
        localBound.height / 2 - thickness
    });
}

bool HelperFunctions::isKeyPressed(sf::Event event, sf::Keyboard::Key key)
{
    return (event.type == sf::Event::EventType::KeyPressed
        && event.key.code == key);
}

sf::Font HelperFunctions::getDefaultFont()
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

sf::RectangleShape HelperFunctions::createRectangleShape(sf::Vector2f size, sf::Vector2f pos, bool isCenter)
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

sf::RectangleShape HelperFunctions::createRectangleShape(const sf::FloatRect& rect)
{
    return createRectangleShape({rect.width, rect.height}, {rect.left, rect.top}, false);
}

sf::CircleShape HelperFunctions::createCircleShape(const float radius, const sf::Vector2f pos)
{
    sf::CircleShape shape(radius);
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    setOriginPointInCenter(shape);
    return shape;
}

sf::RectangleShape HelperFunctions::extractInsideRectShape(const sf::CircleShape& circleShape)
{
    float insideRectSize = cos(45) * circleShape.getRadius() * 2;
    sf::RectangleShape rectShape = createRectangleShape(
        {insideRectSize, insideRectSize}, circleShape.getPosition());
    setOriginPointInCenter(rectShape);
    return rectShape;
}

std::optional<sf::FloatRect> HelperFunctions::getIntersectRect(const sf::Shape& shape1, const sf::Shape& shape2)
{
    const auto& insideRect = shape1.getGlobalBounds();
    const auto& rect = shape2.getGlobalBounds();
    sf::FloatRect outFloatRect;
    auto isIntersect = insideRect.intersects(rect, outFloatRect);
    if (isIntersect)
        return outFloatRect;

    return {};
}

std::optional<sf::RectangleShape> HelperFunctions::getIntersectRectShape(const sf::Shape& shape1,
                                                                         const sf::Shape& shape2)
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

bool HelperFunctions::isIntersect(const sf::Shape& shape1, const sf::Shape& shape2)
{
    return getIntersectRect(shape1, shape2).has_value();
}

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect)
{
    os
        << "pos:(" << rect.left << ", " << rect.top << "), "
        << "size:(" << rect.width << ", " << rect.height << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const sf::RectangleShape& shape)
{
    os
        << "pos:(" << shape.getPosition().x << ", " << shape.getPosition().y << "), "
        << "size:(" << shape.getSize().x << ", " << shape.getSize().y << ")";
    return os;
}
