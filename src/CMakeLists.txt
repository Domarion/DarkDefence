set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O2 -Wall -ggdb")
#    -Weffc++ -pedantic  \
#    -pedantic-errors -Wextra -Waggregate-return -Wcast-align \
#    -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
#    -Wdisabled-optimization \
#    -Wfloat-equal  -Wformat  -Wformat=2 \
#    -Wformat-nonliteral -Wformat-security  \
#    -Wformat-y2k \
#    -Wimplicit  -Wimport  -Winit-self  -Winline \
#    -Winvalid-pch   \
#    -Wunsafe-loop-optimizations  -Wlong-long -Wmissing-braces \
#    -Wmissing-field-initializers -Wmissing-format-attribute   \
#    -Wmissing-include-dirs -Wmissing-noreturn \
#    -Wpacked -Wparentheses  -Wpointer-arith \
#    -Wredundant-decls -Wreturn-type \
#    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
#    -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch \
#    -Wswitch-enum -Wtrigraphs  -Wuninitialized \
#    -Wunknown-pragmas  -Wunreachable-code -Wunused \
#    -Wunused-function  -Wunused-label  -Wunused-parameter \
#    -Wunused-value  -Wunused-variable  -Wvariadic-macros \
#    -Wvolatile-register-var  -Wwrite-strings")

#set(OLD_SRC_LIST
#    GraphicsSystem/UI/MapIndicator.h
#    GraphicsSystem/UI/StateButton.h
#    GraphicsSystem/UI/GroupBox.h
#    GraphicsSystem/UI/ImageButton.h
#    GraphicsSystem/UI/CompositeLabel.h
#    GraphicsSystem/UI/Label.h
#    GraphicsSystem/UI/SlotContainer.h
#    GraphicsSystem/UI/MissionView.h
#    GraphicsSystem/UI/ScrollList.h
#    GraphicsSystem/UI/TextButton.h
#    GraphicsSystem/UI/AnimatedSprite.h
#    GraphicsSystem/UI/ProgressBar.h
#    GraphicsSystem/ShopItemUI.h
#    GraphicsSystem/CFont.h
#    GraphicsSystem/CTexture.h
#    GraphicsSystem/GraphicsManager.h
#    GraphicsSystem/IDrawable.h

#    GraphicsSystem/UI/StateButton.cpp
#    GraphicsSystem/UI/Label.cpp
#    GraphicsSystem/UI/MapIndicator.cpp
#    GraphicsSystem/UI/MissionView.cpp
#    GraphicsSystem/UI/ProgressBar.cpp
#    GraphicsSystem/UI/ScrollList.cpp
#    GraphicsSystem/UI/ImageButton.cpp
#    GraphicsSystem/UI/SlotContainer.cpp
#    GraphicsSystem/UI/CompositeLabel.cpp
#    GraphicsSystem/UI/AnimatedSprite.cpp
#    GraphicsSystem/UI/TextButton.cpp
#    GraphicsSystem/UI/GroupBox.cpp
#    GraphicsSystem/CTexture.cpp
#    GraphicsSystem/CFont.cpp
#    GraphicsSystem/GraphicsManager.cpp
#    GraphicsSystem/ShopItemUI.cpp
#    GlobalScripts/Renderer.h
#    GlobalScripts/Renderer.cpp
#)

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
    GameApp.h
    Mob/Mob.h
    Mob/TowerFabric.hpp
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
    Utility/TreeNode.hpp
    Utility/TreeNode_impl.hpp
    Utility/textfilefunctions.h
    Utility/Size.h
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
    SaveData/DataGenerator.h
    AbilitySystem/MobEffectReceiver.h
    AbilitySystem/EffectReceiver.h
    AbilitySystem/PrickObject.h
    AbilitySystem/SpellStorage.h
    AbilitySystem/ItemAbilities/ChoppersHat.h
    AbilitySystem/ItemAbilities/ItemAbility.h
    AbilitySystem/ItemAbilities/GoldPick.h
    AbilitySystem/ItemAbilities/IceTalisman.h
    AbilitySystem/ItemAbilities/BurningStick.h
    AbilitySystem/ItemAbilities/HelmOfGold.h
    AbilitySystem/ItemAbilities/FeatherOfChap.h
    AbilitySystem/ItemAbilities/CaftanOfGold.h
    AbilitySystem/ItemAbilities/TitanChock.h
    AbilitySystem/ItemAbilities/ItemAbilitiesStorage.h
    AbilitySystem/ItemAbilities/UberionsCloak.h
    AbilitySystem/ItemAbilities/IceBoots.h
    AbilitySystem/ItemAbilities/SteelShield.h
    AbilitySystem/ItemAbilities/VampsRod.h
    AbilitySystem/ItemAbilities/RockSpike.h
    AbilitySystem/ItemAbilities/HelmOfLigofglass.h
    AbilitySystem/ItemAbilities/GulakiAmulet.h

    AbilitySystem/DestructibleObjectEffectReceiver.h
    AbilitySystem/AbilityMagicStones.h
    AbilitySystem/AbilityShrink.h
    AbilitySystem/AbilityModel.h
    AbilitySystem/AbilitySnowStorm.h
    AbilitySystem/AbilityEarthquake.h
    AbilitySystem/AbilityPrick.h
    AbilitySystem/AbilityMagicBlink.h

    AbilitySystem/MobAbilities/MobAbilityRegeneration.h
    AbilitySystem/MobAbilities/MobAbility.h
    AbilitySystem/MobAbilities/MobAbilityArson.h
    AbilitySystem/MobAbilities/MobAbilitySprint.h
    AbilitySystem/MobAbilities/MobAbilityInvisiblity.h
    AbilitySystem/MobAbilities/MobAbilityWheat.h

    AbilitySystem/EffectModel.h
    GlobalScripts/AccountModel.h
    GlobalScripts/ResourcesModel.h
    GlobalScripts/ResourceInfo.h
    GlobalScripts/ManaGlobal.h
    GlobalScripts/TileMapManager.h
    GlobalScripts/GameModel.h

    AI/AIComponent.h
    ItemSystem/Inventory.h
    ItemSystem/InventoryController.h
    ItemSystem/ItemModel.h
    ItemSystem/ShopController.h
    ItemSystem/HeroInventory.h
    ItemSystem/ItemCell.h
    ItemSystem/HeroInventoryController.h
    ItemSystem/ShopInventory.h

    GraphicsSystem/newSystem/Font.h
    GraphicsSystem/newSystem/Composite.h
    GraphicsSystem/newSystem/IComposite.h
    GraphicsSystem/newSystem/UIElement/UILabel.h
    GraphicsSystem/newSystem/UIElement/HorizontalPanel.h
    GraphicsSystem/newSystem/UIElement/UIProgressBar.h
    GraphicsSystem/newSystem/UtilityStructs.h
    GraphicsSystem/newSystem/Texture2D.h
    GraphicsSystem/newSystem/Leaf.h
    Enums.h


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

    GraphicsSystem/newSystem/UtilityStructs.cpp
    Input/InputHandler.cpp
    Input/SceneInputHandler.cpp
    Input/InputDispatcher.cpp
    Scenes/MainScene.cpp
    Scenes/ShopScene.cpp
    Scenes/GameScene.cpp
    Scenes/InventoryScene.cpp
    Scenes/MapMenuScene.cpp
    Scenes/ScoreScene.cpp
    Mob/MineModel.cpp
    Mob/MobSpawner.cpp
    Mob/MobModel.cpp
    Mob/TowerFabric.cpp
    Mob/EnemyInfo.cpp
    Mob/Gates.cpp
    Mob/Mob.cpp
    Mob/Mine.cpp
    Mob/DestructibleObject.cpp
    Mob/TowerUpgradeController.cpp
    Mob/Tower.cpp
    Mob/ResourcePlace.cpp
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
    SaveData/DataGenerator.cpp
    GameApp.cpp
    AbilitySystem/AbilityModel.cpp
    AbilitySystem/DestructibleObjectEffectReceiver.cpp
    AbilitySystem/AbilitySnowStorm.cpp
    AbilitySystem/PrickObject.cpp
    AbilitySystem/AbilityPrick.cpp
    AbilitySystem/ItemAbilities/CaftanOfGold.cpp
    AbilitySystem/ItemAbilities/ItemAbilitiesStorage.cpp
    AbilitySystem/ItemAbilities/VampsRod.cpp
    AbilitySystem/ItemAbilities/FeatherOfChap.cpp
    AbilitySystem/ItemAbilities/HelmOfGold.cpp
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

    AbilitySystem/AbilityShrink.cpp
    AbilitySystem/MobEffectReceiver.cpp
    AbilitySystem/SpellStorage.cpp
    AbilitySystem/AbilityMagicStones.cpp
    AbilitySystem/EffectReceiver.cpp
    AbilitySystem/EffectModel.cpp
    AbilitySystem/AbilityEarthquake.cpp
    AbilitySystem/AbilityMagicBlink.cpp
    AbilitySystem/MobAbilities/MobAbilityRegeneration.cpp
    AbilitySystem/MobAbilities/MobAbilitySprint.cpp
    AbilitySystem/MobAbilities/MobAbilityArson.cpp
    AbilitySystem/MobAbilities/MobAbility.cpp
    AbilitySystem/MobAbilities/MobAbilityInvisiblity.cpp
    AbilitySystem/MobAbilities/MobAbilityWheat.cpp

    GlobalScripts/ManaGlobal.cpp
    GlobalScripts/ResourcesModel.cpp
    GlobalScripts/ResourceInfo.cpp
    GlobalScripts/AccountModel.cpp
    GlobalScripts/GameModel.cpp
    GlobalScripts/TileMapManager.cpp
    main.cpp
    AI/AIComponent.cpp
    ItemSystem/HeroInventory.cpp
    ItemSystem/HeroInventoryController.cpp
    ItemSystem/Inventory.cpp
    ItemSystem/InventoryController.cpp
    ItemSystem/ShopController.cpp
    ItemSystem/ShopInventory.cpp
    ItemSystem/ItemModel.cpp

    GraphicsSystem/newSystem/Leaf.cpp
    GraphicsSystem/newSystem/Composite.cpp
    GraphicsSystem/newSystem/Font.cpp
    GraphicsSystem/newSystem/UIElement/UILabel.cpp
    GraphicsSystem/newSystem/UIElement/HorizontalPanel.cpp
    GraphicsSystem/newSystem/UIElement/UIProgressBar.cpp
    GraphicsSystem/newSystem/Texture2D.cpp

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


find_package(Boost COMPONENTS serialization REQUIRED)
include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(DarkDefenceGame ${SRC_LIST})
target_link_libraries( DarkDefenceGame ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${Boost_LIBRARIES})

