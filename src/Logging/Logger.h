#pragma once

#include <string>

#define LOG_INFO(aMessage) Logger::Info(__func__, aMessage);
#define LOG_ERROR(aMessage) Logger::Error(__func__, aMessage);
#define LOG_DEBUG(aMessage) Logger::Debug(__func__, aMessage);

namespace Logger
{
    extern void Info(const std::string& aMethodName, const std::string& aMessage);
    extern void Error(const std::string& aMethodName, const std::string& aMessage);
    extern void Debug(const std::string& aMethodName, const std::string& aMessage);
    extern char* GetTimeDateNow();
}
