#ifndef SHADER__H
#define SHADER__H

//#include <DxErr.h>
#include <D3Dcompiler.h>
#include <D3DCommon.h>
#include <D3DX11Async.h>
#include "d3dUtil.h"


using namespace std;

class Shader
{

	ID3D11Device*			m_device;
	ID3D11DeviceContext*	m_context;
	ID3D11InputLayout*		m_inputLayout;

	ID3DX11Effect*			m_pEffect;
	ID3DX11EffectTechnique*  m_pTechnique;
	

public:
	Shader();
	~Shader();
	HRESULT					Init(ID3D11Device* p_device, ID3D11DeviceContext *p_context, char* p_filename, DWORD p_shaderFlags);
	HRESULT					Apply(unsigned int p_pass);

	void					SetMatrix(char* p_variable, D3DXMATRIX& p_mat);
	void					SetFloat(char* p_variable, float p_value);
	void					SetFloat3(char* p_variable, D3DXVECTOR3 p_value);
	void					SetFloat4(char* p_variable, D3DXVECTOR4 p_value);

	void					SetInt(char* p_variable, int p_value);
	void					SetBool(char* p_variable, bool p_value);
	void					SetRawData(char* p_variable, void* p_data, size_t p_size);

	void					SetResource(char* p_variable, ID3D11ShaderResourceView* p_value);

	ID3DX11EffectTechnique*	GetTechnique();
	ID3DX11EffectTechnique*	GetTechniqueByName(char* p_tecName);
	void					SetTechniqueByName(char* p_tecName);
	string					GetFXFileName();

private:

	string					m_FXFileName;
	void					CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* p_shaderBlob);

	ID3D10Blob*	m_blobEffect;
	ID3D10Blob*	m_blobReflect;
	ID3D10Blob* m_compilationErrors;
};
#endif