#include "RenderComponentWin.h"
#include <cmath>

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
	delete m_fontRenderer;
	delete m_particleSystem;

	ReleaseCOM(m_d3dDevice);
	ReleaseCOM( m_d3dImmediateContext);
	ReleaseCOM( m_swapChain);
	ReleaseCOM( m_depthStencilBuffer);
	ReleaseCOM( m_renderTargetView);
	ReleaseCOM( m_depthStencilView);

	for (unsigned int i = 0; i < m_objVec.size(); i++)
	{
		delete m_objVec.at(i).instancedBuffer;	
	}
	m_objVec.clear();
}

int RenderComponentWin::Initialize()
{	
	m_clientWidth = 1920;
	m_clientHeight = 1080;
	InitializeDirect3D();

	m_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_modelManager = new ModelManager(m_d3dDevice, m_d3dImmediateContext);
	m_shaderManager = new ShaderManager();
	m_shaderManager->Init(m_d3dDevice, m_d3dImmediateContext);
	m_camera = new Camera();
	m_camera->SetLens(MathHelper::PI * 0.25f, (float)m_clientWidth/m_clientHeight, 0.5f, 1000.0f);

	m_camera->SetPos(300, 90, -500);

	Load();
	CreateTemplates();
	//ShowCursor(true);

	m_fontRenderer = new FontRenderWin();
	m_fontRenderer->Init(m_d3dDevice, L"Arial", m_d3dImmediateContext);

	m_particleSystem = new ParticleSystem(m_d3dDevice, m_d3dImmediateContext, m_modelManager, m_shaderManager, m_camera);

	return 0;
}

void RenderComponentWin::Update( float p_dt )
{
	m_camera->RebuildView();
	m_particleSystem->Update(p_dt);
	m_fontRenderer->Update(p_dt);

}

void RenderComponentWin::RenderObject(BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color)
{
	if(p_textureType == ENEMY1)
	{
		CreateInstancedWorldMatrix(p_boundingBox, p_textureType, p_color);
		return;
	}
	else if (p_textureType == ENEMY2)
	{
		CreateInstancedWorldMatrix(p_boundingBox, p_textureType, p_color);
		return;
	}
	else if(p_textureType == BALL)
	{
		CreateInstancedWorldMatrix(p_boundingBox, p_textureType, p_color);
		return;
	}
	
	Shader* l_shader = m_objVec.at((int)p_textureType).shader;
	Model*	l_model = m_objVec.at((int)p_textureType).model;

	D3DXMATRIX l_scaleMat;
	if(p_boundingBox.Height == -1 || p_boundingBox.Width == -1)
	{
		D3DXMatrixScaling(&l_scaleMat, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		float l_xScaleFactor = 1.0f/(l_model->m_topBoundingCorner.x - l_model->m_bottomBoundingCorner.x);
		float l_yScaleFactor = 1.0f/(l_model->m_topBoundingCorner.y - l_model->m_bottomBoundingCorner.y);
		l_xScaleFactor *= p_boundingBox.Width;
		l_yScaleFactor *= p_boundingBox.Height;

		if(p_boundingBox.Depth == -1)
		{
			D3DXMatrixScaling(&l_scaleMat, l_xScaleFactor, l_yScaleFactor, 1.0f);
		}
		else
		{
			float l_zScaleFactor = 1.0f/(l_model->m_topBoundingCorner.z - l_model->m_bottomBoundingCorner.z);
			l_zScaleFactor *= p_boundingBox.Depth;
			D3DXMatrixScaling(&l_scaleMat, l_xScaleFactor, l_yScaleFactor, l_zScaleFactor);
		}
	}
	
	// Translation matrix
	D3DXMATRIX l_translateMat;
	D3DXMatrixTranslation(&l_translateMat, p_boundingBox.PosX + (p_boundingBox.Width/2.0f), p_boundingBox.PosY + (p_boundingBox.Height/2.0f), p_boundingBox.PosZ);	// Create translation matrix

	D3DXMATRIX l_worldMat	= l_scaleMat *  l_translateMat;												
	D3DXMATRIX l_WVP		= l_worldMat * m_camera->GetViewMatrix() *  m_camera->GetProjMatrix();

	l_model->m_vertexBuffer->Apply(0);
	l_model->m_indexBuffer->Apply(0);

	l_shader->SetMatrix("gWorld", l_worldMat);
	l_shader->SetMatrix("gWVP", l_WVP);
	l_shader->SetResource("gTexture", l_model->m_material->m_textureResource);
	l_shader->SetFloat4("gColor", D3DXVECTOR4(p_color.r, p_color.g, p_color.b, 1.0f));


	D3DX11_TECHNIQUE_DESC techDesc;
	l_shader->GetTechnique()->GetDesc( &techDesc );
	for(int p = 0; p < (int)techDesc.Passes; ++p)
	{
		l_shader->Apply(p);
		m_d3dImmediateContext->DrawIndexed(l_model->m_size, 0, 0);
	}
}

void RenderComponentWin::CreateParticleEmitter(ParticleEmitterDesc p_particleDesc)
{
	m_particleSystem->CreateParticleEmitter(p_particleDesc);
}

void RenderComponentWin::PreRender()
{
	m_d3dImmediateContext->ClearRenderTargetView(m_renderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	m_d3dImmediateContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void RenderComponentWin::PostRender()
{
	RenderInstancedData(ENEMY1);
	RenderInstancedData(ENEMY2);
	RenderInstancedData(BALL);

	m_particleSystem->Render();
	m_fontRenderer->Render();
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

	unsigned int test = 0;
	m_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &test);

	DXGI_SWAP_CHAIN_DESC l_sd;
	l_sd.BufferDesc.Width  = m_clientWidth;//m_clientWidth;
	l_sd.BufferDesc.Height = m_clientHeight;//m_clientHeight;
	l_sd.BufferDesc.RefreshRate.Numerator = 60;
	l_sd.BufferDesc.RefreshRate.Denominator = 1;
	l_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	l_sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	l_sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	l_sd.SampleDesc.Count   = 4;
	l_sd.SampleDesc.Quality = test-1;

	l_sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	l_sd.BufferCount  = 1;
	l_sd.OutputWindow = m_hMainWnd;
	l_sd.Windowed     = (!NULL);
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

	//ReleaseCOM(m_renderTargetView);
	//ReleaseCOM(m_depthStencilView);
	//ReleaseCOM(m_depthStencilBuffer);

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
	l_depthStencilDesc.SampleDesc.Count   = 4;
	l_depthStencilDesc.SampleDesc.Quality = test-1;
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
	m_modelManager->CreateModel("invader.obj",	"object\\invader");
	m_modelManager->CreateModel("invader2.obj",		"object\\invader2");
	m_modelManager->CreateModel("cube.obj",		"object\\cube");
	m_modelManager->CreateModel("cube1.obj",	"object\\colorcube");

	m_modelManager->CreateModel("AddLifePowerup.obj",	"object\\AddLifePowerup");
	m_modelManager->CreateModel("AddBallPowerup.obj",	"object\\AddBallPowerup");
	m_modelManager->CreateModel("LargerPaddlePowerup.obj",	"object\\LargerPaddlePowerup");
	m_modelManager->CreateModel("SmallerPaddlePowerup.obj",	"object\\SmallerPaddlePowerup");
	m_modelManager->CreateModel("background.obj", "object\\levelBackground");
	m_modelManager->CreateModel("mainmenu.obj", "object\\mainmenu_background");

	m_modelManager->CreateModel("ButtonStart.obj", "object\\ButtonStart");
	m_modelManager->CreateModel("ButtonCampaign.obj", "object\\ButtonCampaign");
	m_modelManager->CreateModel("ButtonSurvival.obj", "object\\ButtonSurvival");
	m_modelManager->CreateModel("ButtonCampaignHS.obj", "object\\ButtonCampaignHS");
	m_modelManager->CreateModel("ButtonSurvivalHS.obj", "object\\ButtonSurvivalHS");
	m_modelManager->CreateModel("ButtonExit.obj", "object\\ButtonExit");
	m_modelManager->CreateModel("ButtonArrowUp.obj", "object\\ButtonArrowUp");
	m_modelManager->CreateModel("ButtonArrowDown.obj", "object\\ButtonArrowDown");
	m_modelManager->CreateModel("ButtonSave.obj", "object\\ButtonSave");
	m_modelManager->CreateModel("ButtonReturn.obj", "object\\ButtonReturn");

	//m_modelManager->CreateModel("")

	m_shaderManager->AddShader("effect\\object.fx", 12);	
	m_shaderManager->AddShader("effect\\background.fx", 12);
	m_shaderManager->AddShader("effect\\instanced.fx", 12);
	m_shaderManager->AddShader("effect\\instancedEnemy.fx", 12);

}

void RenderComponentWin::CreateTemplates()
{
	//m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("invader.obj"), m_shaderManager->GetShaderByName("effect\\object.fx")));
	//m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("invader2.obj"), m_shaderManager->GetShaderByName("effect\\object.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("invader.obj"), m_shaderManager->GetShaderByName("effect\\instancedEnemy.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("invader2.obj"), m_shaderManager->GetShaderByName("effect\\instancedEnemy.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("cube.obj"),	 m_shaderManager->GetShaderByName("effect\\instancedEnemy.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("cube1.obj"), m_shaderManager->GetShaderByName("effect\\object.fx")));

	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("AddLifePowerup.obj"), m_shaderManager->GetShaderByName("effect\\object.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("AddBallPowerup.obj"), m_shaderManager->GetShaderByName("effect\\object.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("LargerPaddlePowerup.obj"), m_shaderManager->GetShaderByName("effect\\object.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("SmallerPaddlePowerup.obj"), m_shaderManager->GetShaderByName("effect\\object.fx")));

	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("background.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));

	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("mainmenu.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));

	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonStart.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonCampaign.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonSurvival.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonCampaignHS.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonSurvivalHS.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonExit.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonArrowUp.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonArrowDown.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonSave.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));
	m_objVec.push_back(ObjTemplate(m_modelManager->GetModelByName("ButtonReturn.obj"), m_shaderManager->GetShaderByName("effect\\background.fx")));


	for (unsigned int i = 0; i < m_objVec.size(); i++)
	{
		m_objVec.at(i).instancedBuffer->Init(m_d3dDevice, m_d3dImmediateContext, m_objVec.at(i).bdInstance);
	}
	
}

BoundingBox RenderComponentWin::ConvertIntoScreenSpace( BoundingBox p_boundingBox, TextureType p_textureType)
{		
	D3DXMATRIX l_WVP		= /*l_worldMat */ m_camera->GetViewMatrix() *  m_camera->GetProjMatrix();

	D3DXVECTOR4 l_point = D3DXVECTOR4 ( p_boundingBox.PosX + (p_boundingBox.Width/2.0f), p_boundingBox.PosY + (p_boundingBox.Height/2.0f), p_boundingBox.PosZ, 1.0 );
	
	D3DXVec4Transform(&l_point,&l_point, &l_WVP);
	
	D3DXVECTOR3 l_point2;
	l_point2.x = l_point.x / l_point.w;
	l_point2.y = l_point.y / l_point.w;
	l_point2.z = l_point.z / l_point.w;

	D3DXVECTOR2 l_point3;
	l_point3.x = ((l_point2.x + 1.0) / 2.0) * m_clientWidth;
	l_point3.y = ((l_point2.y + 1.0) / 2.0) * m_clientHeight;

	BoundingBox l_boundingBox;
	l_boundingBox.PosX = l_point3.x - p_boundingBox.Width/1.5f;
	l_boundingBox.PosY = m_clientHeight - (l_point3.y + p_boundingBox.Height/2);
	l_boundingBox.Width = p_boundingBox.Width * 1.3f;
	l_boundingBox.Height = p_boundingBox.Height * 1.3f;
	l_boundingBox.Depth = p_boundingBox.Depth;
	
	return l_boundingBox;
}

void RenderComponentWin::CreateSplashText( wstring p_text, float p_size, float p_posX, float p_posY, float p_travelTime, float p_stillTime )
{
	m_fontRenderer->CreateSplashText(p_text, p_size, p_posX, p_posY, p_travelTime, p_stillTime);
}

// External method found on ze Internet that converts strings to wstrings
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void RenderComponentWin::RenderText(string p_text, float p_size, float p_posX, float p_posY, unsigned int p_color)
{

	m_fontRenderer->RenderText(s2ws(p_text).c_str(), p_size, p_posX, p_posY, p_color);
}

void RenderComponentWin::RenderBackground(TextureType p_textureType)
{
	Shader* l_shader = m_objVec.at((int)p_textureType).shader;
	Model*	l_model = m_objVec.at((int)p_textureType).model;

	D3DXMATRIX l_scaleMat;

	float l_xScaleFactor = 1.0f/(l_model->m_topBoundingCorner.x - l_model->m_bottomBoundingCorner.x);
	float l_yScaleFactor = 1.0f/(l_model->m_topBoundingCorner.y - l_model->m_bottomBoundingCorner.y);
	l_xScaleFactor *= 1600; //TODO do not hard code this
	l_yScaleFactor *= 1000; //TODO do not hard code this

	float l_zScaleFactor = 1.0f;

	D3DXMatrixScaling(&l_scaleMat, l_xScaleFactor, -l_yScaleFactor, l_zScaleFactor);


	// Translation matrix
	D3DXMATRIX l_translateMat;
	D3DXMatrixTranslation(&l_translateMat, 330, 300, 400);	// Create translation matrix

	D3DXMATRIX l_rotationMat;
	D3DXMatrixRotationX(&l_rotationMat, atan(0.2f));

	D3DXMATRIX l_worldMat	= l_rotationMat * l_scaleMat *  l_translateMat;
	D3DXMATRIX l_WVP		= l_worldMat * m_camera->GetViewMatrix() *  m_camera->GetProjMatrix();

	l_model->m_vertexBuffer->Apply(0);
	l_model->m_indexBuffer->Apply(0);

	l_shader->SetMatrix("gWorld", l_worldMat);
	l_shader->SetMatrix("gWVP", l_WVP);
	l_shader->SetResource("gTexture", l_model->m_material->m_textureResource);
	l_shader->SetFloat4("gColor", D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));


	D3DX11_TECHNIQUE_DESC techDesc;
	l_shader->GetTechnique()->GetDesc( &techDesc );
	for(int p = 0; p < (int)techDesc.Passes; ++p)
	{
		l_shader->Apply(p);
		m_d3dImmediateContext->DrawIndexed(l_model->m_size, 0, 0);
	}
}

void RenderComponentWin::CreateInstancedWorldMatrix( BoundingBox p_boundingBox, TextureType p_type, Vect3 p_color )
{
	Model*	l_model = m_objVec.at((int)p_type).model;

	D3DXMATRIX l_scaleMat;
	if(p_boundingBox.Height == -1 || p_boundingBox.Width == -1)
	{
		D3DXMatrixScaling(&l_scaleMat, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		float l_xScaleFactor = 1.0f/(l_model->m_topBoundingCorner.x - l_model->m_bottomBoundingCorner.x);
		float l_yScaleFactor = 1.0f/(l_model->m_topBoundingCorner.y - l_model->m_bottomBoundingCorner.y);
		l_xScaleFactor *= p_boundingBox.Width;
		l_yScaleFactor *= p_boundingBox.Height;

		if(p_boundingBox.Depth == -1)
		{
			D3DXMatrixScaling(&l_scaleMat, l_xScaleFactor, l_yScaleFactor, 1.0f);
		}
		else
		{
			float l_zScaleFactor = 1.0f/(l_model->m_topBoundingCorner.z - l_model->m_bottomBoundingCorner.z);
			l_zScaleFactor *= p_boundingBox.Depth;
			D3DXMatrixScaling(&l_scaleMat, l_xScaleFactor, l_yScaleFactor, l_zScaleFactor);
		}
	}

	// Translation matrix
	D3DXMATRIX l_translateMat;
	D3DXMatrixTranslation(&l_translateMat, p_boundingBox.PosX + (p_boundingBox.Width/2.0f), p_boundingBox.PosY + (p_boundingBox.Height/2.0f), p_boundingBox.PosZ);	// Create translation matrix

	D3DXMATRIX l_worldMat = l_scaleMat *  l_translateMat;

	//Enter color into instancematrix
	l_worldMat._14 = p_color.r;
	l_worldMat._24 = p_color.g;
	l_worldMat._34 = p_color.b;

	m_objVec.at((int)p_type).matrixList.push_back(l_worldMat);
}

void RenderComponentWin::RenderInstancedData( TextureType p_type )
{
	Shader*		l_shader;
	Model*		l_model;

	if(m_objVec.at((int)p_type).matrixList.size() > 0)
	{
		l_shader = m_objVec.at((int)p_type).shader;
		l_model = m_objVec.at((int)p_type).model;

		D3DXMATRIX* verticesPtr;

		D3D11_MAPPED_SUBRESOURCE l_mapped;
		m_d3dImmediateContext->Map(m_objVec.at((int)p_type).instancedBuffer->GetBufferPointer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &l_mapped);

		// Get a pointer to the data in the vertex buffer.
		verticesPtr = (D3DXMATRIX*)l_mapped.pData;  

		// Copy the data into the vertex buffer.
		memcpy(verticesPtr, (void*)m_objVec.at((int)p_type).matrixList[0], (sizeof(D3DXMATRIX) * m_objVec.at((int)p_type).matrixList.size()));

		// Unlock the vertex buffer.
		m_d3dImmediateContext->Unmap(m_objVec.at((int)p_type).instancedBuffer->GetBufferPointer(), 0);

		l_model->m_vertexBuffer->ApplyInstanced(0, m_objVec.at((int)p_type).instancedBuffer);
		l_model->m_indexBuffer->Apply(0);

		l_shader->SetMatrix("gVP", m_camera->GetViewMatrix()*m_camera->GetProjMatrix());

		D3DX11_TECHNIQUE_DESC techDesc;
		l_shader->GetTechnique()->GetDesc( &techDesc );
		for(int p = 0; p < (int)techDesc.Passes; ++p)
		{
			l_shader->Apply(p);
			m_d3dImmediateContext->DrawIndexedInstanced(l_model->m_size, m_objVec.at((int)p_type).matrixList.size(), 0, 0, 0);
		}
		m_objVec.at((int)p_type).matrixList.clear();
	}
}

void RenderComponentWin::SetShowCursor( bool p_showCursor )
{
	ShowCursor(p_showCursor);
}

