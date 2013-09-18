#include "WindowWindows.h"

#include <WindowsX.h>
namespace
{
	// This is just used to forward Windows messages from a global window
	// procedure to our member function window procedure because we cannot
	// assign a member function to WNDCLASS::lpfnWndProc.
	WindowWindows* g_win32 = 0;
}

LRESULT CALLBACK MainWndProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before m_hMainWnd is valid.
	return g_win32->MsgProc(p_hwnd, p_msg, p_wParam, p_lParam);
}

WindowWindows::WindowWindows()
	: WindowBaseClass()
{
	m_renderComponentInterface = new RenderComponentWin();
	m_gameInterface->Initialize(m_renderComponentInterface);
	m_gameTimer = new GameTimer();
	m_appPaused = false;
}

WindowWindows::~WindowWindows()
{
	delete m_renderComponentInterface;
	delete m_gameTimer;
}

bool WindowWindows::Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	g_win32 = this;
	m_clientWidth  = 800; 
	m_clientHeight = 600;
	m_gameTimer->Reset();

	WNDCLASS l_wc;
	l_wc.style         = CS_HREDRAW | CS_VREDRAW;
	l_wc.lpfnWndProc   = MainWndProc; 
	l_wc.cbClsExtra    = 0;
	l_wc.cbWndExtra    = 0;
	l_wc.hInstance     = m_hAppInst;
	l_wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	l_wc.hCursor       = LoadCursor(0, IDC_ARROW);
	l_wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	l_wc.lpszMenuName  = 0;
	l_wc.lpszClassName = "D3DWndClassName";

	if( !RegisterClass(&l_wc) )
	{
		MessageBox(0, "RegisterClass Failed.", 0, 0);
		return false;
	}
	DWORD dwStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT l_r = { 0, 0, m_clientWidth, m_clientHeight };
    AdjustWindowRect(&l_r, dwStyle, false);
	int l_width  = l_r.right - l_r.left;
	int l_height = l_r.bottom - l_r.top;


	m_hMainWnd = CreateWindow("D3DWndClassName", "Spaceout", dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, l_width, l_height, 0, 0, m_hAppInst, 0); 
	if( !m_hMainWnd )
	{
		MessageBox(0, "CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);
	return true;
}

int WindowWindows::Run()
{
	MSG l_msg = {0};
	m_gameTimer->Reset();

	while(l_msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if(PeekMessage( &l_msg, 0, 0, 0, PM_REMOVE ))
		{
			TranslateMessage( &l_msg );
			DispatchMessage( &l_msg );
		}
		// Otherwise, do animation/game stuff.
		else
		{	
			m_gameTimer->Tick();
			if( !m_appPaused )
			{
				//CalculateFrameStats();
				Update();
				Render();
			}
			else
			{
				Sleep(100);
			}
		}
	}
	return (int)l_msg.wParam;
}

void WindowWindows::Update()
{
	// TODO Fix update variables here
	WindowBaseClass::Update(m_gameTimer->DeltaTime(), m_mousePositionX, m_mousePositionY);	
}

void WindowWindows::Render()
{	
	WindowBaseClass::Render();
}

LRESULT WindowWindows::MsgProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
{
	switch( p_msg )
	{
	// WM_ACTIVATE is sent when the window is activated or deactivated.  
	// We pause the game when the window is deactivated and unpause it 
	// when it becomes active.  
	case WM_ACTIVATE:
		if( LOWORD(p_wParam) == WA_INACTIVE )
		{
			m_appPaused = true;
			m_gameTimer->Stop();
		}
		else
		{
			m_appPaused = false;
			m_gameTimer->Start();
		}
		return 0;

	// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	// The WM_MENUCHAR message is sent when a menu is active and the user presses 
	// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
        // Don't beep when we alt-enter.
        return MAKELRESULT(0, MNC_CLOSE);

	case WM_MOUSEMOVE:
		//OnMouseMove(p_wParam, GET_X_LPARAM(p_lParam), GET_Y_LPARAM(p_lParam));
		m_mousePositionX = GET_X_LPARAM(p_lParam); 
		m_mousePositionY = GET_Y_LPARAM(p_lParam);
		return 0;
	
	}
	return DefWindowProc(p_hwnd, p_msg, p_wParam, p_lParam);
}