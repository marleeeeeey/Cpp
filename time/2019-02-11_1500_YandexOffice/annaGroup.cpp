#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

std::vector<std::vector<std::string>> getAnnaGroups(const std::vector<std::string> & c)
{
    std::map<std::string, std::vector<unsigned>> sorted;

    for(unsigned i=0; i < c.size(); ++i)
    {
        std::string s = c[i];
        std::sort(s.begin(), s.end());
        sorted[s].push_back(i);
    }
    
    std::vector<std::vector<std::string>> ret;

    for(const auto & p : sorted)
    {
        std::vector<std::string> group;
        for(auto i : p.second)
        {
            group.push_back(c[i]);
        }

        ret.push_back(group);
    }

    return ret;
}

int main()
{
    std::vector<std::string> in
    {
        "asd",
        "dsa",
        "qwe",
        "ewq",
        "",
    };

    std::vector<std::vector<std::string>> out 
    {
        {
            ""
        },
        {
            "asd",
            "dsa",
        },
        {
            "qwe",
            "ewq",
        },
    };

    assert(getAnnaGroups(in) == out);
}