#pragma once
#include <map>
using std::map;
#include "ItemAbility.h"

class ItemAbilitiesStorage
{
public:
    ItemAbilitiesStorage();
    ~ItemAbilitiesStorage();
    void loadItemAbilities();
    ItemAbility* getItemAbilityByName(string name);
private:
    map<string, ItemAbility*> itemAbilitiesMap;
};

