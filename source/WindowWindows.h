#ifndef WINDOWWINDOWS_H
#define WINDOWWINDOWS_H

#include <windows.h>

#include "RenderComponentWin.h"
#include "WindowBaseClass.h"
#include "D3DX_Graphics\GameTimer.h"

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
	int m_mousePositionX; 
	int m_mousePositionY;
	bool m_lMouseClicked;
	
	RenderComponentWin* m_renderComponent;
};

#endif