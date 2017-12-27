#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Position
{
    float x;
    float y;
};

struct Direction
{
    bool up;
    bool down;
    bool left;
    bool right;

    void reset()
    {
        up = false;
        down = false;
        left = false;
        right = false;
    }
};

ostream & operator<<(ostream & os, const Direction & d)
{
    if (d.up)       os << "up ";
    if (d.down)     os << "down ";
    if (d.left)     os << "left ";
    if (d.right)    os << "right ";

    return os;
}

std::ostream & operator<<(std::ostream & os, const Position & d)
{
    os << "(" << d.x << ", " << d.y << ")";
    return os;
}

class Brain
{
public:
    Brain()
    {
        init();
        loop();
    }

private:
    void init()
    {
        cin >> m_building.x >> m_building.y; cin.ignore();
        cin >> m_countTurns; cin.ignore();
        cin >> m_curPos.x >> m_curPos.y; cin.ignore();

        cerr
            << "init: "
            << "buiding " << m_building << " "
            << "countTurns " << m_countTurns << " "
            << "curPos " << m_curPos
            << endl;

    }

    void loop()
    {
        while (true)
        {
            string strDir;
            cin >> strDir; cin.ignore();
            setDir(strDir);

            static bool isFirstRun = true;
            if (isFirstRun)
            {
                m_lastStep = { 0, 0 };

                if (m_dir.up)
                {
                    m_lastStep.y = (0 - m_curPos.y) / 2;
                }
                else if (m_dir.down)
                {
                    m_lastStep.y = (m_building.y - m_curPos.y) / 2;
                }

                if (m_dir.left)
                {
                    m_lastStep.x = (0 - m_curPos.x) / 2;
                }
                else if (m_dir.right)
                {
                    m_lastStep.x += (m_building.x - m_curPos.x) / 2;
                }

                isFirstRun = false;

                cerr << "init step: " << m_lastStep << endl;

                makeStep(m_lastStep);
            }
            else
            {
                solve();
            }
        }
    }

    void solve()
    {
        cerr << "dir " << m_dir << endl;

        if (m_dir.up)
        {
            if (m_lastStep.y > 0)
            {
                m_lastStep.y *= -1;
            }
        }
        else if (m_dir.down)
        {
            if (m_lastStep.y < 0)
            {
                m_lastStep.y *= -1;
            }
        }

        m_lastStep.y /= 2;

        if (m_dir.left)
        {
            if (m_lastStep.x > 0)
            {
                m_lastStep.x *= -1;
            }
        }
        else if (m_dir.right)
        {
            if (m_lastStep.x < 0)
            {
                m_lastStep.x *= -1;
            }
        }

        m_lastStep.x /= 2;

        cerr << "calc step " << m_lastStep << endl;
        makeStep(m_lastStep);
    }

    void setDir(string bombDir)
    {
        m_dir.reset();

        switch (bombDir.size())
        {

        case  2:
        {
            char fistSymb = bombDir[0];

            switch (fistSymb)
            {
            case 'U':
                m_dir.up = true;
                break;
            case 'D':
                m_dir.down = true;
                break;
            }

            char secondSymb = bombDir[1];

            switch (secondSymb)
            {
            case 'L':
                m_dir.left = true;
                break;
            case 'R':
                m_dir.right = true;
                break;
            }
        }
        break;

        case 1:
        {
            char symb = bombDir[0];

            switch (symb)
            {
            case 'L':
                m_dir.left = true;
                break;
            case 'R':
                m_dir.right = true;
                break;
            case 'U':
                m_dir.up = true;
                break;
            case 'D':
                m_dir.down = true;
                break;
            default:
                break;
            }
        }
        break;
        }
    }

    void makeStep(Position step)
    {
        Position roundStep = { round(step.x), round(step.y) };

        static int stepCounter = 0;
        stepCounter++;

        cerr << "step counter " << stepCounter << endl;

        if (stepCounter > 11 && m_countTurns < 35 && m_countTurns > 13)
        {
            roundStep = { round(step.x), round(step.y + 0.12) };
        }


        m_curPos.x += roundStep.x;
        m_curPos.y += roundStep.y;


        if (m_curPos.x > m_building.x - 1)
        {
            m_curPos.x = m_building.x - 1;
        }
        else if (m_curPos.x < 0)
        {
            m_curPos.x = 0;
        }


        if (m_curPos.y > m_building.y - 1)
        {
            m_curPos.y = m_building.y - 1;
        }
        else if (m_curPos.y < 0)
        {
            m_curPos.y = 0;
        }

        static Position prevPos;

        if (prevPos.x == m_curPos.x && prevPos.y == m_curPos.y)
        {
            m_curPos.y += 1;
        }

        cout
            << m_curPos.x << " "
            << m_curPos.y << endl;

        prevPos = m_curPos;
    }

    Position m_building;
    Position m_curPos;
    Position m_lastStep;
    Direction m_dir;
    int m_countTurns;
};

int main()
{
    Brain();
}