#include "textfilefunctions.h"
#include <iostream>
#include <sstream>

namespace androidText
{

void loadTextFileToString(string filename, string& destString, bool aSetRelativePath)
{
    string filename1 = filename;
    if (aSetRelativePath)
        setRelativePath(filename1);

    SDL_RWops* ooops = SDL_RWFromFile(filename1.c_str(),"rt");

    if (ooops != nullptr)
    {
        size_t file_length = SDL_RWseek(ooops, 0, SEEK_END);
        char* destination = new char[file_length + 1];
        SDL_RWseek(ooops, 0, SEEK_SET);
        SDL_RWread(ooops, (destination), 1, file_length);
        destination[file_length] ='\0';

        destString.assign(destination);

        delete[] destination;
        SDL_RWclose(ooops);
    }
    else
        std::cout << "Nothing on path: " << filename1 << std::endl;
}

void setRelativePath(string& filename)
{
#ifndef __ANDROID__
    //TODO: Заменить на относительный путь
    filename = "/home/kostya_hm/Projects/DarkDefence/"+ filename;
#endif
}

void saveStringsTofile(SDL_RWops* filetoWrite, const vector<string>& strings)
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

void loadStringsFromfile(SDL_RWops* filetoRead, vector<string>& strings)
{
    if (filetoRead != nullptr)
    {
        int stringCount{0};
        SDL_RWread(filetoRead, &stringCount, sizeof(int), 1);
        strings.resize(stringCount);
        for(int i = 0; i < stringCount; ++i)
            strings[i] = loadCharStringFromFile(filetoRead);
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
                int res;
                stream >> res;
                resultingMap[row][column] = res;
            }
    }

    return resultingMap;
}

void loadAnimFromFile(SDL_RWops* filetoRead, map<string, vector<SDL_Rect> >& anims)
{
    if (filetoRead != nullptr)
    {
        int animationStatesCount = 0;
        SDL_RWread(filetoRead, &animationStatesCount, sizeof(int), 1);

        for(int animStateIndex = 0; animStateIndex < animationStatesCount; ++animStateIndex)
        {
            string animationStateName(loadCharStringFromFile(filetoRead));
            int animationStateFrameCount = 0;
            SDL_RWread(filetoRead, &animationStateFrameCount, sizeof(int), 1);
            vector<SDL_Rect> stateRects(animationStateFrameCount);
            for(int animationStateFrameIndex = 0; animationStateFrameIndex < animationStateFrameCount; ++animationStateFrameIndex)
            {
                SDL_Rect animFrameRect = {0, 0, 0, 0};
                SDL_RWread(filetoRead, &animFrameRect, sizeof(SDL_Rect), 1);

                stateRects[animationStateFrameIndex] = animFrameRect;
            }
            anims[animationStateName] = stateRects;
        }

    }
}

void loadAnimFromFile(const std::string& filename, map<string, vector<SDL_Rect> >& anims)
{
    SDL_RWops* binaryDataFile = SDL_RWFromFile(filename.c_str(),"r+b");
    loadAnimFromFile(binaryDataFile, anims);
    SDL_RWclose(binaryDataFile);
}

std::string loadCharStringFromFile(SDL_RWops* filetoRead)
{
    if (filetoRead != nullptr)
    {
        int stringByteLength{};
        SDL_RWread(filetoRead, &stringByteLength, sizeof(int), 1);

        char* char_string = new char[stringByteLength + 1];
        try
        {
            SDL_RWread(filetoRead, char_string, 1, stringByteLength);
            char_string[stringByteLength] = '\0';
        }
        catch(const std::exception&)
        {
            delete[] char_string;
            return std::string{};
        }

        std::string result{char_string};
        delete[] char_string;

        return result;
    }

    return std::string{};
}

void saveAnimsToFile(SDL_RWops* filetoWrite, const map<string, vector<SDL_Rect> >& anims)
{
    if (filetoWrite != nullptr)
    {
        int animationStatesCount = anims.size();
        SDL_RWwrite(filetoWrite, &animationStatesCount, sizeof(int), 1);

        for(const auto& mapIter : anims)
        {

            int stringByteLength = mapIter.first.size();
            SDL_RWwrite(filetoWrite, &stringByteLength, sizeof(int), 1);
            SDL_RWwrite(filetoWrite, mapIter.first.c_str(), stringByteLength, 1);

            int animationStateFrameCount = mapIter.second.size();

            SDL_RWwrite(filetoWrite, &animationStateFrameCount, sizeof(int), 1);


            for(int animationStateFrameIndex = 0; animationStateFrameIndex < animationStateFrameCount; ++animationStateFrameIndex)
            {
                SDL_Rect animFrameRect = mapIter.second[animationStateFrameIndex];
                SDL_RWwrite(filetoWrite, &animFrameRect, sizeof(SDL_Rect), 1);
            }
        }
    }
}

}
