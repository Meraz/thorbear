#include "ModelInstance.h"

#include <cstdio>

ModelInstance::ModelInstance( Model* p_model, glm::mat4 p_modelMatrix )
{
  m_model = p_model;
  m_modelMatrix = p_modelMatrix;
  m_tint = glm::vec3(1.f);
}

ModelInstance::~ModelInstance()
{
}

void ModelInstance::Render( Shader& p_shader )
{
  p_shader.UpdateUniform( m_modelMatrix );

  m_model->Render( p_shader, m_tint );
}

void ModelInstance::SetTint( Vect3 p_color )
{
  m_tint.r = p_color.r;
  m_tint.g = p_color.g;
  m_tint.b = p_color.b;
}
