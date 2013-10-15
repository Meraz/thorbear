#ifndef POWERUP_H
#define POWERUP_H

#include "RenderComponentInterface.h"
enum PowerupType
{
	LARGERPADDLE,
	SMALLERPADDLE,
	ADDBALL,
	ADDLIFE,
	INCREASESPEED,
	DECREASESPEED
};
class Powerup
{
public:
	void			init(float p_posX, float p_posY, int p_width, int p_height, RenderComponentInterface* p_renderComp);
	virtual void	Update(float p_deltaTime) = 0;
	virtual void	Render() = 0;
	BoundingBox		GetBoundingBox();
	PowerupType		GetPowerUpType();

		

protected:
	float						m_velocity;
	float						m_posX;
	float						m_posY;
	BoundingBox					m_boundingBox;
	RenderComponentInterface*	m_renderComp;
	PowerupType					m_type;
	
};

#endif