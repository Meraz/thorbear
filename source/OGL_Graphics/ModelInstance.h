#ifndef MODELINSTANCE_H
#define MODELINSTANCE_H

#include "Model.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "../Vect3.h"

class ModelInstance
{
public:
	ModelInstance( Model* p_model, glm::mat4 p_modelMatrix );
	~ModelInstance();
  
  void Render( Shader& p_shader );
  void SetTint( Vect3 p_color );
  
private:
  Model* m_model;
  glm::mat4 m_modelMatrix;
  
  glm::vec3 m_tint;
  
};

#endif