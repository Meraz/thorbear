#include "ShootingEnemy.h"


ShootingEnemy::ShootingEnemy(void)
{
	m_numOfLives = 1;
	m_enemyType = ENEMY1;
}


ShootingEnemy::~ShootingEnemy(void)
{
}

void ShootingEnemy::Update(int p_posX, int p_posY)
{
	m_BoundingBox.PosX += p_posX;
	m_BoundingBox.PosY += p_posY;

	int l_chanceToFire = rand() % 1000;

	if(l_chanceToFire > 997)
		m_wantsToFire = true;
	l_chanceToFire = 0;
}

void ShootingEnemy::Render()
{
	m_RenderComp->RenderObject(m_BoundingBox, ENEMY1);
}

bool ShootingEnemy::WantsToFire()
{
	bool temp = m_wantsToFire;
	m_wantsToFire = false;
	return temp;
}
