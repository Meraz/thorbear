#include "Laser.h"


Laser::Laser(void)
{
}


Laser::~Laser(void)
{
}

void Laser::Init( RenderComponentInterface* p_renderComp, int p_velocity, BoundingBox p_boundingBox )
{
	m_renderComp = p_renderComp;

	m_BoundingBox = p_boundingBox;

	m_velocity = p_velocity;
}

void Laser::Update()
{
	m_BoundingBox.PosY -= m_velocity;
}

void Laser::Render()
{
	m_renderComp->RenderObject( m_BoundingBox, BALL); //TODO change to LASER once this exists
}
