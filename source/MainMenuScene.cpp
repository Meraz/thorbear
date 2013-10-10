#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
	m_button = std::vector<Button*>();
}

MainMenuScene::~MainMenuScene()
{
	// TODO : Remove everything in vector
}

void MainMenuScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = SceneState::MAIN_MENU;
	
	m_button.push_back(new Button(BoundingBox(250.0f, 225.0f, 70.0f, 30.0f, 50.0f), this, &MainMenuScene::ChangeCurrentState, SceneState::GAME_MODE_MENU,	  0, p_renderComponentInterface, START));
	m_button.push_back(new Button(BoundingBox(250.0f, 150.0f, 70.0f, 30.0f, 50.0f), this, &MainMenuScene::ChangeCurrentState, SceneState::SURVIVALHIGHSCORE, -1, p_renderComponentInterface, SURVIVALHS));
	m_button.push_back(new Button(BoundingBox(250.0f, 75.0f, 70.0f, 30.0f, 50.0f), this, &MainMenuScene::ChangeCurrentState, SceneState::CAMPAIGNHIGHSCORE, -1, p_renderComponentInterface, CAMPAIGNHS));
	m_button.push_back(new Button(BoundingBox(250.0f, 0.0f, 70.0f, 30.0f, 50.0f),	this, &MainMenuScene::ChangeCurrentState, SceneState::EXIT,				  0, p_renderComponentInterface, EXIT));

}

void MainMenuScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	if(p_lMouseClicked == true && m_previousMouseState == false)
		CheckButton(p_mousePositionX, p_mousePositionY);
		m_previousMouseState = p_lMouseClicked;
}

void MainMenuScene::Render()
{
	m_renderComponentInterface->RenderBackground(MAINMENU);
	for(int i = 0; i < m_button.size(); i++)
		m_button.at(i)->Render();
}

void MainMenuScene::CheckButton(int p_mousePositionX, int p_mousePositionY)
{
	for(int i = 0; i < m_button.size(); i++)
	{
		if(m_button.at(i)->CheckIfInside(p_mousePositionX, p_mousePositionY))
		{
			//RenderParticleEffect(p_mousePositionX, p_mousePositionY);	//add
			m_button.at(i)->ExecuteCommand();
		}
	}
}