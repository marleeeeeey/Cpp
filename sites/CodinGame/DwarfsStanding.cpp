#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

enum 
{
    e_notNum = -1,
};

class Node
{
public:
    typedef list<Node *> Nodes;

    Node(int num = e_notNum)
    {
        m_num = num;
    }

    void connectTo(Node & other)
    {
        this->m_outNodes.push_back(&other);
        other.m_inNodes.push_back(this);
    }

    bool isLevel(int level) const
    {
        return (m_level == level);
    }

    bool isStart() const
    {
        return m_inNodes.empty();
    }

    bool isEnd() const
    {
        return m_outNodes.empty();
    }

    int m_level = e_notNum;

    Nodes & inNodes()
    {
        return m_inNodes;
    }

    Nodes & outNodes()
    {
        return m_outNodes;
    }

private:
    friend std::ostream & operator<<(std::ostream & os, const Node & d);
    
    Nodes m_inNodes;
    Nodes m_outNodes;

    int m_num = e_notNum;
};

std::ostream & operator<<(std::ostream & os, const Node & d)
{
    os << d.m_num << ": ";

    struct NameNodes
    {
        string name;
        Node::Nodes nodes;
    };

    vector<NameNodes> nameNodes = 
    {
        { "out: ", d.m_outNodes },
        { "in: ", d.m_inNodes },
    };

    for (auto & nameNode : nameNodes)
    {
        os << nameNode.name;

        for (Node * node : nameNode.nodes)
        {
            os << node->m_num << ", ";
        }

        os << endl << "   ";
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
        solve();
    }


private:
    void init()
    {
        int n; // the number of relationships of influence
        cin >> n; cin.ignore();

        for (int i = 0; i < n; i++) 
        {
            auto pairInt = getPairInt();
            
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

            m_nodes[pairInt[0]].connectTo(m_nodes[pairInt[1]]);            
        }
    }

    void print()
    {
        for (auto & node : m_nodes)
        {
            cerr << node.second << endl;
        }
    }

    void solve()
    {
        vector<Node *> m_startLevelNodes;

        // ищем стартовые узлы
        for (auto & nodeMap : m_nodes)
        {
            Node & curNode = nodeMap.second;

            if (curNode.isStart())
            {
                m_startLevelNodes.push_back(&curNode);
            }
        }

        upLevel(m_startLevelNodes);

    }

    void upLevel(vector<Node *> curLevelNodes)
    {
        static int curLevel = 0;
        curLevel++;

        vector<Node *> nextLevelNodes;

        for (auto curLevelNode : curLevelNodes)
        {
            if (curLevelNode->m_level > curLevel || curLevelNode->m_level == e_notNum)
            {
                curLevelNode->m_level = curLevel;

                for (auto nextLevelNode : curLevelNode->outNodes())
                {
                    nextLevelNodes.push_back(nextLevelNode);
                }

            }

        }

        if (nextLevelNodes.empty())
        {
            getAnswer(curLevel);
        }
        else
        {
            upLevel(nextLevelNodes);
        }
    }

    vector<int> getPairInt()
    {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        cin >> x >> y; cin.ignore();

        vector<int> pair = { x, y };

        return pair;
    }

    void getAnswer(int lastLevel)
    {
        cout << lastLevel << endl; // The number of people involved in the longest succession of influences
        exit(0);
    }

    map<int, Node> m_nodes;
};


int main()
{
    Brain();
}