#include "ScoreScene.h"
#include "../Input/InputDispatcher.h"
#include "../GlobalScripts/GameModel.h"
#include <list>
using std::list;
#include <string>
using std::string;
#include "../GlobalScripts/AccountModel.h"

ScoreScene::ScoreScene()
    :arialFont(nullptr)
{

}

ScoreScene::~ScoreScene()
{
    TTF_CloseFont(arialFont);
    rewardViews.clear();
}

void ScoreScene::initScene(SceneManager *sceneManagerPtr)
{
    if (!wasInited)
    {
        Scene::initScene(sceneManagerPtr);
        arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 18);
        SDL_Color color = {255, 255, 255};
        button.setFont(arialFont, color);
        button.setRect(700, 550, 100, 50);
        button.setText("Главное меню");
        string s = "MainMenu";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s));
        listGUI.push_back(&button);

        ScoreLabel.setFont(arialFont, color);
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
               tempComposite->setFont(arialFont, color);
               string iconPath = "/home/kostya_hm/Projects/DarkDefence/GameData/textures/items/" + *mri + ".png";
              // std::cout << (*mri) << std::endl;
               tempComposite->setIcon(Renderer::getInstance()->loadTextureFromFile( iconPath ));
               tempComposite->setIconRect(0, 0, 30, 30);
               tempComposite->setPos(0, y0);
               tempComposite->setText(*mri);
               y0 += 50;
               rewardViews.push_back(tempComposite);
               listGUI.push_back(tempComposite);
           }

           int goldCoins = 0;
           if (GameModel::getInstance() != nullptr)
                goldCoins =GameModel::getInstance()->getMissionReward().getGoldCoins();
          // std::cout << "goldCoins =" << goldCoins << std::endl;
           if (goldCoins > 0)
           {
           AccountModel::getInstance()->addGold(goldCoins);
           CompositeLabel* tempComposite = new CompositeLabel();
           tempComposite->setFont(arialFont, color);
           string iconPath2 = "/home/kostya_hm/Projects/DarkDefence/GameData/textures/Resources/"
                   + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(0) + ".png";
           tempComposite->setIcon(Renderer::getInstance()->loadTextureFromFile( iconPath2 ));
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
    }
    InputDispatcher::getInstance()->addHandler(&button);
}


void ScoreScene::finalizeScene()
{
    TTF_CloseFont(arialFont);
}
