#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include "BoundingBox.h"
#include "Vect3.h"

struct ParticleEmitterDesc
{
	ParticleEmitterDesc()
	{
		lifeTimeMin = lifeTimeMax	= speedMin		= speedMax = spawnInterval = 0.0f;
		angleMin	= angleMax		= nrOfParticles	= 0;
		loop		= false;
	}
	Vect3		position, scale, acceleration, direction, startColor, endColor;
	float		lifeTimeMin, lifeTimeMax, speedMin, speedMax, spawnInterval;
	int			angleMin, angleMax, nrOfParticles;
	bool		loop;
	
};
#endif