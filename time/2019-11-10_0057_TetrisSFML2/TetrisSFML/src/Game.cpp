#include  "Game.h"

Game::Game(sf::Vector2u size)
    : m_matrix(size)
{
    m_lastTimeStemp = clock.getElapsedTime();
    m_nextObject.setPos({ 20, 0 });
    m_object.setPos({ 1, 0 });
    m_isAcselerate = false;
}

void Game::draw(sf::RenderWindow& window)
{
    auto currentTime = clock.getElapsedTime();
    auto timeDiff = currentTime - m_lastTimeStemp;
    sf::Time period = sf::seconds(0.5);
    if(m_isAcselerate)
        period = sf::seconds(0.05);
    if(timeDiff > period)
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        auto moved = m_object.getMoved(-1, 0);
        if(!m_matrix.checkCollision(moved))
            m_object = moved;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        auto moved = m_object.getMoved(+1, 0);
        if(!m_matrix.checkCollision(moved))
            m_object = moved;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_isAcselerate = true;
    }
    else
    {
        m_isAcselerate = false;
    }
}