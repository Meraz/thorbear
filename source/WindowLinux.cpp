#include "WindowLinux.h"

#include <cstdio>
#include <cstdlib>

WindowLinux::WindowLinux()
	: WindowBaseClass()
{
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
  
	m_gameInterface->Initialize(m_renderComponentInterface);
	m_renderComponentInterface = l_renderComponentLinux;
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
        // GLFW_FULLSCREEN
      )
    )
	{
		glfwTerminate();
		return this->SetError( std::string( "ERROR: creating load window\n" ) );
	}
  
  return true;
}

#define NOTHING_BETTER_TO_DO glfwGetWindowParam(GLFW_OPENED) //3.x.x: !glfwWindowShouldClose(window)
#define GET_CANDY glfwPollEvents()
void WindowLinux::Run()
{
  while( NOTHING_BETTER_TO_DO )
  {
    m_renderComponentInterface->Render();
    
    GET_CANDY;
  }
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