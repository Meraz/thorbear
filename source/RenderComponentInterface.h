#ifndef RENDERCOMPONENTINTERFACE_H
#define RENDERCOMPONENTINTERFACE_H


struct BoundingBox
{
	int farTopLeftX;
	int farTopLeftY;
	int farTopLeftZ;
	int width;
	int heigth;
	int depth;
};

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
	virtual void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType) = 0;	

	/* Add this particle system to be drawn this update */
	virtual void RenderParticleSystem(ParticleSystem p_particleSystem) = 0;					
	
	/* Called by window to render all added objects. */
	virtual void Render() = 0;																													

};

#endif