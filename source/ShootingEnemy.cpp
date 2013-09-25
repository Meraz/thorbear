#include "ShootingEnemy.h"


ShootingEnemy::ShootingEnemy(void)
{
	m_numOfLives = 1;
	m_enemyType = ENEMY1;
	m_wantsToFire = false;
}


ShootingEnemy::~ShootingEnemy(void)
{
}

void ShootingEnemy::Update(float p_velocity, EnemyDirection p_direction)
{
	if(p_direction == HORIZONTAL)
		m_posX += p_velocity;
	else
		m_posY -= p_velocity;

	int l_chanceToFire = rand() % 10000;

	if(l_chanceToFire >= 9998)
		m_wantsToFire = true;
	l_chanceToFire = 0;
}

void ShootingEnemy::Render()
{
	m_RenderComp->RenderObject(GetBoundingBox(), ENEMY1);
}

bool ShootingEnemy::WantsToFire()
{
	bool temp = m_wantsToFire;
	m_wantsToFire = false;
	return temp;
}
