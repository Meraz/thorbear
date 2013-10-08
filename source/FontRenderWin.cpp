#include "FontRenderWin.h"


FontRenderWin::FontRenderWin(void):m_device(NULL),
									m_context(NULL),
									m_fontFactory(NULL)
{
}


FontRenderWin::~FontRenderWin(void)
{
	m_fontFactory->Release();
	m_fontWrapper->Release();
}

void FontRenderWin::Init( ID3D11Device *p_device, LPCWSTR p_font, ID3D11DeviceContext *p_context )
{
	m_device = p_device;
	m_context = p_context;

	FW1CreateFactory(FW1_VERSION, &m_fontFactory);

	m_fontFactory->CreateFontWrapper(m_device, p_font, &m_fontWrapper);
}

void FontRenderWin::RenderText( LPCWSTR p_text, float p_size, float p_posX, float p_posY, UINT32 p_color, UINT FLAG )
{
	if(FLAG = 1)
		m_fontWrapper->DrawString(m_context, p_text, p_size, p_posX, p_posY, p_color, FW1_RESTORESTATE);
	else if(FLAG = 0)
		m_fontWrapper->DrawString(m_context, p_text, p_size, p_posX, p_posY, p_color, FW1_IMMEDIATECALL);

}
