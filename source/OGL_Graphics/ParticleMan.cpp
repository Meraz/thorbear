#include "ParticleMan.h"

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

void ParticleMan::ParticleMan( Camera* p_camera )
{
	m_camera = p_camera;
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
	for (unsigned int i = 0; i < m_emitterList.size(); i++)
	{
		m_emitterList.at(i)->Render( m_camera );
	}
}

void ParticleMan::CreateParticleEmitter( ParticleEmitterDesc p_emitterDesc )
{
	m_emitterList.push_back( new ParticleEmitter( p_emitterDesc ) );
}
