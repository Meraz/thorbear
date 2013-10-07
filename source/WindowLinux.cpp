#include "WindowLinux.h"

#include <cstdio>
#include <cstdlib>

extern inline std::string stringf( const char *p_fmt, ... );

WindowLinux* WindowLinux::m_windowLinux = NULL;

WindowLinux::WindowLinux()
	: WindowBaseClass()
{
  m_countFps = 0;
  m_lastFpsUpdate = 0;
  RenderComponentLinux* l_renderComponentLinux = new RenderComponentLinux();
  
  // Attempt to init the window
  if(! this->Init( l_renderComponentLinux ) )
  {
    printf( this->GetErrorMessage().c_str() );
    exit(1);
  }
  
  // Attempt to init the graphical rendering system
  if( !l_renderComponentLinux->Init() )
  {
    printf( l_renderComponentLinux->GetErrorMessage().c_str() );
    exit(1);
  }
  
	m_renderComponentInterface = l_renderComponentLinux;
	m_gameInterface->Initialize( m_renderComponentInterface );
  
  m_windowLinux = this;
  
	// TODO set-up callbacks. we can also do a keyboard and mouse input callback, and various others
	glfwSetWindowSizeCallback( ResizeCallback ); // register callback for reshape (if set earlier won't be called until an actual resize)
}

WindowLinux::~WindowLinux()
{
	delete m_gameInterface;
}

bool WindowLinux::Init( RenderComponentLinux *p_renderComponentLinux )
{
  // Init the GLFW for creation of the window
	if( !glfwInit() )
		return this->SetError( std::string( "ERROR: GLFW init\n" ) );
    
	// Get a list of supported video modes
	GLFWvidmode l_list[ 20 ];
	int l_numModes = glfwGetVideoModes( l_list, 20 );

	if( l_numModes < 1 )
		return this->SetError( std::string( "No desktop modes available!" ) );

  // The following code is for debugging purposes, to see the available window modes
	/*printf("Supported modes:\n");
	for (int i = 0; i < numModes; i++)
	{
		printf("\t %dx%d (%d, %d, %d)\n", list[i].Width, list[i].Height, list[i].RedBits, list[i].GreenBits, list[i].BlueBits);
	}*/

	// Pick the highest mode available
	int l_currentMode = l_numModes - 1;

  // The window creation requires hints to know the version of OpenGL to attempt to create
  p_renderComponentLinux->SetHints();

  // Attempt to open the window
	if( !glfwOpenWindow(
        l_list[ l_currentMode ].Width,
        l_list[ l_currentMode ].Height,
        l_list[ l_currentMode ].RedBits,
        l_list[ l_currentMode ].GreenBits,
        l_list[ l_currentMode ].BlueBits,
        0,
        0,
        0,
        GLFW_WINDOW
        //GLFW_FULLSCREEN
      )
    )
	{
		glfwTerminate();
		return this->SetError( std::string( "ERROR: creating load window\n" ) );
	}
  
  //glfwDisable( GLFW_MOUSE_CURSOR ); // Disable mouse cursor to prevent it from exiting screen
  
  m_oldTime = glfwGetTime();
  
  return true;
}

int WindowLinux::Run()
{
  while( glfwGetWindowParam(GLFW_OPENED) ) //3.x.x: !glfwWindowShouldClose(window)
  {
    this->Update();
    
    this->Render();
    
    glfwPollEvents();
  }
}

void WindowLinux::Update()
{
	// Fix update variables
  double l_newTime       = glfwGetTime();
	double l_deltaTime     = l_newTime - m_oldTime;
  m_oldTime              = l_newTime;
  
  m_countFps++;
  if( l_newTime - m_lastFpsUpdate >= 1 )
  {
    glfwSetWindowTitle( stringf( "SpaceOut: Linux Edition. Current FPS: %d.", m_countFps ).c_str() );
    m_lastFpsUpdate = l_newTime;
    m_countFps = 0;
  }
  
  int l_mousePositionX, l_mousePositionY;
  glfwGetMousePos( &l_mousePositionX, &l_mousePositionY );
  
  bool l_clicked = (glfwGetMouseButton( GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS);

	WindowBaseClass::Update(l_deltaTime, l_mousePositionX, l_mousePositionY, l_clicked);
  
  //glfwSleep( 1. / 60. - l_deltaTime - .01 ); // Limit UPS
}

void WindowLinux::Render()
{
	WindowBaseClass::Render();
  
  ((RenderComponentLinux*)m_renderComponentInterface)->Render();
}

void GLFWCALL WindowLinux::ResizeCallback( int p_width, int p_height )
{
  WindowLinux::m_windowLinux->UpdateViewportSize( p_width, p_height );
}
void WindowLinux::UpdateViewportSize( int p_width, int p_height )
{
  ((RenderComponentLinux*)m_renderComponentInterface)->UpdateViewportSize( p_width, p_height );
}

std::string WindowLinux::GetErrorMessage( )
{
  return this->m_errorMessage;
}

// Set the error message and return false to be returned further on for the error management
bool WindowLinux::SetError( std::string p_errorMessage )
{
  this->m_errorMessage = p_errorMessage;
  
  return false;
}