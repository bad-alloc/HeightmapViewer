#ifndef COMMANDLINEARGUMENTPARSER_H_INCLUDED
#define COMMANDLINEARGUMENTPARSER_H_INCLUDED

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

void parseCommandLineArguments(int argumentCount, char* argumentVector[],
			       string* heightmapFile,
			       bool* autoResolution,
			       int* X_Resolution, int* Y_Resolution,
			       int* fps, int* red, int* green, int* blue);

#endif // COMMANDLINEARGUMENTPARSER_H_INCLUDED
