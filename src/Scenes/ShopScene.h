/*
 * ShopScene.h
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"
#include "../ItemSystem/ShopController.h"
#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"

//#include "../GraphicsSystem/UI/Label.h"

class ShopScene: public Scene
{
public:
    ShopScene(std::shared_ptr<RenderingSystem> &aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);
	virtual ~ShopScene();
    virtual void init(std::shared_ptr<SceneManager> sceneManagerPtr) override;
    virtual void clear() override;

	virtual void startUpdate(double timestep) override;

private:

    void initControlButton();
    void initBackGroundUI();
    void initShopItemsUI();

    std::shared_ptr<UILabel> goldCoinsLabel;

    std::shared_ptr<ShopController> shopController;

};
