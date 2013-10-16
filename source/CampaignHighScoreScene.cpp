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
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = SceneState::CAMPAIGNHIGHSCORE;
	m_highScore = new Highscore(m_renderComponentInterface);
	m_highScore->Init(m_score, true);

	m_newAdditionToHighscore = m_highScore->GetnewAdditionToHighscorePointer();
	if(*m_newAdditionToHighscore)
		m_button.push_back(new Button(BoundingBox(350.0f, 300.0f, 70, 30, 5),	m_highScore, &Highscore::SaveFile, p_renderComponentInterface, SAVE));

	m_button.push_back(new Button(BoundingBox(10.0f, 30.0f, 70, 30, 1),this, &CampaignHighscoreScene::ChangeCurrentState, SceneState::MAIN_MENU, 0, p_renderComponentInterface, RETURN));
}
void CampaignHighscoreScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	if(*m_newAdditionToHighscore)
		m_highScore->AddCharToName(m_renderComponentInterface->GetKey());
	if(p_lMouseClicked == true && m_previousMouseState == false)
		CheckButton(p_mousePositionX, p_mousePositionY);
	m_previousMouseState = p_lMouseClicked;
}

void CampaignHighscoreScene::Render()
{
	m_renderComponentInterface->RenderBackground(HS);
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
