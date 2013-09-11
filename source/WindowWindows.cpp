#include "WindowWindows.h"

WindowWindows::WindowWindows(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
	: WindowBaseClass()
{
	m_renderComponentInterface = new RenderComponentWin();
	m_gameInterface->Initialize(m_renderComponentInterface);
}

WindowWindows::~WindowWindows()
{
	delete m_renderComponentInterface;
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