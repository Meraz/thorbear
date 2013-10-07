#include "ParticleEmitter.h"


ParticleEmitter::ParticleEmitter(ParticleEmitterDesc p_particleDesc, ModelManager* p_modelManager, ShaderManager* p_shaderManager, ID3D11Device* p_device, ID3D11DeviceContext* p_context )
{
	m_particleDesc		= p_particleDesc;
	m_modelManager		= p_modelManager;
	m_shaderManager		= p_shaderManager;
	m_device			= p_device;
	m_context			= p_context;
	m_nrOfDeadParticles	= 0;

	for (int i = 0; i < m_particleDesc.nrOfParticles; i++)
	{
		m_particleList.push_back(new Particle());

		//l_lifeTime is between m_particleDesc.lifeTimeMin and m_particleDesc.lifeTimeMax
		float l_lifeTime = m_particleDesc.lifeTimeMin + (float)rand()/((float)RAND_MAX/(m_particleDesc.lifeTimeMax-m_particleDesc.lifeTimeMin));
		//l_speed is between m_particleDesc.speedMin and m_particleDesc.speedMax
		float l_speed = m_particleDesc.speedMin + (float)rand()/((float)RAND_MAX/(m_particleDesc.speedMax-m_particleDesc.speedMin));

		//a is between 0 and 2PI
		double a = (double)rand()/((double)RAND_MAX/(2.0*MathHelper::PI));
		//z is between -1 and 1
		double z = (double)rand()/((double)RAND_MAX/(2.0)) - 1;

		//http://math.stackexchange.com/questions/44689/how-to-find-a-random-axis-or-unit-vector-in-
		double p = abs(1 - pow(2.0,z));
		double s = sqrt(p);
		double c = cos(a);
		double si = sin(a);
		float xx = (float)(s*c);
		float yy = (float)(s*si);
		Vect3 l_direction = Vect3(xx, yy, (float)z);

		//TODO calculate direction depending on what angles are set
		m_particleList.at(i)->Init(m_particleDesc.position, m_particleDesc.scale, l_direction, m_particleDesc.acceleration, m_particleDesc.startColor, m_particleDesc.endColor, l_lifeTime, l_speed, 0.0f);

		D3DXMATRIX l_matrix;
		D3DXMatrixIdentity(&l_matrix);	
		m_particleMatrixList.push_back(l_matrix);
	}

	BUFFER_INIT_DESC bdInstance;
	//Instance Buffer Description
	bdInstance.ElementSize = sizeof( D3DXMATRIX );
	bdInstance.InitData = &m_particleMatrixList[0];
	bdInstance.NumElements = m_particleMatrixList.size();
	bdInstance.Type = VERTEX_BUFFER;
	bdInstance.Usage = BUFFER_CPU_WRITE_DISCARD;

	m_matrixBuffer = new Buffer();
	m_matrixBuffer->Init(m_device, m_context, bdInstance);

	m_shader	= m_shaderManager->GetShaderByName("effect\\instanced.fx");
	m_model		= m_modelManager->GetModelByName("cube.obj");

}


ParticleEmitter::~ParticleEmitter(void)
{
	for (unsigned int i = 0; i < m_particleList.size(); i++)
	{
		SafeDelete(m_particleList.at(i));
	}
	m_particleList.clear();
	m_particleList.shrink_to_fit();

	SafeDelete(m_matrixBuffer);
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

void ParticleEmitter::Render(D3DXMATRIX p_view, D3DXMATRIX p_proj)
{
	D3DXMATRIX l_scale, l_translation, l_world;
	Vect3 l_scaleVect, l_posVect, l_colorVect;

	for (unsigned int i = 0; i < m_particleMatrixList.size(); i++)
	{
		l_scaleVect			= m_particleList.at(i)->GetScale();
		l_posVect			= m_particleList.at(i)->GetPosition();
		l_colorVect			= m_particleList.at(i)->GetColor();

		D3DXMatrixScaling(&l_scale, l_scaleVect.r, l_scaleVect.g, l_scaleVect.b);
		D3DXMatrixTranslation(&l_translation, l_posVect.r, l_posVect.g, l_posVect.b);

		l_world = l_scale * l_translation;
		
		//Enter color into instancematrix
		l_world._14 = l_colorVect.r;
		l_world._24 = l_colorVect.g;
		l_world._34 = l_colorVect.b;

		m_particleMatrixList.at(i) = l_world;
	}

	D3DXMATRIX* verticesPtr;

	D3D11_MAPPED_SUBRESOURCE l_mapped;
	m_context->Map(m_matrixBuffer->GetBufferPointer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &l_mapped);

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (D3DXMATRIX*)l_mapped.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)m_particleMatrixList[0], (sizeof(D3DXMATRIX) * m_particleMatrixList.size()));

	// Unlock the vertex buffer.
	m_context->Unmap(m_matrixBuffer->GetBufferPointer(), 0);

	m_model->m_vertexBuffer->ApplyInstanced(0, m_matrixBuffer);
	m_model->m_indexBuffer->Apply(0);

	m_shader->SetMatrix("gVP", p_view*p_proj);

	D3DX11_TECHNIQUE_DESC techDesc;
	m_shader->GetTechnique()->GetDesc( &techDesc );
	for(int p = 0; p < (int)techDesc.Passes; ++p)
	{
		m_shader->Apply(p);
		m_context->DrawIndexedInstanced(m_model->m_size, m_particleMatrixList.size(), 0, 0, 0);
	}
}

