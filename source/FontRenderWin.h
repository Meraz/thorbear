#ifndef FONTRENDERWIN_H
#define FONTRENDERWIN_H

#include "FW1FontWrapper.h"
class FontRenderWin
{
public:
	FontRenderWin(void);
	~FontRenderWin(void);
	void	Init(ID3D11Device *p_device, LPCWSTR p_font, ID3D11DeviceContext *p_context);
	void	RenderText(LPCWSTR p_text, float p_size, float p_posX, float p_posY, UINT32 p_color);
private:
	ID3D11Device			*m_device;
	ID3D11DeviceContext		*m_context;

	IFW1Factory*			m_fontFactory;
	IFW1FontWrapper*		m_fontWrapper;
};

#endif