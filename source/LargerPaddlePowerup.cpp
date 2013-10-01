#include "LargerPaddlePowerup.h"


LargerPaddlePowerup::LargerPaddlePowerup(void)
{
	m_type = LARGERPADDLE;
}
LargerPaddlePowerup::~LargerPaddlePowerup(void)
{

}

void LargerPaddlePowerup::Update(float p_deltaTime)
{
	m_posY -= m_velocity * p_deltaTime;
}
void LargerPaddlePowerup::Render()
{
	m_renderComp->RenderObject(GetBoundingBox(), BALL);
}