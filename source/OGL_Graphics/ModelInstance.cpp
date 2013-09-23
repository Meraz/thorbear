#include "ModelInstance.h"

ModelInstance::ModelInstance( Model* p_model, glm::mat4 p_modelMatrix )
{
  m_model = p_model;
  m_modelMatrix = p_modelMatrix;
}

ModelInstance::~ModelInstance()
{
}

bool firsttime = true;
void ModelInstance::Render( Shader& p_shader )
{
  if( firsttime )
  {
    printf( "Drawing the model instance. Model matrix:\n");
    printf( "%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",
        m_modelMatrix[0], m_modelMatrix[1], m_modelMatrix[2], m_modelMatrix[3],
        m_modelMatrix[4], m_modelMatrix[5], m_modelMatrix[6], m_modelMatrix[7],
        m_modelMatrix[8], m_modelMatrix[9], m_modelMatrix[10], m_modelMatrix[11],
        m_modelMatrix[12], m_modelMatrix[13], m_modelMatrix[14], m_modelMatrix[15]
      );
    firsttime = false;
  }
  p_shader.UpdateUniform( m_modelMatrix );

  m_model->Render( p_shader );
}
