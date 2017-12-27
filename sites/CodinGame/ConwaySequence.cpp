#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream> 

using namespace std;

class Brain
{
public:
    Brain()
    {
        init();
        solve();
        getAnswer();
    }


private:
    void init()
    {
        int R;
        cin >> R; cin.ignore();
        int L;
        cin >> L; cin.ignore();
        
        m_top = R;
        m_targetLineNum = L;

        cerr
            << "m_top = " << m_top << " "
            << "m_targetLineNum = " << m_targetLineNum << " "
            << endl;

        Line firstLine = { m_top };        
        Line secondLine = { 1, m_top };
        
        m_lines = { firstLine, secondLine };

        if (m_targetLineNum <= 2)
        {
            getAnswer(m_targetLineNum);
        }
    }

    void solve()
    {
        Line topLine = m_lines.back();        
        Line curLine;        

        for (unsigned int i = 0; i < topLine.size()-1; i++)
        {
            int curNum = topLine[i];
            int nextNum = topLine[i + 1];
            
            static int m_curCounter = 1;

            if (curNum == nextNum)
            {
                m_curCounter++;

                if ((i + 1) == topLine.size() - 1)
                {
                    curLine.push_back(m_curCounter);
                    curLine.push_back(curNum);
                    m_curCounter = 1;
                }
            }
            else
            {
                curLine.push_back(m_curCounter);
                curLine.push_back(curNum);
                m_curCounter = 1;


                if ((i + 1) == topLine.size() - 1)
                {
                    curLine.push_back(m_curCounter);
                    curLine.push_back(nextNum);
                    m_curCounter = 1;
                }
            }
        }
        
        m_lines.push_back(curLine);

        print();

        cerr
            << "m_lines.size() = " << m_lines.size() << " "
            << "m_targetLineNum =" << m_targetLineNum << " "
            << endl;


        if (m_lines.size() == m_targetLineNum)
        {
            return;
        }
        else
        {
            solve();
        }
    }

    void getAnswer(int num = -1)
    {
        Line resultLine;

        if (num == -1)
        {
            resultLine = m_lines.back();
        }
        else
        {
            resultLine = m_lines[num-1];
        }



        stringstream answer;

        for (int i : resultLine)
        {
            answer << i << " ";
        }

        string ans = answer.str();
        ans.erase(ans.end()-1);
        
        cout << ans << endl;
        exit(0);
    }

    void print() const
    {
        static int lineCounter = 1;

        cerr << endl;
        for (Line line : m_lines)
        {         
            cerr << lineCounter << ": ";
            lineCounter++;
            
            stringstream answer;

            for (int i : line)
            {
                answer << i << " ";
            }

            string ans = answer.str();
            ans.erase(ans.end() - 1);
            
            cerr << ans << endl;
        }

        lineCounter = 1;
    }

    typedef vector<int> Line;
    typedef vector<Line> Lines;

    int m_top = 0;
    int m_targetLineNum = 0;

    Lines m_lines;
};


int main()
{
    Brain();

    cin.get();
}