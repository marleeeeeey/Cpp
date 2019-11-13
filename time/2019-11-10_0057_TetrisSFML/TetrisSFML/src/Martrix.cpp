#include "Matrix.h"

void Matrix::makeBorders()
{
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

void Matrix::clear()
{
    m_removedLineCounter = 0;

    m_cellTable.clear();
    m_cellTable.resize(m_size.y);
    for (auto & line : m_cellTable)
    {
        line.resize(m_size.x);
    }

    makeBorders();
}

unsigned Matrix::getRemovedLineCounter()
{
    return m_removedLineCounter;
}

Matrix::Matrix(sf::Vector2u size)
{
    // borders offset
    m_size = size;
    m_size.x += 2;
    m_size.y += 1;

    clear();
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

    removeFullLines();
}

bool Matrix::checkCollision(const Object& object)
{
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

void Matrix::removeFullLines()
{
    // do not read last line - it is always full
    for(unsigned row = 0; row < m_cellTable.size()-1; ++row)
    {
        bool isLineFull = true;
        const auto& line = m_cellTable[row];
        for(const auto & cell : line)
        {
            if(!cell.isVisible())
            {
                isLineFull = false;
                break;
            }
        }
        if(isLineFull)
        {
            unsigned lineSize = line.size();
            m_cellTable.erase(m_cellTable.begin() + row);
            m_removedLineCounter++;
            Line emptyLine(lineSize);
            m_cellTable.push_front(emptyLine);
            makeBorders();
        }
    }
}
