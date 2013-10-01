#include "GameModeMenuScene.h"


GameModeMenuScene::GameModeMenuScene()
{
	m_button = std::vector<Button*>(); 
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
	if(p_lMouseClicked)
		CheckButton(p_mousePositionX, p_mousePositionY);
}

void GameModeMenuScene::Render()
{
	for(int i = 0; i < m_button.size(); i++)
		m_button.at(i)->Render();
}

void GameModeMenuScene::CheckButton(int p_mousePositionX, int p_mousePositionY)
{
	// TODO : ADD CLICK EVENT
	for(int i = 0; i < m_button.size(); i++)
	{
		if(m_button.at(i)->CheckIfInside(p_mousePositionX, p_mousePositionY))
			m_button.at(i)->ExecuteCommand();
	}
}