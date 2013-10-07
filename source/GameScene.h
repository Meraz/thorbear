#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "BaseScene.h"
#include "Level.h"

#include <iostream>
using namespace std;
class GameScene : public BaseScene
{
public:
	GameScene(int p_gameMode);
	~GameScene(void);

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked /* add keyboard parameters here*/); // TODO add vector with keyclicks here
	void Render();

	//void SetGameMode(int p_gameMode);

private:
	int		m_currentLevel;
	int		m_maxNrOfLevels;
	int		m_enemyWorth;
	int		m_lastKnownNrOfEnemies;
	int		m_nrOfLives;
	int		m_score;
	Level*	m_level;
	int		m_gameMode;

private:
	void NewLevel();
	void CheckEnemyNr();
	void CheckPaddleLife();
};

#endif
