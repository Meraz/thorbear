#include "RenderComponentLinux.h"

#include <cstdarg>
#include <vector>
#include <cstdio>

// Required for stringf below
std::string vformat( const char *fmt, va_list ap )
{
    // Allocate a buffer on the stack that's big enough for us almost
    // all the time.  Be prepared to allocate dynamically if it doesn't fit.
    size_t size = 1024;
    char stackbuf[ 1024 ];
    std::vector<char> dynamicbuf;
    char *buf = &stackbuf[ 0 ];

    while( 1 )
	{
        // Try to vsnprintf into our buffer.
        int needed = vsnprintf( buf, size, fmt, ap );
        // NB. C99 (which modern Linux and OS X follow) says vsnprintf
        // failure returns the length it would have needed.  But older
        // glibc and current Windows return -1 for failure, i.e., not
        // telling us how much was needed.

        if( needed <= ( int )size && needed >= 0 )
		{
            // It fit fine so we're done.
            return std::string( buf, ( size_t )needed );
        }

        // vsnprintf reported that it wanted to write more characters
        // than we allotted.  So try again using a dynamic buffer.  This
        // doesn't happen very often if we chose our initial size well.
        size = ( needed > 0 ) ? ( needed + 1 ) : ( size * 2 );
        dynamicbuf.resize( size );
        buf = &dynamicbuf[ 0 ];
    }
}

// Works just as printf, only that it returns the result as a string instead of printing it
inline std::string stringf( const char *fmt, ... )
{
    va_list ap;
    va_start( ap, fmt );
    std::string buf = vformat( fmt, ap );
    va_end( ap );
    return buf;
}

RenderComponentLinux::RenderComponentLinux()
{
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
	const GLubyte* l_renderer = glGetString( GL_RENDERER );
	const GLubyte* l_vendor = glGetString( GL_VENDOR );
	const GLubyte* l_version = glGetString( GL_VERSION );
	const GLubyte* l_glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );

	GLint l_major, l_minor;
	glGetIntegerv( GL_MAJOR_VERSION, &l_major );
	glGetIntegerv( GL_MINOR_VERSION, &l_minor );
  if( l_major < 4 )
  {
		glfwTerminate();
		return this->SetError( stringf( "ERROR: GL Version not supported: %d\n", l_major ) );
  }
		
	// enable some useful GL behaviours
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_MULTISAMPLE_ARB );

	// set colour to clear screen buffer to
	glClearColor( 0.f, 0.f, 1.f, 1.f );
	glFlush();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear buffer using colour
	
	glfwSetWindowTitle( "SpaceOut: OpenGL4 Test" );//l_windowTitle.c_str( ) );
	glfwSwapInterval( 1 ); // VSync on
	
	// set-up callbacks. we can also do a keyboard and mouse input callback, and various others (see freeGLUT website)
	//glfwSetWindowSizeCallback( ResizeCallback ); // register callback for reshape (if set earlier won't be called until an actual resize)
  return true;
}

void RenderComponentLinux::SetHints()
{
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 4 ); // set version of OpenGL to 4.0
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 0 );
	glfwOpenWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // do not allow deprecated
	//glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 16 ); // Multisampling, yay!
	//glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // force current version of spec
}

void RenderComponentLinux::RenderObject(BoundingBox p_boundingBox, TextureType p_textureType)
{

}

void RenderComponentLinux::RenderParticleSystem(ParticleSystem p_particleSystem)
{

}

void RenderComponentLinux::Render()
{

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