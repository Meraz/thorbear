#ifndef FONTRENDERWIN_H
#define FONTRENDERWIN_H

#include "FontWrapper/FW1FontWrapper.h"
#include "SplashText.h"
#include <vector>

class FontRenderWin
{
public:
	FontRenderWin();
	~FontRenderWin();
	void	Init(ID3D11Device *p_device, LPCWSTR p_font, ID3D11DeviceContext *p_context);
	void	RenderText(LPCWSTR p_text, float p_size, float p_posX, float p_posY, UINT32 p_color, UINT FLAG);
	void	CreateSplashText(wstring p_text, float p_size, float p_posX, float p_posY, float p_travelTime, float p_stillTime);
	void	Render();
	void	Update(float p_dt);
private:
	ID3D11Device			*m_device;
	ID3D11DeviceContext		*m_context;

	IFW1Factory*			m_fontFactory;
	IFW1FontWrapper*		m_fontWrapper;

	vector<SplashText*>		m_splashTextList;
};

#endif