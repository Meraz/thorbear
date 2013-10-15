#ifndef PARTICLEMAN_H
#define PARTICLEMAN_H

#include "ParticleEffect.h"
#include "ParticleEmitter.h"
#include "Camera.h"

class ParticleMan
{
public:
	ParticleMan( );
	~ParticleMan( );
  
  void Init( Camera* p_camera );
	void Update( float p_dt );
	void Render( );
	void CreateParticleEmitter( ParticleEmitterDesc p_emitterDesc );
	
private:
	vector< ParticleEmitter* > m_emitterList;

	Camera* m_camera;

};

#endif