#include "ParticleMan.h"

#include "../MemoryMacro.h"

ParticleMan::ParticleMan( )
{
}

ParticleMan::~ParticleMan()
{
	for (unsigned int i = 0; i < m_emitterList.size(); i++)
	{
		delete m_emitterList.at(i);
		m_emitterList.at(i) = 0;
	}
	m_emitterList.clear();
	m_emitterList.shrink_to_fit();
}

void ParticleMan::Init( Camera p_camera )
{
  m_shader.Init( (SHADER_DIRECTORY + "particleVertex.glsl").c_str(), (SHADER_DIRECTORY + "particleFragment.glsl").c_str(), (SHADER_DIRECTORY + "particleGeometry.glsl").c_str() );
  m_shader.Build( );
  m_shader.Use( );
  m_shader.SetActiveCamera( p_camera );
}

void ParticleMan::Update( float p_dt )
{
	for (unsigned int i = 0; i < m_emitterList.size(); i++)
	{
		if(m_emitterList.at(i)->Update(p_dt))
		{
			SafeDelete(m_emitterList.at(i));
			m_emitterList.erase(m_emitterList.begin() + i);
			i--;
		}
	}
}

void ParticleMan::Render()
{
  m_shader.Use( );
  m_shader.UpdateUniform( glm::mat4(0) );

	for (unsigned int i = 0; i < m_emitterList.size(); i++)
	{
		m_emitterList.at(i)->Render( m_camera );
	}
}

void ParticleMan::CreateParticleEmitter( ParticleEmitterDesc p_emitterDesc )
{
	m_emitterList.push_back( new ParticleEmitter( p_emitterDesc ) );
}
