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
	m_sceneState = SceneState::GAME_MODE_MENU;

	m_button.push_back(new Button(BoundingBox(150.0f, 150.0f, 50.0f, 50.0f, 50.0f), this, &GameModeMenuScene::ChangeCurrentState, SceneState::GAME, START_CAMPAIGN, p_renderComponentInterface, BUTTON3));
	m_button.push_back(new Button(BoundingBox(350.0f, 150.0f, 50.0f, 50.0f, 50.0f), this, &GameModeMenuScene::ChangeCurrentState, SceneState::GAME,	START_SURVIVAL, p_renderComponentInterface, BUTTON3));
}

void GameModeMenuScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	if(p_lMouseClicked == true && m_previousMouseState == false)
		CheckButton(p_mousePositionX, p_mousePositionY);
}

void GameModeMenuScene::Render()
{
	for(int i = 0; i < m_button.size(); i++)
		m_button.at(i)->Render();
}

void GameModeMenuScene::CheckButton(int p_mousePositionX, int p_mousePositionY)
{
	for(int i = 0; i < m_button.size(); i++)
	{
		if(m_button.at(i)->CheckIfInside(p_mousePositionX, p_mousePositionY))
			m_button.at(i)->ExecuteCommand();
	}
}