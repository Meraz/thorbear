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
	a = 0;
}

void HighScoreScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	if(++a > 500)
		m_sceneState = GAME;	// TODO : Remove this. Test code
}

void HighScoreScene::Render()
{

}