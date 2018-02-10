project(DataGenerator)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O2 -Wall -Wextra -pedantic -ggdb")

set (CerealInclude ../../external/cereal/include/)

set(DarkDefenceIncludeDir ../../src)

include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

include_directories(${CerealInclude} ${DarkDefenceIncludeDir} ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${CerealInclude} )

set(HEADERS
    ${DarkDefenceIncludeDir}/GraphicsSystem/newSystem/UtilityStructs.h

    ${DarkDefenceIncludeDir}/GlobalConstants.h
#    ${DarkDefenceIncludeDir}/MissionSystem/Reward.h
#    ${DarkDefenceIncludeDir}/MissionSystem/BasicGoal.h
#    ${DarkDefenceIncludeDir}/MissionSystem/Mission.h
#    ${DarkDefenceIncludeDir}/MissionSystem/ResourceGoal.h
#    ${DarkDefenceIncludeDir}/GlobalScripts/ResourcesModel.h
#    ${DarkDefenceIncludeDir}/GlobalScripts/ResourceInfo.h

#    ${DarkDefenceIncludeDir}/Mob/DestructibleObject.h

#    ${DarkDefenceIncludeDir}/Mob/MineModel.h
#    ${DarkDefenceIncludeDir}/Mob/MobModel.h
#    ${DarkDefenceIncludeDir}/Mob/EnemyInfo.h

    ${DarkDefenceIncludeDir}/Logging/Logger.h

    ${DarkDefenceIncludeDir}/Utility/textfilefunctions.h

#    ${DarkDefenceIncludeDir}/Utility/TreeNode.hpp

#    ${DarkDefenceIncludeDir}/ItemSystem/ItemModel.h

#    ${DarkDefenceIncludeDir}/ItemSystem/Inventory.h
#    ${DarkDefenceIncludeDir}/ItemSystem/ShopInventory.h
#    ${DarkDefenceIncludeDir}/ItemSystem/HeroInventory.h

#    ${DarkDefenceIncludeDir}/AbilitySystem/AbilityModel.h
#    ${DarkDefenceIncludeDir}/AbilitySystem/EffectModel.h

#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/GulakiUpgrade.h
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbility.h
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilityArson.h
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilityInvisiblity.h
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilityRegeneration.h
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilitySprint.h
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilityWheat.h
#    ${DarkDefenceIncludeDir}/Grouping/SceneObject.h
#    ${DarkDefenceIncludeDir}/Grouping/Scene.h

#    ${DarkDefenceIncludeDir}/Mob/Mob.h


    src/DataGenerator.h
    )

set(SRC_LIST

    ${DarkDefenceIncludeDir}/GraphicsSystem/newSystem/Size.cpp
    ${DarkDefenceIncludeDir}/GraphicsSystem/newSystem/Position.cpp

#    ${DarkDefenceIncludeDir}/GlobalScripts/ResourcesModel.cpp
#    ${DarkDefenceIncludeDir}/GlobalScripts/ResourceInfo.cpp

#    ${DarkDefenceIncludeDir}/MissionSystem/Reward.cpp
#    ${DarkDefenceIncludeDir}/MissionSystem/BasicGoal.cpp
#    ${DarkDefenceIncludeDir}/MissionSystem/Mission.cpp
#    ${DarkDefenceIncludeDir}/MissionSystem/ResourceGoal.cpp

#    ${DarkDefenceIncludeDir}/Mob/DestructibleObject.cpp
#    ${DarkDefenceIncludeDir}/Mob/EnemyInfo.cpp

#    ${DarkDefenceIncludeDir}/Mob/MineModel.cpp
#    ${DarkDefenceIncludeDir}/Mob/MobModel.cpp

    ${DarkDefenceIncludeDir}/Logging/Logger.cpp

    ${DarkDefenceIncludeDir}/Utility/textfilefunctions.cpp

#    ${DarkDefenceIncludeDir}/ItemSystem/ItemModel.cpp

#    ${DarkDefenceIncludeDir}/ItemSystem/Inventory.cpp
#    ${DarkDefenceIncludeDir}/ItemSystem/ShopInventory.cpp
#    ${DarkDefenceIncludeDir}/ItemSystem/HeroInventory.cpp
#    ${DarkDefenceIncludeDir}/AbilitySystem/AbilityModel.cpp
#    ${DarkDefenceIncludeDir}/AbilitySystem/EffectModel.cpp

#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/GulakiUpgrade.cpp
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbility.cpp
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilityArson.cpp
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilityInvisiblity.cpp
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilityRegeneration.cpp
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilitySprint.cpp
#    ${DarkDefenceIncludeDir}/AbilitySystem/MobAbilities/MobAbilityWheat.cpp
#    ${DarkDefenceIncludeDir}/Grouping/SceneObject.cpp
#    ${DarkDefenceIncludeDir}/Grouping/Scene.cpp

#    ${DarkDefenceIncludeDir}/Mob/Mob.cpp

    src/DataGenerator.cpp
    src/main.cpp
    )



add_executable(DataGenerator ${HEADERS} ${SRC_LIST})
target_link_libraries(DataGenerator ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
