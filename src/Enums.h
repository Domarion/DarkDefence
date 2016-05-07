/*
 * Enums.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
namespace Enums
{
    enum ItemTypes {DEFAULT = 0, HELM, AMULET, CUIRASS, WEAPON, SHIELD, RING, BOOTS,CONSUMABLE};
	enum GameStatuses {gsINPROGRESS = 0, gsWON, gsLOST};
	enum ResourceTypes {GOLD = 0, WOOD, STONE, WHEAT};
    enum AbilityStates {asNotAvaliable = -1, asReady = 0, asWorking, asOnCooldown};
    enum DamageTypes {dtPHYSICAL = 0, dtFIRE, dtCOLD, dtPSYONICAL};
}



