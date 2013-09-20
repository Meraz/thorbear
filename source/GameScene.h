#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "GameInterface.h"
#include "RenderComponentInterface.h"
#include "Level.h"
class GameScene : public GameInterface
{
public:
	GameScene(void);
	~GameScene(void);

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY /* add keyboard parameters here*/); // TODO add vector with keyclicks here
	void Render();

private:
	int		m_currentLevel;
	int		m_maxNrOfLevels;
	int		m_enemyWorth;
	int		m_lastKnownNrOfEnemies;
	int		m_nrOfLives;
	int		m_score;
	Level*	m_level;
	RenderComponentInterface* m_renderComponentInterface;
private:
	void NewLevel();
	void CheckEnemyNr();
	void CheckPaddleDeath();
	void DecrementLife();
};

#endif
