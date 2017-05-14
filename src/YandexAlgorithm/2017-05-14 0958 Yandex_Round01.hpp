// How to use redirection 
// 0<in.txt 1>out.txt

#ifdef MARLEEEEEEY_PC
#    include "StdPlus/StdPlus.h"
#else // MARLEEEEEEY_PC
#    define AVAR(var)     
#    define AMSG(var)     
#    define AFUN          
#    define AFUN_COUNTER  
#    define ASPLIT        
#    define ASPACE        
#    define ABEEP         
#endif // MARLEEEEEEY_PC


#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iomanip>

class Resolve
{
public:
    Resolve()
    {
        AFUN;

        step10_init();
        step20();

        if (indexFirstUnread < countLetters)
            step30_readAfterTime();
    }



private:

    void step10_init()
    {
        std::cin 
            >> countLetters 
            >> criticalUnread 
            >> criticalTimeInterval
            ;

        lettersTime.reserve(countLetters);
        for (int i = 0; i < countLetters; ++i)
        {
            int letterTime;
            std::cin >> letterTime;
            lettersTime.push_back(letterTime);
        }

        if (!lettersTime.empty())
            timeFirstUnread = lettersTime.at(0);
    }

    void readLetters()
    {
        int numberReadNow = (int)ceil(countUnread / 2.);
        int nextIndexFirstUnread = indexFirstUnread + numberReadNow;

        for (int i = indexFirstUnread; i < nextIndexFirstUnread; ++i)
        {
            std::cout << curLetterTime << " ";
        }

        countUnread -= numberReadNow;
        indexFirstUnread = nextIndexFirstUnread;
        if (indexFirstUnread < countLetters)
            timeFirstUnread = lettersTime.at(indexFirstUnread);
    }

    void step20()
    {        
        for (int i = 0; i < lettersTime.size(); i++)
        {
            if (i < indexFirstUnread)
                i = indexFirstUnread;

            curLetterTime = lettersTime.at(i);
            int nextLetterTime = -1;

            if (i < lettersTime.size() - 1)
                nextLetterTime = lettersTime.at(i + 1);

            int interval = curLetterTime - timeFirstUnread;
            int nextInterval = nextLetterTime - timeFirstUnread;
            countUnread++;


            if (interval >= criticalTimeInterval)
            {
                readLetters();
                continue;
            }
            else if (nextInterval >= criticalTimeInterval)
            {
//                 curLetterTime = nextLetterTime + criticalTimeInterval;
//                 readLetters();
                continue;
            }

            if (countUnread >= criticalUnread)
            {
                readLetters();
                continue;
            }

        }

    }

    void step30_readAfterTime()
    {
        curLetterTime = criticalTimeInterval + timeFirstUnread;

        while (countUnread > 0)
        {
            readLetters();
            curLetterTime = criticalTimeInterval + timeFirstUnread;
        }
    }

    int countLetters;
    int criticalUnread;
    int criticalTimeInterval;
    std::vector<int> lettersTime;

    int indexFirstUnread = 0;
    int timeFirstUnread = -1;
    int curLetterTime = -1;
    int countUnread = 0;
};

int main()
{
    Resolve r;
}
