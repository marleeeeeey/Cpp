#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>

using namespace std;

enum 
{
    e_notWinner = 0,
    e_p1Winner = 1,
    e_p2Winner = 2,
    e_PAT = 3,
};

class Card
{
public:
    Card(string strCard)
    {
        m_strCard = strCard;

        int countLetter = strCard.size();
        
        string strCurWeight;

        auto it = strCard.begin();
        auto itEnd = strCard.end()-1;

        for (; it != itEnd; it++)
        {
            strCurWeight += *it;
        }

        m_suit = *it;

        auto itStrWeight = find(e_weights.begin(), e_weights.end(), strCurWeight);
        

        if (itStrWeight != e_weights.end())
        {
            m_weight = distance(e_weights.begin(), itStrWeight);
        }
        else
        {
            cerr << "error!" << endl;
        }

    }
    
    bool operator<(const Card & other)
    {
        return this->m_weight < other.m_weight;
    }

    bool operator>(const Card & other)
    {
        return this->m_weight > other.m_weight;
    }

private:
    friend std::ostream & operator<<(std::ostream & os, const Card & d);

    const vector<string> e_weights = vector<string>
    { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

    const vector<char> e_suits = vector<char>
    { 'S', 'H', 'D', 'C' };

    int m_weight = 0;
    char m_suit = 0;
    string m_strCard;
};

std::ostream & operator<<(std::ostream & os, const Card & d)
{
    //os << setw(2) << d.m_weight << d.m_suit;
    os << setw(3) << d.m_strCard;
	return os;
}

class Brain
{
public:
    typedef list<Card> Deck;

    Brain()
    {
        init();
        print();
        solve();
        getAnswer();
    }

private:
    void init()
    {
        int n; // the number of cards for player 1
        cin >> n; cin.ignore();

        for (int i = 0; i < n; i++) 
        {
            string cardp1; // the n cards of player 1
            cin >> cardp1; cin.ignore();
            m_p1Cards.push_back(Card(cardp1));
        }


        int m; // the number of cards for player 2
        cin >> m; cin.ignore();

        for (int i = 0; i < m; i++)
        {
            string cardp2; // the m cards of player 2
            cin >> cardp2; cin.ignore();
            m_p2Cards.push_back(Card(cardp2));
        }
    }

    void print()
    {
        cerr << "P1: ";
        for (auto & card : m_p1Cards)
        {
            cerr << card << ", ";
        }
        cerr << endl;

        cerr << "P2: ";
        for (auto & card : m_p2Cards)
        {
            cerr << card << ", ";
        }
        cerr << endl;

        cerr << endl;
    }

    void putBackBattleStock(Deck & playerDeck)
    {
        playerDeck.insert(playerDeck.end(), m_p1BattleStock.begin(), m_p1BattleStock.end());
        playerDeck.insert(playerDeck.end(), m_p2BattleStock.begin(), m_p2BattleStock.end());

        m_p1BattleStock.clear();
        m_p2BattleStock.clear();

        m_counter++;

        print();
    }

    void solve()
    {
        while (!m_p1Cards.empty() && !m_p2Cards.empty())
        {
            m_p1BattleStock.push_back(m_p1Cards.front());
            m_p1Cards.pop_front();

            m_p2BattleStock.push_back(m_p2Cards.front());
            m_p2Cards.pop_front();

            if (m_p1BattleStock.back() > m_p2BattleStock.back())
            {
                cerr << m_p1BattleStock.back() << " > " << m_p2BattleStock.back() << endl;
                putBackBattleStock(m_p1Cards);
            }
            else if (m_p1BattleStock.back() < m_p2BattleStock.back())
            {
                cerr << m_p1BattleStock.back() << " < " << m_p2BattleStock.back() << endl;
                putBackBattleStock(m_p2Cards);
            }
            else
            {
                cerr << m_p1BattleStock.back() << " = " << m_p2BattleStock.back() << endl;

                if (m_p1Cards.size() > 3 && m_p2Cards.size() > 3)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        m_p1BattleStock.push_back(m_p1Cards.front());
                        m_p1Cards.pop_front();

                        m_p2BattleStock.push_back(m_p2Cards.front());
                        m_p2Cards.pop_front();
                    }
                }
                else
                {
                    cout << "PAT" << endl;
                    exit(1);
                }
            }
        }
    }

    void getAnswer()
    {
        if (m_p1Cards.empty())
        {
            m_winner = e_p2Winner;
        }
        else if (m_p2Cards.empty())
        {
            m_winner = e_p1Winner;
        }

        cout << m_winner << " " << m_counter << endl;
    }

    vector<Card> m_p1BattleStock;
    vector<Card> m_p2BattleStock;

    Deck m_p1Cards;
    Deck m_p2Cards;
    int m_counter = 0;
    int m_winner = 0;
};


int main()
{
    Brain();
}