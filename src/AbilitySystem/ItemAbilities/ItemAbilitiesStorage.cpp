#include "ItemAbilitiesStorage.h"
#include "../../Enums.h"
#include "CaftanOfGold.h"
#include "ChoppersHat.h"
#include "HelmOfLigofglass.h"
#include "TitanChock.h"
#include "FeatherOfChap.h"

ItemAbilitiesStorage::ItemAbilitiesStorage()
{

}

ItemAbilitiesStorage::~ItemAbilitiesStorage()
{
    for(auto itemAbility = itemAbilitiesMap.begin(); itemAbility != itemAbilitiesMap.end(); ++itemAbility)
        delete (itemAbility->second);
}


void ItemAbilitiesStorage::loadItemAbilities()
{
    itemAbilitiesMap["CaftanOfGold"] = new CaftanOfGold();
    itemAbilitiesMap["ChoppersHat"] = new ChoppersHat(Enums::ResourceTypes::WOOD);
    itemAbilitiesMap["ScabblerHat"] = new ChoppersHat(Enums::ResourceTypes::STONE);
    itemAbilitiesMap["HelmOfLigofglass"] = new HelmOfLigofglass();
    itemAbilitiesMap["TitanChock"] = new TitanChock();
    itemAbilitiesMap["FeatherOfChap"] = new FeatherOfChap();
}

ItemAbility *ItemAbilitiesStorage::getItemAbilityByName(string name)
{
    return itemAbilitiesMap[name];
}
