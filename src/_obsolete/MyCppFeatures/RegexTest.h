#pragma once

#include "StdHelper.hpp"
#include <regex>

namespace RegexTest
{
    void test_cplusplus()
    {
        AFUN;

        ostringstream os;
        os << "\n";

        if (std::regex_match("subject", std::regex("(sub)(.*)")))
            os << "string literal matched\n";

        const char cstr[] = "subject";
        std::string s("subject");
        std::regex e("(sub)(.*)");

        if (std::regex_match(s, e))
            os << "string object matched\n";

        if (std::regex_match(s.begin(), s.end(), e))
            os << "range matched\n";

        std::cmatch cm;    // same as std::match_results<const char*> cm;
        std::regex_match(cstr, cm, e);
        os << "string literal with " << cm.size() << " matches\n";

        std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
        std::regex_match(s, sm, e);
        os << "string object with " << sm.size() << " matches\n";

        std::regex_match(s.cbegin(), s.cend(), sm, e);
        os << "range with " << sm.size() << " matches\n";

        // using explicit flags:
        std::regex_match(cstr, cm, e, std::regex_constants::match_default);

        os << "the matches were: ";
        for (unsigned i = 0; i < cm.size(); ++i) {
            os << "[" << cm[i] << "] ";
        }

        os << std::endl;


        AMSG(os.str());
    }

    void test_habr()
    {
        AFUN;

//         ostringstream os;
//         os << "\n";
// 
//         std::string xStr("The boost library has a great opportunity for the regex!");
//         std::regex xRegEx("(\\b\\w{5}\\b)*");
//         std::smatch xResults;
//         os << "==========================Results============================== \n";
//         if (std::regex_search(xStr, xResults, xRegEx, std::match_extra))
//         {
//             os << "Words consist from exact 5 digits have been found in our line:\n";
//             for (int j = 0; j < xResults.size(); ++j)
//                 os << xResults[j] << std::endl;
//         }
//         
//         AMSG(os.str());
    }

    void resolve()
    {
        AFUN;
        test_cplusplus();
        test_habr();
    }
}