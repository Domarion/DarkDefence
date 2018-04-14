#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>

#include <cereal/external/rapidjson/document.h>
#include <cereal/external/rapidjson/rapidjson.h>

#include "PathMapGenerator.hpp"

void PathMapGenerator::loadConfig(const std::string& aFilename)
{
    std::ifstream inputStream(aFilename);

    if (!inputStream)
    {
        return;
    }

    std::stringstream buf;
    buf << inputStream.rdbuf();

    inputStream.close();

    std::string content = buf.str();
    rapidjson::Document jsonDoc;
    jsonDoc.Parse(content.c_str());

    if (jsonDoc.HasParseError())
    {
        return;
    }

    mRowsCount = jsonDoc["height"].GetUint64();
    mColumnsCount = jsonDoc["width"].GetUint64();

    auto tilesets = jsonDoc["tilesets"].GetArray();
    auto firstTileset = tilesets.Begin()->GetObject();

    std::set<uint64_t> tileIds;

    {
        auto tilesArray = firstTileset["tiles"].GetArray();
        for (const auto& tileParams : tilesArray)
        {
            if (tileParams.HasMember("type") && tileParams["type"].GetString() == PassType)
            {
                tileIds.insert(tileParams["id"].GetUint64());
            }
        }
    }

    if (!jsonDoc.HasMember("layers"))
    {
        return;
    }
    auto layers = jsonDoc["layers"].GetArray();
    auto firstLayer = layers.Begin()->GetObject();
    const auto dataMemberIter = firstLayer.FindMember("data");

    auto dataArray = dataMemberIter->value.GetArray();

    if (mPathMap.capacity() < dataArray.Size())
    {
        mPathMap.reserve(dataArray.Size());
    }

    std::transform(dataArray.Begin(), dataArray.End(), std::back_inserter(mPathMap), [this, &tileIds](const auto& aItem)
    {
        return tileIds.count(aItem.GetUint64()) > size_t(0) ? Pass : NoPass;
    });
}

void PathMapGenerator::savePathMap(const std::string& aFilename)
{
    if (mPathMap.empty())
    {
        return;
    }

    std::ofstream outputStream(aFilename);
    if (!outputStream)
    {
        return;
    }

    outputStream << mRowsCount << '\t' << mColumnsCount << std::endl;
    for(const auto& item : mPathMap)
    {
        outputStream << item << '\t';
    }

    outputStream.close();
}
