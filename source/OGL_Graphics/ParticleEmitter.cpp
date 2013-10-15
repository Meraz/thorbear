#include "ParticleEmitter.h"

#include <climits>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

ParticleEmitter::ParticleEmitter(ParticleEmitterDesc p_particleDesc, ModelManager* p_modelManager, ShaderManager* p_shaderManager, ID3D11Device* p_device, ID3D11DeviceContext* p_context )
{
	m_particleDesc		= p_particleDesc;
	m_nrOfDeadParticles	= 0;

	for (int i = 0; i < m_particleDesc.nrOfParticles; i++)
	{
		m_particleList.push_back(new Particle());

		//l_lifeTime is between m_particleDesc.lifeTimeMin and m_particleDesc.lifeTimeMax
		float l_lifeTime = m_particleDesc.lifeTimeMin + (float)rand()/((float)RAND_MAX/(m_particleDesc.lifeTimeMax-m_particleDesc.lifeTimeMin));
		//l_speed is between m_particleDesc.speedMin and m_particleDesc.speedMax
		float l_speed = m_particleDesc.speedMin + (float)rand()/((float)RAND_MAX/(m_particleDesc.speedMax-m_particleDesc.speedMin));

		//Random x,y,z between -1 and 1
		double xx = (double)rand()/((double)RAND_MAX*.5) - 1;
		double yy = (double)rand()/((double)RAND_MAX*.5) - 1;
		double zz = (double)rand()/((double)RAND_MAX*.5) - 1;

		//Calculate magnitude of x,y,z
		double vmag = sqrt((xx*xx)+(yy*yy)+(zz*zz));

		//Normalize x,y,z
		xx = xx/vmag;
		yy = yy/vmag;
		zz = zz/vmag;

		//Voila! Random unit vector!
		Vect3 l_direction = Vect3((float)xx, (float)yy, (float)zz);

		//TODO calculate direction depending on what angles are set
		m_particleList.at(i)->Init(m_particleDesc.position, m_particleDesc.scale, l_direction, m_particleDesc.acceleration, m_particleDesc.startColor, m_particleDesc.endColor, l_lifeTime, l_speed, 0.0f);

		m_particleDataList.push_back( glm::vec3(1) );
	}
  
  glGenVertexArrays( 1, &m_vao );
  glBindVertexArray( m_vao );
  
  glGenBuffers( 1, &m_dataBuffer );
  glBindBuffer( GL_ARRAY_BUFFER, m_dataBuffer );
  glBufferData( GL_ARRAY_BUFFER, m_particleDataList.size() * 3 * sizeof( float ), 0, GL_DYNAMIC_DRAW );
  
  glEnableVertexAttribArray( 0 );
  glEnableVertexAttribArray( 1 );
  glEnableVertexAttribArray( 2 );
#define BUFFER_OFFSET( i ) ( ( char * )NULL + ( i ) )
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof( float ), BUFFER_OFFSET( 0 ) );
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof( float ), BUFFER_OFFSET( 3 * sizeof( float ) ) );
  glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof( float ), BUFFER_OFFSET( 6 * sizeof( float ) ) );

  glBindVertexArray( 0 );
  
  
  m_shader.Init( SHADER_DIRECTORY + "particleVertex.glsl", SHADER_DIRECTORY + "particleFragment.glsl", SHADER_DIRECTORY + "particleGeometry.glsl" );
  m_shader.Build( );
  m_shader.Use( );
}


ParticleEmitter::~ParticleEmitter(void)
{
	for (unsigned int i = 0; i < m_particleList.size(); i++)
	{
		SafeDelete(m_particleList.at(i)); // Include "MemoryMacro.h" if not defined
	}
	m_particleList.clear();
	m_particleList.shrink_to_fit();

	//SafeDelete(m_matrixBuffer);
}


bool ParticleEmitter::Update( float p_dt )
{
	for (unsigned int i = 0; i < m_particleList.size(); i++)
	{
		if(m_particleList.at(i)->Update(p_dt))
			m_nrOfDeadParticles++;
	}

	if(m_nrOfDeadParticles == m_particleDesc.nrOfParticles && !m_particleDesc.loop)
		return true;

	return false;
}

void ParticleEmitter::Render( Camera p_camera )
{
	glm::mat4 l_scale, l_translation, l_world;
	Vect3 l_scaleVect, l_posVect, l_colorVect;

	for (unsigned int i = 0; i < m_particleList.size(); i++)
	{
		l_posVect			  = m_particleList.at(i)->GetPosition();
		l_scaleVect			= m_particleList.at(i)->GetScale();
		l_colorVect			= m_particleList.at(i)->GetColor();

		m_particleDataList.at( i*3 )     = glm::vec3( l_posVect.r, l_posVect.g, l_posVect.b );
		m_particleDataList.at( i*3 + 1 ) = glm::vec3( l_scaleVect.r, l_scaleVect.g, l_scaleVect.b );
		m_particleDataList.at( i*3 + 2 ) = glm::vec3( l_colorVect.r, l_colorVect.g, l_colorVect.b );
	}
  
  glBindVertexArray( m_vao );
  glBindBuffer( GL_ARRAY_BUFFER, m_dataBuffer );

  glBufferSubData( GL_ARRAY_BUFFER, 0, m_particleDataList.size( ) * 3 * sizeof( float ), m_particleDataList.data( ) );

	m_shader->SetUniformMatrix( "worldProjectionMatrix", p_camera.GetProjectionMatrix() * p_camera.GetViewMatrix() );

  m_shader->Use( );
  glDrawArrays( GL_POINTS, 0, m_particleMatrixList.size() );
}

