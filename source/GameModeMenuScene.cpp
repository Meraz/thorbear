#include "GameModeMenuScene.h"


GameModeMenuScene::GameModeMenuScene()
{
}


GameModeMenuScene::~GameModeMenuScene()
{
}

void GameModeMenuScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = SceneState::HIGHSCORE;
}

void GameModeMenuScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
}

void GameModeMenuScene::Render()
{

}