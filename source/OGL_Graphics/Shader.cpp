#include "Shader.h"

#include <GL/glfw.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "glm/ext.hpp"

extern std::string stringf( const char *p_fmt, ... );
extern void GLCheckErrors( std::string p_where );

void CompileShader( GLuint& p_shaderHandle, const char* p_shaderFileName, const int& p_type );

void Shader::Init( std::string p_vertFileName, std::string p_fragFileName )
{
  Init( p_vertFileName.c_str(), p_fragFileName.c_str() );
}

void Shader::Init( const char* p_vertFileName, const char* p_fragFileName, const char* p_gsFileName, const char* p_tessConFileName, const char* p_tessEvalFileName )
{
	if( p_vertFileName == NULL )
		printf( "Shader error: Shader must have a vertex shader" );
	
	CompileShader( m_subhandles[ VertShader ], p_vertFileName, GL_VERTEX_SHADER );
  GLCheckErrors( "Shader::Init - GL_VERTEX_SHADER" );

	if( p_gsFileName != NULL )
  {
		CompileShader( m_subhandles[ GeomShader ], p_gsFileName, GL_GEOMETRY_SHADER );
    GLCheckErrors( "Shader::Init - GL_GEOMETRY_SHADER" );
  }

	if( p_tessConFileName != NULL )
	{
		glPatchParameteri( GL_PATCH_VERTICES, 3 );
		CompileShader( m_subhandles[ TConShader ], p_tessConFileName, GL_TESS_CONTROL_SHADER );
    GLCheckErrors( "Shader::Init - GL_TESS_CONTROL_SHADER" );
	}

	if( p_tessEvalFileName != NULL )
  {
		CompileShader( m_subhandles[ TEvalShader ], p_tessEvalFileName, GL_TESS_EVALUATION_SHADER );
    GLCheckErrors( "Shader::Init - GL_TESS_EVALUATION_SHADER" );
  }
	
	if( p_fragFileName != NULL )
  {
		CompileShader( m_subhandles[ FragShader ], p_fragFileName, GL_FRAGMENT_SHADER );
    GLCheckErrors( "Shader::Init - GL_FRAGMENT_SHADER" );
  }

	m_handle = glCreateProgram( );

	if( m_handle == 0 )
		printf( "ERROR creating shader programme\n" );
	
	// attach shaders
	for( unsigned i = 0; i < COUNT; i++ )
    if( m_subhandles[ i ] > 0 )
      glAttachShader( m_handle, m_subhandles[ i ] );
  GLCheckErrors( "Shader::Init" );
}

void Shader::Build( )
{
	CreateProgram( );
  GLCheckErrors( "Shader::Build" );
}

//static Shader* tmp = 0;

//void TmpUse( Shader* _shader )
//{
//	tmp = activeShader;
//	_shader->Use( );
//}
//void TmpReset( )
//{
//	/*if (tmp != NULL)
//		tmp->Use( );*/
//}

Shader* Shader::m_activeShader = 0;
void Shader::Use( )
{
	if( m_activeShader != this )
	{
		glUseProgram(m_handle);
		m_activeShader = this;
	}
  GLCheckErrors( "Shader::Use" );
}

void Shader::BindAttribLocation( GLuint p_location, const char* p_name )
{
	glBindAttribLocation( m_handle, p_location, p_name);
  GLCheckErrors( "Shader::BindAttribLocation" );
}

void Shader::SetUniformInt( const char* p_name, int p_val )
{
	glUniform1i( GetUniformLocation( p_name ), p_val );
}
void Shader::SetUniformFloat( const char* p_name, float p_val )
{
	glUniform1f( GetUniformLocation( p_name ), p_val );
}
void Shader::SetUniformVector( const char* p_name, glm::vec3 p_val )
{
	glUniform3fv( GetUniformLocation( p_name ), 1, &p_val[0] );
}
void Shader::SetUniformVector( const char* p_name, glm::vec4 p_val )
{
	glUniform4fv( GetUniformLocation( p_name ), 1, &p_val[0] );
}
void Shader::SetUniformMatrix( const char* p_name, glm::mat3 p_val )
{
	glUniformMatrix3fv( GetUniformLocation( p_name ), 1, GL_FALSE, &p_val[0][0] );
}
void Shader::SetUniformMatrix( const char* p_name, glm::mat4 p_val )
{
	glUniformMatrix4fv( GetUniformLocation( p_name ), 1, GL_FALSE, &p_val[0][0] );
}

void Shader::CreateProgram( )
{
	// link programme
	glLinkProgram( m_handle );
	
	// verify link status
	GLint l_status;
	glGetProgramiv( m_handle, GL_LINK_STATUS, &l_status );

	if( l_status != GL_TRUE )
	{
		std::string l_error( "ERROR: failed to link shader programme\n" );
		int l_length = 200;
		//glGetShaderiv( handle, GL_INFO_LOG_LENGTH, &length );
		if( l_length > 0 )
		{
			// create a log of error messages
			char* l_errorLog = new char[ l_length ];
			int l_written = 0;
			glGetProgramInfoLog( m_handle, l_length, &l_written, l_errorLog );
			printf( "%s", (l_error + stringf( "Shader error log:\n%s\n", l_errorLog )).c_str() );
			delete[ ] l_errorLog;
		}
		printf( "%s", l_error.c_str() );
	}
  GLCheckErrors( "Shader::CreateProgram" );
}

void CompileShader( GLuint& p_shaderHandle, const char* p_shaderFileName, const int& p_type )
{
	// load file into string
	std::ifstream l_file;

	l_file.open( p_shaderFileName );
	if( !l_file.is_open( ) )
  {
		printf( "ERROR opening shader file %s\n", p_shaderFileName );
    return;
  }

	// Get the size of the file
  l_file.seekg(0,std::ios::end);
  std::streampos l_length = l_file.tellg();
  l_file.seekg(0,std::ios::beg);

	// Use a vector as the buffer.
  std::vector< char > l_buffer( l_length );
  l_file.read( &l_buffer[ 0 ], l_length );

	//std::stringstream ss;
  std::string l_str( &l_buffer[ 0 ], l_length );

	// create shader object
	p_shaderHandle = glCreateShader( p_type );

	// validate creation
	if( p_shaderHandle == 0 )
		printf( "ERROR creating shader type %d\n", p_type );

	// load source from a char array
	const char* l_ptr = l_str.c_str( ); // get character pointer from string
	int l_len = (int)l_length;
	glShaderSource( p_shaderHandle, 1, &l_ptr, NULL );

	// compile shader
	glCompileShader( p_shaderHandle );

	// Check for errors
	int l_result = 0;
	glGetShaderiv( p_shaderHandle, GL_COMPILE_STATUS, &l_result );
	if( l_result != GL_TRUE )
	{
		std::string l_error = stringf( "ERROR compiling shader type %d\n", p_type );
		int l_length = 0;
		glGetShaderiv( p_shaderHandle, GL_INFO_LOG_LENGTH, &l_length );
		if( l_length > 0 )
		{
			// create a log of error messages
			char* l_errorLog = new char[ l_length ];
			int l_written = 0;
			glGetShaderInfoLog( p_shaderHandle, l_length, &l_written, l_errorLog );
			printf( "%s", (l_error + stringf( "Shader error log;\n%s\n", l_errorLog )).c_str() );
			delete[ ] l_errorLog;
		}
		printf( "%s", l_error.c_str() );
	}
  GLCheckErrors( "Shader::CompileShader" );
}

int Shader::GetUniformLocation( const char* p_name )
{
	this->Use( );

	int l_loc = glGetUniformLocation( m_handle, p_name );
#if DEBUG
	if( l_loc < 0 )
		printf( "Warning: Error receiving variable location '%s'\n", p_name );
#endif
	return l_loc;
  GLCheckErrors( "Shader::GetUniformLocation" );
}

void Shader::UpdateUniform( glm::mat4 p_modelMatrix )
{
  SetUniformMatrix( "modelMatrix", p_modelMatrix );
  SetUniformMatrix( "projectionMatrix", m_activeCamera->GetProjectionMatrix( ) );
  SetUniformMatrix( "viewMatrix", m_activeCamera->GetViewMatrix( ) );
  SetUniformMatrix( "modelViewMatrix", m_activeCamera->GetViewMatrix( ) * p_modelMatrix );
  SetUniformMatrix( "normalMatrix", glm::inverseTranspose( glm::mat3( m_activeCamera->GetViewMatrix( ) * p_modelMatrix ) ) );
  SetUniformVector( "lightPosition", glm::vec4( m_activeCamera->GetPosition( ), 1.f ) );
  //GLCheckErrors( "Shader::UpdateUniform" );
  while( glGetError() != GL_NO_ERROR ); // Clear GL errors due to non-existing variable locations
}

void Shader::SetActiveCamera( Camera& p_cam )
{
  m_activeCamera = &p_cam;
  
  // Get window size and adjust camera projection matrix to match
  int l_windowWidth, l_windowHeight;
  glfwGetWindowSize( &l_windowWidth, &l_windowHeight );
  m_activeCamera->SetResolution( l_windowWidth, l_windowHeight );
  
  m_activeCamera->UpdateProjectionMatrix( );
}
