#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "ParticleEffect.h"
#include "Particle.h"
#include "D3DX_Graphics/d3dUtil.h"
#include "D3DX_Graphics/ModelManager.h"
#include "D3DX_Graphics/Buffer.h"
#include "D3DX_Graphics/ShaderManager.h"
#include "D3DX_Graphics/Shader.h"


using namespace std;

class ParticleEmitter
{
public:
	ParticleEmitter(ParticleEmitterDesc p_particleDesc, ModelManager* p_modelManager, ShaderManager* p_shaderManager, ID3D11Device* p_device, ID3D11DeviceContext* p_context);
	~ParticleEmitter(void);

	
	bool Update(float p_dt);
	void Render(D3DXMATRIX p_view, D3DXMATRIX p_proj);
private:
	vector<Particle*>		m_particleList;
	vector<D3DXMATRIX>		m_particleMatrixList;
	ParticleEmitterDesc		m_particleDesc;
	ModelManager*			m_modelManager;
	ShaderManager*			m_shaderManager;
	ID3D11Device*			m_device;
	ID3D11DeviceContext*	m_context;
	Buffer*					m_matrixBuffer;
	Shader*					m_shader;
	Model*					m_model;

};

#endif 