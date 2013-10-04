#include "ModelMan.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

ModelMan::ModelMan( )
{
}

ModelMan::~ModelMan( )
{
}

void ModelMan::LoadModels( )
{
  m_models[ ENEMY1 ].Load( MODEL_DIR+"invader/", "invader.obj");
  m_models[ ENEMY2 ].Load( MODEL_DIR+"invader/", "invader.obj");
  m_models[ BALL ].Load( MODEL_DIR+"cube/", "cube.obj");
  m_models[ PADDLE ].Load( MODEL_DIR+"cube/", "cube.obj");
}

ModelInstance* ModelMan::CreateInstance( BoundingBox p_boundingBox, TextureType p_textureType )
{
  if( p_boundingBox.Depth == -1 )
    p_boundingBox.Depth = 1;
    
  glm::mat4 l_modelMatrix = glm::translate(
      p_boundingBox.PosX + p_boundingBox.Width*0.5f,
      p_boundingBox.PosY + p_boundingBox.Height*0.5f,
      p_boundingBox.PosZ
    ) * glm::scale(glm::mat4(1.f), glm::vec3(p_boundingBox.Width, p_boundingBox.Height, p_boundingBox.Depth));
    
  return new ModelInstance( &m_models[ p_textureType ], l_modelMatrix );
}