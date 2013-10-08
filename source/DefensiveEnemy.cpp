#include "DefensiveEnemy.h"
#include <cstdlib>
#include <climits>
#include <cmath>

DefensiveEnemy::DefensiveEnemy(void)
{
	m_numOfLives = 2;
	m_enemyType = ENEMY2;
	m_phaseZ = ((float)rand())/RAND_MAX*16.0f;
	m_BoundingBox.Depth = 9;
}


DefensiveEnemy::~DefensiveEnemy(void)
{
}

void DefensiveEnemy::Update( float p_velocity, EnemyDirection p_direction, float p_deltaTime)
{
	if(p_direction == HORIZONTAL)
		m_posX += p_velocity;
	else
		m_posY -= abs(p_velocity);
	m_phaseZ += p_deltaTime*4;
	m_BoundingBox.PosZ = 3*sin(m_phaseZ);
}

void DefensiveEnemy::Render()
{
	m_RenderComp->RenderObject(GetBoundingBox(), ENEMY2, Vect3(1.0f)*(m_numOfLives*0.5f)); //TODO change to ENEMY2 once we have a model for it
}

bool DefensiveEnemy::WantsToFire()
{
	return false; //Never fire
}
