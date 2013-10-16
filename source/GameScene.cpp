#include "GameScene.h"

#include <string>
#include <sstream>
#include <climits>

GameScene::GameScene(int p_gameMode, SoundHandler* p_soundHandler)
{
	m_gameMode = p_gameMode;
	m_currentLevel = 1;
	m_maxNrOfLevels = 3;
	m_score = 0;
	m_nrOfLives = 3;
	m_lastKnownNrOfEnemies = 0;
	m_enemyWorth = 100;
	m_scoreMultiplier = 1.0f;
	m_gameMode = p_gameMode;
	m_isGameOver = false;
	m_soundHandler = p_soundHandler;
  m_deltaTime = 0.01;
}

GameScene::~GameScene()
{
	delete m_level;
}

void GameScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = SceneState::GAME;

	m_level = new Level();
	m_level->Init(m_currentLevel, m_gameMode, p_renderComponentInterface, m_soundHandler); 
	m_lastKnownNrOfEnemies = m_level->GetNrOfEnemies();

	m_renderComponentInterface = p_renderComponentInterface;
}

void GameScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked /* add keyboard parameters here*/)
{
	if(!m_isGameOver)
	{
		m_level->Update(p_mousePositionX, p_lMouseClicked, (float)p_deltaTime); 
		m_scoreMultiplier = m_level->GetMultiplier();
		CheckPaddleLife();
		CheckEnemyNr();
	}
	else
	{
		if(p_lMouseClicked == true)
		{
			if(m_gameMode == MODE_CAMPAIGN)
				ChangeCurrentState(SceneState::CAMPAIGNHIGHSCORE, m_score);
			else if(m_gameMode == MODE_SURVIVAL)
				ChangeCurrentState(SceneState::SURVIVALHIGHSCORE, m_score);
		}
	}

	m_deltaTime = p_deltaTime;
}

void GameScene::Render()
{

	m_renderComponentInterface->RenderBackground(LEVEL);
	m_level->Render();
	
	std::ostringstream  l_ss;
	std::ostringstream  l_ss2;
	
	// Lives
	l_ss << "Extra Lives: " << m_nrOfLives << "\n";
	l_ss << "Score: " << m_score  << "\n";

	l_ss2 << 1.0f/m_deltaTime;
	std::string l_fps( l_ss2.str() );
	l_ss2.clear();
	l_ss2.str("");


	l_ss << "FPS: " << l_fps  << "\n";

	l_ss2 << m_scoreMultiplier;
	std::string l_scoreMulti = l_ss2.str().substr(0,4);

	l_ss << "Score Multiplier: x" << l_scoreMulti;

	m_renderComponentInterface->RenderText(l_ss.str(), 15.0f, 10.0f, 0.0f, 0xff0099ff);

	if (m_isGameOver)
	{
		m_renderComponentInterface->RenderText("GAME OVER", 100.0f, 650.0f, 500.0f, 0xff0099ff); //TODO Place in the middle of the screen
	}
}

void GameScene::CheckPaddleLife()
{
	m_nrOfLives += m_level->GetLifeChanged();
	if(m_nrOfLives < 0)
	{
		m_isGameOver = true;
		m_nrOfLives = 0;
	}
}

void GameScene::CheckEnemyNr()
{
	int l_nrEnemies = m_level->GetNrOfEnemies();

	if(l_nrEnemies < m_lastKnownNrOfEnemies)
	{
		m_score += (int)(m_scoreMultiplier * m_enemyWorth * (m_lastKnownNrOfEnemies - l_nrEnemies));
		if(m_score > INT_MAX)
			m_score = INT_MAX;
	}
	m_lastKnownNrOfEnemies = l_nrEnemies;

	if(m_lastKnownNrOfEnemies == 0 && m_gameMode == MODE_CAMPAIGN)
	{
		delete m_level;
		m_currentLevel++;

		if(m_currentLevel > m_maxNrOfLevels)
			m_currentLevel = 1;
		m_level = new Level();
		m_level->Init(m_currentLevel, m_gameMode, m_renderComponentInterface, m_soundHandler); 
	}
}
