#include "RenderComponentWin.h"


RenderComponentWin::RenderComponentWin(HWND p_hMainWnd)
{	
	m_hMainWnd = p_hMainWnd;
	m_objVec = std::vector<ObjTemplate>();	
}

RenderComponentWin::~RenderComponentWin()
{
	delete m_modelManager;
	delete m_shaderManager;
	delete m_camera;
	
	ReleaseCOM(m_d3dDevice);
	ReleaseCOM( m_d3dImmediateContext);
	ReleaseCOM( m_swapChain);
	ReleaseCOM( m_depthStencilBuffer);
	ReleaseCOM( m_renderTargetView);
	ReleaseCOM( m_depthStencilView);

	m_objVec.clear();
}

int RenderComponentWin::Initialize()
{	
	m_clientWidth = 800;
	m_clientHeight = 600;
	InitializeDirect3D();

	m_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_modelManager = new ModelManager(m_d3dDevice, m_d3dImmediateContext);
	m_shaderManager = new ShaderManager();
	m_shaderManager->Init(m_d3dDevice, m_d3dImmediateContext);
	m_camera = new Camera();
	m_camera->SetLens(MathHelper::Pi * 0.25f, m_clientWidth/m_clientHeight, 0.5f, 1000.0f);
	m_camera->SetPos(0, 0, -80);

	Load();
	CreateTemplates();

	return 0;
}

void RenderComponentWin::RenderObject(BoundingBox p_boundingBox, TextureType p_textureType)
{
	Shader* l_shader = m_objVec.at((int)p_textureType).shader;
	Model*	l_model = m_objVec.at((int)p_textureType).model;

	m_camera->RebuildView();
	// Scale matrix
	D3DXMATRIX l_scaleMat;
	D3DXMatrixIdentity(&l_scaleMat);

	// Translation matrix
	D3DXMATRIX l_translateMat;
	D3DXMatrixTranslation(&l_translateMat, p_boundingBox.farTopLeftX, p_boundingBox.farTopLeftY, 0);	// Create translation matrix

	D3DXMATRIX l_worldMat	= l_scaleMat *  l_translateMat;												// 
	D3DXMATRIX l_WVP		= l_worldMat * m_camera->GetViewMatrix() *  m_camera->GetProjMatrix();

	l_model->m_vertexBuffer->Apply(0);
	l_model->m_indexBuffer->Apply(0);

	l_shader->SetMatrix("gWorld", l_worldMat);
	l_shader->SetMatrix("gWVP", l_WVP);
	l_shader->SetResource("gTexture", l_model->m_material->m_textureResource);


	D3DX11_TECHNIQUE_DESC techDesc;
	l_shader->GetTechnique()->GetDesc( &techDesc );
	for(int p = 0; p < (int)techDesc.Passes; ++p)
	{
		l_shader->Apply(p);
		m_d3dImmediateContext->DrawIndexed(l_model->m_size, 0, 0);
	}
}

void RenderComponentWin::RenderParticleSystem(ParticleSystem p_particleSystem)
{

}

void RenderComponentWin::PreRender()
{
	m_d3dImmediateContext->ClearRenderTargetView(m_renderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	m_d3dImmediateContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void RenderComponentWin::PostRender()
{
	HR(m_swapChain->Present(0, 0));
}

bool RenderComponentWin::InitializeDirect3D()
{
	// Create the device and device context.

	UINT l_createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	l_createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL l_featureLevel;
	m_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
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

	DXGI_SWAP_CHAIN_DESC l_sd;
	l_sd.BufferDesc.Width  = m_clientWidth;//m_clientWidth;
	l_sd.BufferDesc.Height = m_clientHeight;//m_clientHeight;
	l_sd.BufferDesc.RefreshRate.Numerator = 60;
	l_sd.BufferDesc.RefreshRate.Denominator = 1;
	l_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	l_sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	l_sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	l_sd.SampleDesc.Count   = 1;
	l_sd.SampleDesc.Quality = 0;

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
	l_depthStencilDesc.SampleDesc.Count   = 1;
	l_depthStencilDesc.SampleDesc.Quality = 0;
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

	return true;
}

void RenderComponentWin::Load()
{
	m_modelManager->CreateModel("invader.obj",	"J:\\thorbear\\DX11\\Invader");
	m_modelManager->CreateModel("bth.obj",		"J:\\thorbear\\DX11\\BTH");
	m_modelManager->CreateModel("cube.obj",		"J:\\thorbear\\DX11\\CUBE");
	m_modelManager->CreateModel("cube1.obj",	"J:\\thorbear\\DX11\\ColorCUBE");

	m_shaderManager->AddShader("J:\\thorbear\\source\\object.fx", 12);	
}

void RenderComponentWin::CreateTemplates()
{
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("invader.obj"), m_shaderManager->GetShaderByName("object.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("bth.obj"), m_shaderManager->GetShaderByName("object.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("cube.obj"),	 m_shaderManager->GetShaderByName("object.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("cube1.obj"), m_shaderManager->GetShaderByName("object.fx")));
}




