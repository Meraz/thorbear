#include "WindowBaseClass.h"


WindowBaseClass::WindowBaseClass()
{
	m_gameInterface = new Game();
}


WindowBaseClass::~WindowBaseClass()
{
	delete m_gameInterface;
}

void WindowBaseClass::Render()
{
	m_gameInterface->Render();
}

void WindowBaseClass::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY)
{
	m_gameInterface->Update(p_deltaTime, p_mousePositionX, p_mousePositionY);
}