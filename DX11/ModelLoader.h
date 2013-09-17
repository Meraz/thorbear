#ifndef MODELLOADER_
#define MODELLOADER_


#include "Vertex.h"
#include "Buffer.h"

#include <fstream>
#include <sstream>

#include <string>
#include <vector>


using namespace std;

class ModelLoader
{

public:
	
	ModelLoader(ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context);
	Model	AddStaticModel(string p_modelName, string p_OBJFileName);
	~ModelLoader();

private:

	HRESULT		CreateBuffers();
	void		CalculateBoundingBox(D3DXVECTOR3 p_vector3);
	void		LoadMaterialFromMTL(string p_materialPath, string p_materialFileName);
	void		LoadModelFromOBJFile(string p_modelName, string p_OBJFileName);
	int			CalculateIndex(LightVertex* p_vertex);
	ID3D11ShaderResourceView*		CreateTexture(string p_textureFileName);

private:

	ID3D11Device*		m_d3dDevice;
	ID3D11DeviceContext* m_context;

	vector<LightVertex>	m_vertices;
	vector<int>			m_indices;

	Buffer*				m_vertexBuffer;
	Buffer*				m_indexBuffer;

	string				m_OBJFileName;

	vector<D3DXVECTOR3>	m_positions;
	vector<D3DXVECTOR2> m_texCoords;
	vector<D3DXVECTOR3> m_normals;

	Material*			m_material;
	Model				m_model;

	D3DXVECTOR3			m_topCorner;
	D3DXVECTOR3			m_bottomCorner;
};
#endif