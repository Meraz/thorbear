#include "ModelMan.h"

#include "glm/glm.hpp"

ModelMan::ModelMan( )
{
}

ModelMan::~ModelMan( )
{
}

void LoadModels( )
{
  model[ ENEMY1 ].Load( MODEL_DIR, "Enemy1.obj");
  model[ ENEMY2 ].Load( MODEL_DIR, "Enemy2.obj");
  model[ BALL ].Load( MODEL_DIR, "Ball.obj");
  model[ PADDLE ].Load( MODEL_DIR, "Paddle.obj");
}

Model* CreateInstance( BoundingBox p_boundingBox, TextureType p_textureType )
{
  glm::mat4 l_modelMatrix = glm::translate(
      p_boundingBox.farTopLeftX + width/2.f,
      p_boundingBox.farTopLeftY + height/2.f,
      0
    );
    
  return new ModelInstance( model[ p_textureType ], l_modelMatrix );
}