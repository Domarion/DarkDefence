#include "MainScene.h"
#include "../Utility/textfilefunctions.h"
#include <sstream>
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
#include "../GlobalScripts/ResourceManager.h"

MainScene::MainScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
{
}

void MainScene::init(const std::shared_ptr<SceneManager>& sceneManagerPtr)
{
    Scene::init(sceneManagerPtr);

    if (itemNamesSceneNamesMapping.empty())
        loadMenuItems("GameData/MainMenu.txt");

    initBackground();
    initUIMenuItems();
    Scene::addToUIList(MainRect);

}

void MainScene::ConnectMethod(std::function<void (std::string)> handler)
{
    method = handler;
}

void MainScene::loadMenuItems(const std::string& aFilename)
{
    string destString;
    androidText::loadTextFileToString(aFilename, destString);

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
        y = MainRect->getNextVerticalPosition().y;

    }
}

void MainScene::initBackground()
{
    renderer->setRendererDrawColor(255, 255, 255, 255);

    auto backGround = std::make_shared<UIImage>(renderer);
    std::string backGroundName {"MainSceneBackground"};
    backGround->setTexture(ResourceManager::getInstance()->getTexture(backGroundName));
    backGround->setSize(MainRect->getSize());
    MainRect->addChild(backGround);
}


