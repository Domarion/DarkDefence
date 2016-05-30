/*
 * MainScene.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"
#include "../GraphicsSystem/UI/Label.h"
#include "../GraphicsSystem/UI/TextButton.h"
#include "../GraphicsSystem/UI/ProgressBar.h"
#include <memory>

class MainScene: public Scene
{
public:
	MainScene();
	virtual ~MainScene();
    virtual void initScene(SceneManager* sceneManagerPtr) override;
	virtual void finalizeScene() override;


	virtual void startUpdate(double timestep) override;


private:
	//Label labelText;
	TextButton button, button2, button3;
    std::shared_ptr<CFont> arialFont;
    CTexture backGround;
	//ProgressBar bar;
};


