#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Ball
{
    sf::CircleShape ballShape;
    float ballRadius = 10.f;
    sf::Sound ballSound;

public:
    Ball();
    void setPosition(float x, float y);
    const sf::Vector2f& getPosition() const;
    void move(float offsetX, float offsetY);
    void changeRandomColor();
    void draw(sf::RenderWindow& window) const;
    float getRadius() const;
    void setSoundBuffer(const sf::SoundBuffer& ballSoundBuffer);
    void playSound();
};
