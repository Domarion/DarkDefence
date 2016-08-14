#include "ScoreScene.h"
#include "../GlobalScripts/GameModel.h"
#include <list>
using std::list;
#include <string>
using std::string;
#include "../GlobalScripts/AccountModel.h"
#include "../GraphicsSystem/UI/TextButton.h"
#include "../GraphicsSystem/UI/CompositeLabel.h"


ScoreScene::ScoreScene()
{

}

ScoreScene::~ScoreScene()
{

}

void ScoreScene::init(SceneManager *sceneManagerPtr)
{
    Renderer::getInstance()->setRendererDrawColor(255, 255, 255);

    Scene::init(sceneManagerPtr);

    showScoreView();

    initControlLabel();
    GameModel::getInstance()->resetGameValues();
}

void ScoreScene::clear()
{
    Scene::clear();

}

void ScoreScene::initControlLabel()
{
    TextButton* backButton = new TextButton();
    backButton->setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
    backButton->setRect(0, 0, 200, 50);
    backButton->setPos(Renderer::getInstance()->getScreenWidth() - 200, Renderer::getInstance()->getScreenHeight() - 50);
    backButton->setText("Главное меню");
    string s = "MainScene";
    backButton->ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, getParentSceneManager(), s));
    Scene::addToUIList(backButton);
}

void ScoreScene::showItemRewards()
{
    list<string> missionRewardItems = GameModel::getInstance()->getMissionReward().getFullDescription();

    int y0 = 50;
    for(auto mri = missionRewardItems.begin(); mri != missionRewardItems.end(); ++mri)
    {

        CompositeLabel* tempComposite = new CompositeLabel();
        tempComposite->setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        string iconPath = "GameData/textures/items/" + *mri + ".png";
        tempComposite->loadIcon( iconPath );
        tempComposite->setIconRect(0, 0, 30, 30);
        tempComposite->setPos(0, y0);
        tempComposite->setText(*mri);
        y0 += 50;
        Scene::addToUIList(tempComposite);

        GameModel::getInstance()->addItemToInventoryByName(*mri);
    }

}

void ScoreScene::showGoldReward()
{
    int y0 = 250;
    int goldCoins = 0;
    if (GameModel::getInstance() != nullptr)
        goldCoins = GameModel::getInstance()->getMissionReward().getGoldCoins();
    if (goldCoins > 0)
    {
        AccountModel::getInstance()->addGold(goldCoins);
        CompositeLabel* tempComposite = new CompositeLabel();
        tempComposite->setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        string iconPath2 = "GameData/textures/Resources/"
                + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(0) + ".png";
        tempComposite->loadIcon(iconPath2);
        tempComposite->setIconRect(0, 0, 30, 30);
        tempComposite->setPos(0, y0);
        tempComposite->setText(std::to_string(goldCoins));

        Scene::addToUIList(tempComposite);
    }
}

void ScoreScene::showScoreView()
{
    string ScoreText;
    if (GameModel::getInstance()->getGameStatus() == Enums::GameStatuses::gsWON)
    {
        ScoreText = "Получена награда:";

        showItemRewards();
        showGoldReward();

        int currentMissionIndex = GameModel::getInstance()->getCurrentMissionIndex();
        GameModel::getInstance()->setCurrentMissionIndex(currentMissionIndex + 1);
    }
    else
        ScoreText = "Миссия провалена";


    GameModel::getInstance()->saveGameData("GameData/save.bin");

    Label *ScoreLabel = new Label(ScoreText, FontManager::getInstance()->getFontByKind("ButtonFont"));

    ScoreLabel->setPos(0, 0);

    Scene::addToUIList(ScoreLabel);
}
