#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iomanip>

typedef int Coord;

struct Point
{
    Coord row = -1;
    Coord col = -1;
};

std::istream & operator>>(std::istream & is, Point & p)
{
    is >> p.row >> p.col;
    return is;
}

std::ostream & operator<<(std::ostream & os, const Point & p)
{
    os
        << "("
        << std::setw(2) << p.row << ", "
        << std::setw(2) << p.col
        << ")"
        ;

    return os;
}

struct Line
{
    Point p1;
    Point p2;

    Point topLeftCorner() const
    {
        Coord row = (std::min)(p1.row, p2.row);
        Coord col = (std::min)(p1.col, p2.col);

        Point ret;
        ret.row = row;
        ret.col = col;

        return ret;
    }


    Point bottomRightCorner() const
    {
        Coord row = (std::max)(p1.row, p2.row);
        Coord col = (std::max)(p1.col, p2.col);

        Point ret;
        ret.row = row;
        ret.col = col;

        return ret;
    }
};

std::ostream & operator<<(std::ostream & os, const Line & line)
{
    os
        << "{"
        << line.p1 << "-"
        << line.p2
        << "}"
        ;

    return os;
}

class MagicWorld
{
public:
    MagicWorld()
    {
        init();
        step01_fillLines();
        step02_alg01_printLinesAsRect();
        step99_printAnswer();
    }

private:
    void init()
    {
        std::cin >> m_rows >> m_cols >> k;

        for (size_t i = 0; i < k; i++)
        {
            Point live;
            std::cin >> live;
            lives.push_back(live);
        }

        for (size_t i = 0; i < k; i++)
        {
            Point magic;
            std::cin >> magic;
            magics.push_back(magic);
        }

        std::vector<char> row = std::vector<char>(m_cols, firstLetter);
        table.resize(m_rows);
        for (size_t i = 0; i < m_rows; i++)
        {
            table[i] = row;
        }
    }
    
    void step01_fillLines()
    {
        for (size_t i = 0; i < k; i++)
        {
            Line line;
            line.p1 = lives[i];
            line.p2 = magics[i];
            lines.push_back(line);
        }
    }

    void printLineInTableAsRect(const Line & line, char letter)
    {
        Point tl = line.topLeftCorner();
        Point br = line.bottomRightCorner();

//         std::cout << "line=" << line << "; ";
// 
//         std::cout
//             << "tl=" << tl << "; "
//             << "br=" << br << "; "
//             << std::endl;

        for (size_t row = tl.row; row <= br.row; ++row)
        {
            for (size_t col = tl.col; col <= br.col; ++col)
            {
                table[row][col] = letter;
            }
        }
    }

    void step02_alg01_printLinesAsRect()
    {
        int index = 0;
        for (auto & line : lines)
        {
            char letter = firstLetter + index;
            printLineInTableAsRect(line, letter);
            index++;
        }
    }

    void step99_printAnswer()
    {
        for (auto & row : table)
        {
            static bool isFirstRow = true;
            if (!isFirstRow)
                std::cout << std::endl;

            isFirstRow = false;

            for (auto & ch : row)
            {
                std::cout << ch;
            }            
        }
    }

    int m_rows, m_cols, k;
    std::vector<Point> lives;
    std::vector<Point> magics;
    std::vector<std::vector<char> > table;
    std::vector<Line> lines;
    const char firstLetter = 'a';

};

int main()
{
    MagicWorld mw;
}
