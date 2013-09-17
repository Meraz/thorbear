#ifndef Vertex_H
#define Vertex_H

#include "d3dUtil.h"
#include "Buffer.h"
#include <string>

using namespace std;

 struct VertPos
{
	D3DXVECTOR4 pos;
};

 struct SimpleVert
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texC;
};

 struct Vert
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texC;
};

 struct LightVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texC;
	D3DXVECTOR4 diff;
	D3DXVECTOR4 spec;
};

 struct Material
{
	D3DXVECTOR3 m_ambient;
	D3DXVECTOR3 m_diffuse;
	D3DXVECTOR3 m_specular;
	int			m_shininess;
	float		m_alpha;
	ID3D11ShaderResourceView* m_textureResource;
};

 struct Model
{
	D3DXVECTOR3 m_topBoundingCorner;
	D3DXVECTOR3 m_bottomBoundingCorner;
	Buffer*		m_vertexBuffer;
	Buffer*		m_indexBuffer;
	string		m_bufferName;
	UINT		m_offset;
	UINT		m_stride;
	int			m_size;
	Material*	m_material;
};

#endif