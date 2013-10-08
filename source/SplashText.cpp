#include "SplashText.h"

SplashText::SplashText()
{

}

SplashText::~SplashText()
{

}

void SplashText::Init( ID3D11DeviceContext* p_context, IFW1FontWrapper* p_fontWrapper, float p_posX, float p_posY, float p_size, wstring p_text, float p_travelTime, float p_stillTime)
{
	m_context		= p_context;
	m_fontWrapper	= p_fontWrapper;
	m_endSize		= p_size;
	m_posX			= p_posX;
	m_posY			= p_posY;
	m_size			= 0;
	m_travelTime	= m_travelTimeConst = p_travelTime;
	m_stillTime		= p_stillTime;
	m_traveling		= true;
	m_text			= p_text;
}

bool SplashText::Update( float p_dt )
{
	if(m_traveling)
	{
		m_travelTime -= p_dt;
		if(m_travelTime <= 0.0f )
		{
			m_traveling = false;
		}
		m_size += (p_dt/m_travelTimeConst)*m_endSize;
	}
	else
	{	
		m_stillTime -= p_dt;
		if(m_stillTime <= 0.0f )
		{
			return true;
		}
	}
	return false;
}

void SplashText::Render()
{
	m_fontWrapper->DrawString(m_context, m_text.c_str(), 100.0f, m_posX, m_posY, 0xff0099ff, (FW1_RESTORESTATE | FW1_CENTER | FW1_VCENTER));
}

