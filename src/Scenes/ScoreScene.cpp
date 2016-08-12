#include "ScoreScene.h"
#include "../GlobalScripts/GameModel.h"
#include <list>
using std::list;
#include <string>
using std::string;
#include "../GlobalScripts/AccountModel.h"

ScoreScene::ScoreScene()
    //:arialFont(new CFont())
{

}

ScoreScene::~ScoreScene()
{

   // rewardViews.clear();
}

void ScoreScene::initScene(SceneManager *sceneManagerPtr)
{
 Renderer::getInstance()->setRendererDrawColor(255, 255, 255);
    if (!wasInited)
    {
        Scene::initScene(sceneManagerPtr);

        button.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        button.setRect(0, 0, 200, 50);
        button.setPos(Renderer::getInstance()->getScreenWidth() - 200, Renderer::getInstance()->getScreenHeight() - 50);
        button.setText("Главное меню");
        string s = "MainScene";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s));
        Scene::addToUIList(&button);

        ScoreLabel.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        ScoreLabel.setRect(0, 0, 200, 50);


        string ScoreText;
        if (GameModel::getInstance()->getGameStatus() == Enums::GameStatuses::gsWON)
        {
           ScoreText = "Получена награда:";


           list<string> missionRewardItems = GameModel::getInstance()->getMissionReward().getFullDescription();

           int y0 = 50;
           rewardViews.reserve(missionRewardItems.size());
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
               rewardViews.push_back(tempComposite);
               Scene::addToUIList(tempComposite);

              GameModel::getInstance()->addItemToInventoryByName(*mri);//TODO::implement method
           }

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

               rewardViews.push_back(tempComposite);
               Scene::addToUIList(tempComposite);
           }
            int currentMissionIndex = GameModel::getInstance()->getCurrentMissionIndex();
            GameModel::getInstance()->setCurrentMissionIndex(currentMissionIndex + 1);
        }
        else
            ScoreText = "Миссия провалена";

        ScoreLabel.setText(ScoreText);
        Scene::addToUIList(&ScoreLabel);


    }
    GameModel::getInstance()->resetGameValues();
}


void ScoreScene::finalizeScene()
{
    //  TTF_CloseFont(arialFont);
}

void ScoreScene::resetState()
{
    ScoreLabel.free();
    for(auto rewardView = rewardViews.begin(); rewardView != rewardViews.end();++rewardView)
        delete (*rewardView);
    rewardViews.clear();
    Scene::resetState();
}
