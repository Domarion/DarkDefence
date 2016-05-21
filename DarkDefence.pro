TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/AI/AIComponent.cpp \
    src/GlobalScripts/AccountModel.cpp \
    src/GlobalScripts/GameModel.cpp \
    src/GlobalScripts/ManaGlobal.cpp \
    src/GlobalScripts/ResourceInfo.cpp \
    src/GlobalScripts/ResourcesModel.cpp \
    src/GraphicsSystem/UI/GroupBox.cpp \
    src/GraphicsSystem/UI/Label.cpp \
    src/GraphicsSystem/UI/ProgressBar.cpp \
    src/GraphicsSystem/UI/ScrollList.cpp \
    src/GraphicsSystem/UI/SlotContainer.cpp \
    src/GraphicsSystem/UI/TextButton.cpp \
    src/GraphicsSystem/Camera.cpp \
    src/GraphicsSystem/CTexture.cpp \
    src/GraphicsSystem/Sprite.cpp \
    src/GraphicsSystem/Terrain.cpp \
    src/GraphicsSystem/Tile.cpp \
    src/Grouping/Scene.cpp \
    src/Grouping/SceneManager.cpp \
    src/Grouping/SceneObject.cpp \
    src/Grouping/SceneObjectFabric.cpp \
    src/Input/InputDispatcher.cpp \
    src/Input/InputHandler.cpp \
    src/ItemSystem/HeroInventory.cpp \
    src/ItemSystem/HeroInventoryController.cpp \
    src/ItemSystem/Inventory.cpp \
    src/ItemSystem/InventoryController.cpp \
    src/ItemSystem/ItemCell.cpp \
    src/ItemSystem/ItemModel.cpp \
    src/ItemSystem/ShopController.cpp \
    src/ItemSystem/ShopInventory.cpp \
    src/ItemSystem/ShopInventoryController.cpp \
    src/MissionSystem/BasicGoal.cpp \
    src/MissionSystem/Mission.cpp \
    src/MissionSystem/Reward.cpp \
    src/Mob/DestructibleObject.cpp \
    src/Mob/Gates.cpp \
    src/Mob/MineModel.cpp \
    src/Mob/Mob.cpp \
    src/Mob/MobModel.cpp \
    src/Mob/MobSpawner.cpp \
    src/Mob/StorageModel.cpp \
    src/Scenes/GameScene.cpp \
    src/Scenes/InventoryScene.cpp \
    src/Scenes/MainScene.cpp \
    src/Scenes/ShopScene.cpp \
    src/GameApp.cpp \
    src/main.cpp \
    src/Utility/NTree.cpp \
    src/Mob/TowerFabric.cpp \
    src/GlobalScripts/Renderer.cpp \
    src/Scenes/ScoreScene.cpp \
    src/Scenes/MapMenuScene.cpp \
    src/MissionSystem/ResourceGoal.cpp \
    src/GraphicsSystem/UI/MapIndicator.cpp \
    src/GraphicsSystem/UI/MissionView.cpp \
    src/GraphicsSystem/UI/ImageButton.cpp \
    src/AbilitySystem/EffectModel.cpp \
    src/AbilitySystem/AbilityModel.cpp \
    src/AbilitySystem/AbilityPrick.cpp \
    src/AbilitySystem/AbilityShrink.cpp \
    src/AbilitySystem/AbilityEarthquake.cpp \
    src/AbilitySystem/AbilitySnowStorm.cpp \
    src/AbilitySystem/AbilityMagicStones.cpp \
    src/AbilitySystem/EffectReceiver.cpp \
    src/AbilitySystem/MobEffectReceiver.cpp \
    src/AbilitySystem/DestructibleObjectEffectReceiver.cpp \
    src/GraphicsSystem/UI/CompositeLabel.cpp \
    src/Input/SceneInputHandler.cpp \
    src/Mob/ResourcePlace.cpp \
    src/Mob/Mine.cpp \
    src/AbilitySystem/ItemAbilities/ItemAbility.cpp \
    src/AbilitySystem/ItemAbilities/UberionsCloak.cpp \
    src/AbilitySystem/ItemAbilities/IceTalisman.cpp \
    src/AbilitySystem/ItemAbilities/HelmOfGold.cpp \
    src/AbilitySystem/ItemAbilities/CaftanOfGold.cpp \
    src/AbilitySystem/ItemAbilities/BurningStick.cpp \
    src/AbilitySystem/ItemAbilities/TitanChock.cpp \
    src/AbilitySystem/ItemAbilities/HelmOfLigofglass.cpp \
    src/AbilitySystem/ItemAbilities/ChoppersHat.cpp \
    src/AbilitySystem/ItemAbilities/GoldPick.cpp \
    src/AbilitySystem/ItemAbilities/IceBoots.cpp \
    src/AbilitySystem/ItemAbilities/RockSpike.cpp \
    src/AbilitySystem/ItemAbilities/SteelShield.cpp \
    src/AbilitySystem/ItemAbilities/VampsRod.cpp \
    src/AbilitySystem/PrickObject.cpp \
    src/AbilitySystem/MobAbilities/MobAbility.cpp \
    src/AbilitySystem/MobAbilities/MobAbilityArson.cpp \
    src/AbilitySystem/MobAbilities/MobAbilityRegeneration.cpp \
    src/AbilitySystem/MobAbilities/MobAbilitySprint.cpp \
    src/GraphicsSystem/UI/AnimatedSprite.cpp \
    src/AbilitySystem/MobAbilities/MobAbilityInvisiblity.cpp \
    src/Mob/Tower.cpp \
    src/Mob/TowerUpgradeController.cpp \
    src/AbilitySystem/ItemAbilities/FeatherOfChap.cpp \
    src/GraphicsSystem/ShopItemUI.cpp \
    src/Utility/textfilefunctions.cpp

HEADERS += \
    src/AI/AIComponent.h \
    src/GlobalScripts/AccountModel.h \
    src/GlobalScripts/GameModel.h \
    src/GlobalScripts/ManaGlobal.h \
    src/GlobalScripts/ResourceInfo.h \
    src/GlobalScripts/ResourcesModel.h \
    src/GraphicsSystem/UI/GroupBox.h \
    src/GraphicsSystem/UI/Label.h \
    src/GraphicsSystem/UI/ProgressBar.h \
    src/GraphicsSystem/UI/ScrollList.h \
    src/GraphicsSystem/UI/SlotContainer.h \
    src/GraphicsSystem/UI/TextButton.h \
    src/GraphicsSystem/Camera.h \
    src/GraphicsSystem/CTexture.h \
    src/GraphicsSystem/Sprite.h \
    src/GraphicsSystem/Terrain.h \
    src/GraphicsSystem/Tile.h \
    src/Grouping/Scene.h \
    src/Grouping/SceneManager.h \
    src/Grouping/SceneObject.h \
    src/Grouping/SceneObjectFabric.h \
    src/Input/InputDispatcher.h \
    src/Input/InputHandler.h \
    src/ItemSystem/HeroInventory.h \
    src/ItemSystem/HeroInventoryController.h \
    src/ItemSystem/Inventory.h \
    src/ItemSystem/InventoryController.h \
    src/ItemSystem/ItemCell.h \
    src/ItemSystem/ItemModel.h \
    src/ItemSystem/ShopController.h \
    src/ItemSystem/ShopInventory.h \
    src/ItemSystem/ShopInventoryController.h \
    src/MissionSystem/BasicGoal.h \
    src/MissionSystem/Mission.h \
    src/MissionSystem/Reward.h \
    src/Mob/DestructibleObject.h \
    src/Mob/Gates.h \
    src/Mob/MineModel.h \
    src/Mob/Mob.h \
    src/Mob/MobModel.h \
    src/Mob/MobSpawner.h \
    src/Mob/StorageModel.h \
    src/Scenes/GameScene.h \
    src/Scenes/InventoryScene.h \
    src/Scenes/MainScene.h \
    src/Scenes/ShopScene.h \
    src/Utility/TreeNode.hpp \
    src/Utility/TreeNode_impl.hpp \
    src/Enums.h \
    src/GameApp.h \
    src/Utility/NTree.h \
    src/Mob/TowerFabric.hpp \
    src/GlobalScripts/Renderer.h \
    src/Scenes/ScoreScene.h \
    src/Scenes/MapMenuScene.h \
    src/MissionSystem/ResourceGoal.h \
    src/GraphicsSystem/UI/MapIndicator.h \
    src/GraphicsSystem/UI/MissionView.h \
    src/GraphicsSystem/UI/ImageButton.h \
    src/AbilitySystem/EffectModel.h \
    src/AbilitySystem/AbilityModel.h \
    src/AbilitySystem/AbilityPrick.h \
    src/AbilitySystem/AbilityShrink.h \
    src/AbilitySystem/AbilityEarthquake.h \
    src/AbilitySystem/AbilitySnowStorm.h \
    src/AbilitySystem/AbilityMagicStones.h \
    src/AbilitySystem/EffectReceiver.h \
    src/AbilitySystem/MobEffectReceiver.h \
    src/AbilitySystem/DestructibleObjectEffectReceiver.h \
    src/GraphicsSystem/UI/CompositeLabel.h \
    src/Input/SceneInputHandler.h \
    src/Mob/ResourcePlace.h \
    src/Mob/Mine.h \
    src/AbilitySystem/ItemAbilities/ItemAbility.h \
    src/AbilitySystem/ItemAbilities/UberionsCloak.h \
    src/AbilitySystem/ItemAbilities/IceTalisman.h \
    src/AbilitySystem/ItemAbilities/HelmOfGold.h \
    src/AbilitySystem/ItemAbilities/CaftanOfGold.h \
    src/AbilitySystem/ItemAbilities/BurningStick.h \
    src/AbilitySystem/ItemAbilities/TitanChock.h \
    src/AbilitySystem/ItemAbilities/HelmOfLigofglass.h \
    src/AbilitySystem/ItemAbilities/ChoppersHat.h \
    src/AbilitySystem/ItemAbilities/GoldPick.h \
    src/AbilitySystem/ItemAbilities/IceBoots.h \
    src/AbilitySystem/ItemAbilities/RockSpike.h \
    src/AbilitySystem/ItemAbilities/SteelShield.h \
    src/AbilitySystem/ItemAbilities/VampsRod.h \
    src/AbilitySystem/PrickObject.h \
    src/AbilitySystem/MobAbilities/MobAbility.h \
    src/AbilitySystem/MobAbilities/MobAbilityArson.h \
    src/AbilitySystem/MobAbilities/MobAbilityRegeneration.h \
    src/AbilitySystem/MobAbilities/MobAbilitySprint.h \
    src/GraphicsSystem/UI/AnimatedSprite.h \
    src/AbilitySystem/MobAbilities/MobAbilityInvisiblity.h \
    src/Mob/Tower.h \
    src/Mob/TowerUpgradeController.h \
    src/AbilitySystem/ItemAbilities/FeatherOfChap.h \
    src/GraphicsSystem/ShopItemUI.h \
    src/Utility/textfilefunctions.h

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib64/ -lboost_serialization

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib64/ -lSDL2

INCLUDEPATH += $$PWD/../../../../usr/include/SDL2
DEPENDPATH += $$PWD/../../../../usr/include/SDL2

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib64/ -lSDL2_image

INCLUDEPATH += $$PWD/../../../../usr/include/SDL2
DEPENDPATH += $$PWD/../../../../usr/include/SDL2

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib64/ -lSDL2_ttf

INCLUDEPATH += $$PWD/../../../../usr/include/SDL2
DEPENDPATH += $$PWD/../../../../usr/include/SDL2
