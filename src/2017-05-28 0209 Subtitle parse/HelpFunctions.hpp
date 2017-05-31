#pragma once

#include "StdPlus/StdInclude.h"

std::set<std::string> getAllUniqueWords(const std::string & fileName,
    size_t minSizeWord = 3, const std::string & trimString = " \n\'\t’‘’‘")
{
    if (fileName.empty())
        throw std::logic_error("file name empty in getAllUniqueWords");
        
    std::ifstream originalFile(fileName);
    std::string fileAsString = stdplus::readText(originalFile);

    std::for_each(fileAsString.begin(), fileAsString.end(),
        [](char & ch)
    {
        if (ch >= 0 && ch <= 255 && !isalpha(ch) && ch != '\'')
        {
            ch = ' ';
        }
        else
        {
            ch = tolower(ch);
        }
    });

    std::vector<std::string> words = stdplus::split(fileAsString, ' ');

    for_each(words.begin(), words.end(),
        [&trimString](std::string & word) 
    { word = stdplus::trim(word, trimString.c_str()); });

    auto it = std::remove_if(words.begin(), words.end(),
        [minSizeWord](const std::string & word)
    {
        if (word.size() < minSizeWord)
            return true;

        return false;
    });

    words.erase(it, words.end());

    std::sort(words.begin(), words.end());

    std::set<std::string> uniqueWords;

    for (auto & word : words)
    {
        uniqueWords.insert(word);
    }

    return uniqueWords;
}

std::set<std::string> getOnlyInFirst(
    std::set<std::string> &first, std::set<std::string> &second)
{
    std::vector<std::string> onlyInFirst(first.size());
    auto it = std::set_difference(first.begin(), first.end(),
        second.begin(), second.end(), onlyInFirst.begin());
    onlyInFirst.resize(it - onlyInFirst.begin());

    std::set<std::string> setWords;
    for (auto & word : onlyInFirst)
    {
        setWords.insert(word);
    }

    return setWords;
}

std::set<std::string> getIntersection(
    const std::set<std::string> & first, const std::set<std::string> & second)
{
    std::vector<std::string> onlyInFirst(first.size());

    auto it = std::set_intersection(first.begin(), first.end(),
        second.begin(), second.end(), onlyInFirst.begin());
    onlyInFirst.resize(it - onlyInFirst.begin());

    std::set<std::string> setWords;
    for (auto & word : onlyInFirst)
    {
        setWords.insert(word);
    }

    return setWords;
}


