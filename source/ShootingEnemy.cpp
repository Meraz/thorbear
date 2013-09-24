#include "ShootingEnemy.h"


ShootingEnemy::ShootingEnemy(void)
{
	m_numOfLives = 1;
	m_enemyType = ENEMY1;
}


ShootingEnemy::~ShootingEnemy(void)
{
}

void ShootingEnemy::Update(float p_deltaTime, EnemyDirection p_direction)
{
	if(p_direction == HORIZONTAL)
		m_posX += m_velocity * p_deltaTime;
	else
		m_posY -= m_velocity * p_deltaTime;

	int l_chanceToFire = rand() % 1000;

	if(l_chanceToFire > 997)
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
