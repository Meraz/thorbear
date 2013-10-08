#ifndef RENDERCOMPONENTWIN_H
#define RENDERCOMPONENTWIN_H

#include <vector>
#include "RenderComponentInterface.h"
#include "D3DX_Graphics\d3dUtil.h"
#include "D3DX_Graphics\ModelManager.h"
#include "D3DX_Graphics\ShaderManager.h"
#include "D3DX_Graphics\Camera.h"
#include "Vect3.h"
#include "ParticleSystem.h"

#include "FontRenderWin.h"

struct ObjTemplate
{
	ObjTemplate(Model* p_model, Shader* p_shader)
	{
		model = p_model;
		shader = p_shader;
	}

	~ObjTemplate()
	{
		//delete model;
		//delete shader;
	}

	Model*	model;
	Shader*	shader;  
};

class RenderComponentWin : public RenderComponentInterface
{
public:
	RenderComponentWin(HWND	p_hMainWnd);
	~RenderComponentWin();

	int Initialize();

	void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color = Vect3(1.0f, 1.0f, 1.0f));
	void CreateParticleEmitter(ParticleEmitterDesc p_particleDesc);
	void RenderParticleSystem(ParticleSystem p_particleSystem);
	void RenderText(string p_text, float p_size, float p_posX, float p_posY, unsigned int p_color, UINT FLAG);

	void RenderBackground(TextureType p_textureType);
	void CreateSplashText(wstring p_text, float p_size, float p_posX, float p_posY, float p_travelTime, float p_stillTime );

	void PreRender();
	void PostRender();

	void Update(float p_dt);
	BoundingBox ConvertIntoScreenSpace(BoundingBox p_boundingBox, TextureType p_textureType);


private:
	bool InitializeDirect3D();
	void Load();
	void CreateTemplates();

private:
	HWND					m_hMainWnd;
	ModelManager*			m_modelManager;
	ShaderManager*			m_shaderManager;
	Camera*					m_camera;

	ParticleSystem*			m_particleSystem;

	ID3D11Device*			m_d3dDevice;
	ID3D11DeviceContext*	m_d3dImmediateContext;
	IDXGISwapChain*			m_swapChain;
	ID3D11Texture2D*		m_depthStencilBuffer;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11DepthStencilView* m_depthStencilView;
	D3D11_VIEWPORT			m_screenViewport;

	std::wstring			m_mainWndCaption;
	D3D_DRIVER_TYPE			m_d3dDriverType;
	int						m_clientWidth;
	int						m_clientHeight;
	bool					m_enable4xMsaa;

	std::vector<ObjTemplate>	m_objVec;

	FontRenderWin*			m_fontRenderer;
};

#endif