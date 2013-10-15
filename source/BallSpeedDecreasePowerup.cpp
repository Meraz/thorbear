#include "BallSpeedDecreasePowerup.h"


BallSpeedDecreasePowerup::BallSpeedDecreasePowerup(void)
{
	m_type = DECREASESPEED;
}
BallSpeedDecreasePowerup::~BallSpeedDecreasePowerup(void)
{

}

void BallSpeedDecreasePowerup::Update(float p_deltaTime)
{
	m_posY -= m_velocity * p_deltaTime;
}
void BallSpeedDecreasePowerup::Render()
{
	m_renderComp->RenderObject(GetBoundingBox(), ADDLIFEPOWERUP);
}