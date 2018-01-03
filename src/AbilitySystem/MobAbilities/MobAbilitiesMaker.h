#pragma once

#include "MobAbility.h"

std::unique_ptr<MobAbility> MakeMobAbilityByName(const string& aAbilityName);
