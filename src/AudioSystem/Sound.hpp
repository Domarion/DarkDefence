#pragma once

#include <cstdint>

#include <memory>
#include <string>

#include <SDL_mixer.h>

class Sound final
{
public:
    void loadSound(const std::string& aFilename);
    void playSound();

private:
    std::shared_ptr<Mix_Chunk> mSound;
};
