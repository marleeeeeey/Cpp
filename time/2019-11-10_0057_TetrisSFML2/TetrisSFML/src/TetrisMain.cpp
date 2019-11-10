#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
    //window.setFramerateLimit(5);
    Game game({8, 16});
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            game.dispatchKey(event);
        }
        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}