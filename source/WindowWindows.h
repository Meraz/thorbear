#ifndef WINDOWWINDOWS_H
#define WINDOWWINDOWS_H

#include <windows.h>

#include "RenderComponentWin.h"
#include "WindowBaseClass.h"
#include "GameTimer.h"

class WindowWindows : public WindowBaseClass
{
public:
	WindowWindows();
	~WindowWindows();
	bool Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow);

	LRESULT MsgProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam);
	int		Run();

private:
	void	Update();
	void	Render();

private:
	HINSTANCE	m_hAppInst;	
	HWND		m_hMainWnd;
	int			m_clientWidth;
	int			m_clientHeight;
	GameTimer*	m_gameTimer;
	bool		m_appPaused;
	float m_mousePositionX;// = GET_X_LPARAM(p_lParam); 
	float m_mousePositionY;// = GET_Y_LPARAM(p_lParam);
	
	RenderComponentWin* m_renderComponent;
};

#endif