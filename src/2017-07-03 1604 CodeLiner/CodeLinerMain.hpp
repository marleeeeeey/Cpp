#pragma once

#include "StdPlus/StdPlus.h"


class FileLiner
{
public:
    FileLiner(const std::string & fileName)
    {
        m_fileName = fileName;

        std::ifstream file(m_fileName);

        std::string line;

        while (std::getline(file, line))
        {
            line = stdplus::trim(line);

            if (isCommentLine(line))
            {
                m_commentLineCounter++;
                continue;
            }

            if (line == "")
            {
                m_emptyLineCounter++;
                continue;
            }
            
            m_fillLineCounter++;
        }

    }

    inline std::string getFileName() const { return m_fileName; }
    inline int getEmptyLineCounter() const { return m_emptyLineCounter; }
    inline int getFillLineCounter() const { return m_fillLineCounter; }
    inline int getCommentLineCounter() const { return m_commentLineCounter; }

private:

    bool isCommentLine(const std::string & line)
    {
        if (line.size() < 2)
            return false;

        if (line[0] == '/' && line[1] == '/')
            return true;
        else
            return false;
    }

    std::string m_fileName;
    int         m_emptyLineCounter   = 0;
    int         m_fillLineCounter    = 0;
    int         m_commentLineCounter = 0;

};

std::ostream & operator<<(std::ostream & os, const FileLiner & d)
{
    std::string shortFileName = stdplus::fileNameFromFullPath(d.getFileName());

    os
        << "empty: "    << std::setw(4)  << d.getEmptyLineCounter() << "; "
        << "comment: "  << std::setw(4)  << d.getCommentLineCounter() << "; "
        << "fill: "     << std::setw(4)  << d.getFillLineCounter() << "; "
        << "fileName: " /*<< std::setw(15)*/ << shortFileName << "; "
        ;

    return os;
}

int main(int argc, char ** argv)
{
    std::ofstream report(stdplus::dateTimeStr() + " report.txt");
    LOG_STD_REGISTER_STREAM(report);

    AMSG("developer: Tyulenev  Sergey <marleeeeeey@gmail.com>");
    ASPLIT;

    std::string dir = ".";
    
    if (argc > 1)
        dir = argv[1];

    AVAR(dir);
    ASPLIT;

    std::vector<std::string> fileMasks = { "*.cpp", "*.h", "*.hpp", "*.cs", "*.c" };

    AVAR(fileMasks);
    ASPLIT;

    auto fileNames = stdplus::getSubFilesIncludeSubfolders(dir, fileMasks);

    AVAR(fileNames);
    ASPLIT;

    std::vector<FileLiner> fileLiners;

    for (const std::string & fileName : fileNames)
    {
        fileLiners.emplace_back(fileName);
    }

    AVAR(fileLiners);
    ASPLIT;

    int sumEmpty = 0;
    int sumFill = 0;
    int sumComment = 0;

    for (const auto & fileLiner : fileLiners)
    {
        sumEmpty += fileLiner.getEmptyLineCounter();
        sumFill += fileLiner.getFillLineCounter();
        sumComment += fileLiner.getCommentLineCounter();
    }

    AVAR(sumEmpty);
    AVAR(sumComment);
    AVAR(sumFill);
    ASPLIT;

    APAUSE_MSG("PRESS ANY KEY FOR CLOSE CONSOLE");
}