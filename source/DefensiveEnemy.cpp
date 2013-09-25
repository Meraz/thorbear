#include "DefensiveEnemy.h"


DefensiveEnemy::DefensiveEnemy(void)
{
	m_numOfLives = 2;
	m_enemyType = ENEMY2;
}


DefensiveEnemy::~DefensiveEnemy(void)
{
}

void DefensiveEnemy::Update( float p_velocity, EnemyDirection p_direction)
{
	if(p_direction == HORIZONTAL)
		m_posX += p_velocity;
	else
		m_posY -= p_velocity;

}

void DefensiveEnemy::Render()
{
	m_RenderComp->RenderObject(GetBoundingBox(), ENEMY1); //TODO change to ENEMY2 once we have a model for it
}

bool DefensiveEnemy::WantsToFire()
{
	return false; //Never fire
}
