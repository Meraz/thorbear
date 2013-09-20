#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Level.h"
class GameScene
{
public:
	GameScene(void);
	~GameScene(void);

	void Init();
	void Update(int p_mousePosX);
	void Render();
	//void SetGraphicalInterface(RenderComponentInterface* p_renderComp);
private:
	int		m_currentLevel;
	int		m_maxNrOfLevels;
	int		m_enemyWorth;
	int		m_lastKnownNrOfEnemies;
	int		m_nrOfLives;
	int		m_score;
	Level*	m_level;

	//RenderComponentInterface m_renderComp;
	//contains a user interface as well
private:
	void NewLevel();
	void CheckEnemyNr();
	void CheckPaddleDeath();
	void DecrementLife();
};

#endif
