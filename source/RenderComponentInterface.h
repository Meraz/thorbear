#ifndef RENDERCOMPONENTINTERFACE_H
#define RENDERCOMPONENTINTERFACE_H

#include "BoundingBox.h"
#include "Vect3.h"

struct ParticleSystem
{
	int x;
	int y;
	int z;
};

enum TextureType
{
	ENEMY1,
	ENEMY2,
	BALL,
	PADDLE
};

class RenderComponentInterface
{
public:
	/* Add this object to be drawn this update. */
	virtual void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color = Vect3(1.0f, 1.0f, 1.0f)) = 0;

	/* Add this particle system to be drawn this update */
	virtual void RenderParticleSystem(ParticleSystem p_particleSystem) = 0;																												
};

#endif