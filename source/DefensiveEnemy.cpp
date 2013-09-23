#include "DefensiveEnemy.h"


DefensiveEnemy::DefensiveEnemy(void)
{
	m_numOfLives = 2;
}


DefensiveEnemy::~DefensiveEnemy(void)
{
}

void DefensiveEnemy::Update( int p_posX, int p_posY )
{
	m_BoundingBox.PosX += p_posX;
	m_BoundingBox.PosY += p_posY;
}

void DefensiveEnemy::Render()
{
	m_RenderComp->RenderObject(m_BoundingBox, ENEMY1);
}
