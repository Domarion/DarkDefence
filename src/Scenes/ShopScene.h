/*
 * ShopScene.h
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"
#include "../ItemSystem/ShopController.h"
#include "../GraphicsSystem/UI/Label.h"

class ShopScene: public Scene
{
public:
	ShopScene();
	virtual ~ShopScene();
    virtual void init(SceneManager* sceneManagerPtr) override;
    virtual void clear() override;

	virtual void startUpdate(double timestep) override;

private:

    void initControlButton();
    void initBackGroundUI();
    void initShopItemsUI();
    Label *goldCoins;

    ShopController* shopController;

};
