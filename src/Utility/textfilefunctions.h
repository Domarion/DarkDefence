#pragma once

#include <string>

using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <SDL_rwops.h>
#include <SDL_rect.h>

namespace androidText
{
    extern void loadTextFileToString(const std::string& aFilename, string& outDestString);
    extern void saveStringsTofile(SDL_RWops* filetoWrite, const vector<string>& strings);
    extern void loadStringsFromfile(SDL_RWops* filetoRead, vector<string>& strings);
    extern std::string loadCharStringFromFile(SDL_RWops* filetoRead);
    extern vector<vector<int> > loadMatrixFromFile(const std::string& aFilename);
    extern void loadAnimFromFile(const std::string& aFilename, map<string, vector<SDL_Rect>>& anims);
    extern void loadAnimFromFile(SDL_RWops* filetoRead, map<string, vector<SDL_Rect>>& anims);
    extern void saveAnimsToFile(SDL_RWops* filetoWrite, const map<string, vector<SDL_Rect>>& anims);
}
