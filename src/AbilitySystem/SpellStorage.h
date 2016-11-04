#pragma once
#include <map>
using std::map;
#include "AbilityModel.h"
#include "../Grouping/Scene.h"
#include "../GlobalScripts/ManaGlobal.h"

class SpellStorage
{
public:
    SpellStorage();
    ~SpellStorage();
    void loadWithScene(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel);
    std::shared_ptr<AbilityModel> getAbilityModelWithName(string name);
    void setAbilityReady(string s);
    void updateAbilities(double timestep);
    map<string, std::shared_ptr<AbilityModel> >& getAbilityModelList();
    void free();
private:
    map<string, std::shared_ptr<AbilityModel> > abilityModelsMap;
};

