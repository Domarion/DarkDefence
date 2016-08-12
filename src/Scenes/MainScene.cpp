/*
 * MainScene.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "MainScene.h"
#include "../GraphicsSystem/UI/Label.h"
#include <iostream>
#include "../Utility/textfilefunctions.h"
#include <sstream>

MainScene::MainScene()

{
	// TODO Auto-generated constructor stub
}

MainScene::~MainScene()
{


}


void MainScene::finalizeScene()
{
}




void MainScene::initScene(SceneManager* sceneManagerPtr)
{
    Renderer::getInstance()->setRendererDrawColor(255, 255, 255);

	if (wasInited == false)
	{
        Scene::initScene(sceneManagerPtr);
        backGround.loadTexture("GameData/textures/castle.jpg");
        backGround.setRect(0, 0, Renderer::getInstance()->getScreenWidth(), Renderer::getInstance()->getScreenHeight());
        Scene::addToUIList(&backGround);
        wasInited = true;
    }
        shared_ptr<CFont> FontManagerFont = FontManager::getInstance()->getFontByKind("MenuFont");
        if (FontManagerFont.get() == nullptr)
            std::cout << "FontManagerFont is null MenuFont" << std::endl;

        int x = Renderer::getInstance()->getScreenWidth()/4;
        int y = Renderer::getInstance()->getScreenHeight()/4;

        loadMenuItems("GameData/MainMenu.txt");
        menuItems.resize(itemNamesSceneNamesMapping.size());
        for(size_t menuIndex = 0; menuIndex < menuItems.size(); ++menuIndex)
        {
            menuItems[menuIndex].setFont(FontManagerFont);
            menuItems[menuIndex].setRect(x, y, 200, 50);
            menuItems[menuIndex].setText(itemNamesSceneNamesMapping[menuIndex].first);
            menuItems[menuIndex].ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, itemNamesSceneNamesMapping[menuIndex].second));
            y += 96;
            Scene::addToUIList(&menuItems[menuIndex]);
        }

}

void MainScene::startUpdate(double timestep)
{
    Scene::startUpdate(timestep);

}

void MainScene::loadMenuItems(string filename)
{
   string destString;
   androidText::loadTextFileToString(filename, destString);

   if (!destString.empty())
   {
        std::istringstream str(destString);

        size_t n  = 0;

        str >> n;
        string str2;
        std::getline(str, str2);
        if (n > 0)
        {
            itemNamesSceneNamesMapping.resize(n);

            for(size_t i = 0; i < n; ++i)
            {
                string item;
               // str >> item;

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



