#define NOMINMAX
#include <ctime>
#include "Windows.h"
#include "ObjectFactory.h"
#include "World.h"
#include "HelperFunctions.h"
#include "LevelGenerator.h"

int main()
{
    if constexpr (false) // set true to hide console
    {
        auto hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    }

    srand(time(nullptr));

    sf::Vector2f windowSize = { 800, 600 };
    auto objectFactory = std::make_shared<ObjectFactory>();
    auto levelGenerator = std::make_shared<LevelGenerator>(objectFactory, windowSize);
    auto world = std::make_shared<World>(objectFactory, levelGenerator, windowSize);
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
        previousTimeStamp = currentTime;
        world->updateState(optEvent, timeDiff);
        window.clear();
        world->draw(window);
        window.display();
    }

    return 0;
}
