#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "../ParticleEffect.h"
#include "../Particle.h"
#include "Camera.h"

#include <GL/glew.h>
#include <vector>

class ParticleEmitter
{
public:
	ParticleEmitter( ParticleEmitterDesc p_particleDesc );
	~ParticleEmitter( void );

	bool Update( float p_dt );
	void Render( );
  
private:
	std::vector< Particle* > m_particleList;
	std::vector< glm::vec3 > m_particleDataList;
	ParticleEmitterDesc m_particleDesc;
  
  GLuint m_dataBuffer;
  GLuint m_vao;

	int m_nrOfDeadParticles;
};

#endif 
