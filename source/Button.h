#ifndef BUTTON_H
#define BUTTON_H

#include "RenderComponentInterface.h"
#include "SceneState.h"
#include "BaseScene.h"

class Button
{
public:
	Button(BoundingBox p_boundingBox, BaseScene* p_scene, void (BaseScene::*p_function)(SceneState::State, GameType::Type), SceneState::State p_sceneState, GameType::Type p_gameType, RenderComponentInterface* p_renderComponentInterface, ButtonTexture p_buttonTexture);
	~Button();
	
	void Render();
	bool CheckIfInside(int p_X, int p_Y);
	void ExecuteCommand();

private:
	BoundingBox m_boundingBox;
	BaseScene* m_scene;
	void (BaseScene::*m_function)(SceneState::State, GameType::Type);
	SceneState::State m_sceneState;
	GameType::Type m_gameType;
	RenderComponentInterface* m_renderComponentInterface;
	ButtonTexture m_buttonTexture;

};

#endif