#include "ModelInstance.h"

#include <cstdio>

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
        (float)m_modelMatrix[0], (float)m_modelMatrix[1], (float)m_modelMatrix[2], (float)m_modelMatrix[3],
        (float)m_modelMatrix[4], (float)m_modelMatrix[5], (float)m_modelMatrix[6], (float)m_modelMatrix[7],
        (float)m_modelMatrix[8], (float)m_modelMatrix[9], (float)m_modelMatrix[10], (float)m_modelMatrix[11],
        (float)m_modelMatrix[12], (float)m_modelMatrix[13], (float)m_modelMatrix[14], (float)m_modelMatrix[15]
      );
    firsttime = false;
  }
  p_shader.UpdateUniform( m_modelMatrix );

  m_model->Render( p_shader );
}
