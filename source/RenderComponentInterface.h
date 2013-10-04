#ifndef RENDERCOMPONENTINTERFACE_H
#define RENDERCOMPONENTINTERFACE_H

#include "BoundingBox.h"
#include "Vect3.h"
#include <string>
using namespace std;

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
	PADDLE,
	ADDLIFEPOWERUP,
	ADDBALLPOWERUP,
	LARGERPADDLEPOWERUP,
	SMALLERPADDLEPOWERUP
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

	virtual void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color = Vect3(1.0f, 1.0f, 1.0f)) = 0;
	
	/* Button texture thingy */
	//virtual void RenderMenuButton(BoundingBox2D p_boundingBox, ButtonTexture p_buttonTexture) = 0;	// Not in the code for the moment.

	/* Add this particle system to be drawn this update */
	virtual void RenderParticleSystem(ParticleSystem p_particleSystem) = 0;			
		
	/* Add this text to be drawn this update */
	virtual void RenderText(wstring p_text, float p_size, float p_posX, float p_posY, unsigned int p_color) = 0;	
	
	virtual BoundingBox ConvertIntoScreenSpace(BoundingBox p_boundingBox, TextureType p_textureType) = 0;
};

#endif