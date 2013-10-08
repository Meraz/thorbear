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

	for (unsigned int i = 0; i < m_splashTextList.size(); i++)
	{
		delete m_splashTextList.at(i);
		 m_splashTextList.at(i) = 0;
	}
	m_splashTextList.clear();
	m_splashTextList.shrink_to_fit();
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

void FontRenderWin::Update( float p_dt )
{
	for (unsigned int i = 0; i < m_splashTextList.size(); i++)
	{
		if(m_splashTextList.at(i)->Update(p_dt))
		{
			delete m_splashTextList.at(i);
			m_splashTextList.at(i) = 0;
			m_splashTextList.erase(m_splashTextList.begin() + i);
			m_splashTextList.shrink_to_fit();
			i--;
		}
	}
}

void FontRenderWin::Render()
{
	for (unsigned int i = 0; i < m_splashTextList.size(); i++)
	{
		m_splashTextList.at(i)->Render();
	}
}

void FontRenderWin::CreateSplashText( wstring p_text, float p_size, float p_posX, float p_posY, float p_travelTime, float p_stillTime )
{
	m_splashTextList.push_back(new SplashText());
	m_splashTextList.back()->Init(m_context, m_fontWrapper, p_posX, p_posY, p_size, p_text, p_travelTime,  p_stillTime);
}
