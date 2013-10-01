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

	m_button.push_back(new Button(BoundingBox2D(100, 100, 50, 50), this, &HighScoreScene::ChangeCurrentState, SceneState::GAME_MODE_MENU, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON2));
	m_button.push_back(new Button(BoundingBox2D(100, 100, 50, 50), this, &HighScoreScene::ChangeCurrentState, SceneState::HIGHSCORE, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON2));
	m_button.push_back(new Button(BoundingBox2D(100, 100, 50, 50), this, &HighScoreScene::ChangeCurrentState, SceneState::EXIT, GameType::NOT_SPECIFIED, p_renderComponentInterface, BUTTON2));
}

void HighScoreScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
}

void HighScoreScene::Render()
{

}