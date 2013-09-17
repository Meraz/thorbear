#include "WindowLinux.h"

WindowLinux::WindowLinux()
	: WindowBaseClass()
{
	m_renderComponentInterface = new RenderComponentLinux();
	m_gameInterface->Initialize(m_renderComponentInterface);
}

WindowLinux::~WindowLinux()
{
	delete m_gameInterface;
}

void WindowLinux::Update()
{
	// TODO Fix update variables here
	double l_deltaTime	   = 0.0;
	float l_mousePositionX = 0.0f;
	float l_mousePositionY = 0.0f;

	WindowBaseClass::Update(l_deltaTime, l_mousePositionX, l_mousePositionY);
}

void WindowLinux::Render()
{

	WindowBaseClass::Render();
}