#pragma once
#include <map>
using std::map;
#include "AbilityModel.h"
#include "../Grouping/Scene.h"
class SpellStorage
{
public:
    SpellStorage();
    ~SpellStorage();
    void loadWithScene(Scene* scenePtr);
    AbilityModel* getAbilityModelWithName(string name);
    void setAbilityReady(string s);
    void updateAbilities(double timestep);
    map<string, AbilityModel* >& getAbilityModelList();
    void free();
private:
    map<string, AbilityModel* > abilityModelsMap;
};

