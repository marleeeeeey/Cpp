#pragma once

#include "StdPlus/StdPlus.h"
#include <boost/algorithm/string.hpp>

struct WordWithTranslate
{
    std::string original;
    std::string translate;
};

std::ostream & operator<<(std::ostream & os, const WordWithTranslate & d)
{
    os << d.original << " >> " << d.translate;
    return os;
}

class HistoryApp
{
public:
    HistoryApp(int argc, char ** argv)
    {
        if (argc < 2)
            throw std::logic_error("ERROR: Use file name as first argument");

        m_fileName = argv[1];
        LOG_STD_VAR(m_fileName);

        m_file.open(m_fileName);

        while(parseSection())/*nothing to do*/;

        makeResultFile();
    }

    ~HistoryApp()
    {
        m_file.close();
    }

private:

    bool parseSection()
    {
        auto originalLines = readOriginal();

        if (originalLines.empty()) return false;

        auto translateLines = readTranslate();
        std::string notUsedLine;
        std::getline(m_file, notUsedLine);

        if (originalLines.size() > translateLines.size())
            throw std::logic_error("ERROR: originalLines.size() > translateLines.size()");
            //return false;

        WordWithTranslate tw;
        for (unsigned i = 0; i < originalLines.size(); ++i)
        {
            tw.original += originalLines.at(i) + " ";
            tw.translate += translateLines.at(i) + " ";
        }

        AVAR(tw);
        m_tranlateDict.push_back(tw);     

        return true;
    }

    std::vector<std::string> readBlock(std::string endPart)
    {
        std::vector<std::string> lines;
        std::string line;
        
        while (std::getline(m_file, line))
        {
            boost::algorithm::erase_all(line, SPLITTER);

            if (line.find(endPart) != std::string::npos)
            {
                lines.pop_back();    // remove last empty string
                return lines;
            }

            lines.push_back(line);
        }

        return lines;
    }

    std::vector<std::string> readOriginal()
    {
        return readBlock(END_ORIGINAL);
    }

    std::vector<std::string> readTranslate()
    {
        return readBlock(END_TRANSLATE);
    }

    void makeResultFile()
    {
        std::string resultFileName = stdplus::dateTimeStr()
            + " Result from " + stdplus::fileNameFromFullPath(m_fileName);

        std::ofstream resultFile(resultFileName);

        for (auto & tw : m_tranlateDict)
            resultFile << tw.original << SPLITTER << tw.translate << std::endl;

        LOG_STD_VAR(m_tranlateDict.size());
    }
    
    const std::string END_TRANSLATE = "================================";
    const std::string END_ORIGINAL = "Translate >";
    const std::string SPLITTER = "\t";
    std::string       m_fileName;
    std::ifstream     m_file;
    std::vector<WordWithTranslate> m_tranlateDict;
};

int main(int argc, char ** argv)
{
    try
    {
        LOG_STD_MSG("developer: Tyulenev  Sergey <marleeeeeey@gmail.com>");
        LOG_STD_MSG("You can download source code from:");
        LOG_STD_MSG("https://github.com/marleeeeeey/CppTests/blob/master/src/2017-07-08%201414%20QHistoryConverter/QHistoryConverter.hpp");
        LOG_STD_SPLIT;
        HistoryApp app(argc, argv);
    }
    catch (std::logic_error & eApp)
    {
        LOG_STD_VAR(eApp.what());
    }

    APAUSE;
}