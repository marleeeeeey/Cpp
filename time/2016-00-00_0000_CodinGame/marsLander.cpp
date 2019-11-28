#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define DEBUG_ON

template <typename T>
ostream & operator<<(ostream & os, const vector<T> & vec)
{
    cerr << "[" << vec.size() << "]:" << endl;
    int index = 0;
    for (const T & var : vec)
    {
        cerr.width(5);
        cerr << index << ": " << var << endl;
        index++;
    }
    return os;
}

template <typename TKey, typename TValue>
ostream & operator<<(ostream & os, const map<TKey, TValue> & m)
{
    cerr << "[" << m.size() << "]:" << endl;
    int index = 0;

    auto it = m.begin();
    auto itEnd = m.end();
    for (; it != itEnd; it++)
    {
        cerr.width(5);
        cerr << it->first << ": " << it->second << endl;
    }

    return os;
}

#ifdef DEBUG_ON
#define DEBUG_VAR(var) cerr << #var << " = " << (var) << endl
#define DEBUG_NLN(var) cerr << #var << " = " << endl << (var) << endl
#define DEBUG_LN(var) #var << " = " << var << "; "
#define DEBUG_MSG(var) cerr << var << endl
#else
#define DEBUG_VAR(var)  
#define DEBUG_NLN(var)  
#define DEBUG_LN(var) 
#define DEBUG_MSG(var)  
#endif // DEBUG_ON


class EC
{
public:
    EC(int widht = e_stdWidht)
    {
        m_widht = widht;
    }

private:
    friend std::ostream & operator<<(std::ostream & os, EC & obj);

    enum
    {
        e_stdWidht = 5,
    };

    int m_widht;
};

std::ostream & operator<<(std::ostream & os, EC & obj)
{
    os.width(obj.m_widht);
    return os;
}

// ******************************************************************************************

std::vector<float> solveQuad(float a, float b, float c, float result)
{

	std::vector<float> ret;

	c -= result;

	float d = b*b - 4 * a*c;

	if (d == 0)
	{
		ret.push_back(-b / (2 * a));
		return ret;
	}
	else if (d > 0)
	{
		float sqrtD = sqrt(d);

		ret.push_back((-b + sqrtD) / (2 * a));
		ret.push_back((-b - sqrtD) / (2 * a));

		return ret;
	}
	else
	{
		return ret;
	}
}

struct Point
{
    int x;
    int y;
};

ostream & operator<<(ostream & os, const Point & p)
{
    EC wPos(4);
    os << "(" << wPos << p.x << ", " << wPos << p.y << ")";
    return os;
}

float mid(queue<int> q)
{
	int mass = 0;
	int counter = 0;

	while (!q.empty())
	{
		mass += q.front();
		q.pop();
		counter++;
	}

	if (counter == 0)
		return 0;

	return static_cast<float>(mass)/counter;
}

struct Ship
{
    void update()
    {
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();

		int hA = 0;
		int vA = 0;

		static bool isFirstRun = true;
		if (isFirstRun)
		{
			isFirstRun = false;
		}
		else
		{
			hA = hSpeed - prevHSpeed;
			vA = vSpeed - prevVSpeed;
		}

		hAqueue.push(hA);
		vAqueue.push(vA);

		if (vAqueue.size() >= 10)
		{
			hAcceleration = mid(hAqueue);
			vAcceleration = mid(vAqueue);
			vAqueue.pop();
			hAqueue.pop();
		}

		prevVSpeed = vSpeed;
		prevHSpeed = hSpeed;
    }

	float timeToDownFlat(int flatY)
	{
		vector<float> result = solveQuad(vAcceleration / 2, vSpeed, flatY, Y);	
		if (result.size() == 2)
		{
			return result[1];
		}

		return 0;
	}

	float correctTimeToFlat(int flatY)
	{
		float downTime = timeToDownFlat(flatY);
		float correctTime = 0;

		if (downTime != 0)
		{
			m_downTimes.push(downTime);
		}
		else
		{
			m_downTimes = queue<float>();
		}

		if (m_downTimes.size() >= 2)
		{
			float var1 = m_downTimes.front();
			m_downTimes.pop();
			float var2 = m_downTimes.front();
			float diff = abs(var1 - var2);

			DEBUG_VAR(diff);

			if (diff < 3)
			{
				correctTime = downTime;
			}
			else
			{
				correctTime = downTime + 2.2 * diff;
			}			
		}

		DEBUG_VAR(correctTime);
		return correctTime;
	}

	float calPosOnFlatLevel(int flatY)
	{
		float posX = 0;

		float t = correctTimeToFlat(flatY);

		if (t != 0)
		{
			t *= -1;
			posX = X + hSpeed * t + hAcceleration * t * t;			
		}

		return posX;
	}

	inline bool isMoveLeft() const { return (hSpeed < 0); }
	inline bool isMoveRight() const { return (hSpeed > 0); }
	inline bool isStopH() const { return (hSpeed == 0); }

    int X;
    int Y;
    int hSpeed;	// the horizontal speed (in m/s), can be negative.
    int vSpeed;	// the vertical speed (in m/s), can be negative.
    int fuel;	// the quantity of remaining fuel in liters.
    int rotate; // the rotation angle in degrees (-90 to 90).
    int power;	// the thrust power (0 to 4).

	float hAcceleration = 0;
	float vAcceleration = 0;
	
private:
	int prevHSpeed = 0;
	int prevVSpeed = 0;

	queue<int> hAqueue;
	queue<int> vAqueue;

	queue<float> m_downTimes;
};

ostream & operator<<(ostream & os, const Ship & p)
{    
    EC wPos(4);
    EC wSpeed(4);
    EC wRotate(3);
	EC wFuel(3);
	EC wA(3);


    os
        << "[" 
        << " Pos(" << wPos << p.X << ", " << wPos << p.Y << ")"
        << "   Speed(" << wSpeed << p.hSpeed << ", " << wSpeed << p.vSpeed << ")"
        << "   Rotate(" << wRotate << p.rotate << ")"
        << "   Power(" << p.power << ")"
		<< "   Fluel(" << wFuel << p.fuel << ")"
		<< "   A(" << wA << p.hAcceleration << ", " << wA << p.vAcceleration << ")"
        << " ]"
        ;

    return os;
}

class Brain
{
public:
    Brain()
    { 
        init();
        gameLoop();
    }
    
private:
    void init()
    {
        int surfaceN; // the number of points used to draw the surface of Mars.
        cin >> surfaceN; cin.ignore();
        for (int i = 0; i < surfaceN; i++) 
        {
            int landX; // X coordinate of a surface point. (0 to 6999)
            int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
            cin >> landX >> landY; cin.ignore();

			if (!m_landPoints.empty())
			{
				auto backPoint = m_landPoints.back();

				if (landY == backPoint.y)
				{
					m_flatPoints.push_back({ backPoint.x, backPoint.y });
					m_flatPoints.push_back({ landX, landY });
				}
			}

            m_landPoints.push_back({ landX, landY });
        }

        DEBUG_VAR(m_landPoints);
		DEBUG_VAR(m_flatPoints);
    }

	inline bool isFlatLeft() const { return (m_curShip.X > m_flatPoints[1].x); }
	inline bool isFlatRight() const { return (m_curShip.X < m_flatPoints[0].x); }
	inline bool isShipOnFlat() const { return (!isFlatLeft() && !isFlatRight()); }

	void solveIt()
	{
        DEBUG_VAR(m_curShip);
		float posOnFlt = m_curShip.calPosOnFlatLevel(m_flatPoints[0].y);

		DEBUG_VAR(posOnFlt);

        cout << "-20 3" << endl; // rotate power. rotate is the desired rotation angle. power is the desired thrust power.
	}

    void gameLoop()
    {
        while (1)
        {
            m_curShip.update();
			solveIt();
        }
    }

    Ship m_curShip;
	vector<Point> m_landPoints;
	vector<Point> m_flatPoints;

};

int main()
{
    Brain();
}