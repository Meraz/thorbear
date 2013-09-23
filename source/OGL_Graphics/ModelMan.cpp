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
  m_models[ ENEMY1 ].Load( MODEL_DIR, "Enemy1.obj");
  m_models[ ENEMY2 ].Load( MODEL_DIR, "invader.obj");
  m_models[ BALL ].Load( MODEL_DIR, "Ball.obj");
  m_models[ PADDLE ].Load( MODEL_DIR, "Paddle.obj");
}

ModelInstance* ModelMan::CreateInstance( BoundingBox p_boundingBox, TextureType p_textureType )
{
  glm::mat4 l_modelMatrix = glm::translate(
      p_boundingBox.PosX + p_boundingBox.Width/2.f,
      p_boundingBox.PosY + p_boundingBox.Height/2.f,
      0.f
    );
    
  return new ModelInstance( &m_models[ p_textureType ], l_modelMatrix );
}