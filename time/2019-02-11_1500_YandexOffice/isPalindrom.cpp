#include <string>
#include <cctype>
#include <cassert>
#include <iostream>

bool isPalindrom(const std::string & c)
{
    int f = 0; // first index   
    int s = c.size()-1; // second index

    while(true)
    {
        if(f >= s)  // My mistake 2: Forget to check.
            return true;

        while(!std::isalpha(c[f]))
        {
            if(f == s) return true;
            f++;
        }

        while(!std::isalpha(c[s]))
        {
            if(f == s) return true;
            s--;
        }

        if(std::tolower(c[f]) != std::tolower(c[s])) return false;
        
        f++; // My mistake 1: Forget to add increasing.
        s--;        
    }
}

int main()
{
    assert(isPalindrom("kazak") == true);
    assert(isPalindrom("") == true);
    assert(isPalindrom("k.a/z.a;k;;;;;") == true);
    assert(isPalindrom(".kazak") == true);
    assert(isPalindrom(".") == true);
    assert(isPalindrom(".a.") == true);
    assert(isPalindrom(".a") == true);
    assert(isPalindrom("moryak") == false);
    assert(isPalindrom("mo.ry.a.k") == false);
    std::cin.get();
}