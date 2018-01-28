project(SceneTests)
add_executable (${PROJECT_NAME} GameSceneTests.cpp)

set(scenesPath ../../src/Scenes)
set(srcPath ../../src)

#TODO: solve include hell.
add_library(Scenes_hpp
    ${srcPath}/AbilitySystem/ItemAbilities/ItemAbilitiesStorage.cpp
    ${srcPath}/AbilitySystem/SpellStorage.cpp

    ${srcPath}/GlobalScripts/ManaGlobal.cpp

    ${srcPath}/GraphicsSystem/newSystem/UIElement/UILabel.cpp
    ${srcPath}/GraphicsSystem/newSystem/UIElement/UIProgressBar.cpp

    ${srcPath}/Grouping/Scene.cpp
    ${srcPath}/Grouping/SceneObjectFabric.cpp

    ${srcPath}/MissionSystem/Mission.cpp

    ${srcPath}/Mob/Gates.cpp
    ${srcPath}/Mob/ResourcePlace.cpp
    ${srcPath}/Mob/Spawner.cpp
    ${srcPath}/Mob/TowerUpgradeController.cpp
)

add_library(Scenes_cpp
    ${srcPath}/Scenes/GameScene.cpp

    ${srcPath}/GlobalScripts/GameModel.cpp
    ${srcPath}/GlobalScripts/ResourceManager.cpp

    ${srcPath}/GraphicsSystem/newSystem/UIElement/UIImageButton.cpp

    ${srcPath}/Input/InputDispatcher.cpp
    ${srcPath}/Input/SceneInputHandler.cpp

    ${srcPath}/Mob/Tower.cpp
    ${srcPath}/Utility/textfilefunctions.cpp
    ${srcPath}/Scenes/GameScene.cpp

    ${srcPath}/Logging/Logger.cpp
)
target_link_libraries (${PROJECT_NAME}
                      Scenes_hpp
                      Scenes_cpp
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME SceneTests COMMAND GameSceneTests)
