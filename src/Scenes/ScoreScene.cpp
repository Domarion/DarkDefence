#include "ScoreScene.h"
#include "../Input/InputDispatcher.h"
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
       // arialFont.get()->loadFromFile("Fonts/arial.ttf", 18);

        button.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        button.setRect(0, 0, 100, 50);
        button.setPos(Renderer::getInstance()->getScreenWidth() - 100, Renderer::getInstance()->getScreenHeight() - 50);
        button.setText("Главное меню");
        string s = "MainScene";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s));
        listGUI.push_back(&button);

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
              // std::cout << (*mri) << std::endl;
               tempComposite->loadIcon( iconPath );
               tempComposite->setIconRect(0, 0, 30, 30);
               tempComposite->setPos(0, y0);
               tempComposite->setText(*mri);
               y0 += 50;
               rewardViews.push_back(tempComposite);
               listGUI.push_back(tempComposite);

              GameModel::getInstance()->addItemToInventoryByName(*mri);//TODO::implement method
           }

           int goldCoins = 0;
           if (GameModel::getInstance() != nullptr)
                goldCoins = GameModel::getInstance()->getMissionReward().getGoldCoins();
          // std::cout << "goldCoins =" << goldCoins << std::endl;
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
               listGUI.push_back(tempComposite);
           }
        }
        else
            ScoreText = "Миссия провалена";

        ScoreLabel.setText(ScoreText);
        listGUI.push_back(&ScoreLabel);

        GameModel::getInstance()->resetGameValues();
    }
    InputDispatcher::getInstance()->addHandler(&button);
}


void ScoreScene::finalizeScene()
{
  //  TTF_CloseFont(arialFont);
}
