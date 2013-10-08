#include "GameScene.h"

#include <string>
#include <sstream>

GameScene::GameScene()
{
	m_currentLevel = 1;
	m_maxNrOfLevels = 3;
	m_score = 0;
	m_nrOfLives = 3;
	m_lastKnownNrOfEnemies = 0;
	m_enemyWorth = 100;
	m_scoreMultiplier = 1.0f;
	m_gameMode = MODE_SURVIVAL;
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
	m_level->Init(m_currentLevel, m_gameMode, p_renderComponentInterface); 
	m_lastKnownNrOfEnemies = m_level->GetNrOfEnemies();
	m_renderComponentInterface = p_renderComponentInterface;
}

void GameScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked /* add keyboard parameters here*/)
{
	m_level->Update(p_mousePositionX, p_lMouseClicked, (float)p_deltaTime); 
	m_scoreMultiplier = m_level->GetMultiplier();
	CheckPaddleLife();
	CheckEnemyNr();
}

void GameScene::Render()
{
	m_renderComponentInterface->RenderBackground(LEVEL);
	m_level->Render();

	std::wostringstream  l_ss;
	l_ss << m_nrOfLives;
	std::wstring l_lives( l_ss.str() );
  
	l_ss.str(L""); // reset stringstream to empty
	l_ss << m_score;
	std::wstring l_score( l_ss.str() );

	l_ss.str(L""); // reset stringstream to empty
	l_ss << m_scoreMultiplier;
	std::wstring l_scoreMulti( l_ss.str().substr(0,4) );
  
	m_renderComponentInterface->RenderText(L"Lives: " + l_lives, 15.0f, 10.0f, 0.0f, 0xff0099ff);
	m_renderComponentInterface->RenderText(L"Score: " + l_score, 15.0f, 10.0f, 20.0f, 0xff0099ff);
	m_renderComponentInterface->RenderText(L"Score Multiplier: x" + l_scoreMulti, 15.0f, 10.0f, 40.0f, 0xff0099ff);
}

void GameScene::CheckPaddleLife()
{
	m_nrOfLives += m_level->GetLifeChanged();
	if(m_nrOfLives < 0)
	{
		//TODO GAME OVER STUFF GOES HERE
	}
}



void GameScene::CheckEnemyNr()
{
	int l_nrEnemies = m_level->GetNrOfEnemies();

	if(l_nrEnemies < m_lastKnownNrOfEnemies)
		m_score += (int)(m_scoreMultiplier * m_enemyWorth * (m_lastKnownNrOfEnemies - l_nrEnemies));
	m_lastKnownNrOfEnemies = l_nrEnemies;

	if(m_lastKnownNrOfEnemies == 0 && m_gameMode == MODE_CAMPAIGN)
	{
		delete m_level;
		m_currentLevel++;

		if(m_currentLevel > m_maxNrOfLevels)
			m_currentLevel = 1;
		m_level = new Level();

		m_level->Init(m_currentLevel, m_gameMode, m_renderComponentInterface); 
	}
}

void GameScene::SetGameMode( int p_gameMode )
{
	m_gameMode = p_gameMode;
}
