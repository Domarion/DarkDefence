#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/sanitizers-cmake/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O0 -Wall -Wextra -pedantic -ggdb \
    -pedantic-errors -Wextra -Wcast-align \
    -Wcast-qual  -Wchar-subscripts  -Wcomment \
    -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 \
    -Wformat-nonliteral -Wformat-security  \
    -Wformat-y2k \
    -Wimport  -Winit-self \
    -Winvalid-pch   \
    -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute   \
    -Wmissing-include-dirs \
    -Wpacked -Wparentheses  -Wpointer-arith \
    -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
    -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch \
    -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused \
    -Wunused-function  -Wunused-label  -Wunused-parameter \
    -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings")
#    -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fuse-ld=lld")

#-Waggregate-return

include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

if (NOT SDL2_FOUND)
	message(SEND_ERROR "Failed to find SDL2")
else()
	include_directories(${SDL2_INCLUDE_DIRS})
endif()

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)

if (NOT SDL2IMAGE_FOUND)
	message(SEND_ERROR "Failed to find SDL2_image")
else()
	include_directories(${SDL2IMAGE_INCLUDE_DIRS})
endif()

PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

if (NOT SDL2MIXER_FOUND)
        message(SEND_ERROR "Failed to find SDL2_mixer")
else()
        include_directories(${SDL2MIXER_INCLUDE_DIRS})
endif()

PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

if (NOT SDL2TTF_FOUND)
	message(SEND_ERROR "Failed to find SDL2_ttf")
else()
        include_directories(${SDL2TTF_INCLUDE_DIRS})
endif()

set (CerealInclude ../external/cereal/include)

find_package (Boost COMPONENTS system filesystem REQUIRED)

include_directories(. ${CerealInclude} ${Boost_INCLUDE_DIRS})


set(SRC_LIST
    Input/InputHandler.h
    Input/SceneInputHandler.h
    Input/InputDispatcher.h
    Scenes/GameScene.h
    Scenes/ScoreScene.h
    Scenes/InventoryScene.h
    Scenes/MainScene.h
    Scenes/ShopScene.h
    Scenes/MapMenuScene.h
    Scenes/include/MissionTumbler.hpp

    GameApp.h
    Mob/Mob.h
    Mob/DestructibleObject.h
    Mob/Mine.h
    Mob/Gates.h
    Mob/Tower.h
    Mob/MineModel.h
    Mob/MobModel.h
    Mob/TowerUpgradeController.h
    Mob/ResourcePlace.h
    Mob/MobSpawner.h
    Mob/EnemyInfo.h
    Mob/Spawner.h
    Mob/ArrowAnim.h
    Utility/TreeNode.hpp
    Utility/TreeNode_impl.hpp
    Utility/textfilefunctions.h
    MissionSystem/ResourceGoal.h
    MissionSystem/BasicGoal.h
    MissionSystem/Reward.h
    MissionSystem/Mission.h
    Grouping/SceneObjectFabric.h
    Grouping/FontManager.h
    Grouping/SceneObject.h
    Grouping/Scene.h
    Grouping/SceneManager.h
    GlobalConstants.h
    AbilitySystem/MobEffectReceiver.h
    AbilitySystem/EffectReceiver.h
    AbilitySystem/PrickObject.h
    AbilitySystem/BlinkObject.h
    AbilitySystem/SpellStorage.h
    AbilitySystem/ItemAbilities/ChoppersHat.h
    AbilitySystem/ItemAbilities/ItemAbility.h
    AbilitySystem/ItemAbilities/GoldPick.h
    AbilitySystem/ItemAbilities/IceTalisman.h
    AbilitySystem/ItemAbilities/BurningStick.h
    AbilitySystem/ItemAbilities/MerchantsHat.h
    AbilitySystem/ItemAbilities/FeatherOfChap.h
    AbilitySystem/ItemAbilities/MerchantsCaftan.h
    AbilitySystem/ItemAbilities/TitanChock.h
    AbilitySystem/ItemAbilities/ItemAbilitiesStorage.h
    AbilitySystem/ItemAbilities/UberionsCloak.h
    AbilitySystem/ItemAbilities/IceBoots.h
    AbilitySystem/ItemAbilities/SteelShield.h
    AbilitySystem/ItemAbilities/VampsRod.h
    AbilitySystem/ItemAbilities/RockSpike.h
    AbilitySystem/ItemAbilities/HelmOfLigofglass.h
    AbilitySystem/ItemAbilities/GulakiAmulet.h
    AbilitySystem/ItemAbilities/CorruptedPineApple.h
    AbilitySystem/ItemAbilities/MonolithShard.h
    AbilitySystem/ItemAbilities/MagicWheat.h
    AbilitySystem/ItemAbilities/BurningAxe.h

    AbilitySystem/DestructibleObjectEffectReceiver.h
    AbilitySystem/AbilityMagicStones.h
    AbilitySystem/AbilityShrink.h
    AbilitySystem/AbilityModel.h
    AbilitySystem/AbilitySnowStorm.h
    AbilitySystem/AbilityEarthquake.h
    AbilitySystem/AbilityAnims/AbilityAnimObject.hpp
    AbilitySystem/AbilityAnims/AbilityMultitargetObject.hpp

    AbilitySystem/AbilityObjectSpawn.h

    AbilitySystem/MobAbilities/MobAbilitiesMaker.h
    AbilitySystem/MobAbilities/MobAbilityRegeneration.h
    AbilitySystem/MobAbilities/MobAbility.h
    AbilitySystem/MobAbilities/MobAbilityArson.h
    AbilitySystem/MobAbilities/MobAbilitySprint.h
    AbilitySystem/MobAbilities/MobAbilityInvisiblity.h
    AbilitySystem/MobAbilities/MobAbilityWheat.h
    AbilitySystem/MobAbilities/MobAbilityFog.h
    AbilitySystem/MobAbilities/MobAbilitySummon.h
    AbilitySystem/MobAbilities/GulakiUpgrade.h
    AbilitySystem/MobAbilities/MobEarthTowerAbility.h
    AbilitySystem/MobAbilities/MobMageTowerAbility.h
    AbilitySystem/MobAbilities/MobCloudTowerAbility.h
    AbilitySystem/MobAbilities/TitanChockUpgrade.h
    AbilitySystem/MobAbilities/TitanChockMassSlow.h
    AbilitySystem/MobAbilities/MobAbilityInvulnerablity.h
    AbilitySystem/MobAbilities/MobAbilityHeal.h
    AbilitySystem/EffectModel.h

    AudioSystem/Sound.hpp
    AudioSystem/Music.hpp

    GlobalScripts/AccountModel.h
    GlobalScripts/ResourcesModel.h
    GlobalScripts/ResourceInfo.h
    GlobalScripts/ManaGlobal.h
    GlobalScripts/TileMapManager.h
    GlobalScripts/GameModel.h
    GlobalScripts/ResourceManager.h

    AI/AIComponent.h
    ItemSystem/Inventory.h
    ItemSystem/InventoryController.h
    ItemSystem/ItemModel.h
    ItemSystem/ShopController.h
    ItemSystem/HeroInventory.h
    ItemSystem/HeroInventoryController.h
    ItemSystem/ShopInventory.h

    GraphicsSystem/newSystem/IHasIdentifier.h
    GraphicsSystem/newSystem/Size.h
    GraphicsSystem/newSystem/Position.h
    GraphicsSystem/newSystem/UtilityStructs.h
    GraphicsSystem/newSystem/Font.h
    GraphicsSystem/newSystem/IComposite.h
    GraphicsSystem/newSystem/Composite.h
    GraphicsSystem/newSystem/ILayout.h
    GraphicsSystem/newSystem/VerticalLayout.h
    GraphicsSystem/newSystem/HorizontalLayout.h
    GraphicsSystem/newSystem/StubLayout.h

    GraphicsSystem/newSystem/UIElement/UILabel.h
    GraphicsSystem/newSystem/UIElement/HorizontalPanel.h
    GraphicsSystem/newSystem/UIElement/UIProgressBar.h

    Utility/StructData.hpp
    Utility/TextureData.hpp
    GraphicsSystem/newSystem/Texture2D.h
    GraphicsSystem/newSystem/Leaf.h
    Enums.h

    Logging/Logger.h
    GraphicsSystem/newSystem/RenderingSystem.h
    SDL_Engine.h
    GraphicsSystem/newSystem/UIElement/ConcreteComposite.h
    GraphicsSystem/newSystem/UIElement/UIImage.h
    GraphicsSystem/newSystem/UIElement/UITextButton.h
    GraphicsSystem/newSystem/UIElement/UIImageButton.h
    GraphicsSystem/newSystem/ConcreteUIViews/UIMissionView.h
    GraphicsSystem/newSystem/ConcreteUIViews/AnimationSceneSprite.h
    GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h
    GraphicsSystem/newSystem/ConcreteUIViews/UIShopItem.h
    GraphicsSystem/newSystem/ConcreteUIViews/UISlot.h

    GraphicsSystem/newSystem/ConcreteUIViews/UISlotContainer.h
    GraphicsSystem/newSystem/Camera2D.h

    GraphicsSystem/newSystem/Size.cpp
    GraphicsSystem/newSystem/Position.cpp
    Input/InputHandler.cpp
    Input/SceneInputHandler.cpp
    Input/InputDispatcher.cpp
    Scenes/MainScene.cpp
    Scenes/ShopScene.cpp
    Scenes/GameScene.cpp
    Scenes/InventoryScene.cpp
    Scenes/MapMenuScene.cpp
    Scenes/ScoreScene.cpp
    Scenes/src/MissionTumbler.cpp

    Mob/MineModel.cpp
    Mob/MobSpawner.cpp
    Mob/MobModel.cpp
    Mob/EnemyInfo.cpp
    Mob/Gates.cpp
    Mob/Mob.cpp
    Mob/Mine.cpp
    Mob/DestructibleObject.cpp
    Mob/TowerUpgradeController.cpp
    Mob/Tower.cpp
    Mob/ResourcePlace.cpp
    Mob/Spawner.cpp
    Mob/ArrowAnim.cpp
    Utility/textfilefunctions.cpp
    MissionSystem/Reward.cpp
    MissionSystem/ResourceGoal.cpp
    MissionSystem/BasicGoal.cpp
    MissionSystem/Mission.cpp
    Grouping/SceneManager.cpp
    Grouping/SceneObjectFabric.cpp
    Grouping/SceneObject.cpp
    Grouping/FontManager.cpp
    Grouping/Scene.cpp
    GameApp.cpp
    AbilitySystem/AbilityModel.cpp
    AbilitySystem/DestructibleObjectEffectReceiver.cpp
    AbilitySystem/AbilitySnowStorm.cpp
    AbilitySystem/PrickObject.cpp
    AbilitySystem/BlinkObject.cpp
    AbilitySystem/ItemAbilities/MerchantsCaftan.cpp
    AbilitySystem/ItemAbilities/ItemAbilitiesStorage.cpp
    AbilitySystem/ItemAbilities/VampsRod.cpp
    AbilitySystem/ItemAbilities/FeatherOfChap.cpp
    AbilitySystem/ItemAbilities/MerchantsHat.cpp
    AbilitySystem/ItemAbilities/GoldPick.cpp
    AbilitySystem/ItemAbilities/IceTalisman.cpp
    AbilitySystem/ItemAbilities/IceBoots.cpp
    AbilitySystem/ItemAbilities/HelmOfLigofglass.cpp
    AbilitySystem/ItemAbilities/BurningStick.cpp
    AbilitySystem/ItemAbilities/TitanChock.cpp
    AbilitySystem/ItemAbilities/RockSpike.cpp
    AbilitySystem/ItemAbilities/UberionsCloak.cpp
    AbilitySystem/ItemAbilities/ChoppersHat.cpp
    AbilitySystem/ItemAbilities/SteelShield.cpp
    AbilitySystem/ItemAbilities/ItemAbility.cpp
    AbilitySystem/ItemAbilities/GulakiAmulet.cpp
    AbilitySystem/ItemAbilities/CorruptedPineApple.cpp
    AbilitySystem/ItemAbilities/MonolithShard.cpp
    AbilitySystem/ItemAbilities/MagicWheat.cpp
    AbilitySystem/ItemAbilities/BurningAxe.cpp

    AbilitySystem/AbilityShrink.cpp
    AbilitySystem/MobEffectReceiver.cpp
    AbilitySystem/SpellStorage.cpp
    AbilitySystem/AbilityMagicStones.cpp
    AbilitySystem/EffectReceiver.cpp
    AbilitySystem/EffectModel.cpp
    AbilitySystem/AbilityEarthquake.cpp
    AbilitySystem/AbilityAnims/AbilityAnimObject.cpp
    AbilitySystem/AbilityAnims/AbilityMultitargetObject.cpp

    AbilitySystem/MobAbilities/MobAbilitiesMaker.cpp
    AbilitySystem/MobAbilities/MobAbilityRegeneration.cpp
    AbilitySystem/MobAbilities/MobAbilitySprint.cpp
    AbilitySystem/MobAbilities/MobAbilityArson.cpp
    AbilitySystem/MobAbilities/MobAbility.cpp
    AbilitySystem/MobAbilities/MobAbilityInvisiblity.cpp
    AbilitySystem/MobAbilities/MobAbilityWheat.cpp
    AbilitySystem/MobAbilities/GulakiUpgrade.cpp
    AbilitySystem/MobAbilities/MobEarthTowerAbility.cpp
    AbilitySystem/MobAbilities/MobMageTowerAbility.cpp
    AbilitySystem/MobAbilities/MobAbilityFog.cpp
    AbilitySystem/MobAbilities/MobAbilitySummon.cpp
    AbilitySystem/MobAbilities/MobCloudTowerAbility.cpp
    AbilitySystem/MobAbilities/TitanChockUpgrade.cpp
    AbilitySystem/MobAbilities/TitanChockMassSlow.cpp
    AbilitySystem/MobAbilities/MobAbilityInvulnerablity.cpp
    AbilitySystem/MobAbilities/MobAbilityHeal.cpp

    AudioSystem/Sound.cpp
    AudioSystem/Music.cpp

    GlobalScripts/ManaGlobal.cpp
    GlobalScripts/ResourcesModel.cpp
    GlobalScripts/ResourceInfo.cpp
    GlobalScripts/AccountModel.cpp
    GlobalScripts/GameModel.cpp
    GlobalScripts/TileMapManager.cpp
    GlobalScripts/ResourceManager.cpp

    main.cpp
    AI/AIComponent.cpp
    ItemSystem/HeroInventory.cpp
    ItemSystem/HeroInventoryController.cpp
    ItemSystem/Inventory.cpp
    ItemSystem/InventoryController.cpp
    ItemSystem/ShopController.cpp
    ItemSystem/ShopInventory.cpp
    ItemSystem/ItemModel.cpp

    GraphicsSystem/newSystem/IHasIdentifier.cpp
    GraphicsSystem/newSystem/Leaf.cpp
    GraphicsSystem/newSystem/Composite.cpp
    GraphicsSystem/newSystem/Font.cpp
    GraphicsSystem/newSystem/UIElement/UILabel.cpp
    GraphicsSystem/newSystem/VerticalLayout.cpp
    GraphicsSystem/newSystem/HorizontalLayout.cpp

    GraphicsSystem/newSystem/UIElement/HorizontalPanel.cpp
    GraphicsSystem/newSystem/UIElement/UIProgressBar.cpp
    GraphicsSystem/newSystem/Texture2D.cpp

    Logging/Logger.cpp
    GraphicsSystem/newSystem/RenderingSystem.cpp
    SDL_Engine.cpp
    GraphicsSystem/newSystem/UIElement/ConcreteComposite.cpp
    GraphicsSystem/newSystem/UIElement/UIImage.cpp
    GraphicsSystem/newSystem/UIElement/UITextButton.cpp
    GraphicsSystem/newSystem/UIElement/UIImageButton.cpp

    GraphicsSystem/newSystem/ConcreteUIViews/UIMissionView.cpp
    GraphicsSystem/newSystem/ConcreteUIViews/AnimationSceneSprite.cpp
    GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.cpp
    GraphicsSystem/newSystem/ConcreteUIViews/UIShopItem.cpp
    GraphicsSystem/newSystem/ConcreteUIViews/UISlot.cpp

    GraphicsSystem/newSystem/ConcreteUIViews/UISlotContainer.cpp
    GraphicsSystem/newSystem/Camera2D.cpp

    )

#find_package(Sanitizers)

add_executable(DarkDefenceGame ${SRC_LIST})
target_link_libraries(DarkDefenceGame
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY})
#add_sanitizers(DarkDefenceGame)

add_subdirectory(Scenes)
