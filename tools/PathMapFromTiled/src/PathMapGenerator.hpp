#pragma once

#include <string>
#include <vector>

class PathMapGenerator
{
public:

    void loadConfig(const std::string& aFilename);
    void savePathMap(const std::string& aFilename);

private:
    std::vector<int> mPathMap;
    size_t mRowsCount = 0;
    size_t mColumnsCount = 0;
    const int Pass = -1;
    const int NoPass = -2;
    const std::string PassType = "pass";
};
