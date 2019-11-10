#include "Matrix.h"

Matrix::Matrix(sf::Vector2u size)
{
    // borders offset
    size.x += 2;
    size.y += 1;

    m_cellTable.resize(size.y);
    for (auto & line : m_cellTable)
    {
        line.resize(size.x);
    }

    for (auto & line : m_cellTable)
    {
        line.front().setVisible(true);
        line.back().setVisible(true);
    }

    for(auto & cell : m_cellTable.back())
    {
        cell.setVisible(true);
    }
}

void Matrix::add(const Object& object)
{
    for(unsigned row = 0; row < m_cellTable.size(); ++row)
    {
        auto& line = m_cellTable[row];
        for(unsigned col = 0; col < line.size(); ++col)
        {
            auto& matrixCell = line[col];
            if(object.isVisible({ col, row }))
                matrixCell = object.getCell({ col, row });
        }
    }
}

bool Matrix::checkCollision(const Object& object)
{
    if(object.getPos().x < 0)
        return true;


    for(unsigned row = 0; row < m_cellTable.size(); ++row)
    {
        const auto& line = m_cellTable[row];
        for(unsigned col = 0; col < line.size(); ++col)
        {
            const auto& matrixCell = line[col];
            if(matrixCell.isVisible() && object.isVisible({ col, row }))
            {
                return true;                
            }
        }
    }

    return false;
}

void Matrix::draw(sf::RenderWindow& window)
{
    for(unsigned row = 0; row < m_cellTable.size(); ++row)
    {
        const auto & line = m_cellTable[row];
        for(unsigned col = 0; col < line.size(); ++col)
        {
            const auto& cell = line[col];
            cell.draw(window, {col, row});
        }
    }
}
