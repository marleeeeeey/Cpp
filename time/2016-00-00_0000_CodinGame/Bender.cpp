#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

enum
{
    e_start = '@',
    e_border = '#',
    e_finish = '$',
    e_rock = 'X',
    e_down = 'S',
    e_right = 'E',
    e_up = 'N',
    e_left = 'W',
};

enum Trend
{
    e_forward,
    e_back,
};

struct Pos
{
    int x, y;
};

ostream & operator<<(ostream & os, const Pos & d)
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
        print();
        solve();
    }

private:
    void init()
    {
        int L;
        int C;
        cin >> L >> C; cin.ignore();
        for (int i = 0; i < L; i++)
        {
            string row;
            getline(cin, row);

            m_strings.push_back(row);
        }

        findStartPos();
    }

    void print()
    {
        for (auto & str : m_strings)
        {
            cerr << str << endl;
        }
    }

    void solve()
    {

        calcDirection();

        cout << "answer" << endl;
    }

    void calcDirection()
    {
        m_curDirection = m_curDirection % m_directions.size();



        cerr << "calcDirection = " << m_curDirection << endl;
    }

    void findStartPos()
    {
        int row = 0;

        for (const auto & str : m_strings)
        {
            int col = 0;

            for (const auto & ch : str)
            {
                if (ch == e_start)
                {
                    m_curPos = { col, row };
                    cerr << "startPos = " << m_curPos << endl;
                    return;
                }

                col++;
            }

            row++;
        }

        cerr << "error: not start pos";
        exit(1);
    }

    const vector<string> m_directions =
        vector<string> { "SOUTH", "EAST", "NORTH", "WEST" };

    vector<string> m_strings;
    Pos m_curPos = Pos{ 0, 0 };
    int m_curDirection = 0;
    Trend m_trend;
};

int main()
{
    Brain();
}