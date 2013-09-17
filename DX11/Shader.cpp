#include "Shader.h"

Shader::Shader()
{
	m_pEffect = NULL;
	m_pTechnique = NULL;
	m_inputLayout = NULL;
}

Shader::~Shader()
{
	delete m_inputLayout;
	//SAFE_RELEASE(m_pEffect);

	if(m_pEffect)
	{
		while(m_pEffect->Release());
		m_pEffect = NULL;
	}
}
HRESULT Shader::Init(ID3D11Device* p_device, ID3D11DeviceContext *p_context, char* p_filename, DWORD p_shaderFlags)
{
	m_device = p_device;
	m_context = p_context;

	m_FXFileName =  p_filename;

	HRESULT hr = S_OK;

	m_blobEffect = NULL;
	m_blobReflect = NULL;
	m_compilationErrors = NULL;

	hr = D3DX11CompileFromFileA( p_filename, NULL, NULL, "VS", "vs_5_0", p_shaderFlags, NULL, NULL, &m_blobReflect, &m_compilationErrors, NULL );

	hr = D3DX11CompileFromFileA( p_filename, NULL, NULL, NULL, "fx_5_0", p_shaderFlags, NULL, NULL, &m_blobEffect, &m_compilationErrors, NULL );

	
	
	if (m_compilationErrors)
	{
		char* temp = (char*)m_compilationErrors->GetBufferPointer();
		//MessageBoxA(0, (char*)m_compilationErrors->GetBufferPointer(), 0, 0);
		m_compilationErrors->Release();
	}
	

	if(m_blobReflect)
		CreateInputLayoutDescFromVertexShaderSignature(m_blobReflect);
	else
		return S_FALSE;
	int te = (int)m_blobEffect->GetBufferSize();
	hr = D3DX11CreateEffectFromMemory(	
		m_blobEffect->GetBufferPointer(),
		m_blobEffect->GetBufferSize(),
		NULL,
		m_device,
		&m_pEffect);
	
	m_pTechnique = m_pEffect->GetTechniqueByIndex(0);

	return hr;
}

void Shader::CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* p_shaderBlob)
{
	m_inputLayout = NULL;
	bool firstInstanceLayout = true;
	// Reflect shader info
	ID3D11ShaderReflection* pVertexShaderReflection = NULL;	
	HRESULT blerg = D3DReflect( p_shaderBlob->GetBufferPointer(), p_shaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection,(void**) &pVertexShaderReflection);


	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc( &shaderDesc );

	// Read input layout description from shader info
	UINT32 byteOffset = 0;
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (UINT32 i=0; i< shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;		
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc );

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;	
		elementDesc.SemanticName = paramDesc.SemanticName;		
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		//elementDesc.InstanceDataStepRate = 0;
		//elementDesc.InputSlot = 0;

		string tempSemanticName = paramDesc.SemanticName;

		if(tempSemanticName == "mTransform") //Instancing rule
		{
			if (firstInstanceLayout)
			{
				byteOffset = 0;
				firstInstanceLayout = false;
			}
			elementDesc.InputSlot = 1;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			elementDesc.InstanceDataStepRate = 1;
		}
		else if(tempSemanticName == "mPOSITION") //Morph rule
		{
			if (firstInstanceLayout)
			{
				byteOffset = 0;
				firstInstanceLayout = false;
			}
			elementDesc.InputSlot = 1;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;
		}
		else if(tempSemanticName == "mNORMAL") //Morph rule
		{
			elementDesc.InputSlot = 1;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;
		}
		else if(tempSemanticName == "mTEXTURE") //Morph rule
		{
			elementDesc.InputSlot = 1;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;
		}
		else
		{
			elementDesc.InputSlot = 0;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;
		}

		elementDesc.AlignedByteOffset = byteOffset;

		// determine DXGI format
		if(tempSemanticName == "POSITIONC")
		{ //Special case for cube shader where we send in 4bytes for position.
			elementDesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
			byteOffset += 4;
		}
		else if ( paramDesc.Mask == 1 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
			byteOffset += 4;
		}
		else if ( paramDesc.Mask <= 3 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			byteOffset += 8;
		}
		else if ( paramDesc.Mask <= 7 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			byteOffset += 12;
		}
		else if ( paramDesc.Mask <= 15 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			byteOffset += 16;
		}

		//save element desc
		inputLayoutDesc.push_back(elementDesc);
	}		

	// Try to create Input Layout
	HRESULT hr = m_device->CreateInputLayout( &inputLayoutDesc[0], inputLayoutDesc.size(), p_shaderBlob->GetBufferPointer(), p_shaderBlob->GetBufferSize(), &m_inputLayout );

	//Free allocation shader reflection memory
	pVertexShaderReflection->Release();

}


HRESULT Shader::Apply(unsigned int p_pass)
{
	ID3DX11EffectPass* p = m_pTechnique->GetPassByIndex(p_pass);
	if(p)
	{
		m_pTechnique->GetPassByIndex(p_pass)->Apply(0, m_context);

		if(m_inputLayout)
		{
			m_context->IASetInputLayout(m_inputLayout);
		}
		return S_OK;
	}

	return E_FAIL;
}

void Shader::SetFloat(char* p_variable, float p_value)
{
	m_pEffect->GetVariableByName(p_variable)->AsScalar()->SetFloat(p_value);
}

void Shader::SetMatrix(char* p_variable, D3DXMATRIX& p_mat)
{
	m_pEffect->GetVariableByName(p_variable)->AsMatrix()->SetMatrix((float*)&p_mat);
}

void Shader::SetFloat3(char* p_variable, D3DXVECTOR3 p_value)
{
	m_pEffect->GetVariableByName(p_variable)->AsVector()->SetFloatVector((float*)&p_value);
}

void Shader::SetFloat4(char* p_variable, D3DXVECTOR4 p_value)
{
	m_pEffect->GetVariableByName(p_variable)->AsVector()->SetFloatVector((float*)&p_value);
}

void Shader::SetResource(char* p_variable, ID3D11ShaderResourceView* p_value)
{
	m_pEffect->GetVariableByName(p_variable)->AsShaderResource()->SetResource(p_value);
}

void Shader::SetInt(char* p_variable, int p_value)
{
	m_pEffect->GetVariableByName(p_variable)->AsScalar()->SetInt(p_value);
}

void Shader::SetBool(char* p_variable, bool p_value)
{
	m_pEffect->GetVariableByName(p_variable)->AsScalar()->SetBool(p_value);
}

void Shader::SetRawData(char* p_variable, void* p_data, size_t p_size)
{
	m_pEffect->GetVariableByName(p_variable)->SetRawValue(p_data, 0, (UINT)p_size);
}

ID3DX11EffectTechnique* Shader::GetTechnique()
{
	return m_pTechnique;
}

ID3DX11EffectTechnique* Shader::GetTechniqueByName(char* p_tecName)
{
	return m_pEffect->GetTechniqueByName(p_tecName);
}

void Shader::SetTechniqueByName(char* p_tecName)
{
	m_pTechnique = m_pEffect->GetTechniqueByName(p_tecName);
}

string Shader::GetFXFileName()
{
	return m_FXFileName;
}
