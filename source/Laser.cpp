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

void Laser::Update(float p_deltaTime)
{
	m_BoundingBox.PosY -= m_velocity * p_deltaTime;
}

void Laser::Render()
{
	m_renderComp->RenderObject( m_BoundingBox, BALL); //TODO change to LASER once this exists
}

BoundingBox Laser::GetBoundingBox()
{
	return m_BoundingBox;
}