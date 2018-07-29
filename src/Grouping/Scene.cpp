#include <algorithm>
#include <cassert>

#include "Scene.h"
#include "SceneObject.h"
#include "SceneObjectFabric.h"
#include "../Input/InputDispatcher.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImageButton.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"
#include "../GlobalScripts/GameModel.h"
#include "../GlobalScripts/ResourceManager.h"
#include "Logging/Logger.h"

Scene::Scene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : renderer(aRenderer)
    , mInputDispatcher(aInputDispatcher)
    , MainRect(std::make_shared<ConcreteComposite>())
    , mCamera(Size(aRenderer->getScreenSize().width, aRenderer->getScreenSize().height))
{
    auto emptyLayout = std::make_shared<StubLayout>();
    MainRect->setLayout(emptyLayout);
    MainRect->setScalingFactor(renderer->getScalingFactor());
    MainRect->setSize(renderer->getScreenSize());
    MainRect->setPosition(Position::Zero());
}

void Scene::init()
{
    ObjectWithId::resetObjectIds();
}

void Scene::copyToRender() const
{
    drawAllObjects();
    drawUI();
}

void Scene::startUpdate(double timestep)
{
    for(auto iter = sceneObjects.begin(); iter != sceneObjects.end();)
    {
        if (!(*iter) || !(*iter)->update(timestep))
        {
            removeDrawObject((*iter)->getSprite()->getId());
            iter = sceneObjects.erase(iter);
            continue;
        }

        ++iter;
    }
}

void Scene::addDrawObject(const std::shared_ptr<AnimationSceneSprite>& aObj)
{
    DrawObject drawObj{aObj->getDrawPriority(), aObj->getId()};

    auto insertBeforePositionIterator = drawObjects.end();
    if (!drawObjects.empty())
    {
        insertBeforePositionIterator = std::upper_bound(drawObjects.begin(), drawObjects.end(), drawObj);
    }

    drawObjects.insert(insertBeforePositionIterator, drawObj);
}

void Scene::replaceDrawObject(size_t aOldObjId, const std::shared_ptr<AnimationSceneSprite>& aNewObject)
{
    auto comparator = [aOldObjId](DrawObject aDrawObject)
    {
        return aDrawObject.SceneObjectId == aOldObjId;
    };

    auto iterToReplace = std::find_if(drawObjects.begin(), drawObjects.end(), comparator);

    if (iterToReplace != drawObjects.end())
    {
        *iterToReplace = DrawObject
            {
                aNewObject->getDrawPriority(),
                aNewObject->getId()
            };
    }
}

std::string Scene::SceneChangeTypeHelper(Scene::SceneChange aChangeType)
{
    switch(aChangeType)
    {
    case SceneChange::Prev:
        return "PrevScene";
    case SceneChange::Next:
        return "NextScene";
    case SceneChange::Main:
        return "MainScene";
    case SceneChange::UNDEFINED:
        assert(false && "Undefined changeType");
        break;
    default:
        assert(false && "Unknown changeType");
        break;
    }
    return std::string{};
}

void Scene::removeDrawObject(size_t aObjId)
{
// Чтобы понять: какой элемент удаляется в AnimationSceneSprite добавлен уникальный в рамках сцены Id.
    auto comparator = [&aObjId](DrawObject aDrawObject)
    {
        return aDrawObject.SceneObjectId == aObjId;
    };

    auto drawObjIter = std::find_if(drawObjects.cbegin(), drawObjects.cend(), comparator);
    if (drawObjIter != drawObjects.cend())
    {
        drawObjects.erase(drawObjIter);
    }
}

void Scene::spawnObject(Position aPos, std::shared_ptr<SceneObject> aObj)
{
    if (!aObj)
        return;

    aObj->setParentScene(shared_from_this());


    aObj->init(aPos.x, aPos.y);

    auto handler = std::dynamic_pointer_cast<InputHandler>(aObj);

    if (handler)
    {
        mInputDispatcher->addHandler(handler);
    }
    else
    {
        auto handler2 = aObj->getInputHandler();
        if (handler2)
        {
            mInputDispatcher->addHandler(handler2);
        }
    }

    sceneObjects.push_back(aObj);

    addDrawObject(aObj->getSprite());
}

void Scene::destroyObject(std::shared_ptr<SceneObject> obj)
{
    auto handler = std::dynamic_pointer_cast<InputHandler>(obj);

    if (handler != nullptr)
        mInputDispatcher->removeHandler(handler);

    sceneObjects.remove(obj);

    obj->finalize();
}

void Scene::addToUIList(const std::shared_ptr<IComposite>& item)
{
    if (item == nullptr)
        return;

    listGUI.push_back(item);

    auto handler = std::dynamic_pointer_cast<InputHandler>(item);

    if (handler)
    {
        mInputDispatcher->addHandler(handler);
        return;
    }

    LOG_INFO("UI Item is not an InputHandler");
}

void Scene::removeFromUIList(const std::shared_ptr<IComposite>& item)
{
    if (item == nullptr)
        return;

    listGUI.remove(item);

    auto handler = std::dynamic_pointer_cast<InputHandler>(item);

    if (handler != nullptr)
        mInputDispatcher->removeHandler(handler);
}

void Scene::addStaticSprite(const std::shared_ptr<AnimationSceneSprite>& aItem)
{
    if (aItem == nullptr)
    {
        return;
    }
    staticObjects.emplace_back(aItem);

    addDrawObject(staticObjects.back());
}

void Scene::replaceObject(std::shared_ptr<SceneObject> aObject, std::shared_ptr<SceneObject> aReplacement)
{
    auto comparator = [&aObject](std::shared_ptr<SceneObject>& aRight)
    {
        return aObject->getSprite()->getId() == aRight->getSprite()->getId();
    };

    auto obj = std::find_if(sceneObjects.begin(), sceneObjects.end(), comparator);
    if (obj != sceneObjects.cend())
    {
        *obj = aReplacement;

        int x = aObject->getPosition().x;
        int y = aObject->getPosition().y;

        (*obj)->setParentScene(shared_from_this());


        (*obj)->init(x, y);
        (*obj)->getSprite()->setDrawPriority(aObject->getSprite()->getDrawPriority());

        auto handler = std::dynamic_pointer_cast<InputHandler>(*obj);

        if (handler != nullptr)
            mInputDispatcher->addHandler(handler);


        auto handler1 = std::dynamic_pointer_cast<InputHandler>(aObject);

        if (handler1 != nullptr)
            mInputDispatcher->removeHandler(handler1);

        aObject->finalize();

        replaceDrawObject(aObject->getSprite()->getId(), (*obj)->getSprite());
    }
}

void Scene::bindChangeScene(const ChangeSceneFunction& aChangeSceneCallback)
{
    mChangeSceneCallback = aChangeSceneCallback;
}

void Scene::askForChangeScene(const std::string& aName)
{
    if (!mChangeSceneCallback)
    {
        LOG_ERROR("Scene:: No binded change scene callback");
        assert(mChangeSceneCallback);
        throw std::logic_error("Scene:: No binded change scene callback");
    }

    mChangeSceneCallback(aName);
}

void Scene::softClear()
{
    clearUIList();
}

void Scene::addAsInputHandler(std::shared_ptr<InputHandler> item)
{
    if (item != nullptr)
        mInputDispatcher->addHandler(item);
}

void Scene::clearUIList()
{
    listGUI.clear();
    MainRect->clearChildren();
    mInputDispatcher->clearHandlers();
}

std::shared_ptr<SceneObject> Scene::findObjectByTag(const std::string& aTag)
{
    for(const auto& sceneObjectPtr : sceneObjects)
    {
        if (sceneObjectPtr->getTag() == aTag)
        {
            return sceneObjectPtr;
        }
    }

    return nullptr;
}

Scene::SceneObjectList Scene::findObjectsByTag(const std::string& aTag)
{
    auto filteredList = std::make_unique<std::list<std::shared_ptr<SceneObject>>>();

    for(const auto& sceneObjectPtr : sceneObjects)
    {
        if (sceneObjectPtr->getTag() == aTag)
        {
            filteredList->push_back(sceneObjectPtr);
        }
    }

    if (filteredList->empty())
    {
        return nullptr;
    }

    return filteredList;
}

std::shared_ptr<SceneObject> Scene::findObjectWithPos(int x, int y)
{
    SDL_Point point = {x, y};
    for(auto& sceneobject : sceneObjects)
    {
        if (sceneobject != nullptr)
        {
            const SDL_Rect some = {sceneobject->getSprite()->getPosition().x
                                   , sceneobject->getSprite()->getPosition().y
                                   , sceneobject->getSprite()->getSize().width
                                   , sceneobject->getSprite()->getSize().height
                                  };

            if (SDL_PointInRect(&point, &some))
                return sceneobject;
        }
    }
    return nullptr;
}

Scene::SceneObjectList Scene::findObjectsWithPos(int x, int y)
{
    SDL_Point point = {x, y};
    auto filteredList =  std::make_unique<std::list<std::shared_ptr<SceneObject>>>();

    for(auto& sceneobject : sceneObjects)
    {
        if (sceneobject != nullptr)
        {
            const SDL_Rect some = {sceneobject->getSprite()->getPosition().x
                                   , sceneobject->getSprite()->getPosition().y
                                   , sceneobject->getSprite()->getSize().width
                                   , sceneobject->getSprite()->getSize().height
                                  };

            if (SDL_PointInRect(&point, &some))
                filteredList->push_back(sceneobject);
        }
    }

    if (filteredList->empty())
    {
        return nullptr;
    }

    return filteredList;

}

Scene::SceneObjectList Scene::findObjectsInRadius(Position aCenter, size_t aRadius)
{
    auto filteredList =  std::make_unique<std::list<std::shared_ptr<SceneObject>>>();
    size_t rSqr = aRadius * aRadius;

    for(auto& sceneobject : sceneObjects)
    {
        if (sceneobject != nullptr)
        {
            Position realPosition = sceneobject->getSprite()->getRealPosition();

            size_t xSqr = static_cast<size_t>((realPosition.x - aCenter.x) * (realPosition.x - aCenter.x));
            size_t ySqr = static_cast<size_t>((realPosition.y - aCenter.y) * (realPosition.y - aCenter.y));

            if (xSqr + ySqr <= rSqr)
            {
                filteredList->push_back(sceneobject);
            }
        }
    }

    if (filteredList->empty())
    {
        return nullptr;
    }

    return filteredList;
}

void Scene::onGameQuit()
{
    GameModel::getInstance()->saveGameData("GameData/save.bin");
}

std::shared_ptr<ConcreteComposite>& Scene::getMainRect()
{
    return MainRect;
}

//TODO Найти наилучшее место для метода
void Scene::onlyTestMoveCamera(Position aDeltaPosition)
{
    #ifdef __ANDROID__
        const int multiplier = 50;
    #else
        const int multiplier = 20;
    #endif

    aDeltaPosition *= multiplier;

    Position pos = mCamera.getWorldPosition() - aDeltaPosition;

    mCamera.setWorldPosition(pos);
}

const Camera2D& Scene::getCamera() const
{
    return mCamera;
}

std::shared_ptr<RenderingSystem>& Scene::getRenderer()
{
    return renderer;
}

void Scene::addLoadSceneButton(const std::string& aSceneName, Position aPos, SceneChange aChangeType)
{
    std::string changeSceneButtonView = SceneChangeTypeHelper(aChangeType);

    auto uiButton = std::make_shared<UIImageButton>(renderer);
    assert(ResourceManager::getInstance()->hasTexture(changeSceneButtonView) && "NextScene texture null");
    auto& texture = ResourceManager::getInstance()->getTexture(changeSceneButtonView);
    uiButton->setTexture(texture);
    uiButton->setPosition(aPos);

    uiButton->ConnectMethod(std::bind(mChangeSceneCallback, aSceneName));

    MainRect->addChild(uiButton);
}


void Scene::addLoadSceneButton(
    const std::string& aButtonName, const std::string& aFontName, const std::string& aSceneName, int posX, int posY)
{
    auto textButton = std::make_shared<UITextButton>(aButtonName, FontManager::getInstance()->getFontByKind2(aFontName),
                      renderer);

    textButton->setPosition(Position(posX, posY));

    textButton->ConnectMethod(std::bind(mChangeSceneCallback, aSceneName));

    MainRect->addChild(textButton);
}

void Scene::addSceneButton(const std::string& aButtonName, const std::string& aFontName, int posX, int posY, int /*width*/, int /*height*/,
    std::function<void(std::string)> handler, const std::string& aMsg)
{
    auto textButton = std::make_shared<UITextButton>(aButtonName, FontManager::getInstance()->getFontByKind2(aFontName),
                      renderer);
    textButton->setPosition(Position(posX, posY));
    textButton->setMessage(aMsg);
    textButton->ConnectMethod(handler);

    MainRect->addChild(textButton);
}

void Scene::drawAllObjects() const
{
    auto drawSprite = [this](DrawObject aDrawObject)
    {
        auto comparator = [&aDrawObject](const std::shared_ptr<SceneObject>& aObject)
        {
            assert(aObject && aObject->getSprite());
            return aObject->getSprite()->getId() == aDrawObject.SceneObjectId;
        };

        auto it = std::find_if(sceneObjects.begin(), sceneObjects.end(), comparator);

        if (it == sceneObjects.end())
        {
            auto comparator2 = [&aDrawObject](const std::shared_ptr<AnimationSceneSprite>& aObject)
            {
                assert(aObject);
                return aObject->getId() == aDrawObject.SceneObjectId;
            };
            auto iterStatic = std::find_if(staticObjects.begin(), staticObjects.end(), comparator2);

            if (iterStatic != staticObjects.end())
            {
                Size objSize = (*iterStatic)->getSize();
                Position objPosition = (*iterStatic)->getRealPosition();
                if (mCamera.hasIntersection(objPosition, objSize))
                {
                    (*iterStatic)->drawAtPosition(mCamera.worldToCameraPosition(objPosition));
                }
            }
            return;
        }


        auto& sprite = (*it)->getSprite();
        Size objSize = sprite->getSize();
        Position objPosition = (*it)->getPosition();
        if (mCamera.hasIntersection(objPosition, objSize))
        {
            sprite->drawAtPosition(mCamera.worldToCameraPosition(objPosition));
        }
    };

    std::for_each(drawObjects.begin(), drawObjects.end(), drawSprite);
}

void Scene::drawUI() const
{
    for(const auto& guiItem : listGUI)
    {
        if (guiItem != nullptr)
        {
            guiItem->draw();
        }
    }
}

void Scene::clear()
{
    if (!listGUI.empty())
    {
        softClear();
    }

    sceneObjects.clear();
    staticObjects.clear();
    drawObjects.clear();

    mCamera.resetWorldPosition();
}

bool operator<(const Scene::DrawObject& aLeft, const Scene::DrawObject& aRight)
{
    return aLeft.DrawPriority < aRight.DrawPriority;
}
