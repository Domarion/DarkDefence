#include "Music.hpp"
#include <Logging/Logger.h>

void Music::loadMusic(const std::string& aFilename)
{
    mMusic = std::shared_ptr<Mix_Music>(Mix_LoadMUS(aFilename.c_str()), Mix_FreeMusic);

    if (!mMusic)
    {
        std::string message = "Can't load music. " ;
        message.append(Mix_GetError());
        LOG_ERROR(message);
    }
}

void Music::playMusic()
{
    if (!mMusic)
    {
        LOG_ERROR("Has no music to play");
        return;
    }

    if (Mix_PlayingMusic() == 1)
    {
        LOG_ERROR("Music already playing");
        return;
    }
    else if (Mix_PausedMusic() == 1)
    {
        LOG_INFO("Music was paused. Resuming.");

        Mix_ResumeMusic();
        return;
    }

    if (Mix_PlayMusic(mMusic.get(), -1) == -1)
    {
        std::string message = "Can't play music. ";
        message.append(Mix_GetError());
        LOG_ERROR(message);
    }
}

void Music::pauseMusic()
{
    LOG_INFO("Try to pause music.");

    if (Mix_PlayingMusic() == 1)
    {
        Mix_PauseMusic();
    }
    else
    {
        LOG_ERROR("No playing music to pause.");
    }
}

void Music::resumeMusic()
{
    LOG_INFO("Try to resume music.");

    if (Mix_PlayingMusic() == 1)
    {
        LOG_ERROR("Can't resume playing music.");
        return;
    }

    Mix_ResumeMusic();
}

void Music::stopMusic()
{
    LOG_INFO("Try to stop music.");

    Mix_HaltMusic();
}
