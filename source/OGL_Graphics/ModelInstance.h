#ifndef MODELINSTANCE_H
#define MODELINSTANCE_H

#include "Model.h"
#include "Shader.h"
#include "glm/glm.hpp"

class ModelInstance
{
public:
	ModelInstance( Model* p_model, glm::mat4 p_modelMatrix );
	~ModelInstance();
  
  void Render( Shader& p_shader );
  
private:
  Model* m_model;
  glm::mat4 m_modelMatrix;
  
};

#endif