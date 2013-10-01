#include "AddLifePowerup.h"


AddLifePowerup::AddLifePowerup(void)
{
	m_type = ADDLIFE;
}
AddLifePowerup::~AddLifePowerup(void)
{

}

void AddLifePowerup::Update(float p_deltaTime)
{
	m_posY -= m_velocity * p_deltaTime;
}
void AddLifePowerup::Render()
{
	m_renderComp->RenderObject(GetBoundingBox(), BALL);
}