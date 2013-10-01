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

	m_button.push_back(new Button(BoundingBox2D(100, 100, 50, 50), this, &MainMenuScene::ChangeCurrentState, SceneState::GAME_MODE_MENU, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON1));
	m_button.push_back(new Button(BoundingBox2D(100, 100, 50, 50), this, &MainMenuScene::ChangeCurrentState, SceneState::HIGHSCORE, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON2));
	m_button.push_back(new Button(BoundingBox2D(100, 100, 50, 50), this, &MainMenuScene::ChangeCurrentState, SceneState::EXIT, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON3));
	a = 0;
}

void MainMenuScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	a++;
	if(a > 300)
		m_button.at(0)->ExecuteCommand();
	for(int i = 0; i < m_button.size(); i++)
	{
		if(m_button.at(i)->CheckIfInside(p_mousePositionX, p_mousePositionY))
			m_button.at(i)->ExecuteCommand();
	}
}

void MainMenuScene::Render()
{

}