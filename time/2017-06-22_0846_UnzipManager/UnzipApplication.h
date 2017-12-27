#pragma once

#include "StdPlus/StdPlus.h"

class UnzipApplication
{
public:

    UnzipApplication(int argc, char ** argv);

    ~UnzipApplication();

private:

    stdplus::SimpleCmdParser    m_cmd;
    stdplus::SimpleSettingsPlus m_settings;

};


