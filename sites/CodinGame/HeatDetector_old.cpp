#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const float div_std = 2;
const float div_min = 1.5;
const float div_mini = 1.1;
const float pers = 0.9;

enum Ver
{
    e_thisRow = 0,
    e_up = -1,
    e_down = 1,
};
enum Hor
{
    e_thisCol = 0,
    e_left = -1,
    e_right = 1,
};
struct Direct
{
    Ver ver;
    Hor hor;
};

int wight;
int height;
int countSteps;
int batX;
int batY;

Direct direct;
Direct prevDirect;
int outX;
int outY;
int stepX;
int stepY;

void directInit(string & bombDir)
{
    direct.hor = e_thisCol;
    direct.ver = e_thisRow;

    switch (bombDir.size())
    {
    case  2:
    {
        char fistSymb = bombDir[0];

        switch (fistSymb)
        {
        case 'U':
            direct.ver = e_up;
            break;
        case 'D':
            direct.ver = e_down;
            break;
        }

        char secondSymb = bombDir[1];

        switch (secondSymb)
        {
        case 'L':
            direct.hor = e_left;
            break;
        case 'R':
            direct.hor = e_right;
            break;
        }
    }

    break;

    case 1:
    {
        char symb = bombDir[0];

        if (symb == 'L')
            direct.hor = e_left;

        switch (symb)
        {
        case 'L':
            direct.hor = e_left;
            break;
        case 'R':
            direct.hor = e_right;
            break;
        case 'U':
            direct.ver = e_up;
            break;
        case 'D':
            direct.ver = e_down;
            break;
        default:
            break;
        }


    }
    break;
    }

    cerr << "directInit:"
        << " ver=" << direct.ver
        << " hor=" << direct.hor
        << endl;
}

void stepInit()
{
    stepX = 0;
    stepY = 0;

    switch (direct.hor)
    {
    case e_left:
        stepX = batX;
        break;
    case e_right:
        stepX = wight - batX;
        break;
    }

    switch (direct.ver)
    {
    case e_up:
        stepY = batY;
        break;
    case e_down:
        stepY = height - batY;
        break;
    }

    cerr << "stepInit(): stepX=" << stepX << " stepY=" << stepY << endl;
}

int main()
{
    cin >> wight >> height; cin.ignore();
    cin >> countSteps; cin.ignore();
    cin >> batX >> batY; cin.ignore();

    cerr << "IN: "
        << " w=" << wight
        << " h=" << height
        << " s=" << countSteps
        << " batX=" << batX
        << " batY=" << batY
        << endl;

    while (1)
    {
        string bombDir;
        cin >> bombDir; cin.ignore();
        directInit(bombDir);

        static bool firstRun = true;

        if (firstRun)
        {
            stepInit();
            firstRun = false;

            (float)stepX / wight > pers ? stepX /= div_mini : stepX /= div_std;
            (float)stepY / height > pers ? stepY /= div_mini : stepY /= div_std;
        }
        else
        {
            prevDirect.ver == direct.ver ? stepY /= div_min : stepY /= div_std;
            prevDirect.hor == direct.hor ? stepX /= div_min : stepX /= div_std;
        }

        if (stepX == 0) { stepX = 1; }
        if (stepY == 0) { stepY = 1; }

        cerr << "calc step:"
            << " stepX=" << stepX
            << " stepY=" << stepY
            << endl;

        batX += direct.hor * stepX;
        batY += direct.ver * stepY;

        if (batX >= wight)  batX = wight - 1, stepX /= div_std;
        if (batX < 0)       batX = 0, stepX /= div_std;
        if (batY >= height) batY = height - 1, stepY /= div_std;
        if (batY < 0)       batY = 0, stepY /= div_std;

        cout << batX << " " << batY << endl;

        prevDirect = direct;
    }
}