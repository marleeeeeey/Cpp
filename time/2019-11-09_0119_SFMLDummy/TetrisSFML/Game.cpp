#pragma once
#include "Game.h"

Game::Game()
{
    m_matrix.resize(rows);    
    for(unsigned row = 0; row < rows; ++row)
    {
        auto& curRow = m_matrix[row];
        for(unsigned col = 0; col < cols; ++col)
        {
            Item item;
            item.setPosition(row, col);
            curRow.push_back(item);
        }
    }
    
    m_colors[0] = sf::Color::Blue;
    m_colors[1] = sf::Color::Red;
}

void Game::setTime(sf::Time time)
{
}

void Game::setKeyEvent(sf::Event keyEvent)
{
}

void Game::resume()
{
}

void Game::pause()
{
}

void Game::drawOn(sf::RenderWindow & window)
{
    for(unsigned row = 0; row < rows; ++row)
    {
        auto& curRow = m_matrix[row];
        for(unsigned col = 0; col < cols; ++col)
        {
            auto& curItem = curRow[col];
            auto& color = m_colors[curItem.value];
            curItem.rect.setFillColor(color);
            window.draw(curItem.rect);
        }
    }
}