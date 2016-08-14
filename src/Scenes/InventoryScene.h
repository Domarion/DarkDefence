/*
 * InventoryScene.h
 *
 *  Created on: 18 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"
#include "../ItemSystem/InventoryController.h"
#include "../ItemSystem/HeroInventoryController.h"

class InventoryScene: public Scene
{
public:
	InventoryScene();
	virtual ~InventoryScene();
    virtual void init(SceneManager* sceneManagerPtr) override;
    virtual void clear() override;

private:
    void initControlButton();
    void initHeroView();
    void initInventoryView();

    InventoryController* inventoryController;
    HeroInventoryController* heroController;
};

