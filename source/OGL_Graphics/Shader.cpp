#include "Shader.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

extern inline std::string stringf( const char *fmt, ... );

void compileShader( GLuint& _shaderHandle, const char* _shaderFileName, const int& _type );

void Shader::Init( const char* _vertFileName, const char* _fragFileName, const char* _gsFileName, const char* _tessConFileName, const char* _tessEvalFileName )
{
	if( _vertFileName == NULL )
		throw "Shader error: Shader must have a vertex shader";
	
	compileShader( subhandles[ ShaderType::VertShader ], _vertFileName, GL_VERTEX_SHADER );

	if( _gsFileName != NULL )
		compileShader( subhandles[ ShaderType::GeomShader ], _gsFileName, GL_GEOMETRY_SHADER );

	if( _tessConFileName != NULL )
	{
		glPatchParameteri( GL_PATCH_VERTICES, 3 );
		compileShader( subhandles[ ShaderType::TConShader ], _tessConFileName, GL_TESS_CONTROL_SHADER );
	}

	if( _tessEvalFileName != NULL )
		compileShader( subhandles[ ShaderType::TEvalShader ], _tessEvalFileName, GL_TESS_EVALUATION_SHADER );
	
	if( _fragFileName != NULL )
		compileShader( subhandles[ ShaderType::FragShader ], _fragFileName, GL_FRAGMENT_SHADER );

	handle = glCreateProgram( );

	if( handle == 0 )
		throw "ERROR creating shader programme\n";
	
	// attach shaders
	for( unsigned i = 0; i < ShaderType::COUNT; i++ )
		glAttachShader( handle, subhandles[ i ] );
}

void Shader::Build( )
{
	CreateProgram( );
}

static Shader* activeShader = 0;
static Shader* tmp = 0;

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

void Shader::Use( )
{
	if( activeShader != this )
	{
		glUseProgram(handle);
		activeShader = this;
	}
}

void Shader::BindAttribLocation( GLuint _location, const char* _name )
{
	glBindAttribLocation( handle, _location, _name);
}

void Shader::SetUniformInt( const char* _name, int _val )
{
	glUniform1i( GetUniformLocation( _name ), _val );
}
void Shader::SetUniformFloat( const char* _name, float _val )
{
	glUniform1f( GetUniformLocation( _name ), _val );
}
void Shader::SetUniformVector( const char* _name, glm::vec3& _val )
{
	glUniform3fv( GetUniformLocation( _name ), 1, &_val[0] );
}
void Shader::SetUniformVector( const char* _name, glm::vec4& _val )
{
	glUniform4fv( GetUniformLocation( _name ), 1, &_val[0] );
}
void Shader::SetUniformMatrix( const char* _name, glm::mat3& _val )
{
	glUniformMatrix3fv( GetUniformLocation( _name ), 1, GL_FALSE, &_val[0][0] );
}
void Shader::SetUniformMatrix( const char* _name, glm::mat4& _val )
{
	glUniformMatrix4fv( GetUniformLocation( _name ), 1, GL_FALSE, &_val[0][0] );
}

void Shader::CreateProgram( )
{
	// link programme
	glLinkProgram( handle );
	
	// verify link status
	GLint status;
	glGetProgramiv( handle, GL_LINK_STATUS, &status );

	if( status != GL_TRUE )
	{
		std::string error( "ERROR: failed to link shader programme\n" );
		int length = 200;
		//glGetShaderiv( handle, GL_INFO_LOG_LENGTH, &length );
		if( length > 0 )
		{
			// create a log of error messages
			char* errorLog = new char[ length ];
			int written = 0;
			glGetProgramInfoLog( handle, length, &written, errorLog );
			throw error + stringf( "Shader error log:\n%s\n", errorLog );
			delete[ ] errorLog;
		}
		throw error;
	}
}

void compileShader( GLuint& _shaderHandle, const char* _shaderFileName, const int& _type )
{
	// load file into string
	std::ifstream file;

	file.open( _shaderFileName );
	if( !file.is_open( ) )
		throw stringf( "ERROR creating opening shader file %s\n", _shaderFileName );

	// Get the size of the file
    file.seekg(0,std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0,std::ios::beg);

	// Use a vector as the buffer.
    std::vector< char > buffer( length );
    file.read( &buffer[ 0 ], length );

	//std::stringstream ss;
    std::string str( &buffer[ 0 ], length );

	// create shader object
	_shaderHandle = glCreateShader( _type );

	// validate creation
	if( _shaderHandle == 0 )
		throw stringf( "ERROR creating shader type %d\n", _type );

	// load source from a char array
	const char* ptr = str.c_str( ); // get character pointer from string
	int len = (int)length;
	glShaderSource( _shaderHandle, 1, &ptr, NULL );

	// compile shader
	glCompileShader( _shaderHandle );

	// Check for errors
	int result = 0;
	glGetShaderiv( _shaderHandle, GL_COMPILE_STATUS, &result );
	if( result != GL_TRUE )
	{
		std::string error = stringf( "ERROR compiling shader type %d\n", _type );
		int length = 0;
		glGetShaderiv( _shaderHandle, GL_INFO_LOG_LENGTH, &length );
		if( length > 0 )
		{
			// create a log of error messages
			char* errorLog = new char[ length ];
			int written = 0;
			glGetShaderInfoLog( _shaderHandle, length, &written, errorLog );
			throw error + stringf( "Shader error log;\n%s\n", errorLog );
			delete[ ] errorLog;
		}
		throw error;
	}
}

int Shader::GetUniformLocation( const char* _name )
{
	this->Use( );

	int loc = glGetUniformLocation( handle, _name );
	if( loc < 0 )
	{
		printf( "Warning: Error receiving variable location '%s'\n", _name );
		//throw stringf( "Error receiving variable location '%s'", _name );
	}
	return loc;
}