#pragma once

#include "StdPlus\StdPlus.h"
#include "EnglishWord.hpp"
#include "Dictionary.hpp"
#include "HelpFunctions.hpp"
#include "IniParser.hpp"
#include "FileName.hpp"

class AppData
{
public:
    static AppData & instanse()
    {
        static AppData appData;
        return appData;
    }

    stdplus::CmdParser cmd;
    FileName originalFileName;
    FileName exportFileName;
    FileName dictFileName = "dict.csv";
    std::string settingsFileName = "settings.ini";
    IniParser settings;
    bool isCompareMode = false;
    Dictionary dict;


private:

    AppData() 
    {
        settings.load(settingsFileName);
        AVAR(settings.keyValues());
    };

    AppData(const AppData &) = delete;
    void operator=(const AppData &) = delete;
};

void parseCmd(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    auto & cmd = app.cmd;
    cmd.parseData(argc, argv);

    cmd.print(std::cout);

    if (cmd.indexedValues().size() > 1)
    {
        app.originalFileName = cmd.indexedValues().at(1);
        app.exportFileName = app.originalFileName;
        app.exportFileName.name += "_tr";
    }
    else
    {
        app.exportFileName = "temp.txt";
    }
    
    app.dict.load(app.dictFileName.getFullName());
    AVAR(app.dict.size());

    app.isCompareMode = app.originalFileName.empty() 
        && app.settings.exist("compare");

    AVAR(app.isCompareMode);
}

std::set<std::string> getAppUniqueWords()
{
    auto & app = AppData::instanse();

    std::set<std::string> allTextWords;

    if (app.isCompareMode)
    {
        for (auto & fileName : app.settings.getValues("compare"))
        {
            AMSG("get unique words from file " + stdplus::fileNamePrepare(fileName));
            auto curUniqueWords = getAllUniqueWords(fileName);
            if (allTextWords.empty())
            {
                allTextWords = curUniqueWords;
                continue;
            }

            std::vector<std::string> curWordUnion(curUniqueWords.size());

            std::set_intersection(allTextWords.begin(), allTextWords.end(),
                curUniqueWords.begin(), curUniqueWords.end(), curWordUnion.begin());

            allTextWords.clear();

            for (auto & w : curWordUnion)
                allTextWords.insert(w);
        }
    }
    else
    {
        allTextWords = getAllUniqueWords(app.originalFileName.getFullName());
    }

    return allTextWords;
}

void addWordsToSubtitle(const std::set<std::string> & newUnknowWords)
{
    auto & app = AppData::instanse();
    std::string originalString = stdplus::readText(app.originalFileName.getFullName());
    originalString = stdplus::tolower(originalString);

    for (auto & word : newUnknowWords)
    {
        std::string bigWord = word;
        for_each(bigWord.begin(), bigWord.end(),
            [](char & ch) { ch = toupper(ch); });

        try
        {
            stdplus::replaceAll(originalString, word,
                bigWord + "(" + app.dict.getTranslate(word) + ")");
        }
        catch (std::logic_error & exceptGetTraslate)
        {
            AVAR(exceptGetTraslate.what());
            AVAR(word);
        }
    }

    std::ofstream os(app.exportFileName.getFullName());
    os << originalString;
}

std::set<std::string> getUnknownWordsFromDict()
{
    auto & app = AppData::instanse();

    auto unknownEnglishWordsFromDict = app.dict.getWordsByLevel(0, 0);
    AVAR(unknownEnglishWordsFromDict.size());

    std::set<std::string> unknownWordsFromDict;
    for (auto & engWord : unknownEnglishWordsFromDict)
        unknownWordsFromDict.insert(engWord.getWord());

    return unknownWordsFromDict;
}

std::set<std::string> getUnknownWordsFromFile(
    const std::string & fileName, const std::set<std::string> & unknownWordsFromDict)
{
    auto & app = AppData::instanse();

    auto allWordsFromFile = getAllUniqueWords(fileName);
    auto unknownWordsFromFile = getIntersection(allWordsFromFile, unknownWordsFromDict);
    
    for (auto & w : unknownWordsFromFile)
        app.dict.addWord(w);

    return unknownWordsFromFile;
}

void makeEditFileForUser(std::set<std::string> &unknownWordsFromFile)
{
    auto & app = AppData::instanse();

    std::ofstream os(app.exportFileName.getFullName());
    for (auto & word : unknownWordsFromFile)
        os << word << "\n";
    os.close();

    std::string cmd = "call \"c:\\Program Files\\Notepad++\\notepad++.exe\" ";
    cmd += "\"" + app.exportFileName.getFullName() + "\"";
    AVAR(cmd);
    system(cmd.c_str());
    APAUSE;
}

size_t freqWord(const std::string & text, const std::string & word)
{
    size_t counter = 0;

    size_t index = 0;

    while ((index = text.find(word, index)) != std::string::npos)
    {
        size_t charAfterWordIndex = index + word.size();
        if (charAfterWordIndex >= text.size())
            break;

        char charAfterWord = text.at(charAfterWordIndex);
        if (isalpha(charAfterWord))
        {
            index = charAfterWordIndex;
            continue;
        }


        size_t charBeforeWordIndex = index - 1;
        if (charBeforeWordIndex > 0)
        {
            char charBeforeWord = text.at(charBeforeWordIndex);
            if (isalpha(charBeforeWord))
            {
                index = charAfterWordIndex;
                continue;
            }
        }

        index += word.size();
        counter++;
    };

    return counter;
}

std::set<std::string> geTopUnknownWordsInFile(
    const std::string & fileName, std::set<std::string> & unknownWordsFromDict, int maxCount = 100)
{
    auto unknownWordsFromFile = getUnknownWordsFromFile(fileName, unknownWordsFromDict);
    std::string fileAsString = stdplus::readText(fileName);

    using WordCounter = std::pair<std::string, size_t>;

    std::vector<WordCounter> WordCounters;
    for (auto & w : unknownWordsFromFile)
        WordCounters.push_back(std::make_pair(w, freqWord(fileAsString, w)));

    std::sort(WordCounters.begin(), WordCounters.end(),
        [](const WordCounter & left, const WordCounter & right)
    { return left.second < right.second; });

    if (WordCounters.size() < maxCount)
        maxCount = WordCounters.size();

    std::set<std::string> topWords;

    std::for_each(WordCounters.rbegin(), WordCounters.rbegin() + maxCount,
        [&topWords](const WordCounter & wc) { topWords.insert(wc.first); });

    return topWords;
}

int main(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    parseCmd(argc, argv);

    auto unknownWordsFromDict = getUnknownWordsFromDict();
        
    auto unknownWordsFromFile = getUnknownWordsFromFile(app.originalFileName.getFullName(), unknownWordsFromDict);
    AVAR(unknownWordsFromFile.size());

    if (!unknownWordsFromFile.empty())
        makeEditFileForUser(unknownWordsFromFile);

    auto newUnknowWords = getAllUniqueWords(app.exportFileName.getFullName());
    AVAR(newUnknowWords.size());

    auto newKnowsWords = getOnlyInFirst(unknownWordsFromFile, newUnknowWords);
    AVAR(newKnowsWords.size());

    int learningWordValue = 0;
    if (!newUnknowWords.empty() && app.isCompareMode)
    {
        ARED(learningWordValue);
    }

    for (auto & w : newUnknowWords)
        app.dict.addWord(w, learningWordValue);

    for (auto & w : newKnowsWords)
        app.dict.addWord(w, 1);

    if (!app.isCompareMode)
        addWordsToSubtitle(newUnknowWords);

    auto topWords = geTopUnknownWordsInFile(
        app.originalFileName.getFullName(), unknownWordsFromDict);

    app.dict.saveAs(app.dictFileName.getFullName(), newUnknowWords, topWords);

    AVAR(topWords.size());
    AVAR(app.dict.size());

    APAUSE;
    return 0;
}
