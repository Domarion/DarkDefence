#pragma once

#include <map>

#include "ItemAbility.h"

class ItemAbilitiesStorage
{
public:
    void loadItemAbilities();
    std::shared_ptr<ItemAbility> getItemAbilityByName(std::string name);

private:
    std::map<string, std::shared_ptr<ItemAbility>> itemAbilitiesMap;
};

