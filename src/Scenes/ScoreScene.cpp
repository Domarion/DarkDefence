#include "ScoreScene.h"
#include "../GlobalScripts/GameModel.h"
#include <list>
#include "../GlobalScripts/AccountModel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"

using std::list;
using std::string;

ScoreScene::ScoreScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
{
}

void ScoreScene::init(std::shared_ptr<SceneManager> sceneManagerPtr)
{
    renderer->setRendererDrawColor(255, 255, 255, 255);

    Scene::init(sceneManagerPtr);

    showScoreView();

    Scene::addLoadSceneButton("Главное меню", "ButtonFont", "MainScene",
                MainRect->getSize().width/2 - 75, MainRect->getSize().height - 50 , 150, 50);

    GameModel::getInstance()->resetGameValues();
    Scene::addToUIList(MainRect);
}

void ScoreScene::clear()
{
    Scene::clear();
}

void ScoreScene::showItemRewards()
{
    auto layout = std::make_shared<StubLayout>();

    auto rewardGroup = std::make_shared<ConcreteComposite>(renderer, layout);
    rewardGroup->setSize(Size(MainRect->getSize().width/2, MainRect->getSize().height/3));
    rewardGroup->setPosition(MainRect->getNextVerticalPosition());

    list<string> missionRewardItems = GameModel::getInstance()->getMissionReward().getFullDescription();

    const auto& font = FontManager::getInstance()->getFontByKind2("ButtonFont");
    for(auto& rewardItem : missionRewardItems)
    {
        auto rewardIcon = std::make_shared<UIImage>(renderer);
        rewardIcon->setSize(Size(30, 30));
        rewardIcon->setPosition(rewardGroup->getNextVerticalPosition());
        string iconPath = "GameData/textures/items/" + rewardItem + ".png";
        rewardIcon->loadTexture( iconPath );

        rewardGroup->addChild(rewardIcon);

        auto rewardLabel = std::make_shared<UILabel>(rewardItem, font, renderer);
        rewardLabel->setPosition(rewardGroup->getNextHorizontalPosition());
        rewardGroup->addChild(rewardLabel);

        GameModel::getInstance()->addItemToInventoryByName(rewardItem);
    }

    MainRect->addChild(rewardGroup);
}

void ScoreScene::showGoldReward()
{
    int goldCoins = 0;
    if (GameModel::getInstance() != nullptr)
        goldCoins = GameModel::getInstance()->getMissionReward().getGoldCoins();
    if (goldCoins > 0)
    {
        AccountModel::getInstance()->addGold(goldCoins);
        auto layout = std::make_shared<StubLayout>();

        auto rewardGoldGroup = std::make_shared<ConcreteComposite>(renderer, layout);
        rewardGoldGroup->setSize(Size(MainRect->getSize().width/2, MainRect->getSize().height/3));
        rewardGoldGroup->setPosition(MainRect->getNextVerticalPosition());


        const auto& font = FontManager::getInstance()->getFontByKind2("ButtonFont");
        auto rewardGoldIcon = std::make_shared<UIImage>(renderer);
        rewardGoldIcon->setSize(Size(30, 30));
        rewardGoldIcon->setPosition(rewardGoldGroup->getNextVerticalPosition());
        string iconPath = "GameData/textures/Resources/Gold.png";
        rewardGoldIcon->loadTexture( iconPath );

        rewardGoldGroup->addChild(rewardGoldIcon);

        auto rewardGoldLabel = std::make_shared<UILabel>(std::to_string(goldCoins), font, renderer);
        rewardGoldLabel->setPosition(rewardGoldGroup->getNextHorizontalPosition());
        rewardGoldGroup->addChild(rewardGoldLabel);

        MainRect->addChild(rewardGoldGroup);
    }
}

void ScoreScene::showScoreView()
{
    const auto& font = FontManager::getInstance()->getFontByKind2("ButtonFont");
    auto scoreLabel = std::make_shared<UILabel>("none", font, renderer);
    scoreLabel->setPosition(Position(MainRect->getSize().width/2 - 75, 0));
    MainRect->addChild(scoreLabel);

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
    {
        ScoreText = "Миссия провалена";
    }

    GameModel::getInstance()->saveGameData("GameData/save.bin");

    scoreLabel->setText(ScoreText);
}
