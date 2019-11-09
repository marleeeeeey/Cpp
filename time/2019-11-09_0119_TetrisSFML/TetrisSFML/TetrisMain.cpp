#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include <iostream>
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Game game;

    // run the program as long as the window is open
    while(window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while(window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed)
                window.close();
        }

        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(800, 600));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(0, 0);        

        sf::Texture texture;
        if(!Collision::CreateTextureAndBitmask(texture, "Untitled-1.png"))
        {
            throw std::exception("Cant load texture");
        }

        sf::Texture texture2;
        if(!Collision::CreateTextureAndBitmask(texture2, "Untitled-2.png"))
        {
            throw std::exception("Cant load texture");
        }

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.5, 0.5);

        sf::Sprite sprite2;
        sprite2.setTexture(texture2);
        sprite2.setScale(0.5, 0.5);
        sprite2.setPosition(35, 20);

        bool result = Collision::PixelPerfectTest(sprite, sprite2);
        std::cout << "result=" << result << std::endl;


        window.draw(rectangle);
        window.draw(sprite);
        window.draw(sprite2);
        game.drawOn(window);
        window.display();
    }

    return 0;
}
