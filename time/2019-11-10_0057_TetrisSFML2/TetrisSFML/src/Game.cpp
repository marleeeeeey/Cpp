#include  "Game.h"

Game::Game(sf::Vector2u size)
    : m_matrix(size)
{
    m_lastTimeStemp = clock.getElapsedTime();
    m_nextObject.setPos({ 20, 0 });
    m_object.setPos({ 1, 0 });
}

void Game::draw(sf::RenderWindow& window)
{
    auto currentTime = clock.getElapsedTime();
    auto timeDiff = currentTime - m_lastTimeStemp;
    if(timeDiff > sf::seconds(1))
    {
        auto moved = m_object.getMoved(0, +1);
        bool isCollision = m_matrix.checkCollision(moved);
        if(isCollision)
        {
            m_matrix.add(m_object);
            m_object.setShape(m_nextObject.getShape());
            m_object.setPos({ 1, 0 });
            m_nextObject.generateShape();
        }
        else
        {
            m_object = moved;
        }

        m_lastTimeStemp = currentTime;
    }

    m_matrix.draw(window);
    m_object.draw(window);
    m_nextObject.draw(window);
}

void Game::dispatchKey(sf::Event key)
{
    Object moved;
    bool isMoved = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        moved = m_object.getMoved(-1, 0);
        isMoved = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        moved = m_object.getMoved(+1, 0);        
        isMoved = true;
    }

    if(!isMoved)
        return;

    bool isCollision = m_matrix.checkCollision(moved);
    
    if(!isCollision)
    {
        m_object = moved;
    }
}
