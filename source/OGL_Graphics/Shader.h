#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include "glm/glm.hpp"

#include "Camera.h"

class Shader
{
	enum ShaderType { VertShader, TConShader, TEvalShader, GeomShader, FragShader, COUNT };

public:
	void Init( const char* _vertFileName, const char* _fragFileName, const char* _gsFileName = NULL, const char* _tessConFileName = NULL, const char* _tessEvalFileName = NULL );
	
	void Build( );
	void Use( );

	void BindAttribLocation( GLuint location, const char* name );
	void BindFragDataLocation( GLuint location, const char* name );

	void SetUniformInt( const char* _name, int _val );
	void SetUniformFloat( const char* _name, float _val );
	void SetUniformVector( const char* _name, glm::vec3 _val );
	void SetUniformVector( const char* _name, glm::vec4 _val );
	void SetUniformMatrix( const char* _name, glm::mat3 _val );
	void SetUniformMatrix( const char* _name, glm::mat4 _val );
	
  
	void UpdateUniform( );
	void SetActiveCamera( Camera& _cam );

private:
	int handle;
	GLuint subhandles[COUNT];
  
	Camera* m_activeCamera;
	glm::mat4 m_modelMatrix;
  
	void CreateProgram( );
	int GetUniformLocation( const char* _name );
};

#endif