#include "GameScene.h"


GameScene::GameScene(void)
{
	m_currentLevel = 1;
	m_maxNrOfLevels = 3;
	m_score = 0;
	m_nrOfLives = 3;
	m_lastKnownNrOfEnemies = 0;
	m_enemyWorth = 100;
}


GameScene::~GameScene(void)
{
	delete m_level;
}

void GameScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	m_renderComponentInterface = p_renderComponentInterface;
	m_level = new Level();
	m_level->Init(m_currentLevel, 600, 400, m_renderComponentInterface); // TODO : Don't hard code this
	m_lastKnownNrOfEnemies = m_level->GetNrOfEnemies();
	//create and init user interface
}

void GameScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked /* add keyboard parameters here*/)
{
	// TODO : delta time.

	m_level->Update(p_mousePositionX, p_lMouseClicked, (float)p_deltaTime); // TODO : NO hardcoded booleans

	CheckPaddleDeath();
	CheckEnemyNr();
	//cout << "Level: " << m_currentLevel << ", lives: " << m_nrOfLives << ", score: " << m_score << endl;
}

void GameScene::Render()
{
	m_level->Render();

	//render UI(lives, m_score)
}

void GameScene::CheckPaddleDeath()
{
	if(m_level->HasPaddleDied())
		DecrementLife();
}

void GameScene::DecrementLife()
{
	m_nrOfLives--;
	if(m_nrOfLives < 0)
	{
		//Trigger game over stuff. 
	}
}

void GameScene::CheckEnemyNr()
{
	int l_nrEnemies = m_level->GetNrOfEnemies();

	if(l_nrEnemies < m_lastKnownNrOfEnemies)
		m_score += m_enemyWorth * (m_lastKnownNrOfEnemies - l_nrEnemies);
	m_lastKnownNrOfEnemies = l_nrEnemies;

	if(m_lastKnownNrOfEnemies == 0)
	{
		delete m_level;
		m_currentLevel++;

		if(m_currentLevel > m_maxNrOfLevels)
			m_currentLevel = 1;
		m_level = new Level();
		m_level->Init(m_currentLevel, 600, 800, m_renderComponentInterface); // TODO : HARDCODED
	}
}