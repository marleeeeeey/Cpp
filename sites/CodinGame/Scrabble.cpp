#include <iostream>
#include <string>
#include <vector>
#include <map>
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
	for ( ; it != itEnd; it++)
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

class Score
{
public:
		
	void setUseLetters(const string & useLetters)
	{
		for (const auto & pls : initData)
		{
			int curPoint = pls.point;

			for (const char & letter : pls.letters)
			{
				size_t pos = useLetters.find(letter);

				if (pos != string::npos)
					m_base[letter] = curPoint;
			}
		}

		DEBUG_VAR(m_base);
	}

	int getPoint(const char & ch) const
	{
		auto it = m_base.find(ch);
		
		if (it == m_base.end())
			return 0;

		return it->second;
	}

private:

	struct PointLetters
	{
		int point;
		string letters;
	};

	vector<PointLetters> initData = vector<PointLetters>
	{
		{ 1, "eaionrtlsu" },
		{ 2, "dg" },
		{ 3, "bcmp" },
		{ 4, "fhvwy" },
		{ 5, "k" },
		{ 8, "jx" },
		{ 10, "qz" },
	};

	map<char, int> m_base;
};

class Brain
{
public:
	Brain()
	{
		init();
		solveIt();
	}

	void init()
	{
		int N;
		cin >> N; cin.ignore();

		for (int i = 0; i < N; i++)
		{
			string W;
			getline(cin, W);
			m_strings.push_back(W);
		}
		string LETTERS;
		getline(cin, LETTERS);

		DEBUG_VAR(LETTERS);

		m_score.setUseLetters(LETTERS);

		DEBUG_VAR(m_strings);
	}

	int getScopes(const string & str) const
	{
		int scopes = 0;

		for (const char & ch : str)
		{
			scopes += m_score.getPoint(ch);
		}

		return scopes;
	}

	void solveIt()
	{
		int maxScopes = 0;
		int targetIndex = -1;
		for (unsigned i = 0; i < m_strings.size(); i++)
		{
			int curScopes = getScopes(m_strings[i]);

			DEBUG_VAR(m_strings[i]);
			DEBUG_VAR(curScopes);


			if (curScopes > maxScopes)
			{
				maxScopes = curScopes;
				targetIndex = i;
			}
		}

		if (targetIndex < 0)
		{
			cout << "targetIndex < 0" << endl;
		}
		else
		{
			cout << m_strings[targetIndex] << endl;
		}
	}

private:
	vector<string> m_strings;
	Score m_score;
};

int main()
{
	Brain();
}