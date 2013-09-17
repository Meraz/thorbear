// Make sure you link: d3d11.lib d3dx11d.lib D3DCompiler.lib D3DX11EffectsD.lib 
//                     dxerr.lib dxgi.lib dxguid.lib.
// Link d3dx11.lib and D3DX11Effects.lib for release mode builds instead
//   of d3dx11d.lib and D3DX11EffectsD.lib.

#ifndef D3DAPP_H
#define D3DAPP_H

#include "d3dUtil.h"
#include "GameTimer.h"
#include <string>

class D3DApp
{
public:
	D3DApp(HINSTANCE p_hInstance);
	virtual ~D3DApp();
	
	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;
	
	int Run();
 
	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.

	virtual bool Init();
	virtual void OnResize(); 
	virtual void UpdateScene(float p_dt)=0;
	virtual void DrawScene()=0; 
	virtual LRESULT MsgProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam);

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM p_btnState, int p_x, int p_y){ }
	virtual void OnMouseUp(WPARAM p_btnState, int p_x, int p_y)  { }
	virtual void OnMouseMove(WPARAM p_btnState, int p_x, int p_y){ }

protected:
	bool InitMainWindow();
	bool InitDirect3D();

	void CalculateFrameStats();

protected:

	HINSTANCE m_hAppInst;
	HWND      m_hMainWnd;
	bool      m_appPaused;
	bool      m_minimized;
	bool      m_maximized;
	bool      m_resizing;
	UINT      m_4xMsaaQuality;

	GameTimer	m_timer;

	ID3D11Device*			m_d3dDevice;
	ID3D11DeviceContext*	m_d3dImmediateContext;
	IDXGISwapChain*			m_swapChain;
	ID3D11Texture2D*		m_depthStencilBuffer;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11DepthStencilView* m_depthStencilView;
	D3D11_VIEWPORT			m_screenViewport;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring	m_mainWndCaption;
	D3D_DRIVER_TYPE m_d3dDriverType;
	int				m_clientWidth;
	int				m_clientHeight;
	bool			m_enable4xMsaa;
};

#endif // D3DAPP_H