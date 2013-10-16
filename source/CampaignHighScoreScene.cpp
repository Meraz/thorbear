#include "CampaignHighScoreScene.h"


CampaignHighscoreScene::CampaignHighscoreScene(int p_score)
{
	m_button = std::vector<Button*>(); 
	
	m_score = p_score;
}


CampaignHighscoreScene::~CampaignHighscoreScene(void)
{
	for(unsigned int i = 0; i < m_button.size(); i++)
		delete m_button[i];
}

void CampaignHighscoreScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	m_highScore = new Highscore(p_renderComponentInterface);
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = SceneState::CAMPAIGNHIGHSCORE;

	m_highScore->Init(m_score, true);

	bool l_newAdditionToHighscore = m_highScore->GetnewAdditionToHighscore();
//	if(l_newAdditionToHighscore)
	{
		m_button.push_back(new Button(BoundingBox(60.0f, 350.0f, 30, 30, 1),	m_highScore, &Highscore::NextChar, 0, p_renderComponentInterface, ARROWUP));
		m_button.push_back(new Button(BoundingBox(60.0f, 275.0f, 30, 30, 1),	m_highScore, &Highscore::PrevChar, 0, p_renderComponentInterface, ARROWDOWN));

		m_button.push_back(new Button(BoundingBox(160.0f, 350.0f, 30, 30, 1),	m_highScore, &Highscore::NextChar, 1, p_renderComponentInterface, ARROWUP));
		m_button.push_back(new Button(BoundingBox(160.0f, 275.0f, 30, 30, 1),	m_highScore, &Highscore::PrevChar, 1, p_renderComponentInterface, ARROWDOWN));

		m_button.push_back(new Button(BoundingBox(260.0f, 350.0f, 30, 30, 1),	m_highScore, &Highscore::NextChar, 2, p_renderComponentInterface, ARROWUP));
		m_button.push_back(new Button(BoundingBox(260.0f, 275.0f, 30, 30, 1),	m_highScore, &Highscore::PrevChar, 2, p_renderComponentInterface, ARROWDOWN));

		m_button.push_back(new Button(BoundingBox(350.0f, 300.0f, 70, 30, 5),	m_highScore, &Highscore::SaveFile, p_renderComponentInterface, SAVE));
	}
	m_button.push_back(new Button(BoundingBox(10.0f, 30.0f, 70, 30, 1),this, &CampaignHighscoreScene::ChangeCurrentState, SceneState::MAIN_MENU, 0, p_renderComponentInterface, RETURN));
}
void CampaignHighscoreScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	if(p_lMouseClicked == true && m_previousMouseState == false)
		CheckButton(p_mousePositionX, p_mousePositionY);
	m_previousMouseState = p_lMouseClicked;
}

void CampaignHighscoreScene::Render()
{
	for(unsigned int i = 0; i < m_button.size(); i++)
		m_button.at(i)->Render();
	m_highScore->Render();
}

void CampaignHighscoreScene::CheckButton(int p_mousePositionX, int p_mousePositionY)
{
	for(unsigned int i = 0; i < m_button.size(); i++)
	{
		if(m_button.at(i)->CheckIfInside(p_mousePositionX, p_mousePositionY))
			m_button.at(i)->ExecuteCommand();
	}
}
