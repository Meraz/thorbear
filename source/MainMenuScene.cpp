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

//	 m_button.push_back(new Button(BoundingBox2D(100, 100, 100, 100), this, &MainMenuScene::ChangeCurrentState, SceneState::GAME_MODE_MENU, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON1));
//	m_button.push_back(new Button(BoundingBox2D(100, 75,  100, 100), this, &MainMenuScene::ChangeCurrentState, SceneState::HIGHSCORE, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON2));
	m_button.push_back(new Button(BoundingBox(0.0f, 0.0f, 50.0f, 50.0f, 50.0f), this, &MainMenuScene::ChangeCurrentState, SceneState::EXIT, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON3));
	a = 0; // Test code TODO : REMOVE
}

void MainMenuScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	//a++;									// Test code TODO : REMOVE
	if(a > 300)								// Test code TODO : REMOVE
		m_button.at(0)->ExecuteCommand();	// Test code TODO : REMOVE

	if(p_lMouseClicked)
		CheckButton(p_mousePositionX, p_mousePositionY);
}

void MainMenuScene::Render()
{
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
