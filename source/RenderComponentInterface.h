#ifndef RENDERCOMPONENTINTERFACE_H
#define RENDERCOMPONENTINTERFACE_H

#include "BoundingBox.h"
#include "BoundingBox2D.h"

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

enum ButtonTexture
{
	BUTTON1,
	BUTTON2,
	BUTTON3,
	BUTTON4
};

class RenderComponentInterface
{
public:
	/* Add this object to be drawn this update. */
	virtual void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType) = 0;	
	
	/* Button texture thingy */
	//virtual void RenderMenuButton(BoundingBox2D p_boundingBox, ButtonTexture p_buttonTexture) = 0;	// Not in the code for the moment.

	/* Add this particle system to be drawn this update */
	virtual void RenderParticleSystem(ParticleSystem p_particleSystem) = 0;			

	
};

#endif