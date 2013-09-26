#include "ShootingEnemy.h"


ShootingEnemy::ShootingEnemy(void)
{
	m_numOfLives = 1;
	m_enemyType = ENEMY1;
	m_wantsToFire = false;
	m_tick = 0;
	m_shootIntervall = 3 +  rand() % 10;
}


ShootingEnemy::~ShootingEnemy(void)
{
}

void ShootingEnemy::Update(float p_velocity, EnemyDirection p_direction, float p_deltaTime)
{
	if(p_direction == HORIZONTAL)
		m_posX += p_velocity;
	else
		m_posY -= p_velocity;

	m_tick += p_deltaTime;

	if(m_tick >= m_shootIntervall)
	{
		m_tick = 0.0f;
		m_shootIntervall = 3 +  rand() % 10;
		int l_chanceToFire = rand() % 100;
		if(l_chanceToFire > 40)
			m_wantsToFire = true;
	}
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
