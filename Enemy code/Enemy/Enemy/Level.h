#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Paddle.h"
#include "ShootingEnemy.h"
#include "LevelImporter.h"

class Level
{
public:
	Level(void);
	~Level(void);

	void Init(int p_lvlNr, int p_lvlWidth, int p_lvlHeight);

	void Update(int p_mousePosX); //Not sure if int or float
	void Render();
	bool HasPaddleDied();
	int GetNrOfEnemies();
	//void SetGraphicalInterface(RenderComponentInterface* p_renderComp)
private:
	BoundingBox	m_mapEdges;
	Paddle*		m_paddle;
	int**		m_map;
	bool		m_PaddleHasDied;
	//RenderComponentInterface*	m_renderComp;
	vector<Enemy*> m_enemy;
	enum m_enemyDirection {VERTICAL, HORIZONTAL};
	m_enemyDirection m_currentEnemyDirection;
	int m_enemyVelocityX;
	int m_enemyVelocityY;
	int m_targetY; //used to check how far down the enemies have moved in one go
	int m_currentEnemyY; //dynamic variable for above check
	int		m_nrOfEnemies; //TEST

private:
	void CheckAllCollisions();
	bool BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2);
};

#endif LEVEL_H