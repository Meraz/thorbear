#include "HighScoreScene.h"


HighScoreScene::HighScoreScene(void)
{
}


HighScoreScene::~HighScoreScene(void)
{
}

void HighScoreScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = HIGHSCORE;
}

void HighScoreScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
}

void HighScoreScene::Render()
{

}