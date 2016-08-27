#include "textfilefunctions.h"
#include <iostream>
#include <sstream>

namespace androidText
{


void loadTextFileToString(string filename, string& destString)
{

    string filename1 = filename;

    setRelativePath(filename1);

    SDL_RWops* ooops = SDL_RWFromFile(filename1.c_str(),"rt");


    if (ooops != nullptr)
    {
        size_t file_length = SDL_RWseek(ooops, 0, SEEK_END);
        char* destination = new char[file_length + 1];
        SDL_RWseek(ooops, 0, SEEK_SET);
        //int bytes =
        SDL_RWread(ooops, (destination), 1, file_length);
        destination[file_length] ='\0';


        destString.assign(destination);

        delete[] destination;
    }
    else
        std::cout << "Nothing on path: " << filename1 << std::endl;
    SDL_RWclose(ooops);
}

void setRelativePath(string &filename)
{
   #ifndef __ANDROID__
   filename = "/home/kostya_hm/Projects/DarkDefence/"+ filename;
#endif
}

void saveStringsTofile(SDL_RWops* filetoWrite, const vector<string> &strings)
{
    if (filetoWrite != nullptr)
    {
        int stringCount = strings.size();
        SDL_RWwrite(filetoWrite, &stringCount, sizeof(int), 1);

        for(int i = 0; i < stringCount; ++i)
        {
            int stringByteLength = strings[i].size();
            SDL_RWwrite(filetoWrite, &stringByteLength, sizeof(int), 1);
            SDL_RWwrite(filetoWrite, strings[i].c_str(), stringByteLength, 1);
        }
    }
}
void loadStringsFromfile(SDL_RWops* filetoRead, vector<string> &strings)
{
    if (filetoRead != nullptr)
    {
        int stringCount{0};
        SDL_RWread(filetoRead, &stringCount, sizeof(int), 1);
        strings.resize(stringCount);
        for(int i = 0; i < stringCount; ++i)
        {
            int stringByteLength{};
            SDL_RWread(filetoRead, &stringByteLength, sizeof(int), 1);

            char* char_string =  new char[stringByteLength + 1];
            SDL_RWread(filetoRead, char_string, 1, stringByteLength);
            char_string[stringByteLength] = '\0';

            strings[i].assign(char_string);
        }
    }
}

vector<vector<int> > loadMatrixFromFile(string filename)
{
    string destString;
    loadTextFileToString(filename, destString);


    vector<vector<int> > resultingMap;

    if (!destString.empty())
    {
        std::stringstream stream(destString);
        size_t n = 0;
        size_t m = 0;

        stream >> n;
        stream >> m;

        resultingMap.resize(n);
        for(size_t row = 0; row < n; ++row)
            resultingMap[row].resize(m);

        for(size_t row = 0; row < n; ++row)
            for(size_t column = 0; column < m; ++column)
            {
                std::cout << "row = " << row << " column= " << column;
                int res;
                stream >> res;
                std::cout << "result = " << res << std::endl;
                resultingMap[row][column] = res;
            }
    }

    return resultingMap;
}
}
