#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "ParticleEffect.h"
#include "ParticleEmitter.h"
#include "D3DX_Graphics/d3dUtil.h"
#include "D3DX_Graphics/ModelManager.h"
#include "D3DX_Graphics/Buffer.h"
#include "D3DX_Graphics/ShaderManager.h"
#include "D3DX_Graphics/Camera.h"

using namespace std;

class ParticleSystem
{
public:
	ParticleSystem(ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context, ModelManager* p_modelManager, ShaderManager* p_shaderManager, Camera* p_camera );
	~ParticleSystem();

	void Update(float p_dt);
	void Render();
	void CreateParticleEmitter(ParticleEmitterDesc p_emitterDesc);
	
private:
	ID3D11Device*				m_d3dDevice;
	ID3D11DeviceContext*		m_context;

	vector<ParticleEmitter*>	m_emitterList;

	ModelManager*				m_modelManager;
	ShaderManager*				m_shaderManager;
	Buffer*						m_matrixBuffer;
	Camera*						m_camera;

};

#endif