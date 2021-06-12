#pragma once

#include <cstdint>

#include <memory>
#include <string>

#include <SDL_mixer.h>

class Music final
{
public:
    void loadMusic(const std::string& aFilename);
    void playMusic();
    void pauseMusic();
    void resumeMusic();
    void stopMusic();

private:
    std::shared_ptr<Mix_Music> mMusic;
};
