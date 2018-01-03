#include "MobAbilitiesMaker.h"

#include "MobAbilityArson.h"
#include "MobAbilityRegeneration.h"
#include "MobAbilitySprint.h"
#include "MobAbilityInvisiblity.h"
#include "MobAbilityFog.h"
#include "MobAbilitySummon.h"
#include "MobAbilityInvulnerablity.h"
#include "MobAbilityHeal.h"

#include "MobAbilityWheat.h"
#include "GulakiUpgrade.h"
#include "MobEarthTowerAbility.h"
#include "MobMageTowerAbility.h"
#include "MobCloudTowerAbility.h"
#include "TitanChockUpgrade.h"
#include "TitanChockMassSlow.h"

std::unique_ptr<MobAbility> MakeMobAbilityByName(const std::string& aAbilityName)
{
    if (aAbilityName == "MobAbilityArson")
        return std::make_unique<MobAbilityArson>();

    if (aAbilityName == "MobAbilityRegeneration")
        return std::make_unique<MobAbilityRegeneration>();

    if (aAbilityName == "MobAbilityHeal")
        return std::make_unique<MobAbilityHeal>();

    if (aAbilityName == "MobAbilitySprint")
        return std::make_unique<MobAbilitySprint>();

    if (aAbilityName == "MobAbilityFog")
        return std::make_unique<MobAbilityFog>();

    if (aAbilityName == "MobAbilityInvisiblity")
        return std::make_unique<MobAbilityInvisiblity>();

    if (aAbilityName == "MobAbilityInvulnerablity")
        return std::make_unique<MobAbilityInvulnerablity>();

    if (aAbilityName == "MobAbilityWheat")
        return std::make_unique<MobAbilityWheat>();

    if (aAbilityName == "GulakiAmulet")
        return std::make_unique<GulakiUpgrade>();

    if (aAbilityName == "MobEarthTowerAbility")
        return std::make_unique<MobEarthTowerAbility>();

    if (aAbilityName == "MobMageTowerAbility")
        return std::make_unique<MobMageTowerAbility>();

    if (aAbilityName == "MobCloudTowerAbility")
        return std::make_unique<MobCloudTowerAbility>();

    if (aAbilityName == "TitanChockUpgrade")
        return std::make_unique<TitanChockUpgrade>();

    if (aAbilityName == "TitanChockMassSlow")
        return std::make_unique<TitanChockMassSlow>();

    if (aAbilityName == "MobAbilitySummon")
        return std::make_unique<MobAbilitySummon>();

    return nullptr;
}
