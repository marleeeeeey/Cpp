#pragma once

#include "StdHelper.hpp"


std::ifstream & inputFile(string fileName = "");

std::ofstream & outputFile(string fileName = "");

string readFileToString(string fileName);