#include "ShootingEnemy.h"


ShootingEnemy::ShootingEnemy(void)
{
	m_numOfLives = 1;
}


ShootingEnemy::~ShootingEnemy(void)
{
}

void ShootingEnemy::Update(int p_posX, int p_posY)
{
	m_BoundingBox.PosX += p_posX;
	m_BoundingBox.PosY += p_posY;

	int l_chanceToFire = rand() % 100;

	if(l_chanceToFire > 75)
		//Fire shoot
			l_chanceToFire = 0;
}

void ShootingEnemy::Render()
{
	m_RenderComp->RenderObject(m_BoundingBox, ENEMY1);
}
