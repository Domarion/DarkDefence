#pragma once

#include <string>

using std::string;
#include <vector>
using std::vector;
#include <SDL_rwops.h>

namespace androidText
{
    extern void setRelativePath(string& filename);
    extern void loadTextFileToString(string filename, string& destString);
    extern void saveStringsTofile(SDL_RWops* filetoWrite, const vector<string> &strings);
    extern void loadStringsFromfile(SDL_RWops* filetoRead, vector<string> &strings);
}
