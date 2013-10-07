#ifndef RENDERCOMPONENTINTERFACE_H
#define RENDERCOMPONENTINTERFACE_H

#include "ParticleEffect.h"
#include "BoundingBox.h"
#include "Vect3.h"
#include <string>
using namespace std;


enum TextureType
{
	ENEMY1,
	ENEMY2,
	BALL,
	PADDLE,
	ADDLIFEPOWERUP,
	ADDBALLPOWERUP,
	LARGERPADDLEPOWERUP,
	SMALLERPADDLEPOWERUP
};

class RenderComponentInterface
{
public:
	/* Add this object to be drawn this update. */
	virtual void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color = Vect3(1.0f, 1.0f, 1.0f)) = 0;

	/* Add this particle system to be drawn this update */
	virtual void CreateParticleEmitter(ParticleEmitterDesc p_particleDesc) = 0;				

	/* Add this text to be drawn this update */
	virtual void RenderText(wstring p_text, float p_size, float p_posX, float p_posY, unsigned int p_color) = 0;

	/* Only used in the render component */
	virtual void Update(float p_dt) = 0;
	
};

#endif