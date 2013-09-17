#include "Obj.h"


Obj::Obj(ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context, Shader* p_shader, float p_x, float p_y, float p_z, Model* p_model)
{
	m_d3dDevice	= p_d3dDevice;
	m_context	= p_context;
	m_shader	= p_shader;
	m_model		= p_model;
	
	m_XScale	= 1.0f;
	m_YScale	= 1.0f;
	m_ZScale	= 1.0f;

	m_rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_position	= D3DXVECTOR3(p_x, p_y, p_z);
	
	D3DXMatrixIdentity(&m_scaleMat);
	D3DXMatrixIdentity(&m_rotationMatX);
	D3DXMatrixIdentity(&m_rotationMatY);
	D3DXMatrixIdentity(&m_rotationMatZ);
	D3DXMatrixIdentity(&m_translateMat);
	
	D3DXMatrixScaling(&m_scaleMat, m_XScale, m_YScale, m_ZScale);
	D3DXMatrixRotationX(&m_rotationMatX, m_rotation.x);
	D3DXMatrixRotationY(&m_rotationMatY, m_rotation.y);
	D3DXMatrixRotationZ(&m_rotationMatZ, m_rotation.z);
	D3DXMatrixTranslation(&m_translateMat, m_position.x, m_position.y, m_position.z);
}

Obj::~Obj(void)
{

}

void Obj::SetScale( float p_XScale, float p_YScale, float p_ZScale )
{
	m_XScale = p_XScale;
	m_YScale = p_YScale;
	m_ZScale = p_ZScale;

	D3DXMatrixScaling(&m_scaleMat, p_XScale, p_YScale, p_ZScale);

}


void Obj::SetXRotation( float p_rotation )
{
	float t_rad = p_rotation*(MathHelper::Pi/180);

	m_rotation.x = t_rad;
	D3DXMatrixRotationX(&m_rotationMatX, m_rotation.x);
}

void Obj::SetYRotation( float p_rotation )
{
	float t_rad = p_rotation*(MathHelper::Pi/180);

	m_rotation.y = t_rad;
	D3DXMatrixRotationY(&m_rotationMatY, m_rotation.y);
}

void Obj::SetZRotation( float p_rotation )
{
	float t_rad = p_rotation*(MathHelper::Pi/180);

	m_rotation.z = t_rad;
	D3DXMatrixRotationZ(&m_rotationMatZ, m_rotation.z);
}

void Obj::SetXPosition( float p_position )
{
	m_position.x = p_position;
	D3DXMatrixTranslation(&m_translateMat, m_position.x, m_position.y, m_position.z);
}

void Obj::SetYPosition( float p_position )
{
	m_position.y = p_position;
	D3DXMatrixTranslation(&m_translateMat, m_position.x, m_position.y, m_position.z);
}

void Obj::SetZPosition( float p_position )
{
	m_position.z = p_position;
	D3DXMatrixTranslation(&m_translateMat, m_position.x, m_position.y, m_position.z);
}

float Obj::GetXScale()
{
	return m_XScale;
}

float Obj::GetYScale()
{
	return m_YScale;
}

float Obj::GetZScale()
{
	return m_ZScale;
}

float Obj::GetXRotation()
{
	return m_rotation.x * (180/MathHelper::Pi);
}

float Obj::GetYRotation()
{
	return m_rotation.y * (180/MathHelper::Pi);
}

float Obj::GetZRotation()
{
	return m_rotation.z * (180/MathHelper::Pi);
}

float Obj::GetXPosition()
{
	return m_position.x;
}

float Obj::GetYPosition()
{
	return m_position.y;
}

float Obj::GetZPosition()
{
	return m_position.z;
}

void Obj::Update( float p_dt )
{

}

void Obj::Draw( D3DXMATRIX p_viewMatrix, D3DXMATRIX p_projMatrix, D3DXVECTOR3 p_eyePos )
{
	D3DXMATRIX t_worldMat	= m_scaleMat * m_rotationMatX * m_rotationMatY * m_rotationMatZ * m_translateMat;
	D3DXMATRIX t_WVP		= t_worldMat * p_viewMatrix * p_projMatrix;

	

	m_model->m_vertexBuffer->Apply(0);
	m_model->m_indexBuffer->Apply(0);

	m_shader->SetMatrix("gWVP", t_WVP);
	m_shader->SetMatrix("gWorld", t_worldMat);
	m_shader->SetResource("gTexture", m_model->m_material->m_textureResource);
	
	
	D3DX11_TECHNIQUE_DESC techDesc;
	m_shader->GetTechnique()->GetDesc( &techDesc );
	for(int p = 0; p < (int)techDesc.Passes; ++p)
	{
		m_shader->Apply(p);
		m_context->DrawIndexed(m_model->m_size, 0, 0);
	}
}


