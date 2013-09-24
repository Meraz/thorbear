#include "Enemy.h"

void Enemy::Init(float p_posX, float p_posY, int p_width, int p_height, float p_velocity)
{
	m_BoundingBox.PosX = m_posX = p_posX;
	m_BoundingBox.PosY = m_posY = p_posY;
	m_BoundingBox.Width = p_width;
	m_BoundingBox.Height = p_height;
	m_velocity = p_velocity;
}

BoundingBox Enemy::GetBoundingBox()
{
	m_BoundingBox.PosX = m_posX;
	m_BoundingBox.PosY = m_posY;
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

float Enemy::GetVelocity()
{
	return m_velocity;
}

void Enemy::SetVelocity(float p_velocity)
{
	m_velocity = p_velocity;
}
