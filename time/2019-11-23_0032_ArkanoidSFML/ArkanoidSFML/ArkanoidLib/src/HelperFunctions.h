#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <sstream>

namespace HelperFunctions
{
    bool isKeyPressed(sf::Event event, sf::Keyboard::Key key);

    sf::Font getDefaultFont();

    sf::RectangleShape createRectangleShape(sf::Vector2f size, sf::Vector2f pos, bool isCenter = true);
    sf::RectangleShape createRectangleShape(const sf::FloatRect& rect);
    sf::CircleShape createCircleShape(const float radius, const sf::Vector2f pos);
    void setTextCenterTo(sf::Text& text, sf::Vector2f centerPos);

    sf::RectangleShape extractInsideRectShape(const sf::CircleShape& circleShape);
    std::optional<sf::FloatRect> getIntersectRect(const sf::Shape& shape1, const sf::Shape& shape2);
    std::optional<sf::RectangleShape> getIntersectRectShape(const sf::Shape& shape1, const sf::Shape& shape2);
    bool isIntersect(const sf::Shape& shape1, const sf::Shape& shape2);

    sf::Color getAlphaColor(sf::Color color, sf::Uint8 alpha);

    template <typename T>
    std::string to_string(const T& value)
    {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }

    template <typename T>
    bool isEqual(T lhs, T rhs)
    {
        return fabs(lhs - rhs) < 0.01;
    }

    int charToInt(char ch);

    int randomInt(int min, int max);

    // trim from start (in place)
    static inline void ltrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
            }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
            }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string& s) {
        ltrim(s);
        rtrim(s);
    }

    // trim from start (copying)
    static inline std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }

    // trim from both ends (copying)
    static inline std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }
}

namespace hf = HelperFunctions;

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& vec);

std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect);

std::ostream& operator<<(std::ostream& os, const sf::RectangleShape& shape);
