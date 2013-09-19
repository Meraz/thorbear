#include "ObjManager.h"

ObjManager::ObjManager( ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context, ModelManager* p_modelManager, ShaderManager* p_shaderManager)
{
	m_d3dDevice		= p_d3dDevice;
	m_context		= p_context;
	m_modelManager	= p_modelManager;
	m_shaderManager = p_shaderManager;
	
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_shaderManager->AddShader("object.fx", 12);
	//m_shaderManager->AddShader("objectShadowMap.fx", 12);
	//m_shaderManager->AddShader("objectNoCullAlphaShadowMap.fx", 12);
}

ObjManager::~ObjManager(void)
{
}

void ObjManager::AddObject( float p_x, float p_y, float p_z, string p_modelName, string p_shaderName )
{
	m_objList.push_back(new Obj(m_d3dDevice, m_context, m_shaderManager->GetShaderByName(p_shaderName), p_x, p_y, p_z, m_modelManager->GetModelByName(p_modelName)));
}

void ObjManager::Update( float p_dt )
{
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList.at(i)->Update(p_dt);
	}
}

void ObjManager::Draw( D3DXMATRIX p_viewMatrix, D3DXMATRIX p_projMatrix, D3DXVECTOR3 p_eyePos )
{
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList.at(i)->Draw(p_viewMatrix, p_projMatrix, p_eyePos);
	}
}

Obj* ObjManager::GetObjectAt( int p_index )
{
	return m_objList.at(p_index);
}






