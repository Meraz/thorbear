#ifndef PARTICLEMAN_H
#define PARTICLEMAN_H

#include "ParticleEffect.h"
#include "ParticleEmitter.h"
#include "Shader.h"
#include "Camera.h"

#include "glm/glm.hpp"

#include <vector>

class ParticleMan
{
public:
	ParticleMan( );
	~ParticleMan( );
  
  void Init( Camera p_camera, glm::vec3 p_lightPos );
	void Update( float p_dt );
	void Render( );
	void CreateParticleEmitter( ParticleEmitterDesc p_emitterDesc );
	
private:
	std::vector< ParticleEmitter* > m_emitterList;

	Shader m_shader;

};

#endif
