#pragma once

#include <map>
using std::map;
#include "AbilityModel.h"
#include "../Grouping/Scene.h"
#include "../GlobalScripts/ManaGlobal.h"

class SpellStorage final
{
public:
    void loadWithScene(std::shared_ptr<Scene> scenePtr, const std::shared_ptr<ManaGlobal>& aManaModel);
    std::shared_ptr<AbilityModel> getAbilityModelWithName(const std::string& aName);
    bool setAbilityReady(const std::string& aAbilityName);
    void updateAbilities(double aTimeStep);
    const map<std::string, std::shared_ptr<AbilityModel> >& getAbilityModelList() const;
    bool canPlaceObjectAbility(const std::string& aAbilityName) const;

private:
    map<string, std::shared_ptr<AbilityModel> > abilityModelsMap;
};

