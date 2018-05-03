#pragma once

#include <map>
#include <memory>
#include <string>

class ItemAbility;

class ItemAbilitiesStorage
{
public:
    void loadItemAbilities();
    std::shared_ptr<ItemAbility>& getItemAbilityByName(const std::string& aName);

private:
    std::map<std::string, std::shared_ptr<ItemAbility>> itemAbilitiesMap;
};

