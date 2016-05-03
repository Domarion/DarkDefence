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
    src/GraphicsSystem/UI/ImageButton.cpp

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
    src/GraphicsSystem/UI/ImageButton.h

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
