/*
 * InventoryScene.h
 *
 *  Created on: 18 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"
#include "../GraphicsSystem/UI/TextButton.h"

#include "../ItemSystem/InventoryController.h"
#include "../ItemSystem/HeroInventoryController.h"
class InventoryScene: public Scene
{
public:
	InventoryScene();
	virtual ~InventoryScene();
    virtual void initScene(SceneManager* sceneManagerPtr) override;
	virtual void finalizeScene() override;

	virtual void startUpdate(double timestep) override;

private:
	ScrollList scroll;
    SlotContainer heroFigure;
	InventoryController inventoryController;
    HeroInventoryController heroController;
	TextButton button;
   // std::shared_ptr<CFont> arialFont;

};

