#include "TestShared.h"

template<typename FileStream>
FileStream & getOneFile(string fileName)
{
    static string prevFileName;
    static FileStream fs;
    
    if (prevFileName != fileName && !prevFileName.empty())
    {
        fs.close();
        AMSG("File: '" + prevFileName + "' closed OK");
        prevFileName.clear();
    }

    if (!fs.is_open())
    {
        if (fileName.empty())
        {
            AMSG("Please input file name");
            cin >> fileName;
        }

        fs.open(fileName);

        if (!fs)
            AMSG("File '" + to_string(fileName) + "' not opened");

        AMSG("File: '" + fileName + "' opened OK");

        prevFileName = fileName;
    }

    return fs;
}


std::ifstream & inputFile(string fileName)
{
    return getOneFile<std::ifstream>(fileName);
}


std::ofstream & outputFile(string fileName)
{
    return getOneFile<std::ofstream>(fileName);
}


string readFileToString(string fileName)
{
    auto & ist = inputFile(fileName);

    string retString;

    while (!ist.eof())
    {
        string str;
        getline(ist, str);
        retString += str + "\n";
    }

    return retString;
}
