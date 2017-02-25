#include "ItemAbilitiesStorage.h"
#include "../../Enums.h"
#include "CaftanOfGold.h"
#include "ChoppersHat.h"
#include "HelmOfLigofglass.h"
#include "TitanChock.h"
#include "FeatherOfChap.h"
#include "GulakiAmulet.h"
#include "CorruptedPineApple.h"


void ItemAbilitiesStorage::loadItemAbilities()
{
    itemAbilitiesMap["CaftanOfGold"] = std::make_shared<CaftanOfGold>();
    itemAbilitiesMap["ChoppersHat"] = std::make_shared<ChoppersHat>(Enums::ResourceTypes::WOOD);
    itemAbilitiesMap["ScabblerHat"] = std::make_shared<ChoppersHat>(Enums::ResourceTypes::STONE);
    itemAbilitiesMap["HelmOfLigofglass"] = std::make_shared<HelmOfLigofglass>();
    itemAbilitiesMap["TitanChock"] = std::make_shared<TitanChock>();
    itemAbilitiesMap["FeatherOfChap"] = std::make_shared<FeatherOfChap>();
    itemAbilitiesMap["GulakiAmulet"] = std::make_shared<GulakiAmulet>();
    itemAbilitiesMap["CorruptedPineApple"] = std::make_shared<CorruptedPineApple>();

}

std::shared_ptr<ItemAbility> ItemAbilitiesStorage::getItemAbilityByName(string name)
{
    return itemAbilitiesMap[name];
}
