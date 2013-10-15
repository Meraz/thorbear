#include "BallSpeedIncreasePowerup.h"


BallSpeedIncreasePowerup::BallSpeedIncreasePowerup(void)
{
	m_type = INCREASESPEED;
}
BallSpeedIncreasePowerup::~BallSpeedIncreasePowerup(void)
{

}

void BallSpeedIncreasePowerup::Update(float p_deltaTime)
{
	m_posY -= m_velocity * p_deltaTime;
}
void BallSpeedIncreasePowerup::Render()
{
	m_renderComp->RenderObject(GetBoundingBox(), ADDLIFEPOWERUP);
}