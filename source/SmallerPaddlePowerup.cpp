#include "SmallerPaddlePowerup.h"


SmallerPaddlePowerUp::SmallerPaddlePowerUp(void)
{
	m_type = SMALLERPADDLE;
}
SmallerPaddlePowerUp::~SmallerPaddlePowerUp(void)
{

}

void SmallerPaddlePowerUp::Update(float p_deltaTime)
{
	m_posY -= m_velocity * p_deltaTime;
}
void SmallerPaddlePowerUp::Render()
{
	m_renderComp->RenderObject(GetBoundingBox(), BALL);
}