#include "UnzipApplication.h"

std::string getOnlyPathFromFullPath(std::string fullPath)
{
    size_t pos = fullPath.find_last_of('\\');
    if (pos == std::string::npos)
        return "";

    fullPath.erase(pos);
    return fullPath;
}

UnzipApplication::UnzipApplication(int argc, char ** argv)
{
    AMSG("Hello from UnzipApplication");

    m_cmd.parseData(argc, argv);

    std::string fileName;

    if (m_cmd.indexedValues().size() > 1)
        fileName = m_cmd.indexedValues().at(1);

    if (!fileName.empty())
        m_settings.open(fileName);

    std::string notepadPath = m_settings.getValue<std::string>("notepadPath");
    std::string sourceFolder = m_settings.getValue<std::string>("sourceFolder");
    std::string fileMask = m_settings.getValue<std::string>("fileMask");
    std::string sevenZipPath = m_settings.getValue<std::string>("sevenZipPath");
    std::string targetFolder = m_settings.getValue<std::string>("targetFolder");

    AVAR(notepadPath);
    AVAR(sourceFolder);
    AVAR(fileMask);
    AVAR(sevenZipPath);
    AVAR(targetFolder);
    
    auto fileList = stdplus::getSubFilesIncludeSubfolders(sourceFolder, fileMask);    
    std::sort(fileList.begin(), fileList.end());
    AVAR(fileList);

    std::string systemCommand;
    std::string sevenZipOnlyPath = getOnlyPathFromFullPath(sevenZipPath);
//     systemCommand = "cd " + sevenZipOnlyPath;
//     AVAR(systemCommand);
//     system(systemCommand.c_str());


    std::string sevenZipFile = stdplus::fileNameFromFullPath(sevenZipPath);
    //systemCommand = "" + sevenZipFile + " x \"" + fileList.front() + "\" -o\"" + targetFolder + "\"";
    systemCommand = "dir";
    AVAR(systemCommand);
    system(systemCommand.c_str());
}

UnzipApplication::~UnzipApplication()
{

}
