#include "SurvivalHighscoreScene.h"


SurvivalHighscoreScene::SurvivalHighscoreScene(int p_score)
{
	m_button = std::vector<Button*>(); 
	m_highScore = new Highscore();
	m_score = p_score;
}

SurvivalHighscoreScene::~SurvivalHighscoreScene()
{
	// TODO : Remove everything in vector
	delete m_highScore;
}

void SurvivalHighscoreScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = SceneState::SURVIVALHIGHSCORE;
	
	m_highScore->Init(m_score, false);

	bool l_newAdditionToHighscore = m_highScore->GetnewAdditionToHighscore();
	if(l_newAdditionToHighscore)
	{
		m_button.push_back(new Button(BoundingBox(50.0f, 350.0f, 50.0f, 50.0f, 50.0f),	m_highScore, &Highscore::NextChar, 0, p_renderComponentInterface, BUTTON3));
		m_button.push_back(new Button(BoundingBox(50.0f, 250.0f, 50.0f, 50.0f, 50.0f),	m_highScore, &Highscore::PrevChar, 0, p_renderComponentInterface, BUTTON3));

		m_button.push_back(new Button(BoundingBox(150.0f, 350.0f, 50.0f, 50.0f, 50.0f),	m_highScore, &Highscore::NextChar, 1, p_renderComponentInterface, BUTTON3));
		m_button.push_back(new Button(BoundingBox(150.0f, 250.0f, 50.0f, 50.0f, 50.0f),	m_highScore, &Highscore::PrevChar, 1, p_renderComponentInterface, BUTTON3));

		m_button.push_back(new Button(BoundingBox(250.0f, 250.0f, 50.0f, 50.0f, 50.0f),	m_highScore, &Highscore::NextChar, 2, p_renderComponentInterface, BUTTON3));
		m_button.push_back(new Button(BoundingBox(250.0f, 350.0f, 50.0f, 50.0f, 50.0f),	m_highScore, &Highscore::PrevChar, 2, p_renderComponentInterface, BUTTON3));
		
		m_button.push_back(new Button(BoundingBox(350.0f, 300.0f, 50.0f, 50.0f, 50.0f),	m_highScore, &Highscore::SaveFile, p_renderComponentInterface, BUTTON3));
	}
	m_button.push_back(new Button(BoundingBox(250.0f, 50.0f, 50.0f, 50.0f, 50.0f),	this, &SurvivalHighscoreScene::ChangeCurrentState, SceneState::MAIN_MENU, 0, p_renderComponentInterface, BUTTON3));
}

void SurvivalHighscoreScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	if(p_lMouseClicked)
		CheckButton(p_mousePositionX, p_mousePositionY);
}

void SurvivalHighscoreScene::Render()
{
	for(int i = 0; i < m_button.size(); i++)
		m_button.at(i)->Render();
}

void SurvivalHighscoreScene::CheckButton(int p_mousePositionX, int p_mousePositionY)
{
	for(int i = 0; i < m_button.size(); i++)
	{
		if(m_button.at(i)->CheckIfInside(p_mousePositionX, p_mousePositionY))
			m_button.at(i)->ExecuteCommand();
	}
}