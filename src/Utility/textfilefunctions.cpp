#include "textfilefunctions.h"
#include <sstream>
#include "Logging/Logger.h"

namespace androidText
{

void loadTextFileToString(const std::string& aFilename, string& outDestString)
{
    SDL_RWops* rwOps = SDL_RWFromFile(aFilename.c_str(),"rt");

    if (rwOps)
    {
        size_t file_length = SDL_RWseek(rwOps, 0, SEEK_END);
        char* destination = new char[file_length + 1];
        SDL_RWseek(rwOps, 0, SEEK_SET);
        SDL_RWread(rwOps, (destination), 1, file_length);
        destination[file_length] ='\0';

        outDestString.assign(destination);

        delete[] destination;
        SDL_RWclose(rwOps);
        return;
    }

    std::string msg = std::string{"File not found: "} + aFilename;
    LOG_ERROR(msg);
}

void saveStringsTofile(SDL_RWops* filetoWrite, const vector<string>& strings)
{
    if (filetoWrite)
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
    if (filetoRead)
    {
        int stringCount{0};
        SDL_RWread(filetoRead, &stringCount, sizeof(int), 1);
        strings.resize(stringCount);
        for(int i = 0; i < stringCount; ++i)
            strings[i] = loadCharStringFromFile(filetoRead);
    }
}

vector<vector<int>> loadMatrixFromFile(const std::string& aFilename)
{
    string destString;
    loadTextFileToString(aFilename, destString);

    vector<vector<int>> resultingMap;

    if (!destString.empty())
    {
        std::stringstream stream(destString);
        size_t n = 0;
        size_t m = 0;

        stream >> n >> m;

        resultingMap.resize(n);
        for(size_t row = 0; row < n; ++row)
        {
            resultingMap[row].resize(m);
        }

        for(size_t row = 0; row < n; ++row)
        {
            for(size_t column = 0; column < m; ++column)
            {
                int res;
                stream >> res;
                resultingMap[row][column] = res;
            }
        }
    }

    return resultingMap;
}

void loadAnimFromFile(SDL_RWops* filetoRead, map<string, vector<SDL_Rect> >& anims)
{
    if (!filetoRead)
    {
        return;
    }

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

void loadAnimFromFile(const std::string& aFilename, map<string, vector<SDL_Rect>>& anims)
{
    SDL_RWops* binaryDataFile = SDL_RWFromFile(aFilename.c_str(),"r+b");
    loadAnimFromFile(binaryDataFile, anims);
    SDL_RWclose(binaryDataFile);
}

std::string loadCharStringFromFile(SDL_RWops* filetoRead)
{
    if (filetoRead)
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
    if (filetoWrite)
    {
        int statesCount = anims.size();
        SDL_RWwrite(filetoWrite, &statesCount, sizeof(int), 1);

        for(const auto& mapItem : anims)
        {
            int stringByteLength = mapItem.first.size();
            SDL_RWwrite(filetoWrite, &stringByteLength, sizeof(int), 1);
            SDL_RWwrite(filetoWrite, mapItem.first.c_str(), stringByteLength, 1);

            int frameCount = mapItem.second.size();

            SDL_RWwrite(filetoWrite, &frameCount, sizeof(int), 1);

            for(int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
            {
                SDL_Rect animFrameRect = mapItem.second[frameIndex];
                SDL_RWwrite(filetoWrite, &animFrameRect, sizeof(SDL_Rect), 1);
            }
        }
    }
}

}
