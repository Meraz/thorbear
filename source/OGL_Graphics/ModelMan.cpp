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
  m_models[ ENEMY2 ].Load( MODEL_DIR+"invader2/", "invader2.obj");
  m_models[ BALL ].Load( MODEL_DIR+"cube/", "cube.obj");
  m_models[ PADDLE ].Load( MODEL_DIR+"cube/", "cube.obj");
  m_models[ ADDLIFEPOWERUP ].Load( MODEL_DIR+"AddLifePowerup/", "AddLifePowerup.obj");
  m_models[ ADDBALLPOWERUP ].Load( MODEL_DIR+"AddBallPowerup/", "AddBallPowerup.obj");
  m_models[ LARGERPADDLEPOWERUP ].Load( MODEL_DIR+"LargerPaddlePowerup/", "LargerPaddlePowerup.obj");
  m_models[ SMALLERPADDLEPOWERUP ].Load( MODEL_DIR+"SmallerPaddlePowerup/", "SmallerPaddlePowerup.obj");
  m_models[ LEVEL ].Load( MODEL_DIR+"levelBackground/", "background.obj");
  m_models[ MAINMENU ].Load( MODEL_DIR+"mainmenu_background/", "mainmenu.obj");
  
  m_models[ START ].Load( MODEL_DIR+"ButtonStart/", "ButtonStart.obj");
  m_models[ CAMPAIGN ].Load( MODEL_DIR+"ButtonCampaign/", "ButtonCampaign.obj");
  m_models[ SURVIVAL ].Load( MODEL_DIR+"ButtonSurvival/", "ButtonSurvival.obj");
  m_models[ CAMPAIGNHS ].Load( MODEL_DIR+"ButtonCampaignHS/", "ButtonCampaignHS.obj");
  m_models[ SURVIVALHS ].Load( MODEL_DIR+"ButtonSurvivalHS/", "ButtonSurvivalHS.obj");
  m_models[ EXIT ].Load( MODEL_DIR+"ButtonExit/", "ButtonExit.obj");
  m_models[ ARROWUP ].Load( MODEL_DIR+"ButtonArrowUp/", "ButtonArrowUp.obj");
  m_models[ ARROWDOWN ].Load( MODEL_DIR+"ButtonArrowDown/", "ButtonArrowDown.obj");
  m_models[ SAVE ].Load( MODEL_DIR+"ButtonSave/", "ButtonSave.obj");
  m_models[ RETURN ].Load( MODEL_DIR+"ButtonReturn/", "ButtonReturn.obj");
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
