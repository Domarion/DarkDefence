#include "Sound.hpp"
#include <Logging/Logger.h>


void Sound::loadSound(const std::string& aFilename)
{
    mSound = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(aFilename.c_str()), Mix_FreeChunk);

    if (!mSound)
    {
        std::string message = "Can't load sound. " ;
        message.append(Mix_GetError());
        LOG_ERROR(message);
    }
}

void Sound::playSound()
{
    if (!mSound)
    {
        LOG_ERROR("Has no sound to play");
        return;
    }
    const int repeatCount = 0;
    const int channelId = -1; // Any available.
    if (Mix_PlayChannel(channelId, mSound.get(), repeatCount) == -1)
    {
        std::string message = "Can't play sound. ";
        message.append(Mix_GetError());
        LOG_ERROR(message);
    }
}
