#pragma once
#include <string>

class DataGenerator
{
public:
    DataGenerator();
    void saveMission();
    void saveTowerTree();
    void saveMineCollection();
    void saveMonsterCollection();
    void saveItems();
    void saveAnim();
    void saveTerrain(std::string filename);
};

