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
        (float)m_modelMatrix[0][0], (float)m_modelMatrix[0][1], (float)m_modelMatrix[0][2], (float)m_modelMatrix[0][3],
        (float)m_modelMatrix[1][0], (float)m_modelMatrix[1][1], (float)m_modelMatrix[1][2], (float)m_modelMatrix[1][3],
        (float)m_modelMatrix[2][0], (float)m_modelMatrix[2][1], (float)m_modelMatrix[2][2], (float)m_modelMatrix[2][3],
        (float)m_modelMatrix[3][0], (float)m_modelMatrix[3][1], (float)m_modelMatrix[3][2], (float)m_modelMatrix[3][3]
      );
    firsttime = false;
  }
  p_shader.UpdateUniform( m_modelMatrix );
  p_shader.SetUniformVector( "intensityDiffuse", m_tint );

  m_model->Render( p_shader );
}

void ModelInstance::SetTint( Vect3 p_color )
{
  m_tint.r = p_color.r;
  m_tint.g = p_color.g;
  m_tint.b = p_color.b;
}
