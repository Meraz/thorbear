#ifndef RENDERCOMPONENTWIN_H
#define RENDERCOMPONENTWIN_H

#include "RenderComponentInterface.h"

class RenderComponentWin : public RenderComponentInterface
{
public:
	RenderComponentWin();
	~RenderComponentWin();

	void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType);
	void RenderParticleSystem(ParticleSystem p_particleSystem);

	void Render();
};

#endif