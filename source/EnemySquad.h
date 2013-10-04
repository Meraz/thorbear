#ifndef ENEMYSQUAD_H
#define ENEMYSQUAD_H

#include "ShootingEnemy.h"
#include "DefensiveEnemy.h"
#include "Laser.h"
#include <vector>
#include <algorithm>

class EnemySquad
{
public:
	EnemySquad();
	~EnemySquad();
	void			Init(BoundingBox p_mapEdges, float p_velocity, vector<Enemy*> p_enemy);
	void			Update(float p_deltaTime);
	void			Render();
	void			SetSquadRenderComponent(RenderComponentInterface* p_renderComp);
	BoundingBox		GetBoundingBox();
	int				GetNumOfEnemies();
	int				GetDirection();
	vector<Enemy*>	GetEnemies();
	vector<Laser*>	GetLasers();
	void			EraseMember(int p_type, int p_vectorPos);
	void			PauseMovement();
	void			StartMovement();
	bool			IsPaused();
private:
	RenderComponentInterface*	m_renderComp;
	vector<Enemy*>				m_enemy;
	vector<Laser*>				m_laser;
	BoundingBox					m_BoundingBox;
	BoundingBox					m_mapEdges;
	float						m_velocity;
	float						m_prevVelocity;
	float						m_targetY; //used to check how far down the enemies have moved in one go
	bool						m_isPaused;
	EnemyDirection				m_currentEnemyDirection;
private:

	void	MoveEnemies(float p_deltaTime);
	void	HandleLaserFiring();
	vector<int>	CheckLowestEnemiesInSquad();
	void	CalculateBoundingBox();
};

#endif