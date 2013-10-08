#include "RenderComponentLinux.h"

#include "OGL_Graphics/Camera.h"

#include <cstdarg>
#include <vector>
#include <cstdio>
#include <cmath>

#define SCREEN_UNITS_X 1920
#define SCREEN_UNITS_Y 1080

#include "OGL_Graphics/glm/ext.hpp"

// Required for stringf below
std::string vformat( const char *p_fmt, va_list p_ap )
{
    // Allocate a buffer on the stack that's big enough for us almost
    // all the time.  Be prepared to allocate dynamically if it doesn't fit.
    size_t l_size = 1024;
    char l_stackBuf[ 1024 ];
    std::vector<char> l_dynamicBuf;
    char *l_buf = &l_stackBuf[ 0 ];

    while( 1 )
	{
        // Try to vsnprintf into our buffer.
        int l_needed = vsnprintf( l_buf, l_size, p_fmt, p_ap );
        // NB. C99 (which modern Linux and OS X follow) says vsnprintf
        // failure returns the length it would have needed.  But older
        // glibc and current Windows return -1 for failure, i.e., not
        // telling us how much was needed.

        if( l_needed <= ( int )l_size && l_needed >= 0 )
		{
            // It fit fine so we're done.
            return std::string( l_buf, ( size_t )l_needed );
        }

        // vsnprintf reported that it wanted to write more characters
        // than we allotted.  So try again using a dynamic buffer.  This
        // doesn't happen very often if we chose our initial size well.
        l_size = ( l_needed > 0 ) ? ( l_needed + 1 ) : ( l_size * 2 );
        l_dynamicBuf.resize( l_size );
        l_buf = &l_dynamicBuf[ 0 ];
    }
}

// Works just as printf, only that it returns the result as a string instead of printing it
inline std::string stringf( const char *p_fmt, ... )
{
    va_list l_ap;
    va_start( l_ap, p_fmt );
    std::string l_buf = vformat( p_fmt, l_ap );
    va_end( l_ap );
    return l_buf;
}

inline void GLCheckErrors( std::string p_where )
{
  int l_errCount = 0;
  for(GLenum currError = glGetError(); currError != GL_NO_ERROR; currError = glGetError())
  {
    //Do something with `currError`.
    printf( "OpenGL error #%d: %s.\n", currError, gluErrorString( currError ) );
    ++l_errCount;
  }
  if( l_errCount > 0 )
    printf( "%s: Total of %d OpenGL errors.\n", p_where.c_str(), l_errCount );
}

RenderComponentLinux::RenderComponentLinux()
{
  m_renderfirsttime = true;
}

RenderComponentLinux::~RenderComponentLinux()
{
}

bool RenderComponentLinux::Init()
{
	// Start GLEW (that's it! - we could also use GLEW to check for driver support of all GL extensions)
	glewExperimental = 1;
	GLenum l_err = glewInit( );
	if ( l_err != GLEW_OK )
	{
		glfwTerminate();
		return this->SetError( stringf( "ERROR starting GLEW: %s\n", glewGetErrorString( l_err ) ) );
	}

	// Get version info and print it to the console
	// const GLubyte* l_renderer = glGetString( GL_RENDERER );
	// const GLubyte* l_vendor = glGetString( GL_VENDOR );
	// const GLubyte* l_version = glGetString( GL_VERSION );
	// const GLubyte* l_glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );

	GLint l_major, l_minor;
	glGetIntegerv( GL_MAJOR_VERSION, &l_major );
	glGetIntegerv( GL_MINOR_VERSION, &l_minor );
  if( l_major < 4 )
  {
		glfwTerminate();
		return this->SetError( stringf( "ERROR: GL Version not supported: %d\n", l_major ) );
  }
  GLCheckErrors( "RenderComponentLinux::Init - Glew" );
		
	// enable some useful GL behaviours
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_MULTISAMPLE_ARB );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  
  GLCheckErrors( "RenderComponentLinux::Init - Options" );

	// set colour to clear screen buffer to
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glFlush();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear buffer using colour
  
  GLCheckErrors( "RenderComponentLinux::Init - Clear" );
	
	glfwSetWindowTitle( "SpaceOut: OpenGL4 Test" );//l_windowTitle.c_str( ) );
	glfwSwapInterval( 1 ); // 0: VSync off, 1: on
    
  m_genericShader.Init( SHADER_DIRECTORY + "genericVertex.glsl", SHADER_DIRECTORY + "genericFragment.glsl" );
  m_genericShader.Build( );
  m_genericShader.Use( );
  
  // Create and attach a camera
  static Camera l_cam;
  l_cam.SetPosition( glm::vec3( 300.f, 90.f, 500.f ) );
  l_cam.SetYawPitch( 0, 11.31f );
  l_cam.UpdateViewMatrix( );
  l_cam.SetClip( 10.f, 1000.f );
  l_cam.SetFoV( 45.f );
  //l_cam.UpdateProjectionMatrix( );
  m_genericShader.SetActiveCamera( l_cam );
  
  // Get window size and set the viewport to match
  int l_windowWidth, l_windowHeight; // 800x600?
  glfwGetWindowSize( &l_windowWidth, &l_windowHeight );
  UpdateViewportSize( l_windowWidth, l_windowHeight );
  
  glm::vec3 l_fwd = glm::vec3(0.f, 0.f, -1.f) * glm::mat3( m_genericShader.m_activeCamera->GetViewMatrix() );
  printf( "Debug info: Forward is towards %f, %f, %f\n", l_fwd[0], l_fwd[1], l_fwd[2] );
  
  GLCheckErrors( "RenderComponentLinux::Init" );
  
  m_modelManager.LoadModels();
  
  GLCheckErrors( "RenderComponentLinux::m_modelManager.LoadModels" );
    
  m_fontManager.Init();
  
  GLCheckErrors( "RenderComponentLinux::m_fontManager.Init" );
  
  return true;
}

void RenderComponentLinux::SetHints()
{
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 4 ); // set version of OpenGL to 4.0
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 0 );
	glfwOpenWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // do not allow deprecated
	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 16 ); // Multisampling, yay!
	//glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // force current version of spec
}

void RenderComponentLinux::RenderObject(BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color)
{
  // Create an object based on p_objectType (p_textureType)
  ModelInstance* l_modelInstance = m_modelManager.CreateInstance( p_boundingBox, p_textureType );
  l_modelInstance->SetTint( p_color );
  
  // Add the object to the list of objects to render
  //m_objectList.push_back( l_modelInstance );
  
  m_genericShader.Use( );
  if( m_renderfirsttime )
    GLCheckErrors( "RenderComponentLinux::RenderObject - m_genericShader.Use" );
  
  l_modelInstance->Render( m_genericShader );
    
  if( m_renderfirsttime )
    GLCheckErrors( "RenderComponentLinux::RenderObject - l_modelInstance.Render" );
    
  delete l_modelInstance;
}

void RenderComponentLinux::RenderParticleSystem(ParticleSystem p_particleSystem)
{
}

void RenderComponentLinux::RenderText(wstring p_text, float p_size, float p_posX, float p_posY, unsigned int p_color)
{
  m_fontManager.Draw( p_text, p_size, p_posX, p_posY, p_color );
}
  
void RenderComponentLinux::Render()
{
  // m_genericShader.Use( );
  // if( m_renderfirsttime )
    // GLCheckErrors( "RenderComponentLinux::m_genericShader.Use" );
  
  // Render all objects
  //for( int i = 0; i < m_objectList.size(); i++ )
  //  m_objectList[i]->Render( m_genericShader );
    
  //if( m_renderfirsttime )
  //  GLCheckErrors( "RenderComponentLinux::m_objectList[].Render" );
    
  // Text rendering here
  
  glfwSwapBuffers();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear buffer using colour
  
  // Clear the render object list for next frame
  //for( int i = 0; i < m_objectList.size(); i++ )
  //  delete m_objectList[i];
  //m_objectList.clear();
  
  if( m_renderfirsttime )
  {
    GLCheckErrors( "RenderComponentLinux::Render" );
    m_renderfirsttime = false;
  }
}

void RenderComponentLinux::UpdateViewportSize( int p_width, int p_height )
{
  glViewport( 0, 0, p_width, p_height );
  m_genericShader.m_activeCamera->SetResolution( p_width, p_height );
  m_genericShader.m_activeCamera->UpdateProjectionMatrix( );
}

std::string RenderComponentLinux::GetErrorMessage( )
{
  return this->m_errorMessage;
}

// Set the error message and return false to be returned further on for the error management
bool RenderComponentLinux::SetError( std::string p_errorMessage )
{
  this->m_errorMessage = p_errorMessage;
  
  return false;
}
