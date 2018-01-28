#pragma once

#include <map>
using std::map;
#include "ItemAbility.h"

class ItemAbilitiesStorage
{
public:
    void loadItemAbilities();
    std::shared_ptr<ItemAbility> getItemAbilityByName(string name);
private:
    map<string, std::shared_ptr<ItemAbility>> itemAbilitiesMap;
};

