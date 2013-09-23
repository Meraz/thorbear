#include "Enemy.h"

void Enemy::Init(int p_posX, int p_posY, int p_width, int p_height)
{
	m_BoundingBox.PosX = p_posX;
	m_BoundingBox.PosY = p_posY;
	m_BoundingBox.Width = p_width;
	m_BoundingBox.Height = p_height;
}

BoundingBox Enemy::GetBoundingBox()
{
	return m_BoundingBox;
}

void Enemy::TakeDamage()
{
	if(m_numOfLives > 0)
		m_numOfLives --;
}

int Enemy::GetNumOfLives()
{
	return m_numOfLives;
}

void Enemy::WritePosition()
{
	cout << "x position: " << m_BoundingBox.PosX << endl;
	cout << "y position: " << m_BoundingBox.PosY << endl;
}

void Enemy::SetRenderComponentInterface(RenderComponentInterface* p_RenderComp)
{
	m_RenderComp = p_RenderComp;
}

