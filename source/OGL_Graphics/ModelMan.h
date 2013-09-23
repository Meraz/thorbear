#ifndef MODELMAN_H
#define MODELMAN_H

#include "ModelInstance.h"
#include "RenderComponentInterface.h"

#define MODEL_DIR "resources/models/"

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