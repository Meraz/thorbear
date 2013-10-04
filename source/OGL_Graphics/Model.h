#ifndef MODEL_H
#define MODEL_H

#include "Material.h"

#include <string>

#define TEXTURE_EXT ".tga"

class Model
{
public:
	Model();
	~Model();
  
	bool Load( std::string p_dir, std::string p_fileName );
  
  void Render( Shader &p_shader, glm::vec3 p_tint );
  
  int m_vertexCount;
  
  Material* m_mtl;
  
	GLuint m_handleVAO;
	GLuint m_handleVBO;
  
};

#endif
