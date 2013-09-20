#include "ModelInstance.h"

ModelInstance::ModelInstance( Model* p_model, glm::mat4 p_modelMatrix )
{
  m_model = p_model;
  m_modelMatrix = p_modelMatrix;
}

ModelInstance::~ModelInstance()
{
}

void ModelInstance::Render( Shader& p_shader )
{
  p_shader.SetUniformMatrix( "modelMatrix", m_modelMatrix );
  p_shader.UpdateUniform( );

  m_model->Render( p_shader );
}
