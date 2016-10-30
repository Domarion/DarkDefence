#pragma once
#include <map>
using std::map;
#include "ItemAbility.h"

class ItemAbilitiesStorage
{
public:
    ItemAbilitiesStorage() = default;
    ~ItemAbilitiesStorage() = default;
    void loadItemAbilities();
    std::shared_ptr<ItemAbility> getItemAbilityByName(string name);
private:
    map<string, std::shared_ptr<ItemAbility>> itemAbilitiesMap;
};

