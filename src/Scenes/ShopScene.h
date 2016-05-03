/*
 * ShopScene.h
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"
#include "../GraphicsSystem/UI/TextButton.h"
#include "../ItemSystem/ShopController.h"
class ShopScene: public Scene
{
public:
	ShopScene();
	virtual ~ShopScene();
    virtual void initScene(SceneManager* sceneManagerPtr) override;
	virtual void finalizeScene() override;
	virtual void loadScene() override;
	virtual void unloadScene() override;

	virtual void startUpdate(double timestep) override;

private:
	ScrollList scroll;
	ShopController shopController;
	TextButton button;
};
