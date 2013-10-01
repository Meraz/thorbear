#include "AddBallPowerup.h"


AddBallPowerup::AddBallPowerup(void)
{
	m_type = ADDBALL;
}
AddBallPowerup::~AddBallPowerup(void)
{

}

void AddBallPowerup::Update(float p_deltaTime)
{
	m_posY -= m_velocity * p_deltaTime;
}
void AddBallPowerup::Render()
{
	m_renderComp->RenderObject(GetBoundingBox(), ADDBALLPOWERUP);
}