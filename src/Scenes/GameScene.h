/*
 * GameScene.h
 *
 *  Created on: 4 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"
#include "../Mob/MobSpawner.h"
#include "../Grouping/SceneObjectFabric.h"
#include "../GraphicsSystem/Sprite.h"
#include "../GraphicsSystem/UI/GroupBox.h"
#include "../GraphicsSystem/UI/Label.h"
#include "../GraphicsSystem/UI/TextButton.h"
#include "../GraphicsSystem/UI/ProgressBar.h"
#include "../GraphicsSystem/Camera.h"
#include "../Mob/Gates.h"
#include "../Mob/TowerFabric.hpp"
class GameScene: public Scene
{
public:
	GameScene();
	virtual ~GameScene();
	virtual void initScene(SDL_Renderer* renderer, SceneManager* sceneManagerPtr) override;
	virtual void finalizeScene() override;
	virtual void loadScene() override;
	virtual void unloadScene() override;
	virtual void startUpdate(double timestep) override;
    virtual void copyToRender(SDL_Renderer* renderer) const override;

private:
    SceneObjectFabric objectFabric;
    SceneObject* Terrain;
	//TextButton* AbilityButtons;
    GroupBox topPanel;
    vector<Label*> resourceLabels;
    ProgressBar gatesHealthBar;
    TowerFabric towerFabric;
	MobSpawner monsterSpawner;
	Gates gates;
	SDL_Rect* worldRect;
	Camera* mainCamera;

};
