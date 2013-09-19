#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	/*m_shaderList.clear();
	m_shaderList.shrink_to_fit();*/
	for(int i = 0; i < m_shaderList.size(); i++)
	{
		delete m_shaderList.at(i);
	}
}

void ShaderManager::Init( ID3D11Device* p_d3dDevice, ID3D11DeviceContext* p_context )
{
	m_d3dDevice = p_d3dDevice;
	m_context = p_context;
}

void ShaderManager::AddShader(char* p_FXFileName, int p_shaderFlags)
{
	m_shaderList.push_back(new Shader());
	m_shaderList.at(m_shaderList.size()-1)->Init(m_d3dDevice, m_context, p_FXFileName, p_shaderFlags);
}

Shader* ShaderManager::GetShaderByName(string p_FXFileName)
{
	for (int i = 0; i < (int)m_shaderList.size(); i++)
	{
		if(m_shaderList[i]->GetFXFileName() == p_FXFileName)
		{
			return m_shaderList[i];
		}

	}
	return m_shaderList[0];
}


