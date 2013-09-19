#include "RenderComponentLinux.h"

#include "OGL_Graphics/Camera.h"

#include <cstdarg>
#include <vector>
#include <cstdio>

#include "OGL_Graphics/glm/ext.hpp"

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
  
  // Get window size and set the viewport to match
  int l_windowWidth, l_windowHeight; // 800x600?
  glfwGetWindowSize( &l_windowWidth, &l_windowHeight );
  glViewport( 0, 0, l_windowWidth, l_windowHeight );
    
  m_genericShader.Init( "../resources/OGLShaders/genericVertex.glsl", "../resources/OGLShaders/genericFragment.glsl" );
  m_genericShader.Build( );
  m_genericShader.Use( );
  
  // Create and attach a camera
  static Camera l_cam;
  l_cam.SetPosition( glm::vec3( 0.f, 0.f, 0.f ) );
  l_cam.UpdateViewMatrix( );
  l_cam.SetClip( 5.f, 1000.f );
  l_cam.SetFoV( 45.f );
  //l_cam.UpdateProjectionMatrix( );
  m_genericShader.SetActiveCamera( l_cam );
  
  float vertices[] = {
      -100.f, -10.f, 100.f, 0.f, 0.f, 0.f, 0.f, 1.f,
      -100.f, -10.f, -100.f, 0.f, 0.f, 0.f, 0.f, 1.f,
      100.f, -10.f, -100.f, 0.f, 0.f, 0.f, 0.f, 1.f,
      100.f, -10.f, -100.f, 0.f, 0.f, 0.f, 0.f, 1.f,
      -100.f, -10.f, 100.f, 0.f, 0.f, 0.f, 0.f, 1.f,
      100.f, -10.f, 100.f, 0.f, 0.f, 0.f, 0.f, 1.f
    };
  GLuint l_vbo;
  glGenVertexArrays(1, &tmp_vao);
  glBindVertexArray(tmp_vao);
  
  glEnableVertexAttribArray( 0 ); // position
  glEnableVertexAttribArray( 1 ); // UV
  glEnableVertexAttribArray( 2 ); // normals
  
  glGenBuffers(1, &l_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, l_vbo);
  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid *)(sizeof(float)*3));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid *)(sizeof(float)*5));
	
  glBindVertexArray(0);
  
  glm::vec3 fwd = glm::vec3(0.f, 0.f, -1.f) * glm::mat3( m_genericShader.m_activeCamera->GetViewMatrix() );
  printf( "Forward is: %f, %f, %f\n", fwd[0], fwd[1], fwd[2] );
  
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
  // Create an object based on p_objectType (p_textureType)
  // Add the object to the list of objects to render
}

void RenderComponentLinux::RenderParticleSystem(ParticleSystem p_particleSystem)
{
  
}

void RenderComponentLinux::Render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear buffer using colour
  
  m_genericShader.Use( );
  
  // Render here
  m_genericShader.SetUniformMatrix( "modelMatrix", glm::mat4(1.f) );
  m_genericShader.UpdateUniform( );
  glBindVertexArray(tmp_vao);
  glDrawArrays( GL_TRIANGLES, 0, 6 );
  
  glfwSwapBuffers();
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