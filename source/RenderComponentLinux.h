#ifndef RENDERCOMPONENTLINUX_H
#define RENDERCOMPONENTLINUX_H

#include "RenderComponentInterface.h"
#include "OGL_Graphics/Shader.h"
#include "OGL_Graphics/ModelMan.h"
#include "OGL_Graphics/FontMan.h"

#include <GL/glew.h> // always include GLEW before including freeGLUT so that you get the latest opengl headers and not the default ones
#include <GL/glfw.h>
#include <string>
#include <vector>

class RenderComponentLinux : public RenderComponentInterface
{
    
public:
	RenderComponentLinux();
	~RenderComponentLinux();
  
  // Initialize the Win/Lin window and set up OpenGL 4
  bool Init();
  // Sets the hints for window, such as required version of the OpenGL
  void SetHints();

  // Instant render functions
	void RenderObject( BoundingBox p_boundingBox, TextureType p_textureType, Vect3 p_color = Vect3(1.0f, 1.0f, 1.0f) );
	void RenderText( std::string p_text, float p_size, float p_posX, float p_posY, unsigned int p_color );
	void RenderBackground(TextureType p_textureType);
  // Managed render functions
	void CreateSplashText(wstring p_text, float p_size, float p_posX, float p_posY, float p_travelTime, float p_stillTime );
	void CreateParticleEmitter( ParticleEmitterDesc p_particleDesc );
	// Update managed render objects, swap buffer
	void Update( float p_deltatime );
	
	// Convert coordinates to screen space
	BoundingBox ConvertIntoScreenSpace(BoundingBox p_boundingBox, TextureType p_textureType);
	
	// Show or hide mouse cursor
	void SetShowCursor(bool p_showCursor);

  // Update viewport on window resize
  void UpdateViewportSize( int p_width, int p_height );
  
  // Return the error message
  std::string GetErrorMessage( );
  
private:
  std::string m_errorMessage;
  
  Shader m_genericShader;
  
  ModelMan m_modelManager;
  FontMan m_fontManager;
  
  bool m_renderfirsttime;
  
  std::vector< ModelInstance* > m_objectList;
  
  // Set the error message and return false to be returned further on for the error management
  bool SetError( std::string p_errorMessage );
};

#endif
