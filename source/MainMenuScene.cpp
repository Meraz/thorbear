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
	
	m_button.push_back(new Button(BoundingBox(250.0f, 350.0f, 50.0f, 50.0f, 50.0f), this, &MainMenuScene::ChangeCurrentState, SceneState::GAME_MODE_MENU,	  0, p_renderComponentInterface, BUTTON3));
	m_button.push_back(new Button(BoundingBox(250.0f, 250.0f, 50.0f, 50.0f, 50.0f), this, &MainMenuScene::ChangeCurrentState, SceneState::SURVIVALHIGHSCORE, -1, p_renderComponentInterface, BUTTON3));
	m_button.push_back(new Button(BoundingBox(250.0f, 150.0f, 50.0f, 50.0f, 50.0f), this, &MainMenuScene::ChangeCurrentState, SceneState::CAMPAIGNHIGHSCORE, -1, p_renderComponentInterface, BUTTON3));
	m_button.push_back(new Button(BoundingBox(250.0f, 50.0f, 50.0f, 50.0f, 50.0f),	this, &MainMenuScene::ChangeCurrentState, SceneState::EXIT,				  0, p_renderComponentInterface, BUTTON3));
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
			m_button.at(i)->ExecuteCommand();
	}
}