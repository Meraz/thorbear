#include "HighScoreScene.h"


HighScoreScene::HighScoreScene(void)
{
	m_button = std::vector<Button*>(); 
}


HighScoreScene::~HighScoreScene(void)
{
	// TODO : Remove everything in vector
}

void HighScoreScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = SceneState::HIGHSCORE;

	m_button.push_back(new Button(BoundingBox2D(100, 100, 50, 50), this, &HighScoreScene::ChangeCurrentState, SceneState::GAME_MODE_MENU,	GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON2));
	m_button.push_back(new Button(BoundingBox2D(100, 75,  50, 50), this, &HighScoreScene::ChangeCurrentState, SceneState::HIGHSCORE,		GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON2));
	m_button.push_back(new Button(BoundingBox2D(100, 50,  50, 50), this, &HighScoreScene::ChangeCurrentState, SceneState::EXIT,				GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON2));
}

void HighScoreScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	if(p_lMouseClicked)
		CheckButton(p_mousePositionX, p_mousePositionY);
}

void HighScoreScene::Render()
{
	for(int i = 0; i < m_button.size(); i++)
		m_button.at(i)->Render();
}

void HighScoreScene::CheckButton(int p_mousePositionX, int p_mousePositionY)
{
	// TODO : ADD CLICK EVENT
	for(int i = 0; i < m_button.size(); i++)
	{
		if(m_button.at(i)->CheckIfInside(p_mousePositionX, p_mousePositionY))
			m_button.at(i)->ExecuteCommand();
	}
}