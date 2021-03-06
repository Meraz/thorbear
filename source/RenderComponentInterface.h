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
	SMALLERPADDLEPOWERUP,
	BALLSPEEDINCREASEPOWERUP,
	BALLSPEEDDECREASEPOWERUP,
	LEVEL,
	MAINMENU,
	HS,
	START,
	CAMPAIGN,
	SURVIVAL,
	CAMPAIGNHS,
	SURVIVALHS,
	EXIT,
	ARROWUP,
	ARROWDOWN,
	SAVE,
	RETURN,
	TTCOUNT // Leave this last, you can loop i < TTCOUNT
};



class RenderComponentInterface
{
public:

	virtual void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color = Vect3(1.0f, 1.0f, 1.0f)) = 0;
	
	/* Button texture thingy */
	//virtual void RenderMenuButton(BoundingBox2D p_boundingBox, ButtonTexture p_buttonTexture) = 0;	// Not in the code for the moment.

	/* Add this particle system to be drawn this update */
	virtual void CreateParticleEmitter(ParticleEmitterDesc p_particleDesc) = 0;				

	/* Add this text to be drawn this update */
	virtual void RenderText(string p_text, float p_size, float p_posX, float p_posY, unsigned int p_color) = 0;

	/* Only used in the render component */
	virtual void Update(float p_dt) = 0;
	
	virtual BoundingBox ConvertIntoScreenSpace(BoundingBox p_boundingBox, TextureType p_textureType) = 0;

	virtual void RenderBackground(TextureType p_textureType) = 0;

	virtual void CreateSplashText(wstring p_text, float p_size, float p_posX, float p_posY, float p_travelTime, float p_stillTime ) = 0;

	virtual void SetShowCursor(bool p_showCursor) = 0;

	virtual char GetKey() = 0;

};

#endif