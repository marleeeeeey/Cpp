#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair
{
    int min;
    int max;

    int diff() const 
    {
        return (max - min);
    }

    bool operator>(const Pair & other)
    {
        return this->diff() > other.diff();
    }

    bool operator<(const Pair & other)
    {
        return this->diff() < other.diff();
    }
};

std::ostream & operator<<(std::ostream & os, const Pair & d)
{
    os << "(" << d.min << ", " << d.max << ")";
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
        int n;
        cin >> n; cin.ignore();
        for (int i = 0; i < n; i++)
        {
            int v;
            cin >> v; cin.ignore();
            m_stockValues.push_back(v);
        }
    }

    void print()
    {
        for (auto & val : m_stockValues)
        {
            cerr << val << ", ";
        }

        cerr << endl;
    }

    void solve()
    {
        auto minIt = m_stockValues.begin();
        auto maxIt = m_stockValues.begin();
        auto startIt = minIt;

        while (startIt != m_stockValues.end())
        {
            minIt = min_element(startIt, m_stockValues.end());
            maxIt = max_element(startIt, minIt);

            m_pairs.push_back({ *minIt, *maxIt });

            startIt = minIt;
            startIt++;
        }

        auto resultIt = max_element(m_pairs.begin(), m_pairs.end());
        Pair result = *resultIt;

        cout << -result.diff() << endl;
    }

    vector<int> m_stockValues;
    vector<Pair> m_pairs;
};

int main()
{
    Brain();
}