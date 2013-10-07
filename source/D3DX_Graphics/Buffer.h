#ifndef BUFFER__H
#define BUFFER__H

//#include "stdafx.h"
#include "d3dUtil.h"


enum BUFFER_TYPE
{
	VERTEX_BUFFER,
	INDEX_BUFFER,
	CONSTANT_BUFFER_VS,
	CONSTANT_BUFFER_GS,
	CONSTANT_BUFFER_PS,
	BUFFER_TYPE_COUNT
};

enum BUFFER_USAGE
{
	BUFFER_DEFAULT,
	BUFFER_IMMUTABLE,
	BUFFER_STREAM_OUT_TARGET,
	BUFFER_CPU_WRITE,
	BUFFER_CPU_WRITE_DISCARD,
	BUFFER_CPU_READ,
	BUFFER_USAGE_COUNT,
	BUFFER_CPU_WRITE_NO_OVERWRITE
};

struct BUFFER_INIT_DESC
{
	BUFFER_TYPE		Type;
	UINT32			NumElements;
	UINT32			ElementSize;
	BUFFER_USAGE	Usage;
	void*			InitData;

	BUFFER_INIT_DESC()
	{
		InitData = NULL;
	}
};

class Buffer
{
protected:
	ID3D11Buffer*			m_buffer;

	BUFFER_TYPE				m_type;
	BUFFER_USAGE			m_usage;

	UINT32					m_elementSize;
	UINT32					m_elementCount;
	UINT32					m_vertexSize;
	UINT32					m_offset;

	ID3D11Device*			m_device;
	ID3D11DeviceContext*	m_context;
public:
	Buffer();
	virtual ~Buffer();

	HRESULT			Init(	ID3D11Device* p_device, ID3D11DeviceContext* p_context,
							BUFFER_INIT_DESC& p_initDesc);

	void			Map(void* p_mappedData);
	void			Unmap();

	HRESULT			Apply(UINT32 p_misc = 0);
	HRESULT			ApplyInstanced(UINT32 p_misc, Buffer* p_transformBuffer);

	ID3D11Buffer*	GetBufferPointer();
	void			SetBufferPointer(ID3D11Buffer* p_b);

	UINT32			GetVertexSize();
	UINT32			GetElementCount();
	UINT32			GetOffset();
};
#endif