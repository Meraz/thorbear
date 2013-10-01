#ifndef RENDERCOMPONENTLINUX_H
#define RENDERCOMPONENTLINUX_H

#include "RenderComponentInterface.h"
#include "OGL_Graphics/Shader.h"
#include "OGL_Graphics/ModelMan.h"

#include <GL/glew.h> // always include GLEW before including freeGLUT so that you get the latest opengl headers and not the default ones
#include <GL/glfw.h>
#include <string>
#include <vector>

#define SHADER_DIRECTORY std::string("effect/")

class RenderComponentLinux : public RenderComponentInterface
{
    
public:
	RenderComponentLinux();
	~RenderComponentLinux();
  
  // Initialize the Win/Lin window and set up OpenGL 4
  bool Init();
  // Sets the hints for window, such as required version of the OpenGL
  void SetHints();

	void RenderObject(BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color);
	void RenderParticleSystem(ParticleSystem p_particleSystem);
	void Render();
  
  void UpdateViewportSize( int p_width, int p_height );
  
  // Return the error message
  std::string GetErrorMessage( );
  
private:
  std::string m_errorMessage;
  
  Shader m_genericShader;
  
  ModelMan m_modelManager;
  std::vector< ModelInstance* > m_objectList;
  
  // Set the error message and return false to be returned further on for the error management
  bool SetError( std::string p_errorMessage );
};

#endif