#ifndef MODELMAN_H
#define MODELMAN_H

#include "ModelInstance.h"
#include "RenderComponentInterface.h"

#include <string>

#define MODEL_DIR std::string("objects/")

class ModelMan
{
public:
	ModelMan( );
	~ModelMan( );
  
  void LoadModels( );
  
  ModelInstance* CreateInstance( BoundingBox p_boundingBox, TextureType p_textureType );
  
private:
  Model m_models[4];

};

#endif