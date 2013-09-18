#include "ShootingEnemy.h"


ShootingEnemy::ShootingEnemy(void)
{
}


ShootingEnemy::~ShootingEnemy(void)
{
}

void ShootingEnemy::Init(int p_posX, int p_posY, int p_width, int p_height)
{
	m_BoundingBox.farTopLeftX = p_posX;
	m_BoundingBox.farTopLeftY = p_posY;
	m_BoundingBox.width = p_width;
	m_BoundingBox.heigth = p_height;
}

void ShootingEnemy::Update(int p_posX, int p_posY)
{
	m_BoundingBox.farTopLeftX = p_posX;
	m_BoundingBox.farTopLeftY = p_posY;

	int l_chanceToFire = rand() % 100;

	if(l_chanceToFire > 75)
		//Fire shoot
			l_chanceToFire = 0;
}

void ShootingEnemy::Render()
{
	//m_RenderComp->Render(ENEMYTYPE1,m_BoundingBox);
}
