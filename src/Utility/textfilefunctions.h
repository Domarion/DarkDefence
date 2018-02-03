#pragma once

#include <string>
#include <vector>
#include <map>

#include <SDL_rwops.h>
#include <SDL_rect.h>

using std::string;
using std::vector;
using std::map;

namespace androidText
{
void loadTextFileToString(const std::string& aFilename, string& outDestString);
void saveStringsTofile(SDL_RWops* filetoWrite, const vector<string>& strings);
void saveStringToFile(SDL_RWops* filetoWrite, const string& aString);
void loadStringsFromfile(SDL_RWops* filetoRead, vector<string>& strings);
std::string loadCharStringFromFile(SDL_RWops* filetoRead);
vector<vector<int>> loadMatrixFromFile(const std::string& aFilename);
void loadAnimFromFile(const std::string& aFilename, map<string, vector<SDL_Rect>>& anims);
void loadAnimFromFile(SDL_RWops* filetoRead, map<string, vector<SDL_Rect>>& anims);
void saveAnimsToFile(SDL_RWops* filetoWrite, const map<string, vector<SDL_Rect>>& anims);
}
