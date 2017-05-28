#pragma once

#include "StdPlus\StdPlus.h"

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
    std::string translateFileName;
    const std::string dictFileName = "dict.txt";

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
        if (!isalpha(ch))
        {
            ch = ' ';
        }
        else
        {
            ch = tolower(ch);
        }
    });

    std::vector<std::string> words = stdplus::split(fileAsString, ' ');

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

void appendToDict(std::set<std::string> knowsWords)
{
    auto & app = AppData::instanse();
    std::ofstream exportFile(app.dictFileName, std::ostream::app);

    for (auto & word : knowsWords)
        exportFile << word << "\n";

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

void changeWordsAndAppendToDict()
{
    auto & app = AppData::instanse();

    auto allWords = getAllUniqueWords(app.originalFileName);
    AVAR(allWords.size());

    // TODO !!! In dict include translate too
    auto dictWords = getAllUniqueWords(app.dictFileName);
    AVAR(dictWords.size());

    auto allWithoutDictWords = getOnlyInFirst(allWords, dictWords);
    AVAR(allWithoutDictWords.size());

    {
        std::ofstream exportFile(app.exportFileName);
        for (auto & word : allWithoutDictWords)
            exportFile << word << "\n";
    }

    AMSG("open " + stdplus::fileNamePrepare(app.exportFileName));
    APAUSE_MSG("Delete all knows words. After press any key.");

    auto newWords = getAllUniqueWords(app.exportFileName);
    AVAR(newWords.size());

    auto knowsWords = getOnlyInFirst(allWithoutDictWords, newWords);
    AVAR(knowsWords.size());

    appendToDict(knowsWords);
}

void parseCmd(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    auto & cmd = app.cmd;
    cmd.parseData(argc, argv);
    app.originalFileName = cmd.indexedValues().at(1);
    app.exportFileName = app.originalFileName + "export";
    app.translateFileName = app.originalFileName + "translate";
}

int main(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    parseCmd(argc, argv);
    changeWordsAndAppendToDict();

    {
        std::ofstream translateFile(app.translateFileName);
    }
    
    AMSG("open file " + app.translateFileName);
    APAUSE_MSG("Insert translate of all new words. After press any key...");
    
    //std::ifstream translateFile(app.translateFileName);


    APAUSE_MSG("Press any key for quit application");
}