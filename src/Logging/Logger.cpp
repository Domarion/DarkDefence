#include "Logger.h"
#include <SDL_log.h>
#include <chrono>

namespace Logger
{

void Info(const std::string& aMethodName, const std::string& aMessage)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s: %s", GetTimeDateNow(), aMethodName.c_str(), aMessage.c_str());
}

void Error(const std::string& aMethodName, const std::string& aMessage)
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s: %s", GetTimeDateNow(), aMethodName.c_str(), aMessage.c_str());
}

void Debug(const std::string& aMethodName, const std::string& aMessage)
{
    #ifdef DEBUG
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s: %s", GetTimeDateNow(), aMethodName.c_str(), aMessage.c_str());
    #endif
}

char* GetTimeDateNow()
{
    using std::chrono::system_clock;
    auto now = system_clock::to_time_t(system_clock::now());
    return std::ctime(&now);
}

}
