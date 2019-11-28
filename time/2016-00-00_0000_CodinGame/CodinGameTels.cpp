#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


enum
{
    e_tabSize = 8,
};

int compare(const string & s1, const string & s2)
{
    int lenghtS1 = s1.length();
    int counter = 0;

    for (int i = 0; i < lenghtS1; i++)
    {
        if (s1[i] == s2[i])
        {
            counter++;
        }
        else
        {
            return counter;
        }
    }

    return counter;
}

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

vector<string> splitByCount(const string & s, int counter)
{
    string s1;
    s1.append(s.begin(), s.begin() + counter);

    string s2;
    s2.append(s.begin() + counter, s.end());

    return{ s1, s2 };
}

#define DEBUG_VAR(var) cerr << #var << " = " << (var) << endl
#define DEBUG_NLN(var) cerr << #var << " = " << endl << (var) << endl
#define DEBUG_LN(var) #var << " = " << var << "; "
#define DEBUG_MSG(var) cerr << var << endl

class Node
{
public:
    Node()
    {
        static bool isFirstRun = true;
        if (isFirstRun)
        {
            g_headNode = this;
            isFirstRun = false;
        }
    }

    typedef vector<Node *> VecNode;

    inline void setTelNumber(const string & telNumber) { m_telNumber = telNumber; }
    const string & telNumber() const { return m_telNumber; }
    inline void setParent(Node * parent) 
    {
        if (!m_parent)
        {
            m_parent = parent;
        }
        else
        {
            if (!m_parent->m_childrens.empty())
            {
                auto itBegin = m_parent->m_childrens.begin();
                auto itEnd = m_parent->m_childrens.end();

                auto it = find(itBegin, itEnd, this);

                if (it != itEnd)
                {
                    m_parent->m_childrens.erase(it);
                }
            }
        }

        parent->m_childrens.push_back(this);
    }

    inline VecNode & childrens() { return m_childrens; }
    int getNodeCounts() const;

    bool getSimilar(const Node * newChildren, Node * & similarNode, int & charCounter)
    {
        for (Node * c : m_childrens)
        {
            charCounter = compare(c->telNumber(), newChildren->telNumber());

            if (charCounter != 0)
            {
                similarNode = c;
                return true;
            }
        }

        return false;
    }

    Node * makeFront(Node * node)
    {
        Node * frontNode = new Node;
        frontNode->setTelNumber("frontNode");
        frontNode->setParent(node->m_parent);
        frontNode->addChildren(node);
        return frontNode;
    }

    void logicAddChildren(Node * & newChildren)
    {
        int comp = 0;
        Node * similarNode = nullptr;

        if (getSimilar(newChildren, similarNode, comp))
        {
            auto baseParts = splitByCount(similarNode->telNumber(), comp);
            Node * frontNode = makeFront(similarNode);
            frontNode->setTelNumber(baseParts[0]);
            similarNode->setTelNumber(baseParts[1]);
            
            auto childParts = splitByCount(newChildren->telNumber(), comp);
            Node * childPartTwo = new Node;
            childPartTwo->setTelNumber(childParts[1]);
            frontNode->logicAddChildren(childPartTwo);            
        }
        else
        {
            addChildren(newChildren);
        }
    }


    void addChildren(Node * children)
    {
        children->setParent(this);
    }

    static Node * g_headNode;

private:

    friend ostream & operator<<(ostream & os, const Node & node);

    string m_telNumber = "";
    Node * m_parent = nullptr;
    vector<Node *> m_childrens;

        
};

Node * Node::g_headNode = nullptr;

ostream & operator<<(ostream & os, const Node & node)
{
    static int tab = 0;
    os.width(tab);
    os << "";

    os << node.m_telNumber;

    int size = node.m_childrens.size();

    if (size > 0)
    {
        os
            << "[" << size << "]:"
            << endl
            ;

        for (const Node * insideNote : node.m_childrens)
        {
            tab += e_tabSize;
            os << *insideNote << endl;
            tab -= e_tabSize;
        }
    }

    return os;
}


class Brain
{
public:
    Brain()
    {
        m_base.setTelNumber("base");
        init();
        solveIt();
    }

private:
    void solveIt();

    void init();

    int N;
    vector <string> tels;
    Node m_base;
};

void Brain::init()
{
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++)
    {
        string telephone;
        cin >> telephone; cin.ignore();
        tels.push_back(telephone);
    }

    //DEBUG_VAR(tels);
}

void Brain::solveIt()
{
    for (const auto & tel : tels)
    {
        Node * node = new Node();
        node->setTelNumber(tel);
        m_base.logicAddChildren(node);
    }

    //DEBUG_NLN(m_base);

    cout 
        << m_base.getNodeCounts() - m_base.telNumber().length() 
        << endl; 
}

int Node::getNodeCounts() const
{
    int count = 0;

    for (const Node * pInsideNode : m_childrens)
    {
        const Node & insideNode = *pInsideNode;
        count += insideNode.getNodeCounts();
    }

    count += m_telNumber.size();

    return count;
}


int main()
{
    Brain();
}
