#ifndef RENDERCOMPONENTLINUX_H
#define RENDERCOMPONENTLINUX_H

#include "RenderComponentInterface.h"

class RenderComponentLinux : public RenderComponentInterface
{
public:
	RenderComponentLinux();
	~RenderComponentLinux();

	void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType);
	void RenderParticleSystem(ParticleSystem p_particleSystem);
	void Render();
};

#endif