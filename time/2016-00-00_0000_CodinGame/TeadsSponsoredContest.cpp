#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

class Node
{
public:
    explicit Node(int num = -1)
    {
        m_num = num;
    }
    
    ~Node()
    {
        for (auto & node : m_nodesPointer)
        {

        }
    }

    int countLinks() const
    {
        return m_nodesPointer.size();
    }

    void linkTo(Node & other)
    {
        m_nodesPointer.push_back(&other);
        other.m_nodesPointer.push_back(this);
    }
    
    void unlink(Node & other)
    {
        this->unlinkTo(other);
        other.unlinkTo(*this);
    }

    void unlinkAll()
    {
        for (auto nodePointer : m_nodesPointer)
        {
            nodePointer->unlinkTo(*this);
        }

        m_nodesPointer.clear();
    }

    void fixStartCountLinks()
    {
        m_startCountLinks = m_nodesPointer.size();
    }

    int startCountLinks() const
    {
        return m_startCountLinks;
    }

    bool operator<(const Node & other) const
    {
        return this->m_num < other.m_num;
    }

    bool operator>(const Node & other) const
    {
        return this->m_num > other.m_num;
    }

    bool operator==(const Node & other) const
    {
        return this->m_num == other.m_num;
    }
        
private:
    friend std::ostream & operator<<(std::ostream & os, const Node & d);
    
    void unlinkTo(Node & other)
    {
        Node * deleteNode = nullptr;

        for (auto nodePointer : m_nodesPointer)
        {
            if (*nodePointer == other)
            {
                deleteNode = nodePointer;
                break;
            }
        }

        if (deleteNode)
        {
            m_nodesPointer.remove(deleteNode);
        }
    }

    list<Node*> m_nodesPointer;
    int m_startCountLinks = 0;
    int m_num = 0;
};

std::ostream & operator<<(std::ostream & os, const Node & d)
{
    os << d.m_num << ": ";

    for (const auto & node : d.m_nodesPointer)
    {
        os << node->m_num << ", ";
    }

	return os;
}

class Brain
{
public:
    Brain()
    {
        init();
        print();

        cout << solve() << endl; 
    }


private:
    void init()
    {
        int n; 
        cin >> n; cin.ignore();

        for (int i = 0; i < n; i++) 
        {
            auto pairInt = getPairNumNode();
            
            for (auto i : pairInt)
            {
                try
                {
                    m_nodes.at(i);
                }
                catch (const std::out_of_range & e)
                {
                    e.what();
                    m_nodes[i] = Node(i);
                }
            }
            
            m_nodes[pairInt[0]].linkTo(m_nodes[pairInt[1]]);
        }

        for (auto & node : m_nodes)
        {
            node.second.fixStartCountLinks();
        }
    }

    vector<int> getPairNumNode()
    {
        vector<int> pairInt;
        int firstInt;
        int secondInt;
        cin >> firstInt >> secondInt; cin.ignore();
        pairInt = { firstInt, secondInt };
        //cerr << "(" << pairInt[0] << ", " << pairInt[1] << ")" << endl;
        return pairInt;
    }
    
    void print()
    {
        for (auto & node : m_nodes)
        {
            cerr << node.second << endl;
        }
    }

    int solve()
    {
        vector<int> removeKeys;

        for (auto & node : m_nodes)
        {
            int countLinks = node.second.countLinks();

            if (countLinks == 1)
            {
                removeKeys.push_back(node.first);
            }
        }
        
        static int answer = 0;

        answer++;

        cerr << "removeKeys.size()=" << removeKeys.size() << ": ";


        for (auto key : removeKeys)
        {
            cerr << key << ", ";
        }
        cerr << endl;
        
        for (auto remKey : removeKeys)
        {
            m_nodes[remKey].unlinkAll();
            m_nodes.erase(remKey);
        }

        if (m_nodes.size() <= 2)
        {
            enum { e_notNode = -1 };

            int maxStartCountLinks = 0;
            int resultNode = e_notNode;

            for (auto & node : m_nodes)
            {
                int curStartCountLinks = node.second.startCountLinks();

                cerr
                    << "maxStartCountLinks = " << maxStartCountLinks << " "
                    << "curIndex = " << node.first << " "
                    << "curStartCountLinks = " << curStartCountLinks
                    << endl;

                if (maxStartCountLinks < curStartCountLinks)
                {
                    maxStartCountLinks = curStartCountLinks;
                    resultNode = node.first;

                    cerr
                        << "OK "
                        << "maxStartCountLinks = " << maxStartCountLinks << " "
                        << "resultNode = " << resultNode << " "
                        << endl;
                }
            }

            if (m_nodes.size() == 2)
            {
                answer++;
            }

            if (resultNode != e_notNode)
            {
                return answer;
            }
            else
            {
                cerr << "last node Error!" << endl;
            }
        }

        print();

        return solve();
    }

    map<int, Node> m_nodes;
};


int main()
{
    Brain();    
}