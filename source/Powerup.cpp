#include "Powerup.h"


void Powerup::init(float p_posX, float p_posY, int p_width, int p_height)
{
	m_boundingBox.PosX = m_posX = p_posX;
	m_boundingBox.PosY = m_posY = p_posY;
	m_boundingBox.Width = p_width;
	m_boundingBox.Height = p_height;
	m_boundingBox.Depth	 = 2;   //Hardcoded for glory
	m_velocity			 = 100;

}
BoundingBox Powerup::GetBoundingBox()
{
	m_boundingBox.PosX = m_posX;
	m_boundingBox.PosY = m_posY;
	return m_boundingBox;
}
PowerupType	Powerup::GetPowerUpType()
{
	return m_type;
}

void Powerup::SetRenderComponentInterface(RenderComponentInterface* p_renderComp)
{
	m_renderComp = p_renderComp;
}