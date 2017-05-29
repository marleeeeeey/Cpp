#pragma once

#include "StdPlus\StdPlus.h"
#include "EnglishWord.hpp"
#include "Dictionary.hpp"

class AppData
{
public:
    static AppData & instanse()
    {
        static AppData appData;
        return appData;
    }

    stdplus::CmdParser cmd;
    std::string originalFileName;
    std::string exportFileName;
    std::string newSubFileName;
    const std::string dictFileName = "dict.csv";

private:

    AppData() {};
    AppData(const AppData &) = delete;
    void operator=(const AppData &) = delete;
};

std::set<std::string> getAllUniqueWords(const std::string & fileName, size_t minSizeWord = 3)
{
    auto & app = AppData::instanse();
    auto & cmd = app.cmd;
    
    std::ifstream originalFile(fileName);
    std::string fileAsString = stdplus::readText(originalFile);

    std::for_each(fileAsString.begin(), fileAsString.end(),
        [](char & ch)
    {
        if (!isalpha(ch) && ch != '\'')
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
        [](std::string & word) { word = stdplus::trim(word, " \n\'\t"); });

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
    std::set<std::string> &first, std::set<std::string> &second)
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

void parseCmd(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    auto & cmd = app.cmd;
    cmd.parseData(argc, argv);
    app.originalFileName = cmd.indexedValues().at(1);
    app.exportFileName = app.originalFileName + "export";
    app.newSubFileName = app.originalFileName + "new";
}

void replaceAll(std::string & source, const std::string & oldValue, const std::string & newValue)
{
    size_t index = 0;

    while ((index = source.find(oldValue, index)) != std::string::npos)
    {
        size_t charAfterWordIndex = index + oldValue.size();
        if (charAfterWordIndex >= source.size())
            return;

        char charAfterWord = source.at(charAfterWordIndex);
        if (isalpha(charAfterWord))
        {
            index = charAfterWordIndex;
            continue;
        }


        size_t charBeforeWordIndex = index - 1;
        if (charBeforeWordIndex > 0)
        {
            char charBeforeWord = source.at(charBeforeWordIndex);
            if (isalpha(charBeforeWord))
            {
                index = charAfterWordIndex;
                continue;
            }
        }


        source.replace(index, oldValue.size(), newValue);
        index += newValue.size();
    };
}

int main(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    parseCmd(argc, argv);

    Dictionary dict;
    dict.load(app.dictFileName);
    AVAR(dict.size());

    auto allTextWords = getAllUniqueWords(app.originalFileName);
    AVAR(allTextWords.size());

    for (auto & w : allTextWords)
        dict.addWord(w);
    
    auto levelWords = dict.getWordsByLevel(0, 0);
    AVAR(levelWords.size());

    std::set<std::string> allUnknowWords;
    for (auto & engWord : levelWords)
        allUnknowWords.insert(engWord.getWord());

    auto unknownInThisText = getIntersection(allTextWords, allUnknowWords);
    {
        std::ofstream os(app.exportFileName);
        for (auto & word : unknownInThisText)
            os << word << "\n";
    }

    std::string cmd = "call \"c:\\Program Files\\Notepad++\\notepad++.exe\" ";
    cmd += "\"" + app.exportFileName + "\"";
    AVAR(cmd);
    system(cmd.c_str());
    APAUSE;

    auto newUnknowWords = getAllUniqueWords(app.exportFileName);
    auto newKnowsWords = getOnlyInFirst(unknownInThisText, newUnknowWords);

    for (auto & w : newKnowsWords)
        dict.addWord(w, 1);


    {
        std::string originalString = stdplus::readText(app.originalFileName);
        originalString = stdplus::tolower(originalString);

        for (auto & w : newUnknowWords)
        {
            std::string bigWord = w;
            for_each(bigWord.begin(), bigWord.end(),
                [](char & ch) { ch = toupper(ch); });

            replaceAll(originalString, w, 
                bigWord + "(" + dict.getTranslate(w) + ")");
        }

        std::ofstream os(app.exportFileName);
        os << originalString;
    }


    AVAR(dict.size());

    dict.saveAs(app.dictFileName);

    APAUSE;
    return 0;

}
