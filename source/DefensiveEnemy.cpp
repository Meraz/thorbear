#include "DefensiveEnemy.h"


DefensiveEnemy::DefensiveEnemy(void)
{
	m_numOfLives = 2;
	m_enemyType = ENEMY2;
}


DefensiveEnemy::~DefensiveEnemy(void)
{
}

void DefensiveEnemy::Update( float p_deltaTime, EnemyDirection p_direction)
{
	if(p_direction == HORIZONTAL)
		m_posX += m_velocity * p_deltaTime;
	else
		m_posY -= m_velocity * p_deltaTime;

}

void DefensiveEnemy::Render()
{
	m_RenderComp->RenderObject(GetBoundingBox(), ENEMY1); //TODO change to ENEMY2 once we have a model for it
}

bool DefensiveEnemy::WantsToFire()
{
	return false; //Never fire
}
