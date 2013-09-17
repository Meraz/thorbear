#include "Buffer.h"

Buffer::Buffer()
{
	m_buffer = NULL;
	m_vertexSize = 0;
	m_offset = 0;
}

Buffer::~Buffer()
{
	delete m_buffer;
}


HRESULT Buffer::ApplyInstanced( UINT32 p_misc, Buffer* p_transformBuffer )
{
	HRESULT hr = S_OK;

	if(m_type != VERTEX_BUFFER)
		return E_FAIL;

	ID3D11Buffer*	instancedBuffer[2] = {m_buffer, p_transformBuffer->GetBufferPointer()};
	UINT			strides[2] = {m_elementSize, sizeof( D3DXMATRIX )};
	UINT			offsets[2] = {0, 0};

	m_context->IASetVertexBuffers(p_misc, 2, instancedBuffer, strides, offsets );

	return S_OK;
}

HRESULT Buffer::Apply(UINT32 p_misc)
{
	HRESULT hr = S_OK;

	switch(m_type)
	{
		case VERTEX_BUFFER:
			{
				m_vertexSize = m_elementSize;
				m_offset = 0;
				m_context->IASetVertexBuffers(p_misc, 1, &m_buffer, &m_vertexSize, &m_offset );
			}
			break;
		case INDEX_BUFFER:
			{
				m_context->IASetIndexBuffer(m_buffer, DXGI_FORMAT_R32_UINT, 0);
			}
			break;
		case CONSTANT_BUFFER_VS:
			{
				m_context->VSSetConstantBuffers(p_misc, 1, &m_buffer);
			}
			break;
		case CONSTANT_BUFFER_GS:
			{
				m_context->GSSetConstantBuffers(p_misc, 1, &m_buffer);
			}
			break;
		case CONSTANT_BUFFER_PS:
			{
				m_context->PSSetConstantBuffers(p_misc, 1, &m_buffer);
			}
			break;
		default:
			hr = E_FAIL;
			break;
	};

	return hr;
}

HRESULT Buffer::Init(ID3D11Device* p_device, ID3D11DeviceContext* p_context,
		BUFFER_INIT_DESC& p_initDesc)
{
	m_device = p_device;
	m_context = p_context;
	
	D3D11_BUFFER_DESC bufferDesc;

	m_type = p_initDesc.Type;
	switch(m_type)
	{
		case VERTEX_BUFFER:
			{
				bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				if(p_initDesc.Usage == BUFFER_STREAM_OUT_TARGET)
					bufferDesc.BindFlags |= D3D11_BIND_STREAM_OUTPUT;
			}
			break;
		case INDEX_BUFFER:
			{
				bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			}
			break;
		case CONSTANT_BUFFER_VS:
		case CONSTANT_BUFFER_GS:
		case CONSTANT_BUFFER_PS:
			{
				bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			}
			break;
		default:
			return E_FAIL;
			break;
	};

	m_usage = p_initDesc.Usage;
	m_elementSize = p_initDesc.ElementSize;
	m_elementCount = p_initDesc.NumElements;

	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	if(m_usage == BUFFER_CPU_READ)
	{
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
	}
	else if(m_usage == BUFFER_CPU_WRITE)
	{
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
	}
	else if(m_usage == BUFFER_CPU_WRITE_DISCARD)
	{
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
	}
	else if(m_usage == BUFFER_CPU_WRITE_NO_OVERWRITE)
	{
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
	}
	else if(m_usage == BUFFER_IMMUTABLE)
	{
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		bufferDesc.CPUAccessFlags |= 0;
	}
	
	//Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.ByteWidth = p_initDesc.NumElements * p_initDesc.ElementSize;

	//set at least 16 bytes
	if(bufferDesc.ByteWidth < 16)
		bufferDesc.ByteWidth = 16;

	HRESULT hr = S_OK;
	if(p_initDesc.InitData)
	{
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = p_initDesc.InitData;
		hr = m_device->CreateBuffer(&bufferDesc, &data, &m_buffer);
	}
	else
	{
		hr = m_device->CreateBuffer(&bufferDesc, NULL, &m_buffer);
	}

	if(FAILED(hr))
	{
		MessageBox(NULL, L"Unable to create buffer.", L"Slenda Error", MB_ICONERROR | MB_OK);
	}

	return hr;
}

void Buffer::Map(void** p_b)
{
	UINT32 mapType = 0;

	if(m_usage == BUFFER_CPU_READ)
		mapType = D3D11_MAP_READ;
	else if(m_usage == BUFFER_CPU_WRITE)
		mapType = D3D11_MAP_WRITE;
	else if(m_usage == BUFFER_CPU_WRITE_DISCARD)
		mapType = D3D11_MAP_WRITE_DISCARD;
	else if(m_usage == BUFFER_CPU_WRITE_NO_OVERWRITE)
		mapType = D3D11_MAP_WRITE_NO_OVERWRITE;
	else if(m_usage == BUFFER_IMMUTABLE)
		mapType = D3D11_MAP_READ;
	else 
		mapType = D3D11_MAP_WRITE_DISCARD;

	//Fix DX11 MAP
	//m_buffer->Map( (D3D11_MAP)mapType, 0, (LPVOID*)p_b );
	//m_context->Map()
}

void Buffer::Unmap()
{
	//FIX DX11 UNMAP
	//m_buffer->Unmap();
}

ID3D11Buffer* Buffer::GetBufferPointer()
{
	return m_buffer;
}

UINT32 Buffer::GetVertexSize()
{
	return m_elementSize;
}

UINT32 Buffer::GetElementCount()
{
	return m_elementCount;
}

UINT32 Buffer::GetOffset()
{
	return m_offset;
}

void Buffer::SetBufferPointer(ID3D11Buffer* p_b)
{
	m_buffer = p_b;
}
