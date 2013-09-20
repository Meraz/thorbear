#ifndef MODEL_H
#define MODEL_H

#include "Material.h"

#include <string>

class Model
{
public:
	Model();
	~Model();
  
	bool Load( std::string p_dir, std::string p_fileName );
  
  void Render( Shader &p_shader );
  
  int m_vertexCount;
  
private:
  Material* m_mtl;

	GLuint m_handleVAO;
	GLuint m_handleVBO;
  
};

#endif
