#ifndef BUTTON_H
#define BUTTON_H

#include "RenderComponentInterface.h"
#include "SceneState.h"
#include "BaseScene.h"
#include "Highscore.h"
#include "MemoryMacro.h"

class Button
{
public:
	Button(BoundingBox p_boundingBox, BaseScene* p_scene, void (BaseScene::*p_function)(SceneState::State, int), SceneState::State p_sceneState, int p_menuFlag, RenderComponentInterface* p_renderComponentInterface, ButtonTexture p_buttonTexture);
	
	// Used for Higscore function "NextChar(int)" and "PrevChar(int)"
	Button(BoundingBox p_boundingBox, Highscore* p_highscore, void (Highscore::*p_function)(int), int p_buttonId, RenderComponentInterface* p_renderComponentInterface, ButtonTexture p_buttonTexture);
	
	// Used for Higscore function "SaveFile()"
	Button(BoundingBox p_boundingBox, Highscore* p_highscore, void (Highscore::*p_function)(), RenderComponentInterface* p_renderComponentInterface, ButtonTexture p_buttonTexture);
	
	~Button();
	

	void Update();

	void Render();
	bool CheckIfInside(int p_X, int p_Y);
	void ExecuteCommand();

private:
	BoundingBox m_boundingBox;
	int m_constructorId;
	bool* m_clickable;

	// Change menuscenes
	BaseScene* m_scene;
	void (BaseScene::*m_function)(SceneState::State, int);
	SceneState::State m_sceneState;
	int m_menuFlag;

	// Update in Highscorescene
	Highscore* m_highscore;
	void (Highscore::*m_functionCharChange)(int);
	void (Highscore::*m_functionSave)();
	int m_buttonId;


	RenderComponentInterface* m_renderComponentInterface;
	ButtonTexture m_buttonTexture;

};

#endif