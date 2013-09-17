#include "d3dApp.h"
#include <WindowsX.h>
#include <sstream>

namespace
{
	// This is just used to forward Windows messages from a global window
	// procedure to our member function window procedure because we cannot
	// assign a member function to WNDCLASS::lpfnWndProc.
	D3DApp* g_d3dApp = 0;
}

LRESULT CALLBACK MainWndProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before m_hMainWnd is valid.
	return g_d3dApp->MsgProc(p_hwnd, p_msg, p_wParam, p_lParam);
}

D3DApp::D3DApp(HINSTANCE p_hInstance)
:	m_hAppInst(p_hInstance),
	m_mainWndCaption(L"Space Out"),
	m_d3dDriverType(D3D_DRIVER_TYPE_HARDWARE),
	m_clientWidth(800),
	m_clientHeight(600),
	m_enable4xMsaa(false),
	m_hMainWnd(0),
	m_appPaused(false),
	m_minimized(false),
	m_maximized(false),
	m_resizing(false),
	m_4xMsaaQuality(0),
 
	m_d3dDevice(0),
	m_d3dImmediateContext(0),
	m_swapChain(0),
	m_depthStencilBuffer(0),
	m_renderTargetView(0),
	m_depthStencilView(0)
{
	ZeroMemory(&m_screenViewport, sizeof(D3D11_VIEWPORT));

	// Get a pointer to the application object so we can forward 
	// Windows messages to the object's window procedure through
	// the global window procedure.
	g_d3dApp = this;
}

D3DApp::~D3DApp()
{
	ReleaseCOM(m_renderTargetView);
	ReleaseCOM(m_depthStencilView);
	ReleaseCOM(m_swapChain);
	ReleaseCOM(m_depthStencilBuffer);

	// Restore all default settings.
	if( m_d3dImmediateContext )
		m_d3dImmediateContext->ClearState();

	ReleaseCOM(m_d3dImmediateContext);
	ReleaseCOM(m_d3dDevice);
}

HINSTANCE D3DApp::AppInst()const
{
	return m_hAppInst;
}

HWND D3DApp::MainWnd()const
{
	return m_hMainWnd;
}

float D3DApp::AspectRatio()const
{
	return static_cast<float>(m_clientWidth) / m_clientHeight;
}

int D3DApp::Run()
{
	MSG l_msg = {0};
 
	m_timer.Reset();

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
			m_timer.Tick();

			if( !m_appPaused )
			{
				CalculateFrameStats();
				UpdateScene(m_timer.DeltaTime());	
				DrawScene();
			}
			else
			{
				Sleep(100);
			}
        }
    }

	return (int)l_msg.wParam;
}

bool D3DApp::Init()
{
	if(!InitMainWindow())
		return false;

	if(!InitDirect3D())
		return false;

	return true;
}
 
void D3DApp::OnResize()
{
	assert(m_d3dImmediateContext);
	assert(m_d3dDevice);
	assert(m_swapChain);

	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.

	ReleaseCOM(m_renderTargetView);
	ReleaseCOM(m_depthStencilView);
	ReleaseCOM(m_depthStencilBuffer);


	// Resize the swap chain and recreate the render target GetProjMatrix.

	HR(m_swapChain->ResizeBuffers(1, m_clientWidth, m_clientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* l_backBuffer;
	HR(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&l_backBuffer)));
	HR(m_d3dDevice->CreateRenderTargetView(l_backBuffer, 0, &m_renderTargetView));
	ReleaseCOM(l_backBuffer);

	// Create the depth/stencil buffer and GetProjMatrix.

	D3D11_TEXTURE2D_DESC l_depthStencilDesc;
	
	l_depthStencilDesc.Width     = m_clientWidth;
	l_depthStencilDesc.Height    = m_clientHeight;
	l_depthStencilDesc.MipLevels = 1;
	l_depthStencilDesc.ArraySize = 1;
	l_depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Use 4X MSAA? --must match swap chain MSAA values.
	if( m_enable4xMsaa )
	{
		l_depthStencilDesc.SampleDesc.Count   = 4;
		l_depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality-1;
	}
	// No MSAA
	else
	{
		l_depthStencilDesc.SampleDesc.Count   = 1;
		l_depthStencilDesc.SampleDesc.Quality = 0;
	}

	l_depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	l_depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	l_depthStencilDesc.CPUAccessFlags = 0; 
	l_depthStencilDesc.MiscFlags      = 0;

	HR(m_d3dDevice->CreateTexture2D(&l_depthStencilDesc, 0, &m_depthStencilBuffer));
	HR(m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, 0, &m_depthStencilView));


	// Bind the render target GetProjMatrix and depth/stencil GetProjMatrix to the pipeline.

	m_d3dImmediateContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	

	// Set the viewport transform.

	m_screenViewport.TopLeftX = 0;
	m_screenViewport.TopLeftY = 0;
	m_screenViewport.Width    = static_cast<float>(m_clientWidth);
	m_screenViewport.Height   = static_cast<float>(m_clientHeight);
	m_screenViewport.MinDepth = 0.0f;
	m_screenViewport.MaxDepth = 1.0f;

	m_d3dImmediateContext->RSSetViewports(1, &m_screenViewport);
}
 
LRESULT D3DApp::MsgProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
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
			m_timer.Stop();
		}
		else
		{
			m_appPaused = false;
			m_timer.Start();
		}
		return 0;

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

	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_appPaused = true;
		m_resizing  = true;
		m_timer.Stop();
		return 0;

	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		m_appPaused = false;
		m_resizing  = false;
		m_timer.Start();
		OnResize();
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

	// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)p_lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)p_lParam)->ptMinTrackSize.y = 200; 
		return 0;

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
	}

	return DefWindowProc(p_hwnd, p_msg, p_wParam, p_lParam);
}


bool D3DApp::InitMainWindow()
{
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
	l_wc.lpszClassName = L"D3DWndClassName";

	if( !RegisterClass(&l_wc) )
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT l_r = { 0, 0, m_clientWidth, m_clientHeight };
    AdjustWindowRect(&l_r, WS_OVERLAPPEDWINDOW, false);
	int l_width  = l_r.right - l_r.left;
	int l_height = l_r.bottom - l_r.top;

	m_hMainWnd = CreateWindow(L"D3DWndClassName", m_mainWndCaption.c_str(), 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, l_width, l_height, 0, 0, m_hAppInst, 0); 
	if( !m_hMainWnd )
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

	return true;
}

bool D3DApp::InitDirect3D()
{
	// Create the device and device context.

	UINT l_createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    l_createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL l_featureLevel;
	HRESULT hr = D3D11CreateDevice(
			0,                 // default adapter
			m_d3dDriverType,
			0,                 // no software device
			l_createDeviceFlags, 
			0, 0,              // default feature level array
			D3D11_SDK_VERSION,
			&m_d3dDevice,
			&l_featureLevel,
			&m_d3dImmediateContext);

	if( FAILED(hr) )
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if( l_featureLevel != D3D_FEATURE_LEVEL_11_0 )
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	HR(m_d3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));
	assert( m_4xMsaaQuality > 0 );

	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

	DXGI_SWAP_CHAIN_DESC l_sd;
	l_sd.BufferDesc.Width  = m_clientWidth;
	l_sd.BufferDesc.Height = m_clientHeight;
	l_sd.BufferDesc.RefreshRate.Numerator = 60;
	l_sd.BufferDesc.RefreshRate.Denominator = 1;
	l_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	l_sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	l_sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Use 4X MSAA? 
	if( m_enable4xMsaa )
	{
		l_sd.SampleDesc.Count   = 4;
		l_sd.SampleDesc.Quality = m_4xMsaaQuality-1;
	}
	// No MSAA
	else
	{
		l_sd.SampleDesc.Count   = 1;
		l_sd.SampleDesc.Quality = 0;
	}

	l_sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	l_sd.BufferCount  = 1;
	l_sd.OutputWindow = m_hMainWnd;
	l_sd.Windowed     = true;
	l_sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	l_sd.Flags        = 0;

	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory instance
	// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
	// This function is being called with a device from a different IDXGIFactory."

	IDXGIDevice* l_dxgiDevice = 0;
	HR(m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&l_dxgiDevice));
	      
	IDXGIAdapter* l_dxgiAdapter = 0;
	HR(l_dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&l_dxgiAdapter));

	IDXGIFactory* l_dxgiFactory = 0;
	HR(l_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&l_dxgiFactory));

	HR(l_dxgiFactory->CreateSwapChain(m_d3dDevice, &l_sd, &m_swapChain));
	
	ReleaseCOM(l_dxgiDevice);
	ReleaseCOM(l_dxgiAdapter);
	ReleaseCOM(l_dxgiFactory);

	// The remaining steps that need to be carried out for d3d creation
	// also need to be executed every time the window is resized.  So
	// just call the OnResize method here to avoid code duplication.
	
	OnResize();

	return true;
}

void D3DApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int l_frameCnt = 0;
	static float l_timeElapsed = 0.0f;

	l_frameCnt++;

	// Compute averages over one second period.
	if( (m_timer.TotalTime() - l_timeElapsed) >= 1.0f )
	{
		float l_fps = (float)l_frameCnt; // l_fps = l_frameCnt / 1
		float l_mspf = 1000.0f / l_fps;

		std::wostringstream l_outs;   
		l_outs.precision(6);
		l_outs << m_mainWndCaption << L"    "
			 << L"FPS: " << l_fps << L"    " 
			 << L"Frame Time: " << l_mspf << L" (ms)";
		SetWindowText(m_hMainWnd, l_outs.str().c_str());
		
		// Reset for next average.
		l_frameCnt = 0;
		l_timeElapsed += 1.0f;
	}
}


