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

int WindowLinux::Run()
{
	return 0;
}


void WindowLinux::Update()
{
	// TODO Fix update variables here
	double l_deltaTime	   = 0.0;
	int l_mousePositionX = 0;
	int l_mousePositionY = 0;

	WindowBaseClass::Update(l_deltaTime, l_mousePositionX, l_mousePositionY, true);
}

void WindowLinux::Render()
{

	WindowBaseClass::Render();
}