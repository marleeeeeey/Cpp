#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

namespace HelperFunctions
{
    bool isKeyPressed(sf::Event event, sf::Keyboard::Key key);

    sf::Font getDefaultFont();

    sf::RectangleShape createRectangleShape(sf::Vector2f size, sf::Vector2f pos, bool isCenter = true);
    sf::RectangleShape createRectangleShape(const sf::FloatRect& rect);
    sf::CircleShape createCircleShape(const float radius, const sf::Vector2f pos);

    sf::RectangleShape extractInsideRectShape(const sf::CircleShape& circleShape);
    std::optional<sf::FloatRect> getIntersectRect(const sf::Shape& shape1, const sf::Shape& shape2);
    std::optional<sf::RectangleShape> getIntersectRectShape(const sf::Shape& shape1, const sf::Shape& shape2);
    bool isIntersect(const sf::Shape& shape1, const sf::Shape& shape2);
}

namespace hf = HelperFunctions;

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& vec);

std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect);

std::ostream& operator<<(std::ostream& os, const sf::RectangleShape& shape);
