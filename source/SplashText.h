#ifndef	SPLASHTEXT_H
#define SPLASHTEXT_H

#include "D3DX_Graphics/d3dUtil.h"
#include "FontWrapper/FW1FontWrapper.h"

using namespace std;

class SplashText
{
public:
	SplashText();
	~SplashText();
	void	Init(ID3D11DeviceContext* p_context, IFW1FontWrapper* p_fontWrapper, float p_posX, float p_posY, float p_size, wstring p_text, float p_travelTime, float p_stillTime);
	bool	Update(float p_dt);
	void	Render();
private:
	ID3D11DeviceContext		*m_context;

	IFW1FontWrapper*		m_fontWrapper;

	float m_size, m_endSize;
	float m_travelTime, m_travelTimeConst, m_stillTime;
	float m_posX, m_posY;

	bool m_traveling;

	wstring m_text;
};
#endif