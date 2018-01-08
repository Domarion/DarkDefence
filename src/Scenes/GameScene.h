#pragma once

#include "../Grouping/Scene.h"
#include "../Mob/Spawner.h"
#include "../Grouping/SceneObjectFabric.h"
#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIProgressBar.h"

#include "../Mob/Gates.h"

#include "../MissionSystem/Mission.h"
#include "../AbilitySystem/SpellStorage.h"

#include "../Mob/ResourcePlace.h"
#include "../Mob/TowerUpgradeController.h"
#include "../AbilitySystem/ItemAbilities/ItemAbilitiesStorage.h"

#include "../GlobalScripts/ManaGlobal.h"
#include "Utility/StructData.hpp"
using std::vector;

class GameScene : public Scene
{
public:
    enum class SceneModeT
    {
        StandardMode = 0,
        PlacingMode = 1
    };

    GameScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);

    const map<std::string, std::shared_ptr<AbilityModel> >& getAbilityModelList() const;
    void ConnectMethod(std::function<void(string)> handler);
    std::shared_ptr<AbilityModel> getAbilityModelWithName(string name);
    void sendMessage(string msgText);

    std::shared_ptr<ManaGlobal> getManaModel() const;
    void processWaveInfo(std::string aInfo);
    void setGameSceneStatus(Enums::GameSceneStatuses aStatus);
    Enums::GameSceneStatuses getGameSceneStatus() const;
    void setAbilityPlacingMode(const std::string& aAbilityName);

    void placingCallBack();
    void spawningCallBack(std::string aMobName, Position aSpawnPosition, size_t aDrawPriority);

    // Scene interface
    void init(std::shared_ptr<SceneManager> sceneManagerPtr) override;
    void clear() override;
    void startUpdate(double timestep) override;
    void copyToRender() const override;

    SceneModeT getSceneMode() const;

    const std::shared_ptr<TileMapManager>& getTileMap() const;

private:

    void loadData();

    void initTopPanel();
    void initAbilitiesButtons();
    void initUILayer();

//    void placeResourcesPlaces();
//    void placeCastle();
//    void placeTowers();
    void placeSceneObjects();

    void applyArtefactEffects();
    void initResourceView();
    void initProgressBars();
    void setActiveMstones(string s);
    void initAbilityCallBacks(const std::string& aAbilityName);

    std::shared_ptr<Gates> gates;
    std::shared_ptr<UIProgressBar> gatesHealthBar, manaBar;
    std::shared_ptr<UILabel> pointsLabel;
    std::shared_ptr<UILabel> waveLabel;

    SceneObjectFabric objectFabric;

    vector<std::shared_ptr<UILabel> > resourceLabels;

    std::shared_ptr<Spawner> monsterSpawner;

    Mission currentMission;

    SpellStorage spellStorage;
    ItemAbilitiesStorage itemAbilitiesStorage;
    std::shared_ptr<TowerUpgradeController> towerUpgradeController;

    std::function<void(string)> method;

    std::shared_ptr<TileMapManager> tileMap;
    std::shared_ptr<ManaGlobal> mManaModel;
    vector<StructureData> mPositionsVector;
    Enums::GameSceneStatuses mGameSceneCurrentStatus = Enums::GameSceneStatuses::Default;
    SceneModeT mSceneMode = SceneModeT::StandardMode;
    double counter = 5000;
};
