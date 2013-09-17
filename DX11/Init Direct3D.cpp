
#include "d3dApp.h"
#include "ShaderManager.h"
#include "ObjManager.h"
#include "ModelManager.h"
#include "Camera.h"


class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE p_hInstance);
	~InitDirect3DApp();

	bool Init();
	void OnResize();
	void UpdateScene(float p_dt);
	void DrawScene(); 

	ShaderManager*	m_shaderManager;
	ObjManager*		m_objManager;
	ModelManager*	m_modelManager;
	Camera*			m_camera;
};




int WINAPI WinMain(HINSTANCE p_hInstance, HINSTANCE p_prevInstance,
				   PSTR p_cmdLine, int p_showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	InitDirect3DApp theApp(p_hInstance);
	
	if( !theApp.Init() )
		return 0;
	
	

	return theApp.Run();
}

InitDirect3DApp::InitDirect3DApp(HINSTANCE p_hInstance)
: D3DApp(p_hInstance) 
{
}

InitDirect3DApp::~InitDirect3DApp()
{
}

bool InitDirect3DApp::Init()
{
	if(!D3DApp::Init())
		return false;

	m_shaderManager = NULL;
	m_objManager	= NULL;
	m_modelManager	= NULL;
	m_camera		= NULL;

	m_camera = new Camera();
	m_camera->SetPos(0, 40, -170);
	m_shaderManager = new ShaderManager();
	m_shaderManager->Init(m_d3dDevice, m_d3dImmediateContext);
	m_modelManager = new ModelManager(m_d3dDevice, m_d3dImmediateContext);
	m_objManager = new ObjManager(m_d3dDevice, m_d3dImmediateContext, m_modelManager, m_shaderManager);
	
	m_modelManager->CreateModel("invader.obj", "C:\\Users\\KevLaptop\\Documents\\Visual Studio 2012\\Projects\\DX11\\DX11\\INVADER");
	m_modelManager->CreateModel("cube.obj", "C:\\Users\\KevLaptop\\Documents\\Visual Studio 2012\\Projects\\DX11\\DX11\\CUBE");
	m_modelManager->CreateModel("cube1.obj", "C:\\Users\\KevLaptop\\Documents\\Visual Studio 2012\\Projects\\DX11\\DX11\\ColorCUBE");

	
	m_objManager->AddObject(0, -20, 0, "cube.obj", "object.fx" );
	m_objManager->AddObject(0, -10, 0, "cube1.obj", "object.fx");

	for(int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m_objManager->AddObject(75 - i * 10, 60 + j*7, 0, "invader.obj", "object.fx");
		}
	}

	m_objManager->GetObjectAt(0)->SetScale(9.0f, 0.5f, 0.5f);
	m_objManager->GetObjectAt(1)->SetScale(0.5f, 0.5f, 0.5f);

	m_camera->SetLens(MathHelper::Pi*0.25f, AspectRatio(), 0.5f, 1000.0f);

	return true;
}

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();
}

void InitDirect3DApp::UpdateScene(float p_dt)
{
	if(m_objManager)
	{
		m_objManager->Update(p_dt);
	}

	if(m_camera)
	{
		m_camera->Update(p_dt);
	}	
}

void InitDirect3DApp::DrawScene()
{
	assert(m_d3dImmediateContext);
	assert(m_swapChain);

	m_d3dImmediateContext->ClearRenderTargetView(m_renderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	m_d3dImmediateContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	if(m_objManager)
		m_objManager->Draw(m_camera->GetViewMatrix(), m_camera->GetProjMatrix(), m_camera->GetPos());

	HR(m_swapChain->Present(0, 0));
}
