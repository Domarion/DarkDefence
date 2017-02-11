#include "AnimSaver.hpp" 
#include <fstream>
#include <iostream>
#include "Utility/textfilefunctions.h"

void AnimSaver::makeAnim(const std::string& aFilename, const std::string& aOutAnimName)
{
    std::ifstream inputFile(aFilename);
    if (!inputFile)
    {
        std::cerr << "No such input file" << std::endl;
        return;
    }
    std::string lexem;
    inputFile >> lexem;
    if (lexem != "animCount")
    {
        std::cerr << "Incorrect header. Expected animcount keyword" << std::endl;
        return;
    }
    size_t animCount{};
    inputFile >> animCount;

    if (animCount <= 0)
    {
        std::cerr << "Incorrect animcount. Expected positive integer" << std::endl;
        return;
    }

    std::map<std::string, std::vector<SDL_Rect>> anims;

    for (size_t animIndex = 0; animIndex < animCount; ++animIndex)
    {
        inputFile >> lexem;
        if (lexem != "animName")
        {
            std::cerr << "Incorrect header. Expected animName keyword" << std::endl;
            return;
        }

        std::string animName;
        inputFile >> animName;

        inputFile >> lexem;
        if (lexem != "framescount")
        {
            std::cerr << "Incorrect header. Expected framescount keyword" << std::endl;
            return;
        }

        size_t framesCount{};
        inputFile >> framesCount;
        if (framesCount <= 0)
        {
            std::cerr << "Incorrect framesCount. Expected positive integer" << std::endl;
            return;
        }
        std::vector<SDL_Rect> frameVector;
        frameVector.reserve(framesCount);

        for(size_t frame = 0; frame < framesCount; ++frame)
        {
            SDL_Rect frameRect;
            inputFile >> frameRect.x >> frameRect.y >> frameRect.w >> frameRect.h;
            frameVector.push_back(frameRect);
        }

        anims[animName] = frameVector;
    }

    inputFile.close();


    SDL_RWops* binaryDataFile = SDL_RWFromFile(aOutAnimName.c_str(),"w+b");
    if (binaryDataFile != nullptr)
    {
        androidText::saveAnimsToFile(binaryDataFile, anims);
        SDL_RWclose(binaryDataFile);
    }
}
