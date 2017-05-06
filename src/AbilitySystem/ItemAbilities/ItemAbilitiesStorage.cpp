#include "ItemAbilitiesStorage.h"
#include "../../Enums.h"
#include "MerchantsCaftan.h"
#include "ChoppersHat.h"
#include "HelmOfLigofglass.h"
#include "TitanChock.h"
#include "FeatherOfChap.h"
#include "GulakiAmulet.h"
#include "CorruptedPineApple.h"
#include "MonolithShard.h"
#include "SteelShield.h"
#include "UberionsCloak.h"
#include "VampsRod.h"
#include "MerchantsHat.h"
#include "MagicWheat.h"
#include "BurningAxe.h"

void ItemAbilitiesStorage::loadItemAbilities()
{
    itemAbilitiesMap["MerchantsCaftan"] = std::make_shared<MerchantsCaftan>();
    itemAbilitiesMap["ChoppersHat"] = std::make_shared<ChoppersHat>(Enums::ResourceTypes::WOOD);
    itemAbilitiesMap["ScabblerHat"] = std::make_shared<ChoppersHat>(Enums::ResourceTypes::STONE);
    itemAbilitiesMap["HelmOfLigofglass"] = std::make_shared<HelmOfLigofglass>();
    itemAbilitiesMap["TitanChock"] = std::make_shared<TitanChock>();
    itemAbilitiesMap["FeatherOfChap"] = std::make_shared<FeatherOfChap>();
    itemAbilitiesMap["GulakiAmulet"] = std::make_shared<GulakiAmulet>();
    itemAbilitiesMap["CorruptedPineApple"] = std::make_shared<CorruptedPineApple>();
    itemAbilitiesMap["MonolithShard"] = std::make_shared<MonolithShard>();
    itemAbilitiesMap["SteelShield"] = std::make_shared<SteelShield>();
    itemAbilitiesMap["UberionsCloak"] = std::make_shared<UberionsCloak>();
    itemAbilitiesMap["VampsRod"] = std::make_shared<VampsRod>();
    itemAbilitiesMap["MerchantsHat"] = std::make_shared<MerchantsHat>();
    itemAbilitiesMap["MagicWheat"] = std::make_shared<MagicWheat>(Enums::ResourceTypes::WHEAT);
    itemAbilitiesMap["BurningAxe"] = std::make_shared<BurningAxe>();
}

std::shared_ptr<ItemAbility> ItemAbilitiesStorage::getItemAbilityByName(string name)
{
    return itemAbilitiesMap[name];
}
