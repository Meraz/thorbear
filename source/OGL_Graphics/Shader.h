#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include "glm/glm.hpp"
#include <string>

#define SHADER_DIRECTORY std::string("effect/")

#include "Camera.h"

class Shader
{
	enum ShaderType { VertShader, TConShader, TEvalShader, GeomShader, FragShader, COUNT };

public:
  Shader();
  ~Shader();
  
  void Init( std::string p_vertFileName, std::string p_fragFileName );
	void Init( const char* p_vertFileName, const char* p_fragFileName, const char* p_gsFileName = NULL, const char* p_tessConFileName = NULL, const char* p_tessEvalFileName = NULL );
	
	void Build( );
	void Use( );

	void BindAttribLocation( GLuint p_location, const char* p_name );
	void BindFragDataLocation( GLuint p_location, const char* p_name );

	void SetUniformInt( const char* p_name, int p_val );
	void SetUniformFloat( const char* p_name, float p_val );
	void SetUniformVector( const char* p_name, glm::vec3 p_val );
	void SetUniformVector( const char* p_name, glm::vec4 p_val );
	void SetUniformMatrix( const char* p_name, glm::mat3 p_val );
	void SetUniformMatrix( const char* p_name, glm::mat4 p_val );
	
  
	void UpdateUniform( glm::mat4 p_modelMatrix );
	void SetActiveCamera( Camera& p_cam );
  
	Camera* m_activeCamera;

  static Shader* m_activeShader;
private:
	int m_handle;
	GLuint m_subhandles[COUNT];
  
	void CreateProgram( );
	int GetUniformLocation( const char* p_name );
};

#endif
