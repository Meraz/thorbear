#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "GameInterface.h"
#include "RenderComponentInterface.h"
#include "Level.h"
#include <iostream>
using namespace std;
class GameScene : public GameInterface
{
public:
	GameScene(void);
	~GameScene(void);

	void Initialize(int p_gameMode, RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked /* add keyboard parameters here*/); // TODO add vector with keyclicks here
	void Render();

private:
	int		m_currentLevel;
	int		m_maxNrOfLevels;
	int		m_enemyWorth;
	int		m_lastKnownNrOfEnemies;
	int		m_nrOfLives;
	int		m_score;
	Level*	m_level;
	int		m_gameMode;
	RenderComponentInterface* m_renderComponentInterface;
private:
	void NewLevel();
	void CheckEnemyNr();
	void CheckPaddleLife();
};

#endif
