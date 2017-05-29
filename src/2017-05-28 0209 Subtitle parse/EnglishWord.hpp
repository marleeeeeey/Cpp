#pragma once

#include "StdPlus/StdPlus.h"

class EnglishWord
{
    friend bool operator<(const EnglishWord & left, const EnglishWord & right);
    friend std::ostream & operator<<(std::ostream & os, const EnglishWord & d);

public:

    explicit EnglishWord(const std::string & word="", const std::string & translate = "", int level = 0)
    {
        m_word = word;
        addTranslate(translate);
        m_level = level;
    }

    std::string getWord() const { return m_word; }

    std::string translate() const 
    {
        if (m_translates.empty())
            return "---";

        return *m_translates.begin();
    }
    void addTranslate(const std::string & translate)
    {
        if (translate.empty())
            return;
        
        m_translates.insert(translatePrepare(translate));
    }

    void levelUp() { ++m_level; }
    void levelDown() { --m_level; }
    int level() const { return m_level; }
    void setLevel(int level) { m_level = level; }

    void merge(const EnglishWord & other)
    {
        if (this->m_word != other.m_word)
            throw std::exception("not equle words");

        m_level = (std::max)(m_level, other.m_level);

        m_translates.insert(other.m_translates.begin(), other.m_translates.end());
    }
    
private:
    std::string translatePrepare(const std::string & translate)
    {
        // TODO
        return translate;
    }

    std::string           m_word;
    std::set<std::string> m_translates;
    int                   m_level;
};

bool operator<(const EnglishWord & left, const EnglishWord & right)
{
    return left.m_word < right.m_word;
}

std::ostream & operator<<(std::ostream & os, const EnglishWord & d)
{
    os
        << d.m_word << "; "
        << d.m_level << "; "
        ;

    for (auto & tranlate : d.m_translates)
    {
        os << tranlate << "; ";
    }

    return os;
}