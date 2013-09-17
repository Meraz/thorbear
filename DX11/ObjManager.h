#ifndef OBJMANAGER_H
#define OBJMANAGER_H

#include "Obj.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include <vector>
#include <string>


using namespace std;

class ObjManager
{
public:

	ObjManager(ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context, ModelManager* p_modelManager, ShaderManager* p_shaderManager);
	~ObjManager();
	void AddObject(float p_x, float p_y, float p_z, string p_modelName, string p_shaderName);
	Obj* GetObjectAt(int p_index);
	void Update(float p_dt);
	void Draw(D3DXMATRIX p_viewMatrix, D3DXMATRIX p_projMatrix, D3DXVECTOR3 p_eyePos);


private:

	ID3D11Device*			m_d3dDevice;
	ID3D11DeviceContext*	m_context;
	vector<Obj*>			m_objList;
	ModelManager*			m_modelManager;
	ShaderManager*			m_shaderManager;

};
#endif
