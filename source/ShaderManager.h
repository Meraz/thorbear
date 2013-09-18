#ifndef ShaderManager_
#define ShaderManager_

#include "d3dUtil.h"
#include "Shader.h"
#include <vector>

using namespace std;

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void		Init(ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context);
	void		AddShader(char* p_FXFileName, int p_shaderFlags);
	Shader*		GetShaderByName(string p_FXFileName);

private:

	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_context;
	vector<Shader*> m_shaderList;
};
#endif