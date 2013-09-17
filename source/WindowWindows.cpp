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
}

WindowWindows::~WindowWindows()
{
	delete m_renderComponentInterface;
}

bool WindowWindows::Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	g_win32 = this;
	m_clientWidth  = 800; 
	m_clientHeight = 600;

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

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT l_r = { 0, 0, m_clientWidth, m_clientHeight };
    AdjustWindowRect(&l_r, WS_OVERLAPPEDWINDOW, false);
	int l_width  = l_r.right - l_r.left;
	int l_height = l_r.bottom - l_r.top;

	m_hMainWnd = CreateWindow("D3DWndClassName", "Test", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, l_width, l_height, 0, 0, m_hAppInst, 0); 
	if( !m_hMainWnd )
	{
		MessageBox(0, "CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);
	return true;
}


void WindowWindows::Update()
{
	// TODO Fix update variables here
	double l_deltaTime	   = 0.0;
	float l_mousePositionX = 0.0f;
	float l_mousePositionY = 0.0f;

	WindowBaseClass::Update(l_deltaTime, l_mousePositionX, l_mousePositionY);
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
			//m_appPaused = true;
			//m_timer.Stop();
		}
		else
		{
			//m_appPaused = false;
			//m_timer.Start();
		}
		return 0;
	/*
	// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		// Save the new client area dimensions.
		m_clientWidth  = LOWORD(p_lParam);
		m_clientHeight = HIWORD(p_lParam);
		if( m_d3dDevice )
		{
			if( p_wParam == SIZE_MINIMIZED )
			{
				m_appPaused = true;
				m_minimized = true;
				m_maximized = false;
			}
			else if( p_wParam == SIZE_MAXIMIZED )
			{
				m_appPaused = false;
				m_minimized = false;
				m_maximized = true;
				OnResize();
			}
			else if( p_wParam == SIZE_RESTORED )
			{
				
				// Restoring from minimized state?
				if( m_minimized )
				{
					m_appPaused = false;
					m_minimized = false;
					OnResize();
				}

				// Restoring from maximized state?
				else if( m_maximized )
				{
					m_appPaused = false;
					m_maximized = false;
					OnResize();
				}
				else if( m_resizing )
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or m_swapChain->SetFullscreenState.
				{
					OnResize();
				}
			}
		}
		return 0;
	*/
	/*
	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_appPaused = true;
		m_resizing  = true;
		m_timer.Stop();
		return 0;
	*/
	/*
	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		m_appPaused = false;
		m_resizing  = false;
		m_timer.Start();
		OnResize();
		return 0;
		*/
 
	// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	// The WM_MENUCHAR message is sent when a menu is active and the user presses 
	// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
        // Don't beep when we alt-enter.
        return MAKELRESULT(0, MNC_CLOSE);

	// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)p_lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)p_lParam)->ptMinTrackSize.y = 200; 
		return 0;
	/*
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(p_wParam, GET_X_LPARAM(p_lParam), GET_Y_LPARAM(p_lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(p_wParam, GET_X_LPARAM(p_lParam), GET_Y_LPARAM(p_lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(p_wParam, GET_X_LPARAM(p_lParam), GET_Y_LPARAM(p_lParam));
		return 0;
	*/
	}

	return DefWindowProc(p_hwnd, p_msg, p_wParam, p_lParam);
}
