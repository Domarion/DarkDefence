/*
 * Enums.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
namespace Enums
{
    enum class ItemTypes {DEFAULT = 0, HELM, AMULET, WEAPON, CUIRASS, SHIELD, RING, BOOTS,CONSUMABLE};
    enum class GameStatuses {gsINPROGRESS = 0, gsWON, gsLOST};
    enum class ResourceTypes {STONE = 0, WOOD, WHEAT};
    enum class AbilityStates {asNotAvaliable = -1, asReady = 0, asWorking, asOnCooldown};
    enum class DamageTypes {dtPHYSICAL = 0, dtFIRE, dtCOLD};
    enum class EReaction: bool
    {
        Attack,
        UseAbilities
    };
    enum class AIMobStates{aiSEARCH = 0, aiSELECT, aiMOVE, aiATTACK, aiRELOAD};
}



