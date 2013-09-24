#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Paddle.h"
#include "ShootingEnemy.h"
#include "Laser.h"
#include "DefensiveEnemy.h"
#include "LevelImporter.h"
#include "Ball.h"

class Level
{
public:
	Level(void);
	~Level(void);

	void Init(int p_lvlNr, int p_lvlWidth, int p_lvlHeight, RenderComponentInterface* p_renderComp);

	void	Update(int p_mousePosX, bool p_isMouseClicked, float p_deltaTime); //Not sure if int or float
	void	Render();
	bool	HasPaddleDied();
	int		GetNrOfEnemies();

private:
	BoundingBox	m_mapEdges;
	Paddle*		m_paddle;
	Ball*		m_ball;
	int**		m_map;
	bool		m_PaddleHasDied;

	RenderComponentInterface*	m_renderComp;

	vector<Enemy*> m_enemy;
	vector<Laser*> m_laser;
	
	EnemyDirection m_currentEnemyDirection;

	float	m_enemyVelocityX;
	float	m_enemyVelocityY;
	float	m_targetY; //used to check how far down the enemies have moved in one go
	float	m_currentEnemyY; //dynamic variable for above check
	int		m_nrOfEnemies; //TEST

private:
	void	CheckAllCollisions();
	bool	BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2);
	float	CalculateBallOnPaddlePosX();
	void	ShootBallFromPaddle();
	void	CreateEnemies();
	void	MoveEnemies(float p_deltaTime);
	float	FindLowestEnemyRow();
	void	HandleLaserFiring();
};

#endif LEVEL_H