#ifndef LASER_H
#define LASER_H

#include "RenderComponentInterface.h"
class Laser
{
public:
	Laser(void);
	~Laser(void);
	void Init(RenderComponentInterface* p_renderComp, int p_velocity, BoundingBox p_BoundingBox);
	void Update(float p_deltaTime);
	void Render();
	BoundingBox GetBoundingBox();
private:
	BoundingBox m_BoundingBox;
	int m_velocity;
	RenderComponentInterface* m_renderComp;

};

#endif