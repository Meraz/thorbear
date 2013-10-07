#include "ParticleSystem.h"

ParticleSystem::ParticleSystem( ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context, ModelManager* p_modelManager, ShaderManager* p_shaderManager, Camera* p_camera )
{
	m_d3dDevice		= p_d3dDevice;
	m_context		= p_context;
	m_modelManager	= p_modelManager;
	m_shaderManager = p_shaderManager;
	m_camera		= p_camera;
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::Update( float p_dt )
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

void ParticleSystem::Render()
{
	for (unsigned int i = 0; i < m_emitterList.size(); i++)
	{
		m_emitterList.at(i)->Render(m_camera->GetViewMatrix(), m_camera->GetProjMatrix());
	}
}

void ParticleSystem::CreateParticleEmitter( ParticleEmitterDesc p_emitterDesc )
{
	m_emitterList.push_back(new ParticleEmitter(p_emitterDesc, m_modelManager, m_shaderManager, m_d3dDevice, m_context));
}
