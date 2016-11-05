/*
 * MainScene.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "MainScene.h"
#include "../Utility/textfilefunctions.h"
#include <sstream>
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"

MainScene::MainScene(std::shared_ptr<RenderingSystem> &aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    :Scene(aRenderer, aInputDispatcher)
{
}

MainScene::~MainScene()
{
    clear();
}


void MainScene::init(std::shared_ptr<SceneManager> sceneManagerPtr)
{
    Scene::init(sceneManagerPtr);

    if (itemNamesSceneNamesMapping.empty())
        loadMenuItems("GameData/MainMenu.txt");

    initBackground();
    initUIMenuItems();
    Scene::addToUIList(MainRect);
}



void MainScene::loadMenuItems(string filename)
{
   string destString;
   androidText::loadTextFileToString(filename, destString);

   if (!destString.empty())
   {
        std::istringstream str(destString);

        size_t pairCount{};

        str >> pairCount;
        string str2;
        std::getline(str, str2);

        if (pairCount > 0)
        {
            itemNamesSceneNamesMapping.resize(pairCount);

            for(size_t i = 0; i < pairCount; ++i)
            {
                string item;
                std::getline(str, item);
                std::cout << std::noskipws << item << std::endl;
                size_t firstEnd = item.find('=');
                string itemName = item.substr(0, firstEnd);
                string sceneName = item.substr(firstEnd + 1, item.size() - firstEnd);
                itemNamesSceneNamesMapping[i] = std::make_pair(itemName, sceneName);
            }
        }
   }
}

void MainScene::initUIMenuItems()
{


    int x = MainRect->getSize().width/4;
    int y = MainRect->getSize().height/4;

    for(size_t menuIndex = 0; menuIndex < itemNamesSceneNamesMapping.size(); ++menuIndex)
    {
        Scene::addLoadSceneButton(itemNamesSceneNamesMapping[menuIndex].first,
                                  "MenuFont",
                                  itemNamesSceneNamesMapping[menuIndex].second,
                                  x, y, 200, 50);
        y += 96;

    }
}

void MainScene::initBackground()
{
      renderer->setRendererDrawColor(255, 255, 255, 255);

      auto backGround = std::make_shared<UIImage>(renderer);
      backGround->loadTexture("GameData/textures/castle.jpg");
      backGround->setSize(MainRect->getSize());
      MainRect->addChild(backGround);


//    CTexture* backGround = new CTexture();
//    backGround->loadTexture("GameData/textures/castle.jpg");
//    backGround->setRect(0, 0, Renderer::getInstance()->getScreenWidth(), Renderer::getInstance()->getScreenHeight());
//    Scene::addToUIList(backGround);

    //GameModel::getInstance()->loadGameData("GameData/save.bin");
}


