/*
 * Enums.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <type_traits>

namespace Enums
{
    enum class ItemTypes {DEFAULT = 0, HELM, AMULET, WEAPON, CUIRASS, SHIELD, RING, BOOTS, CONSUMABLE};
    enum class GameStatuses {gsINPROGRESS = 0, gsWON, gsLOST};
    enum class ResourceTypes {STONE = 0, WOOD, WHEAT};
    enum class AbilityStates {asNotAvaliable = -1, asReady = 0, asWorking, asOnCooldown};
    enum class DamageTypes {dtPHYSICAL = 0, dtFIRE, dtCOLD};
    enum class EReaction: bool {Attack, UseAbilities};
    enum class AIMobStates {aiSEARCH = 0, aiSELECT, aiMOVE, aiATTACK, aiRELOAD};
    enum class GameSceneStatuses {Default = 0, SpellCasting = 1, Menu = 2};
    enum class AnchorCoordTypes { Min = 0, Middle = 1, Max = 2};

    template<typename TEnumType>
    constexpr auto toIntegralType(TEnumType aEnumVar) -> typename std::underlying_type_t<TEnumType>
    {
        return static_cast<typename std::underlying_type_t<TEnumType>>(aEnumVar);
    }
}
