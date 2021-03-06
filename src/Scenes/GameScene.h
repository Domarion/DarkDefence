#pragma once

#include "../AbilitySystem/ItemAbilities/ItemAbilitiesStorage.h"
#include "../AbilitySystem/SpellStorage.h"

#include "../GlobalScripts/ManaGlobal.h"

#include "../Grouping/Scene.h"
#include "../Grouping/SceneObjectFabric.h"

#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIProgressBar.h"

#include "../MissionSystem/Mission.h"

#include "../Mob/Gates.h"
#include "../Mob/ResourcePlace.h"
#include "../Mob/Spawner.h"
#include "../Mob/TowerUpgradeController.h"
#include "GlobalScripts/TileMapManager.h"

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

    const std::map<std::string, std::shared_ptr<AbilityModel>>& getAbilityModelList() const;
    void ConnectMethod(std::function<void(string)> handler);
    const std::shared_ptr<AbilityModel>& getAbilityModelWithName(const std::string& aName);
    void sendMessage(string msgText);

    const std::shared_ptr<ManaGlobal>& getManaModel() const;
    void processWaveInfo(std::string aInfo);
    void setGameSceneStatus(Enums::GameSceneStatuses aStatus);
    Enums::GameSceneStatuses getGameSceneStatus() const;
    void setAbilityPlacingMode(const std::string& aAbilityName);

    void placingCallBack();
    void spawningCallBack(std::string aMobName, Position aSpawnPosition, size_t aDrawPriority);

    // Scene interface
    void init() override;
    void clear() override;
    void startUpdate(double timestep) override;
    void copyToRender() const override;

    SceneModeT getSceneMode() const;

    const TileMapManager& getTileMap() const;

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

    TileMapManager mTileMap;
    std::shared_ptr<ManaGlobal> mManaModel;
    vector<StructureData> mPositionsVector;
    Enums::GameSceneStatuses mGameSceneCurrentStatus = Enums::GameSceneStatuses::Default;
    SceneModeT mSceneMode = SceneModeT::StandardMode;
    double counter = 5000;
    std::string currentMissionPath;
};
