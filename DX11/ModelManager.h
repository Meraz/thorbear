#ifndef MODELMANAGER_
#define MODELMANAGER_

#include "ModelLoader.h"
#include "Vertex.h"
#include <vector>
#include <string>


using namespace std;

class ModelManager
{
public:

	ModelManager(ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context);
	Model*			GetModelByName(string p_modelName);
	void			CreateModel(string p_modelName, string p_OBJFileName);
	~ModelManager();

private:

	Model					m_modelList[256];
	int						m_arraySize;
	ID3D11Device*			m_d3dDevice;
	ID3D11DeviceContext*	m_context;

};
#endif
