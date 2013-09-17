#include "WindowLinux.h"

#include <cstdio>
#include <cstdlib>

WindowLinux::WindowLinux()
	: WindowBaseClass()
{
  RenderComponentLinux* l_renderComponentInterface = new RenderComponentLinux();
  
  if( !l_renderComponentInterface->Init() )
  {
    printf( l_renderComponentInterface->GetErrorMessage() );
    exit(1);
  }
  
	m_gameInterface->Initialize(m_renderComponentInterface);
	m_renderComponentInterface = l_renderComponentInterface;
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