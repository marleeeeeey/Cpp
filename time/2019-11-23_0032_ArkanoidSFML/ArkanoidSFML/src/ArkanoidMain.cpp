#define NOMINMAX
#include "Windows.h"
#include <ctime>
#include "ObjectFactory.h"
#include "GameEngine.h"
#include "World.h"
#include "HelperFunctions.h"
#include <cassert>
#include <iostream>

int main()
{
    if (false) // set true to hide console
    {
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    }

    srand(time(NULL));

    auto objectFactory = std::make_shared<ObjectFactory>();
    sf::Vector2f windowSize = {800, 600};
    auto world = std::make_shared<World>(objectFactory, windowSize);
    GameEngine gameEngine(world);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Arkanoid");
    sf::Clock clock;
    auto previousTimeStamp = clock.getElapsedTime();
    while (window.isOpen())
    {
        std::optional<sf::Event> optEvent;
        sf::Event tempEvent;
        if (window.pollEvent(tempEvent))
        {
            if (tempEvent.type == sf::Event::Closed
                || hf::isKeyPressed(tempEvent, sf::Keyboard::Escape))
            {
                window.close();
            }

            optEvent = tempEvent;
        }

        auto currentTime = clock.getElapsedTime();
        auto timeDiff = currentTime - previousTimeStamp;
        assert(timeDiff.asSeconds() >= 0);
        previousTimeStamp = currentTime;
        gameEngine.setEvent(optEvent, timeDiff);
        window.clear();
        gameEngine.draw(window);
        window.display();
    }

    return 0;
}
