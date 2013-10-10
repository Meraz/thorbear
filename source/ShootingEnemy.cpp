#include "ShootingEnemy.h"
#include <cstdlib>
#include <climits>
#include <cmath>

ShootingEnemy::ShootingEnemy(void)
{
	m_numOfLives = 1;
	m_enemyType = ENEMY1;
	m_wantsToFire = false;
	m_tick = 0;
	m_shootIntervall = 3.0f +  rand() % 10;
	m_phaseZ = ((float)rand())/RAND_MAX*16.f;
	m_BoundingBox.Depth = 9;
	m_colour = Vect3(0.247, 0.611, 0.282);
}


ShootingEnemy::~ShootingEnemy(void)
{
}

void ShootingEnemy::Update(float p_velocity, EnemyDirection p_direction, float p_deltaTime)
{
	if(p_direction == HORIZONTAL)
		m_posX += p_velocity;
	else
		m_posY -= abs(p_velocity);

	m_tick += p_deltaTime;

	m_phaseZ += p_deltaTime*4;
	m_BoundingBox.PosZ = 3*sin(m_phaseZ);

	if(m_tick >= m_shootIntervall)
	{
		m_tick = 0.0f;
		m_shootIntervall = 3.0f +  rand() % 10;
		int l_chanceToFire = rand() % 100;
		if(l_chanceToFire > 40)
			m_wantsToFire = true;
	}
}

void ShootingEnemy::Render()
{
	m_RenderComp->RenderObject(GetBoundingBox(), ENEMY1, m_colour);
}

bool ShootingEnemy::WantsToFire()
{
	bool temp = m_wantsToFire;
	m_wantsToFire = false;
	return temp;
}
