#include "SurvivalHighscoreScene.h"


SurvivalHighscoreScene::SurvivalHighscoreScene(int p_score)
{
	m_button = std::vector<Button*>(); 
	m_score = p_score;
	m_previousMouseState = false;
}

SurvivalHighscoreScene::~SurvivalHighscoreScene()
{
	for(unsigned int i = 0; i < m_button.size(); i++)
		delete m_button[i];
	delete m_highScore;
}

void SurvivalHighscoreScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = SceneState::SURVIVALHIGHSCORE;
	m_highScore = new Highscore(m_renderComponentInterface);
	m_highScore->Init(m_score, false);

	bool l_newAdditionToHighscore = m_highScore->GetnewAdditionToHighscore();
	//if(l_newAdditionToHighscore)
	{
		m_button.push_back(new Button(BoundingBox(60.0f, 350.0f, 30, 30, 1),	m_highScore, &Highscore::NextChar, 0, p_renderComponentInterface, ARROWUP));
		m_button.push_back(new Button(BoundingBox(60.0f, 275.0f, 30, 30, 1),	m_highScore, &Highscore::PrevChar, 0, p_renderComponentInterface, ARROWDOWN));

		m_button.push_back(new Button(BoundingBox(160.0f, 350.0f, 30, 30, 1),	m_highScore, &Highscore::NextChar, 1, p_renderComponentInterface, ARROWUP));
		m_button.push_back(new Button(BoundingBox(160.0f, 275.0f, 30, 30, 1),	m_highScore, &Highscore::PrevChar, 1, p_renderComponentInterface, ARROWDOWN));

		m_button.push_back(new Button(BoundingBox(260.0f, 350.0f, 30, 30, 1),	m_highScore, &Highscore::NextChar, 2, p_renderComponentInterface, ARROWUP));
		m_button.push_back(new Button(BoundingBox(260.0f, 275.0f, 30, 30, 1),	m_highScore, &Highscore::PrevChar, 2, p_renderComponentInterface, ARROWDOWN));
		
		m_button.push_back(new Button(BoundingBox(350.0f, 300.0f, 70, 30, 5),	m_highScore, &Highscore::SaveFile, p_renderComponentInterface, SAVE));
	}
	m_button.push_back(new Button(BoundingBox(10.0f, 30.0f, 70, 30, 1),this, &SurvivalHighscoreScene::ChangeCurrentState, SceneState::MAIN_MENU, 0, p_renderComponentInterface, RETURN));
}

void SurvivalHighscoreScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	if(p_lMouseClicked == true && m_previousMouseState == false)
		CheckButton(p_mousePositionX, p_mousePositionY);
	m_previousMouseState = p_lMouseClicked;
}

void SurvivalHighscoreScene::Render()
{
	for(unsigned int i = 0; i < m_button.size(); i++)
		m_button.at(i)->Render();
	m_highScore->Render();
}

void SurvivalHighscoreScene::CheckButton(int p_mousePositionX, int p_mousePositionY)
{
	for(unsigned int i = 0; i < m_button.size(); i++)
	{
		if(m_button.at(i)->CheckIfInside(p_mousePositionX, p_mousePositionY))
			m_button.at(i)->ExecuteCommand();
	}
}